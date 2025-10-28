#include "asteroid.h"
#include <iostream>
#include "random.h"

namespace asteroid
{
	// Large
	Texture2D largeMoving;
	Texture2D largeBrake1;
	Texture2D largeBrake2;

	// Medium
	Texture2D mediumMoving;
	Texture2D mediumBrake1;
	Texture2D mediumBrake2;

	// Small
	Texture2D smallMoving;
	Texture2D smallBrake1;
	Texture2D smallBrake2;



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
			asteroid.sprite = smallMoving;
			asteroid.shape.size = { asteroid.collision.radius * 5, asteroid.collision.radius * 5 };
			break;
		case 2:
			asteroid.collision.radius = static_cast<float>(Size::Medium);
			asteroid.sprite = mediumMoving;
			asteroid.shape.size = { asteroid.collision.radius * 3, asteroid.collision.radius * 3 };
			break;
		case 3:
			asteroid.collision.radius = static_cast<float>(Size::Large);
			asteroid.sprite = largeMoving;
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
			asteroid.sprite = smallMoving;
			asteroid.shape.size = { asteroid.collision.radius * 5, asteroid.collision.radius * 5 };
			break;
		case Size::Medium:
			asteroid.sprite = mediumMoving;
			asteroid.shape.size = { asteroid.collision.radius * 3, asteroid.collision.radius * 3 };
			break;
		case Size::Large:
			asteroid.sprite = largeMoving;
			asteroid.shape.size = { asteroid.collision.radius * 2, asteroid.collision.radius * 2 };
			break;
		}
		asteroid.shape.position = asteroid.collision.position;

		asteroid.speed = random::intRange(minSpeed, maxSpeed);
		asteroid.isActive = true;
	}

	void destroy(Asteroid& asteroid)
	{
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

	void loadSprites()
	{
		// Large
		largeMoving = LoadTexture("resources/sprites/enemies/asteroid-large/moving/snowball_B.png");
		largeBrake1 = LoadTexture("resources/sprites/enemies/asteroid-large/break/snowball_B_broken.png");
		largeBrake2 = LoadTexture("resources/sprites/enemies/asteroid-large/break/snowball_B_broken2.png");

		// Medium
		mediumMoving = LoadTexture("resources/sprites/enemies/asteroid-medium/moving/snowball_M.png");
		mediumBrake1 = LoadTexture("resources/sprites/enemies/asteroid-medium/break/snowball_M_broken.png");
		mediumBrake2 = LoadTexture("resources/sprites/enemies/asteroid-medium/break/snowball_M_broken2.png");

		// Small
		smallMoving = LoadTexture("resources/sprites/enemies/asteroid-small/moving/snowball_S.png");
		smallBrake1 = LoadTexture("resources/sprites/enemies/asteroid-small/break/snowball_S_broken.png");
		smallBrake2 = LoadTexture("resources/sprites/enemies/asteroid-small/break/snowball_S_broken2.png");
	}

	void unloadSprites()
	{
		UnloadTexture(largeMoving);
		UnloadTexture(largeBrake1);
		UnloadTexture(largeBrake2);
		UnloadTexture(mediumMoving);
		UnloadTexture(mediumBrake1);
		UnloadTexture(mediumBrake2);
		UnloadTexture(smallMoving);
		UnloadTexture(smallBrake1);
		UnloadTexture(smallBrake2);
	}
}