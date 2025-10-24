#include "game.h"

#include <iostream>
#include <cmath>
#include <ctime>

#include "config.h"
#include "ship.h"
#include "bullet.h"
#include "asteroid.h"
#include "collision.h"
#include "random.h"

namespace game
{
	
	ship::Ship ship;
	bullet::Bullet bullets[bullet::maxBullets];
	asteroid::Asteroid asteroids[asteroid::maxAsteroids];

	static Vector2 getShipDirection();
	static float getShipRotation(Vector2 direction);
	static Vector2 getAsteroidStartPos();
	static void returnFromOtherSide(shape::Circle& circle);

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
			asteroid::create(asteroids[i], getAsteroidStartPos());
		}
	}

	void update()
	{
		Vector2 direction = getShipDirection();

		if (ship.isAlive)
		{
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
			returnFromOtherSide(ship.shape);
		}

		for (int i = 0; i < bullet::maxBullets; i++)
		{
			if (bullets[i].isActive)
			{
				bullet::move(bullets[i]);
				returnFromOtherSide(bullets[i].shape);
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
				returnFromOtherSide(asteroids[i].shape);
				if (coll::circleCircle(ship.shape, asteroids[i].shape) && 
					GetTime() - ship.immunityTimer > ship::immunityCooldown &&
					ship.isAlive)
				{
					ship::die(ship);
					asteroid::destroy(asteroids[i]);
				}
			}	
		}

		if (!ship.isAlive && GetTime() - ship.deathTimer > ship::deathCooldown)
			ship::spawn(ship);
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

	static Vector2 getShipDirection()
	{
		Vector2 direction;

		Vector2 mousePosition = GetMousePosition();
		Vector2 resPosition = render::getResPointFromGamespace(ship.shape.position);

		direction.x = mousePosition.x - resPosition.x;
		direction.y = mousePosition.y - resPosition.y;

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