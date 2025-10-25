#include "ship.h"
#include <cmath>
#include "config.h"

namespace ship
{
	Ship init()
	{
		Ship ship;
		
		ship.sprite = LoadTexture("resources/ship.png");
		ship.shape.position = { config::gamespace.x / 2, config::gamespace.y / 2 };
		ship.shape.radius = 2;

		ship.lives = 3;
		ship.velocity = { 0, 0 };
		ship.rotation = 0;
		ship.state = State::Moving;

		for (int i = 0; i < bullet::maxBullets; i++)
		{
			ship.bullets[i] = bullet::init();
		}

		ship.immunityTimer = 0;
		ship.deathTimer = 0;
		
		return ship;
	}

	void unload(Ship& ship)
	{
		UnloadTexture(ship.sprite);
	}

	void accelerate(Ship& ship)
	{
		ship.state = State::Accelerating;
		if (abs(ship.velocity.x + ship.direction.x * acceleration * GetFrameTime()) < maxSpeed)
			ship.velocity.x = ship.velocity.x + ship.direction.x * acceleration * GetFrameTime();
		if (abs(ship.velocity.y + ship.direction.y * acceleration * GetFrameTime()) < maxSpeed)
			ship.velocity.y = ship.velocity.y + ship.direction.y * acceleration * GetFrameTime();
	}

	void move(Ship& ship)
	{
		ship.state = State::Moving;
		ship.shape.position.x += ship.velocity.x * GetFrameTime();
		ship.shape.position.y += ship.velocity.y * GetFrameTime();
	}

	void shoot(Ship& ship)
	{
		ship.state = State::Shooting;
		for (int i = 0; i < bullet::maxBullets; i++)
		{
			if (!ship.bullets[i].isActive)
			{
				bullet::create(ship.bullets[i], ship.shape.position, ship.direction);
				break;
			}
		}
	}

	void spawn(Ship& ship)
	{
		ship.state = State::Moving;
		ship.shape.position = { config::gamespace.x / 2, config::gamespace.y / 2 };
		ship.velocity = { 0, 0 };
		ship.immunityTimer = GetTime();
	}

	void die(Ship& ship)
	{
		ship.lives--;
		ship.state = State::Dead;
		ship.velocity = { 0, 0 };
		ship.deathTimer = GetTime();
	}
	
	Vector2 getDirection(Ship& ship)
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

	void draw(Ship ship)
	{
		switch (ship.state)
		{
		case State::Moving:
			render::circle(ship.shape, WHITE);
			break;
		case State::Accelerating:
			render::circle(ship.shape, GRAY);
			break;
		case State::Shooting:
			render::circle(ship.shape, BLUE);
			break;
		case State::Dead:
			render::circle(ship.shape, RED);
			break;
		}

		render::sprite(ship.sprite, ship.shape, ship.rotation);
	}

}