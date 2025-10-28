#pragma once
#include "shapes.h"
#include "animation.h"

namespace seal
{
	struct Seal
	{
		bool isActive;
		anim::Animation animation;
		shape::Rectangle shape;

		shape::Circle collision;
		Vector2 velocity;
		float rotation;

		float health;
	};

	Seal init();
	void create(Seal& seal);
	void move(Seal& seal, Vector2 direction);
	void damage(Seal& seal);
	void draw(Seal seal);

	void destroy(Seal& seal);
	void unload(Seal& seal);

	const int speed = 15;
}