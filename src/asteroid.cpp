#include "asteroid.h"
#include <iostream>

namespace asteroid
{
	Asteroid init()
	{
		Asteroid asteroid;

		asteroid.shape.position = { 0, 0 };
		asteroid.shape.radius = static_cast<float>(Size::Small);
		asteroid.velocity = { 0, 0 };
		asteroid.isActive = false;

		return asteroid;
	}

	void create(Asteroid& asteroid, Vector2 position)
	{
		asteroid.shape.position = position;

		asteroid.velocity.x = (rand() % 10000) / 10000.0f;
		asteroid.velocity.y = sqrt(1 - asteroid.velocity.x * asteroid.velocity.x);

		switch (rand() % 3 + 1)
		{
		case 1:
			asteroid.shape.radius = static_cast<float>(Size::Small);
			break;
		case 2:
			asteroid.shape.radius = static_cast<float>(Size::Medium);
			break;
		case 3:
			asteroid.shape.radius = static_cast<float>(Size::Large);
			break;
		}

		asteroid.isActive = true;
	}

	void create(Asteroid& asteroid, Vector2 position, Vector2 direction, Size size)
	{
		asteroid.shape.position = position;
		asteroid.shape.radius = static_cast<float>(size);
		asteroid.velocity = direction;
		asteroid.isActive = true;
	}

	void destroy(Asteroid& asteroid)
	{
		asteroid.shape.position = { 0, 0 };
		asteroid.shape.radius = static_cast<float>(Size::Small);
		asteroid.velocity = { 0, 0 };
		asteroid.isActive = false;
	}

	void move(Asteroid& asteroid)
	{
		asteroid.shape.position.x += asteroid.velocity.x * speed * GetFrameTime();
		asteroid.shape.position.y += asteroid.velocity.y * speed * GetFrameTime();
	}

	void draw(Asteroid asteroid)
	{
		render::circle(asteroid.shape.position, static_cast<float>(asteroid.shape.radius), WHITE);
	}
}