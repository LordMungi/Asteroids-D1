#pragma once
#include "render.h"

namespace ship
{
	struct Ship
	{
		shape::Circle shape;
		Texture2D sprite;
		Vector2 velocity;
		float rotation;
	};

	const int acceleration = 60;
	const int maxSpeed = 200;

	Ship init();
	void unload(Ship& ship);

	void accelerate(Ship& ship, Vector2 direction);
	void move(Ship& ship);

	void draw(Ship ship);
}