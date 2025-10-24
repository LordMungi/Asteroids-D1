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
		bool isAlive;

		double immunityTimer;
		double deathTimer;
	};

	const int acceleration = 60;
	const int maxSpeed = 200;

	const int immunityCooldown = 2;
	const int deathCooldown = 2;

	Ship init();
	void unload(Ship& ship);

	void accelerate(Ship& ship, Vector2 direction);
	void move(Ship& ship);
	void spawn(Ship& ship);
	void die(Ship& ship);

	void draw(Ship ship);
}