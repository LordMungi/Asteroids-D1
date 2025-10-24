#include "asteroid.h"
#include <iostream>

namespace asteroid
{
	Asteroid init()
	{
		Asteroid asteroid;

		asteroid.position = { 0, 0 };
		asteroid.velocity = { 0, 0 };
		asteroid.size = Size::Small;

		return asteroid;
	}

	void create(Asteroid& asteroid, Vector2 position)
	{
		asteroid.position = position;

		asteroid.velocity.x = (rand() % 10000) / 10000.0f;
		asteroid.velocity.y = sqrt(1 - asteroid.velocity.x * asteroid.velocity.x);

		switch (rand() % 3 + 1)
		{
		case 1:
			asteroid.size = Size::Small;
			break;
		case 2:
			asteroid.size = Size::Medium;
			break;
		case 3:
			asteroid.size = Size::Large;
			break;
		}

		asteroid.isActive = true;
	}

	void create(Asteroid& asteroid, Vector2 position, Vector2 direction, Size size)
	{
		asteroid.position = position;
		asteroid.velocity = direction;
		asteroid.size = size;
		asteroid.isActive = true;
	}

	void destroy(Asteroid& asteroid)
	{
		asteroid.position = { 0, 0 };
		asteroid.velocity = { 0, 0 };
		asteroid.size = Size::Small;
		asteroid.isActive = false;
	}

	void move(Asteroid& asteroid)
	{
		asteroid.position.x += asteroid.velocity.x * speed * GetFrameTime();
		asteroid.position.y += asteroid.velocity.y * speed * GetFrameTime();
	}

	void draw(Asteroid asteroid)
	{
		render::circle(asteroid.position, static_cast<float>(asteroid.size), WHITE);
	}
}