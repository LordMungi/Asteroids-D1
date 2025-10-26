#include "game.h"

#include <iostream>
#include <cmath>
#include <ctime>

#include "config.h"
#include "ship.h"
#include "asteroid.h"
#include "collision.h"
#include "random.h"

namespace game
{
	enum class State
	{
		Playing,
		Won,
		Lost,
		Paused
	};
	
	State gamestate;
	ship::Ship ship;
	asteroid::Asteroid asteroids[asteroid::maxAsteroids];
	screen::Type nextScreen;

	static void updateShip();
	static void updateBullets();
	static void updateAsteroids();
	static void updateGameState();

	static int asteroidsLeft();
	static void divideAsteroid(asteroid::Asteroid& asteroid);
	static float getRotation(Vector2 direction);
	static Vector2 getAsteroidStartPos();
	static void returnFromOtherSide(shape::Circle& circle);

	void init()
	{
		ship = ship::init();

		for (int i = 0; i < asteroid::maxAsteroids; i++)
		{
			asteroids[i] = asteroid::init();
		}

		for (int i = 0; i < 10; i++)
		{
			asteroid::create(asteroids[i], getAsteroidStartPos());
		}

		nextScreen = screen::Type::Game;
	}

	screen::Type update()
	{
		nextScreen = screen::Type::Game;

		if (gamestate != State::Paused)
		{
			updateShip();
			updateBullets();
			updateAsteroids();
		}
		updateGameState();

		return nextScreen;
	}

	void draw()
	{
		BeginDrawing();
		ClearBackground(BLACK);

		for (int i = 0; i < bullet::maxBullets; i++)
		{
			if (ship.bullets[i].isActive)
				bullet::draw(ship.bullets[i]);
		}
		for (int i = 0; i < asteroid::maxAsteroids; i++)
		{
			if (asteroids[i].isActive)
				asteroid::draw(asteroids[i]);
		}
		ship::draw(ship);

		EndDrawing();
	}

	void unload()
	{
		ship::unload(ship);
	}

	static void updateShip()
	{
		ship.direction = ship::getDirection(ship);

		if (ship.state != ship::State::Dead)
		{
			ship::move(ship);
			returnFromOtherSide(ship.shape);

			ship.rotation = getRotation(ship.direction);

			if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
				ship::accelerate(ship);

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				ship::shoot(ship);
			}	
		}
		else if (GetTime() - ship.deathTimer > ship::deathCooldown && ship.lives >= 0)
			ship::spawn(ship);
	}

	static void updateBullets()
	{
		for (int i = 0; i < bullet::maxBullets; i++)
		{
			if (ship.bullets[i].isActive)
			{
				bullet::move(ship.bullets[i]);
				returnFromOtherSide(ship.bullets[i].shape);

				for (int j = 0; j < asteroid::maxAsteroids; j++)
				{
					if (asteroids[j].isActive)
					{
						if (coll::circleCircle(ship.bullets[i].shape, asteroids[j].shape))
						{
							bullet::destroy(ship.bullets[i]);
							if (asteroids[j].shape.radius != static_cast<int>(asteroid::Size::Small))
								divideAsteroid(asteroids[j]);
							else
								asteroid::destroy(asteroids[j]);
						}
					}
				}

				if (GetTime() - ship.bullets[i].activeTimer > bullet::activeCooldown)
					bullet::destroy(ship.bullets[i]);
			}
		}
	}

	static void updateAsteroids()
	{
		for (int i = 0; i < asteroid::maxAsteroids; i++)
		{
			if (asteroids[i].isActive)
			{
				asteroid::move(asteroids[i]);
				returnFromOtherSide(asteroids[i].shape);

				if (coll::circleCircle(ship.shape, asteroids[i].shape) &&
					GetTime() - ship.immunityTimer > ship::immunityCooldown &&
					ship.state != ship::State::Dead)
				{
					ship::die(ship);
					asteroid::destroy(asteroids[i]);
				}
			}
		}
	}

	static void updateGameState()
	{
		if (asteroidsLeft() == 0)
			gamestate = State::Won;
		else if (ship.lives < 0)
			gamestate = State::Lost;
		else
			gamestate = State::Playing;
	}

	static int asteroidsLeft()
	{
		int count = 0;
		for (int i = 0; i < asteroid::maxAsteroids; i++)
		{
			if (asteroids[i].isActive)
				count++;
		}
		return count;
	}

	static void divideAsteroid(asteroid::Asteroid& asteroid)
	{
		const int maxNewAsteroids = 3;
		int asteroidsCreated = 0;

		asteroid::Size newSize = asteroid::Size::Small;

		switch (static_cast<int>(asteroid.shape.radius))
		{
		case static_cast<int>(asteroid::Size::Medium):
			newSize = asteroid::Size::Small;
			break;
		case static_cast<int>(asteroid::Size::Large):
			newSize = asteroid::Size::Medium;
			break;
		}

		for (int i = 0; i < asteroid::maxAsteroids; i++)
		{
			if (!asteroids[i].isActive && asteroidsCreated < maxNewAsteroids)
			{
				asteroid::create(asteroids[i], asteroid.shape.position, newSize);
				asteroidsCreated++;
			}
		}

		asteroid::destroy(asteroid);
	}

	float getRotation(Vector2 direction)
	{
		float rotation = atan(direction.y / direction.x) * (180 / PI);

		if (direction.x < 0) rotation += 180;
		else if (direction.y < 0) rotation += 360;

		return rotation;
	}
		
	static Vector2 getAsteroidStartPos()
	{
		shape::Circle newAsteroid;
		newAsteroid.radius = static_cast<float>(asteroid::Size::Large);
		bool isColliding;

		do
		{
			isColliding = false;

			newAsteroid.position.x = static_cast<float>(random::intRange(0, static_cast<int>(config::gamespace.x)));
			newAsteroid.position.y = static_cast<float>(random::intRange(0, static_cast<int>(config::gamespace.y)));
			
			if (coll::circleCircle(newAsteroid, ship.shape))
				isColliding = true;
			
			
			for (int i = 0; i < asteroid::maxAsteroids; i++)
			{
				if (asteroids[i].isActive && coll::circleCircle(newAsteroid, asteroids[i].shape))
					isColliding = true;
			}
			
		} while (isColliding);
		return newAsteroid.position;
	}	
	
	static void returnFromOtherSide(shape::Circle& circle)
	{
		if (circle.position.x - circle.radius > config::gamespace.x)
			circle.position.x = 0 - circle.radius;
		if (circle.position.y - circle.radius > config::gamespace.y)
			circle.position.y = 0 - circle.radius;
		if (circle.position.x + circle.radius < 0)
			circle.position.x = config::gamespace.x + circle.radius;
		if (circle.position.y + circle.radius < 0)
			circle.position.y = config::gamespace.y + circle.radius;
	}

}