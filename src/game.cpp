#include "game.h"

#include <iostream>
#include <cmath>
#include <ctime>

#include "config.h"
#include "ship.h"
#include "asteroid.h"
#include "collision.h"
#include "random.h"
#include "hud.h"
#include "background.h"
#include "math.h"


namespace game
{	
	Stats stats;
	ship::Ship ship;
	asteroid::Asteroid asteroids[asteroid::maxAsteroids];
	screen::Type nextScreen;

	static void updateShip();
	static void updateBullets();
	static void updateAsteroids();
	static void updateGameState();

	background::Background bg;

	static int asteroidsLeft();
	static void divideAsteroid(asteroid::Asteroid& asteroid);
	static Vector2 getAsteroidStartPos();
	static void returnFromOtherSide(shape::Circle& circle);

	void init()
	{
		ship = ship::init();

		asteroid::loadSprites();
		for (int i = 0; i < asteroid::maxAsteroids; i++)
		{
			asteroids[i] = asteroid::init();
		}
		bg.picture = LoadTexture("resources/bg/game.jpg");
		bg.shape.position = { config::gamespace.x / 2, config::gamespace.y / 2 };
		bg.shape.size = { (21 * config::gamespace.y / 9), config::gamespace.y };


		for (int i = 0; i < 10; i++)
		{
			asteroid::create(asteroids[i], getAsteroidStartPos());
		}


		nextScreen = screen::Type::Game;
	}

	screen::Type update()
	{
		nextScreen = screen::Type::Game;

		if (stats.gamestate != State::Paused)
		{
			render::updateFrame();

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

		render::sprite(bg.picture, bg.shape, 0);
		for (int i = 0; i < bullet::maxBullets; i++)
		{
			if (ship.bullets[i].isActive)
				bullet::draw(ship.bullets[i]);
		}
		for (int i = 0; i < asteroid::maxAsteroids; i++)
		{
			asteroid::draw(asteroids[i]);
		}
		ship::draw(ship);
		hud::draw(stats);

		EndDrawing();
	}

	void unload()
	{
		ship::unload(ship);
		asteroid::unloadSprites();
	}

	static void updateShip()
	{
		ship.direction = math::getDirection(ship.collision.position, math::getGamespacePointFromRes(GetMousePosition()));

		if (ship.state != ship::State::Dead)
		{
			ship::move(ship);
			returnFromOtherSide(ship.collision);

			if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
				ship::accelerate(ship);

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				ship::shoot(ship);
			}	
		}
		else if (GetTime() - ship.deathTimer > ship::deathCooldown && ship.lives >= 0)
			ship::spawn(ship);

		stats.lives = ship.lives;
	}

	static void updateBullets()
	{
		for (int i = 0; i < bullet::maxBullets; i++)
		{
			if (ship.bullets[i].isActive)
			{
				bullet::move(ship.bullets[i]);
				returnFromOtherSide(ship.bullets[i].collision);

				for (int j = 0; j < asteroid::maxAsteroids; j++)
				{
					if (asteroids[j].state == asteroid::State::Active)
					{
						if (coll::circleCircle(ship.bullets[i].collision, asteroids[j].collision))
						{
							bullet::destroy(ship.bullets[i]);
							if (asteroids[j].collision.radius != static_cast<int>(asteroid::Size::Small))
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
			if (asteroids[i].state == asteroid::State::Active)
			{
				asteroid::move(asteroids[i]);
				returnFromOtherSide(asteroids[i].collision);

				if (coll::circleCircle(ship.collision, asteroids[i].collision) &&
					GetTime() - ship.immunityTimer > ship::immunityCooldown &&
					ship.state != ship::State::Dead)
				{
					ship::die(ship);
					asteroid::destroy(asteroids[i]);
				}
			}

			if (asteroids[i].state == asteroid::State::Destroying && GetTime() - asteroids[i].destroyTimer > asteroid::destroyTime)
				asteroid::disable(asteroids[i]);
		}
	}

	static void updateGameState()
	{
		if (asteroidsLeft() == 0)
			stats.gamestate = State::Won;
		else if (ship.lives < 0)
			stats.gamestate = State::Lost;
		else
			stats.gamestate = State::Playing;
	}

	static int asteroidsLeft()
	{
		int count = 0;
		for (int i = 0; i < asteroid::maxAsteroids; i++)
		{
			if (asteroids[i].state == asteroid::State::Active)
				count++;
		}
		return count;
	}

	static void divideAsteroid(asteroid::Asteroid& asteroid)
	{
		const int maxNewAsteroids = 3;
		int asteroidsCreated = 0;

		asteroid::Size newSize = asteroid::Size::Small;

		switch (static_cast<int>(asteroid.collision.radius))
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
			if (asteroids[i].state == asteroid::State::Inactive && asteroidsCreated < maxNewAsteroids)
			{
				asteroid::create(asteroids[i], asteroid.collision.position, newSize);
				asteroidsCreated++;
			}
		}

		asteroid::destroy(asteroid);
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
			
			if (coll::circleCircle(newAsteroid, ship.collision))
				isColliding = true;
			
			
			for (int i = 0; i < asteroid::maxAsteroids; i++)
			{
				if (asteroids[i].state == asteroid::State::Active && coll::circleCircle(newAsteroid, asteroids[i].collision))
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