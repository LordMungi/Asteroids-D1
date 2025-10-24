#pragma once
#include "render.h"

namespace bullet
{
	struct Bullet
	{
		shape::Circle shape;
		Vector2 velocity;
		bool isActive;
	};

	const int maxBullets = 100;
	const int speed = 100;

	Bullet init();
	
	void create(Bullet& bullet, Vector2 position, Vector2 direction);
	void destroy(Bullet& bullet);

	void move(Bullet& bullet);
	void draw(Bullet bullet);
}