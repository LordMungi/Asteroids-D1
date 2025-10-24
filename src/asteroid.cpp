#include "asteroid.h"
#include <iostream>
#include "random.h"

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

		asteroid.velocity.x = random::floatRange(-1, 1);
		asteroid.velocity.y = sqrt(1 - asteroid.velocity.x * asteroid.velocity.x);
		if (random::coinFlip())
			asteroid.velocity.y *= -1;

		switch (random::intRange(1, 3))
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

		asteroid.speed = random::intRange(minSpeed, maxSpeed);
		asteroid.isActive = true;
	}

	void create(Asteroid& asteroid, Vector2 position, Size size)
	{
		asteroid.shape.position = position;
		asteroid.velocity.x = random::floatRange(-1, 1);
		asteroid.velocity.y = sqrt(1 - asteroid.velocity.x * asteroid.velocity.x);
		if (random::coinFlip())
			asteroid.velocity.y *= -1;

		asteroid.shape.radius = static_cast<float>(size);
		asteroid.speed = random::intRange(minSpeed, maxSpeed);
		asteroid.isActive = true;
	}

	void destroy(Asteroid& asteroid)
	{
		asteroid.shape.position = { 0, 0 };
		asteroid.shape.radius = static_cast<float>(Size::Small);
		asteroid.velocity = { 0, 0 };
		asteroid.speed = 0;
		asteroid.isActive = false;
	}

	void move(Asteroid& asteroid)
	{
		asteroid.shape.position.x += asteroid.velocity.x * asteroid.speed * GetFrameTime();
		asteroid.shape.position.y += asteroid.velocity.y * asteroid.speed * GetFrameTime();
	}

	void draw(Asteroid asteroid)
	{
		render::circle(asteroid.shape, WHITE);
	}
}