#pragma once
#include "render.h"

namespace ship
{
	struct Ship
	{
		Vector2 position;
		Vector2 velocity;
		float rotation;
		float size;
		
		int acceleration;
		int maxSpeed;
	};

	Ship init();

	void accelerate(Ship& ship, Vector2 direction);
	//void decelerate(Ship& ship, Vector2 direction);
	void move(Ship& ship);

}