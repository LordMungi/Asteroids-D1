#pragma once
#include "render.h"

namespace asteroid
{
	enum class Size
	{
		Small = 2,
		Medium = 5,
		Large = 8
	};

	struct Asteroid
	{
		shape::Circle shape;
		Vector2 velocity;
		bool isActive;
	};

	const int maxAsteroids = 30;
	const int speed = 30;

	Asteroid init();

	void create(Asteroid& asteroid, Vector2 position);
	void create(Asteroid& asteroid, Vector2 position, Vector2 direction, Size size);
	void destroy(Asteroid& asteroid);

	void move(Asteroid& asteroid);
	void draw(Asteroid asteroid);
}