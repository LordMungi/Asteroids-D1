#pragma once
#include "render.h"

namespace bullet
{
	struct Bullet
	{
		shape::Rectangle shape;
		shape::Circle collision;
		
		Vector2 velocity;
		float rotation;

		bool isActive;
		double activeTimer;
	};

	const int maxBullets = 20;
	const int speed = 120;
	const int activeCooldown = 1;

	Bullet init();
	
	void create(Bullet& bullet, Vector2 position, Vector2 direction);
	void destroy(Bullet& bullet);

	void move(Bullet& bullet);
	void draw(Bullet bullet);

	void loadSprite();
	void unloadSprite();
}