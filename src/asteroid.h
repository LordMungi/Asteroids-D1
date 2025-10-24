#pragma once
#include "render.h"

namespace asteroid
{
	enum class Size
	{
		Small = 10,
		Medium = 20,
		Large = 30
	};

	struct Asteroid
	{
		shape::Circle shape;
		Vector2 velocity;
		bool isActive;
	};

	const int maxAsteroids = 30;
	const int speed = 50;

	Asteroid init();

	void create(Asteroid& asteroid, Vector2 position);
	void create(Asteroid& asteroid, Vector2 position, Vector2 direction, Size size);
	void destroy(Asteroid& asteroid);

	void move(Asteroid& asteroid);
	void draw(Asteroid asteroid);
}