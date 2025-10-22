#include "ship.h"
#include <cmath>

namespace ship
{
	Ship init()
	{
		Ship ship;

		ship.sprite = LoadTexture("resources/ship.png");
		ship.position = { config::gamespace.x / 2, config::gamespace.y / 2 };
		ship.velocity = { 0, 0 };
		ship.rotation = 0;
		ship.size = 5;
		
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
		ship.position.x += ship.velocity.x * GetFrameTime();
		ship.position.y += ship.velocity.y * GetFrameTime();
	}

	void draw(Ship ship)
	{
		render::sprite(ship.sprite, ship.position, { ship.size, ship.size }, ship.rotation);
	}

}