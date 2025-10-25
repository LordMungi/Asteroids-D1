#include "ship.h"
#include <cmath>
#include "config.h"

namespace ship
{
	Ship init()
	{
		Ship ship;

		ship.state = State::Moving;
		ship.sprite = LoadTexture("resources/ship.png");
		ship.shape.position = { config::gamespace.x / 2, config::gamespace.y / 2 };
		ship.shape.radius = 2;
		ship.velocity = { 0, 0 };
		ship.rotation = 0;
		ship.immunityTimer = 0;
		ship.deathTimer = 0;
		
		return ship;
	}

	void unload(Ship& ship)
	{
		UnloadTexture(ship.sprite);
	}

	void accelerate(Ship& ship, Vector2 direction)
	{
		ship.state = State::Accelerating;
		ship.velocity.x = static_cast<float>(std::fmin(ship.velocity.x + direction.x * acceleration * GetFrameTime(), maxSpeed));
		ship.velocity.y = static_cast<float>(std::fmin(ship.velocity.y + direction.y * acceleration * GetFrameTime(), maxSpeed));
	}

	void move(Ship& ship)
	{
		ship.state = State::Moving;
		ship.shape.position.x += ship.velocity.x * GetFrameTime();
		ship.shape.position.y += ship.velocity.y * GetFrameTime();
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
		ship.state = State::Dead;
		ship.velocity = { 0, 0 };
		ship.deathTimer = GetTime();
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