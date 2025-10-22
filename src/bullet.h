#pragma once
#include "render.h"

namespace bullet
{
	struct Bullet
	{
		Vector2 position;
		Vector2 velocity;
		bool isActive;
	};

	const int maxBullets = 100;
	const int speed = 100;
	const int size = 2;

	Bullet init();
	
	void create(Bullet& bullet, Vector2 position, Vector2 direction);
	void destroy(Bullet& bullet);

	void move(Bullet& bullet);
	void draw(Bullet bullet);
}