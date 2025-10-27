#include "asteroid.h"
#include <iostream>
#include "random.h"

namespace asteroid
{
	Asteroid init()
	{
		Asteroid asteroid;

		asteroid.collision.position = { 0, 0 };
		asteroid.collision.radius = static_cast<float>(Size::Small);
		asteroid.velocity = { 0, 0 };
		asteroid.isActive = false;

		return asteroid;
	}

	void create(Asteroid& asteroid, Vector2 position)
	{

		asteroid.velocity.x = random::floatRange(-1, 1);
		asteroid.velocity.y = sqrt(1 - asteroid.velocity.x * asteroid.velocity.x);
		if (random::coinFlip())
			asteroid.velocity.y *= -1;

		asteroid.collision.position = position;
		switch (random::intRange(1, 3))
		{
		case 1:
			asteroid.collision.radius = static_cast<float>(Size::Small);
			asteroid.sprite = LoadTexture("resources/sprites/enemies/asteroid-small/moving/snowball_S.png");
			asteroid.shape.size = { asteroid.collision.radius * 5, asteroid.collision.radius * 5 };
			break;
		case 2:
			asteroid.collision.radius = static_cast<float>(Size::Medium);
			asteroid.sprite = LoadTexture("resources/sprites/enemies/asteroid-medium/moving/snowball_M.png");
			asteroid.shape.size = { asteroid.collision.radius * 3, asteroid.collision.radius * 3 };
			break;
		case 3:
			asteroid.collision.radius = static_cast<float>(Size::Large);
			asteroid.sprite = LoadTexture("resources/sprites/enemies/asteroid-large/moving/snowball_B.png");
			asteroid.shape.size = { asteroid.collision.radius * 2, asteroid.collision.radius * 2 };
			break;
		}
		asteroid.shape.position = asteroid.collision.position;

		asteroid.speed = random::intRange(minSpeed, maxSpeed);
		asteroid.isActive = true;
	}

	void create(Asteroid& asteroid, Vector2 position, Size size)
	{
		asteroid.collision.position = position;
		asteroid.collision.radius = static_cast<float>(size);

		asteroid.velocity.x = random::floatRange(-1, 1);
		asteroid.velocity.y = sqrt(1 - asteroid.velocity.x * asteroid.velocity.x);
		if (random::coinFlip())
			asteroid.velocity.y *= -1;

		switch (size)
		{
		case Size::Small:
			asteroid.sprite = LoadTexture("resources/sprites/enemies/asteroid-small/moving/snowball_S.png");
			asteroid.shape.size = { asteroid.collision.radius * 5, asteroid.collision.radius * 5 };
			break;
		case Size::Medium:
			asteroid.sprite = LoadTexture("resources/sprites/enemies/asteroid-medium/moving/snowball_M.png");
			asteroid.shape.size = { asteroid.collision.radius * 3, asteroid.collision.radius * 3 };
			break;
		case Size::Large:
			asteroid.sprite = LoadTexture("resources/sprites/enemies/asteroid-large/moving/snowball_B.png");
			asteroid.shape.size = { asteroid.collision.radius * 2, asteroid.collision.radius * 2 };
			break;
		}
		asteroid.shape.position = asteroid.collision.position;

		asteroid.speed = random::intRange(minSpeed, maxSpeed);
		asteroid.isActive = true;
	}

	void destroy(Asteroid& asteroid)
	{
		UnloadTexture(asteroid.sprite);
		asteroid.collision.position = { 0, 0 };
		asteroid.collision.radius = static_cast<float>(Size::Small);
		asteroid.velocity = { 0, 0 };
		asteroid.speed = 0;
		asteroid.isActive = false;
	}

	void move(Asteroid& asteroid)
	{
		asteroid.collision.position.x += asteroid.velocity.x * asteroid.speed * GetFrameTime();
		asteroid.collision.position.y += asteroid.velocity.y * asteroid.speed * GetFrameTime();
		asteroid.shape.position = asteroid.collision.position;
	}

	void draw(Asteroid asteroid)
	{
		//render::circle(asteroid.collision, WHITE);
		render::sprite(asteroid.sprite, asteroid.shape, 0);
	}
}