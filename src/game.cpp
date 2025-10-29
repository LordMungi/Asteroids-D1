#include "game.h"

#include <iostream>
#include <cmath>
#include <ctime>

#include "config.h"
#include "ship.h"
#include "asteroid.h"
#include "seal.h"
#include "collision.h"
#include "random.h"
#include "hud.h"
#include "background.h"
#include "math.h"


namespace game
{	
	double sealTimer;
	double sealCooldown = 15;
	bool hasBeenSeal;
	const int asteroidCount = 10;

	Stats stats;
	ship::Ship ship;
	seal::Seal seal;
	asteroid::Asteroid asteroids[asteroid::maxAsteroids];
	screen::Type nextScreen;

	static void updateShip();
	static void updateBoomerang();
	static void updateBullets();
	static void updateAsteroids();
	static void updateSeal();
	static void updateGameState();

	background::Background bg;

	static void resetGame();
	static void createAsteroids();
	static int asteroidsLeft();
	static void divideAsteroid(asteroid::Asteroid& asteroid);
	static Vector2 getAsteroidStartPos();
	static void returnFromOtherSide(shape::Circle& circle);

	void init()
	{
		ship = ship::init();

		asteroid::loadSprites();

		seal = seal::init();

		for (int i = 0; i < asteroid::maxAsteroids; i++)
		{
			asteroids[i] = asteroid::init();
		}
		bg.picture = LoadTexture("resources/bg/game.jpg");
		bg.shape.position = { config::gamespace.x / 2, config::gamespace.y / 2 };
		bg.shape.size = { (21 * config::gamespace.y / 9), config::gamespace.y };


		createAsteroids();

		sealTimer = GetTime();
		hasBeenSeal = false;
		nextScreen = screen::Type::Game;
	}

	screen::Type update()
	{
		nextScreen = screen::Type::Game;

		if (stats.gamestate != State::Paused)
		{
			render::updateFrame();

			updateShip();
			updateBoomerang();
			updateBullets();
			updateAsteroids();
			updateSeal();
		}
		updateGameState();

		return nextScreen;
	}

	void draw()
	{
		BeginDrawing();
		ClearBackground(BLACK);

		render::sprite(bg.picture, bg.shape, 0);

		ship::draw(ship);

		seal::draw(seal);
		for (int i = 0; i < bullet::maxBullets; i++)
		{
			if (ship.bullets[i].isActive)
				bullet::draw(ship.bullets[i]);
		}
		for (int i = 0; i < asteroid::maxAsteroids; i++)
		{
			asteroid::draw(asteroids[i]);
		}
		boomerang::draw(ship.boomerang);
		hud::draw(stats);

		EndDrawing();
	}

	void unload()
	{
		ship::unload(ship);
		asteroid::unloadSprites();
		seal::unload(seal);
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

			if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
				ship::throwBoomerang(ship);

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				ship::shoot(ship);
		}
		else if (GetTime() - ship.deathTimer > ship::deathCooldown && ship.lives >= 0)
			ship::spawn(ship);

		stats.lives = ship.lives;
	}

	static void updateBoomerang()
	{
		boomerang::move(ship.boomerang, ship.collision.position);
		returnFromOtherSide(ship.boomerang.collision);

		if (coll::circleCircle(ship.boomerang.collision, ship.collision) && (ship.boomerang.state == boomerang::State::Stationary || ship.boomerang.state == boomerang::State::Returning))
			ship.boomerang.state = boomerang::State::Carried;

		if (ship.boomerang.state == boomerang::State::Flying || ship.boomerang.state == boomerang::State::Returning)
		{
			for (int i = 0; i < asteroid::maxAsteroids; i++)
			{
				if (asteroids[i].state == asteroid::State::Active)
				{
					if (coll::circleCircle(ship.boomerang.collision, asteroids[i].collision))
					{
						if (asteroids[i].collision.radius != static_cast<int>(asteroid::Size::Small))
							divideAsteroid(asteroids[i]);
						else
							asteroid::destroy(asteroids[i]);
					}
				}
			}
		}

		if (coll::circleCircle(ship.boomerang.collision, seal.collision))
			seal::damage(seal);
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

							if(random::intRange(1, 100) < 10 && ship.boomerang.state == boomerang::State::Inactive)
								boomerang::create(ship.boomerang, asteroids[j].collision.position);

							if (asteroids[j].collision.radius != static_cast<int>(asteroid::Size::Small))
								divideAsteroid(asteroids[j]);
							else
								asteroid::destroy(asteroids[j]);
						}
					}
				}

				if (coll::circleCircle(ship.bullets[i].collision, seal.collision))
				{
					bullet::destroy(ship.bullets[i]);
					seal::damage(seal);
				}

				if (GetTime() - ship.bullets[i].activeTimer > bullet::activeCooldown)
					bullet::destroy(ship.bullets[i]);
			}
		}
	}

	static void updateSeal()
	{
		if (!seal.isActive && GetTime() - sealTimer > sealCooldown && !hasBeenSeal)
		{
			hasBeenSeal = true;
			sealTimer = GetTime();
			seal::create(seal);
		}

		if (ship.state != ship::State::Dead && seal.isActive)
		{
			seal::move(seal, math::getDirection(seal.collision.position, ship.collision.position));
			if (coll::circleCircle(ship.collision, seal.collision) &&
				GetTime() - ship.immunityTimer > ship::immunityCooldown)
				ship::die(ship);
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
			resetGame();
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
		const int maxNewAsteroids = 2;
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

	static void resetGame()
	{
		sealTimer = GetTime();
		hasBeenSeal = false;
		ship.immunityTimer = GetTime();
		createAsteroids();
	}

	static void createAsteroids()
	{
		for (int i = 0; i < asteroidCount; i++)
		{
			asteroid::create(asteroids[i], getAsteroidStartPos());
		}
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