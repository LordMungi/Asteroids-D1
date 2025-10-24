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
	
	ship::Ship ship;
	bullet::Bullet bullets[bullet::maxBullets];
	asteroid::Asteroid asteroids[asteroid::maxAsteroids];

	static Vector2 getShipDirection(Vector2 position);
	static float getShipRotation(Vector2 direction);

	void init()
	{
		ship = ship::init();

		for (int i = 0; i < bullet::maxBullets; i++)
		{
			bullets[i] = bullet::init();
		}

		for (int i = 0; i < asteroid::maxAsteroids; i++)
		{
			asteroids[i] = asteroid::init();
		}

		for (int i = 0; i < 10; i++)
		{
			asteroid::create(asteroids[i], { 50, 50 });
		}
	}

	void update()
	{
		Vector2 direction = getShipDirection(ship.shape.position);

		ship.rotation = getShipRotation(direction);
		
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
			ship::accelerate(ship, direction);

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			for (int i = 0; i < bullet::maxBullets; i++)
			{
				if (!bullets[i].isActive)
				{
					bullet::create(bullets[i], ship.shape.position, direction);
					break;
				}
			}
		}

		ship::move(ship);

		for (int i = 0; i < bullet::maxBullets; i++)
		{
			if (bullets[i].isActive)
			{
				bullet::move(bullets[i]);
				for (int j = 0; j < asteroid::maxAsteroids; j++)
				{
					if (asteroids[j].isActive)
					{
						if (coll::circleCircle(bullets[i].shape, asteroids[j].shape))
						{
							bullet::destroy(bullets[i]);
							asteroid::destroy(asteroids[j]);
						}
					}
				}

			}


		}

		for (int i = 0; i < asteroid::maxAsteroids; i++)
		{
			if (asteroids[i].isActive)
			{
				asteroid::move(asteroids[i]);
				if (coll::circleCircle(ship.shape, asteroids[i].shape))
				coll::correctCircleCircle(ship.shape, asteroids[i].shape);
			}
		}

		// Return from the other side if leaving screen
		if (ship.shape.position.x - ship.shape.radius / 2 > config::gamespace.x) 
			ship.shape.position.x = 0 - ship.shape.radius /2;
		if (ship.shape.position.y - ship.shape.radius / 2 > config::gamespace.y)
			ship.shape.position.y = 0 - ship.shape.radius / 2;
		if (ship.shape.position.x + ship.shape.radius / 2 < 0)
			ship.shape.position.x = config::gamespace.x + ship.shape.radius / 2;
		if (ship.shape.position.y + ship.shape.radius / 2 < 0)
			ship.shape.position.y = config::gamespace.y + ship.shape.radius / 2;
	}

	void draw()
	{
		BeginDrawing();
		ClearBackground(BLACK);

		for (int i = 0; i < bullet::maxBullets; i++)
		{
			if (bullets[i].isActive)
				bullet::draw(bullets[i]);
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