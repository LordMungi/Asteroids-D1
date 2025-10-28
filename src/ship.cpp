#include "ship.h"
#include <cmath>
#include "config.h"
#include "math.h"

namespace ship
{
	Ship init()
	{
		Ship ship;
		
		ship.collision.position = { config::gamespace.x / 2, config::gamespace.y / 2 };
		ship.collision.radius = 4;

		ship.shape.position = ship.collision.position;
		ship.shape.size = { 15, 15 };

		ship.idleAnimation = anim::init(3);
		ship.idleAnimation.frames[0] = LoadTexture("resources/sprites/ship/idle/idle1.png");
		ship.idleAnimation.frames[1] = LoadTexture("resources/sprites/ship/idle/idle2.png");
		ship.idleAnimation.frames[2] = LoadTexture("resources/sprites/ship/idle/idle3.png");

		ship.accelAnimation = anim::init(3);
		ship.accelAnimation.frames[0] = LoadTexture("resources/sprites/ship/acceleration/squash.png");
		ship.accelAnimation.frames[1] = LoadTexture("resources/sprites/ship/acceleration/stretch1.png");
		ship.accelAnimation.frames[2] = LoadTexture("resources/sprites/ship/acceleration/stretch2.png");

		ship.deathSprite = LoadTexture("resources/sprites/ship/death/death.png");


		ship.lives = 3;
		ship.velocity = { 0, 0 };
		ship.rotation = 0;
		ship.state = State::Moving;

		for (int i = 0; i < bullet::maxBullets; i++)
		{
			ship.bullets[i] = bullet::init();
		}
		bullet::loadSprite();

		ship.immunityTimer = 0;
		ship.deathTimer = 0;
		
		return ship;
	}

	void unload(Ship& ship)
	{
		anim::unload(ship.idleAnimation);
		anim::unload(ship.accelAnimation);
		UnloadTexture(ship.deathSprite);

		bullet::unloadSprite();
	}

	void accelerate(Ship& ship)
	{
		ship.state = State::Accelerating;
		if (abs(ship.velocity.x + ship.direction.x * acceleration * GetFrameTime()) < maxSpeed)
			ship.velocity.x = ship.velocity.x + ship.direction.x * acceleration * GetFrameTime();
		if (abs(ship.velocity.y + ship.direction.y * acceleration * GetFrameTime()) < maxSpeed)
			ship.velocity.y = ship.velocity.y + ship.direction.y * acceleration * GetFrameTime();
	}

	void move(Ship& ship)
	{
		ship.state = State::Moving;
		ship.rotation = math::getRotation(ship.direction);
		ship.collision.position.x += ship.velocity.x * GetFrameTime();
		ship.collision.position.y += ship.velocity.y * GetFrameTime();
		ship.shape.position = ship.collision.position;
	}

	void shoot(Ship& ship)
	{
		ship.state = State::Shooting;
		for (int i = 0; i < bullet::maxBullets; i++)
		{
			if (!ship.bullets[i].isActive)
			{
				bullet::create(ship.bullets[i], ship.collision.position, ship.direction);
				break;
			}
		}
	}

	void spawn(Ship& ship)
	{
		ship.state = State::Moving;
		ship.collision.position = { config::gamespace.x / 2, config::gamespace.y / 2 };
		ship.velocity = { 0, 0 };
		ship.immunityTimer = GetTime();
	}

	void die(Ship& ship)
	{
		ship.lives--;
		ship.state = State::Dead;
		ship.velocity = { 0, 0 };
		ship.deathTimer = GetTime();
	}
	
	Vector2 getDirection(Ship& ship)
	{
		Vector2 direction;

		Vector2 mousePosition = GetMousePosition();
		Vector2 resPosition = math::getResPointFromGamespace(ship.collision.position);

		direction.x = mousePosition.x - resPosition.x;
		direction.y = mousePosition.y - resPosition.y;

		float mag = sqrt((direction.x * direction.x) + (direction.y * direction.y));

		direction.x /= mag;
		direction.y /= mag;

		return direction;
	}

	void draw(Ship& ship)
	{
		switch (ship.state)
		{
		case State::Moving:
			//render::circle(ship.collision, WHITE);
			render::animation(ship.idleAnimation, ship.shape, ship.rotation);
			break;
		case State::Accelerating:
			//render::circle(ship.collision, GRAY);
			render::animation(ship.accelAnimation, ship.shape, ship.rotation);
			break;
		case State::Shooting:
			//render::circle(ship.collision, BLUE);
			break;
		case State::Dead:
			//render::circle(ship.collision, RED);
			render::sprite(ship.deathSprite, ship.shape, ship.rotation);
			break;
		}

	}

}