#include "ship.h"
#include <cmath>
#include "config.h"

namespace ship
{
	Ship init()
	{
		Ship ship;

		ship.isAlive = true;
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
		ship.velocity.x = static_cast<float>(std::fmin(ship.velocity.x + direction.x * acceleration * GetFrameTime(), maxSpeed));
		ship.velocity.y = static_cast<float>(std::fmin(ship.velocity.y + direction.y * acceleration * GetFrameTime(), maxSpeed));
	}

	void move(Ship& ship)
	{
		ship.shape.position.x += ship.velocity.x * GetFrameTime();
		ship.shape.position.y += ship.velocity.y * GetFrameTime();
	}

	void spawn(Ship& ship)
	{
		ship.isAlive = true;
		ship.shape.position = { config::gamespace.x / 2, config::gamespace.y / 2 };
		ship.velocity = { 0, 0 };
		ship.immunityTimer = GetTime();
	}

	void die(Ship& ship)
	{
		ship.isAlive = false;
		ship.velocity = { 0, 0 };
		ship.deathTimer = GetTime();
	}
	

	void draw(Ship ship)
	{
		render::circle(ship.shape, WHITE);
		render::sprite(ship.sprite, ship.shape, ship.rotation);
	}

}