#pragma once
#include "shapes.h"

namespace boomerang
{
	enum class State
	{
		Inactive,
		Stationary,
		Carried,
		Flying,
		Returning
	};

	struct Boomerang
	{
		State state;

		Texture2D sprite;
		shape::Rectangle shape;
		shape::Circle collision;
		
		Vector2 velocity;
		float rotation;
	};

	const int rotationSpeedStationary = 30;
	const int rotationSpeedMoving = 200;
	const int speed = 10;
	const int maxSpeed = 40;
	const int acceleration = 10;
	const int throwStrength = 10;

	Boomerang init();
	void create(Boomerang& boomerang, Vector2 position);

	void throwTo(Boomerang& boomerang, Vector2 direction);
	void move(Boomerang& boomerang, Vector2 origin);
	void draw(Boomerang boomerang);

	void unload(Boomerang& boomerang);
}