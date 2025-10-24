#include "game.h"

#include <iostream>
#include <cmath>
#include <ctime>

#include "config.h"
#include "ship.h"
#include "bullet.h"
#include "asteroid.h"
#include "collision.h"

namespace game
{
	struct Game
	{
		ship::Ship ship;
		bullet::Bullet bullets[bullet::maxBullets];
		asteroid::Asteroid asteroids[asteroid::maxAsteroids];
	};

	static Game init();
	static void update(Game& game);
	static void draw(Game game);
	static void unload(Game& game);

	static Vector2 getShipDirection(Vector2 position);
	static float getShipRotation(Vector2 direction);

	void run()
	{
		render::startWindow();

		Game game = init();

		while (!WindowShouldClose())
		{
			update(game);
			draw(game);
		}

		unload(game);
		render::closeWindow();
	}

	static Game init()
	{
		srand(static_cast<int>(time(0)));

		Game game;
		game.ship = ship::init();

		for (int i = 0; i < bullet::maxBullets; i++)
		{
			game.bullets[i] = bullet::init();
		}

		for (int i = 0; i < asteroid::maxAsteroids; i++)
		{
			game.asteroids[i] = asteroid::init();
		}

		for (int i = 0; i < 10; i++)
		{
			asteroid::create(game.asteroids[i], { 50, 50 });
		}

		return game;
	}

	static void update(Game& game)
	{
		Vector2 direction = getShipDirection(game.ship.shape.position);

		game.ship.rotation = getShipRotation(direction);
		
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
			ship::accelerate(game.ship, direction);

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			for (int i = 0; i < bullet::maxBullets; i++)
			{
				if (!game.bullets[i].isActive)
				{
					bullet::create(game.bullets[i], game.ship.shape.position, direction);
					break;
				}
			}
		}

		ship::move(game.ship);

		for (int i = 0; i < bullet::maxBullets; i++)
		{
			if (game.bullets[i].isActive)
			{
				bullet::move(game.bullets[i]);
				for (int j = 0; j < asteroid::maxAsteroids; j++)
				{
					if (game.asteroids[j].isActive)
					{
						if (coll::circleCircle(game.bullets[i].shape, game.asteroids[j].shape))
						{
							bullet::destroy(game.bullets[i]);
							asteroid::destroy(game.asteroids[j]);
						}
					}
				}

			}


		}

		for (int i = 0; i < asteroid::maxAsteroids; i++)
		{
			if (game.asteroids[i].isActive)
			{
				asteroid::move(game.asteroids[i]);
				if (coll::circleCircle(game.ship.shape, game.asteroids[i].shape))
				coll::correctCircleCircle(game.ship.shape, game.asteroids[i].shape);
			}
		}

		// Return from the other side if leaving screen
		if (game.ship.shape.position.x - game.ship.shape.radius / 2 > config::gamespace.x) 
			game.ship.shape.position.x = 0 - game.ship.shape.radius /2;
		if (game.ship.shape.position.y - game.ship.shape.radius / 2 > config::gamespace.y)
			game.ship.shape.position.y = 0 - game.ship.shape.radius / 2;
		if (game.ship.shape.position.x + game.ship.shape.radius / 2 < 0)
			game.ship.shape.position.x = config::gamespace.x + game.ship.shape.radius / 2;
		if (game.ship.shape.position.y + game.ship.shape.radius / 2 < 0)
			game.ship.shape.position.y = config::gamespace.y + game.ship.shape.radius / 2;
	}

	static void draw(Game game)
	{
		BeginDrawing();
		ClearBackground(BLACK);

		for (int i = 0; i < bullet::maxBullets; i++)
		{
			if (game.bullets[i].isActive)
				bullet::draw(game.bullets[i]);
		}
		for (int i = 0; i < asteroid::maxAsteroids; i++)
		{
			if (game.asteroids[i].isActive)
				asteroid::draw(game.asteroids[i]);
		}
		ship::draw(game.ship);

		EndDrawing();
	}

	static void unload(Game& game)
	{
		ship::unload(game.ship);
	}

	static Vector2 getShipDirection(Vector2 position)
	{
		Vector2 direction;

		Vector2 mousePosition = GetMousePosition();
		position = render::getResPointFromGamespace(position);

		direction.x = mousePosition.x - position.x;
		direction.y = mousePosition.y - position.y;

		float mag = sqrt((direction.x * direction.x) + (direction.y * direction.y));

		direction.x /= mag;
		direction.y /= mag;

		return direction;
	}
	static float getShipRotation(Vector2 direction)
	{
		float rotation = atan(direction.y / direction.x) * (180 / PI);

		if (direction.x < 0) rotation += 180;
		else if (direction.y < 0) rotation += 360;

		return rotation;
	}

	/*
	static Vector2 getAsteroidStartPos(Game game)
	{
		Vector2 startPosition;
		do
		{
			startPosition.x = static_cast<float>(rand() % static_cast<int>(config::gamespace.x));
			startPosition.y = static_cast<float>(rand() % static_cast<int>(config::gamespace.y));
		} while (true);
	}	
	*/
}