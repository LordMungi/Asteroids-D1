#pragma once
#include "render.h"

namespace asteroid
{
	enum class Size
	{
		Small = 2,
		Medium = 4,
		Large = 6
	};

	enum class State
	{
		Active,
		Destroying,
		Inactive
	};

	struct Asteroid
	{
		Texture2D sprite;
		anim::Animation destroyAnim;
		shape::Rectangle shape;

		shape::Circle collision;
		Vector2 velocity;
		int speed;
		float rotation;

		State state;
		double destroyTimer;
	};

	const double destroyTime = 0.5;

	const int maxAsteroids = 50;
	const int minSpeed = 10;
	const int maxSpeed = 30;

	Asteroid init();

	void create(Asteroid& asteroid, Vector2 position);
	void create(Asteroid& asteroid, Vector2 position, Size size);
	void destroy(Asteroid& asteroid);
	void disable(Asteroid& asteroid);
	
	void move(Asteroid& asteroid);
	void draw(Asteroid& asteroid);

	void loadSprites();
	void unloadSprites();
}