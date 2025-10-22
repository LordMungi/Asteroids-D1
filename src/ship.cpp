#include "ship.h"
#include <cmath>

namespace ship
{
	Ship init()
	{
		Ship ship;

		ship.position = { config::gamespace.x / 2, config::gamespace.y / 2 };
		ship.velocity = { 0, 0 };
		ship.rotation = 0;
		ship.size = 5;

		ship.acceleration = 20;
		ship.maxSpeed = 100;
		
		return ship;
	}

	void accelerate(Ship& ship, Vector2 direction)
	{
		ship.velocity.x = static_cast<float>(std::fmin(ship.velocity.x + direction.x * ship.acceleration * GetFrameTime(), ship.maxSpeed));
		ship.velocity.y = static_cast<float>(std::fmin(ship.velocity.y + direction.y * ship.acceleration * GetFrameTime(), ship.maxSpeed));
	}

	void move(Ship& ship)
	{
		ship.position.x += ship.velocity.x * GetFrameTime();
		ship.position.y += ship.velocity.y * GetFrameTime();
	}
}