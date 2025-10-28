#include "asteroid.h"
#include <iostream>
#include "random.h"
#include "math.h"

namespace asteroid
{
	// Large
	Texture2D largeMoving;
	anim::Animation largeDestroy;

	// Medium
	Texture2D mediumMoving;
	anim::Animation mediumDestroy;

	// Small
	Texture2D smallMoving;
	anim::Animation smallDestroy;

	static void setSprites(Asteroid& asteroid);

	Asteroid init()
	{
		Asteroid asteroid;

		asteroid.collision.position = { 0, 0 };
		asteroid.collision.radius = static_cast<float>(Size::Small);
		asteroid.velocity = { 0, 0 };
		asteroid.state = State::Inactive;

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
			break;
		case 2:
			asteroid.collision.radius = static_cast<float>(Size::Medium);
			break;
		case 3:
			asteroid.collision.radius = static_cast<float>(Size::Large);
			break;
		}

		setSprites(asteroid);
		asteroid.shape.position = asteroid.collision.position;

		asteroid.speed = random::intRange(minSpeed, maxSpeed);
		asteroid.state = State::Active;
	}

	void create(Asteroid& asteroid, Vector2 position, Size size)
	{
		asteroid.collision.position = position;
		asteroid.collision.radius = static_cast<float>(size);

		asteroid.velocity.x = random::floatRange(-1, 1);
		asteroid.velocity.y = sqrt(1 - asteroid.velocity.x * asteroid.velocity.x);
		if (random::coinFlip())
			asteroid.velocity.y *= -1;
		asteroid.rotation = math::getRotation(asteroid.velocity);

		setSprites(asteroid);
		asteroid.shape.position = asteroid.collision.position;

		asteroid.speed = random::intRange(minSpeed, maxSpeed);
		asteroid.state = State::Active;
	}

	void destroy(Asteroid& asteroid)
	{
		asteroid.collision.position = { 0, 0 };
		asteroid.collision.radius = static_cast<float>(Size::Small);
		asteroid.velocity = { 0, 0 };
		asteroid.speed = 0;
		asteroid.state = State::Destroying;
		asteroid.destroyTimer = GetTime();
	}

	void disable(Asteroid& asteroid)
	{
		asteroid.state = State::Inactive;
	}

	void move(Asteroid& asteroid)
	{
		asteroid.collision.position.x += asteroid.velocity.x * asteroid.speed * GetFrameTime();
		asteroid.collision.position.y += asteroid.velocity.y * asteroid.speed * GetFrameTime();
		asteroid.shape.position = asteroid.collision.position;
		asteroid.rotation -= asteroid.speed * 4 * GetFrameTime();
	}

	void draw(Asteroid& asteroid)
	{
		//render::circle(asteroid.collision, WHITE);
		switch (asteroid.state)
		{
		case State::Active:
			render::sprite(asteroid.sprite, asteroid.shape, asteroid.rotation);
			break;
		case State::Destroying:
			render::oneshot(asteroid.destroyAnim, asteroid.shape, asteroid.rotation);
			break;
		}

	}

	void loadSprites()
	{
		// Large
		largeMoving = LoadTexture("resources/sprites/enemies/asteroid-large/moving/snowball_B.png");
		largeDestroy = anim::init(4);
		largeDestroy.frames[0] = LoadTexture("resources/sprites/enemies/asteroid-large/break/snowball_B_broken.png");
		largeDestroy.frames[1] = largeDestroy.frames[0];
		largeDestroy.frames[2] = LoadTexture("resources/sprites/enemies/asteroid-large/break/snowball_B_broken2.png");
		largeDestroy.frames[3] = largeDestroy.frames[2];

		// Medium
		mediumMoving = LoadTexture("resources/sprites/enemies/asteroid-medium/moving/snowball_M.png");
		mediumDestroy = anim::init(4);
		mediumDestroy.frames[0] = LoadTexture("resources/sprites/enemies/asteroid-medium/break/snowball_M_broken.png");
		mediumDestroy.frames[1] = mediumDestroy.frames[0];
		mediumDestroy.frames[2] = LoadTexture("resources/sprites/enemies/asteroid-medium/break/snowball_M_broken2.png");
		mediumDestroy.frames[3] = mediumDestroy.frames[2];

		// Small
		smallMoving = LoadTexture("resources/sprites/enemies/asteroid-small/moving/snowball_S.png");
		smallDestroy = anim::init(4);
		smallDestroy.frames[0] = LoadTexture("resources/sprites/enemies/asteroid-small/break/snowball_S_broken.png");
		smallDestroy.frames[1] = smallDestroy.frames[0];
		smallDestroy.frames[2] = LoadTexture("resources/sprites/enemies/asteroid-small/break/snowball_S_broken2.png");
		smallDestroy.frames[3] = smallDestroy.frames[2];
	}

	void unloadSprites()
	{
		UnloadTexture(largeMoving);
		for (int i = 0; i < largeDestroy.length; i++)
			UnloadTexture(largeDestroy.frames[i]);
		UnloadTexture(mediumMoving);
		for (int i = 0; i < mediumDestroy.length; i++)
			UnloadTexture(mediumDestroy.frames[i]);
		UnloadTexture(smallMoving);
		for (int i = 0; i < smallDestroy.length; i++)
			UnloadTexture(smallDestroy.frames[i]);
	}

	static void setSprites(Asteroid& asteroid)
	{
		switch (static_cast<int>(asteroid.collision.radius))
		{
		case static_cast<int>(Size::Small):
			asteroid.sprite = smallMoving;
			asteroid.destroyAnim = smallDestroy;
			asteroid.shape.size = { asteroid.collision.radius * 5, asteroid.collision.radius * 5 };
			break;
		case static_cast<int>(Size::Medium):
			asteroid.sprite = mediumMoving;
			asteroid.destroyAnim = mediumDestroy;
			asteroid.shape.size = { asteroid.collision.radius * 3, asteroid.collision.radius * 3 };
			break;
		case static_cast<int>(Size::Large):
			asteroid.sprite = largeMoving;
			asteroid.destroyAnim = largeDestroy;
			asteroid.shape.size = { asteroid.collision.radius * 2, asteroid.collision.radius * 2 };
			break;
		}
	}
}