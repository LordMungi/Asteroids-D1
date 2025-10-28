#pragma once
#include "shapes.h"

namespace boomerang
{
	enum class State
	{
		Stationary,
		Carried,
		Flying,
		Returning
	};

	struct Boomerang
	{
		State state;

		shape::Rectangle shape;
		shape::Circle collision;
		
		Vector2 velocity;
		float rotation;
	};

	const int rotationSpeedStationary = 10;
	const int rotationSpeedMoving = 30;
	const int speed = 10;
	const int maxSpeed = 40;
	const int acceleration = 10;
	const int throwStrength = 10;

	Boomerang create(shape::Circle collision);

	void throwTo(Boomerang& boomerang, Vector2 direction);
	void move(Boomerang& boomerang, Vector2 origin);
	void draw(Boomerang boomerang);
}