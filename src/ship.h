#pragma once
#include "render.h"

namespace ship
{
	struct Ship
	{
		Texture2D sprite;
		Vector2 position;
		Vector2 velocity;
		float rotation;
		float size;
	};

	const int acceleration = 20;
	const int maxSpeed = 100;

	Ship init();
	void unload(Ship& ship);

	void accelerate(Ship& ship, Vector2 direction);
	//void decelerate(Ship& ship, Vector2 direction);
	void move(Ship& ship);

}