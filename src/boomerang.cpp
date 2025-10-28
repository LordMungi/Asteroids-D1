#include "boomerang.h"
#include <cmath>
#include <iostream>
#include "random.h"
#include "math.h"
#include "render.h"

namespace boomerang
{
	static void decelerate(Boomerang& boomerang);
	static void returnTo(Boomerang& boomerang, Vector2 origin);

	Boomerang create(shape::Circle collision)
	{
		Boomerang boomerang;
		boomerang.collision = collision;
		boomerang.shape = { collision.position, collision.radius * 2, collision.radius * 2 };
		boomerang.velocity = { 0, 0 };
		boomerang.rotation = static_cast<float>(random::intRange(1, 360));
		boomerang.state = State::Carried;

		return boomerang;
	}

	void throwTo(Boomerang& boomerang, Vector2 direction)
	{
		boomerang.velocity.x = direction.x * throwStrength;
		boomerang.velocity.y = direction.y * throwStrength;
		boomerang.state = State::Flying;
	}

	void move(Boomerang& boomerang, Vector2 origin)
	{
		switch (boomerang.state)
		{
		case State::Stationary:
			boomerang.rotation += rotationSpeedStationary * GetFrameTime();
			break;
		case State::Carried:
			boomerang.collision.position = origin;
			boomerang.rotation += rotationSpeedStationary * GetFrameTime();
			break;
		case State::Flying:
			decelerate(boomerang);
			if (boomerang.velocity.x == 0 && boomerang.velocity.y == 0)
				boomerang.state = State::Returning;

			boomerang.collision.position.x += boomerang.velocity.x * speed * GetFrameTime();
			boomerang.collision.position.y += boomerang.velocity.y * speed * GetFrameTime();
			boomerang.rotation += rotationSpeedMoving * GetFrameTime();
			break;
		case State::Returning:
			returnTo(boomerang, origin);			
			std::cout << "<\n";
			boomerang.collision.position.x += boomerang.velocity.x * speed * GetFrameTime();
			boomerang.collision.position.y += boomerang.velocity.y * speed * GetFrameTime();
			boomerang.rotation += rotationSpeedMoving * GetFrameTime();
			break;
		}

		boomerang.shape.position = boomerang.collision.position;

	}

	static void decelerate(Boomerang& boomerang)
	{
		Vector2 direction = math::normalizeVector(boomerang.velocity);

		if (fabsf(boomerang.velocity.x) - acceleration * GetFrameTime() > 0)
			boomerang.velocity.x += (direction.x * -1) * acceleration * GetFrameTime();
		else
			boomerang.velocity.x = 0;

		if (fabsf(boomerang.velocity.y) - acceleration * GetFrameTime() > 0)
			boomerang.velocity.y += (direction.y * -1) * acceleration * GetFrameTime();
		else
			boomerang.velocity.y = 0;
	}

	static void returnTo(Boomerang& boomerang, Vector2 origin)
	{
		Vector2 direction = math::getDirection(boomerang.collision.position, origin);
		if (abs(boomerang.velocity.x + direction.x * acceleration * GetFrameTime()) < maxSpeed)
			boomerang.velocity.x += direction.x * acceleration * GetFrameTime();
		if (abs(boomerang.velocity.y + direction.y * acceleration * GetFrameTime()) < maxSpeed)
			boomerang.velocity.y += direction.y * acceleration * GetFrameTime();
	}

	void draw(Boomerang boomerang)
	{
		render::circle(boomerang.collision, BLUE);
	}
}