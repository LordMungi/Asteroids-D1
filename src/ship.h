#pragma once
#include "render.h"
#include "bullet.h"

namespace ship
{
	enum class State
	{
		Moving,
		Accelerating,
		Shooting,
		Dead,
	};

	struct Ship
	{
		anim::Animation idleAnimation;

		Texture2D sprite;
		shape::Circle shape;
				
		int lives;
		Vector2 direction;
		Vector2 velocity;
		float rotation;
		State state;

		bullet::Bullet bullets[bullet::maxBullets];

		double immunityTimer;
		double deathTimer;
	};

	const int acceleration = 60;
	const int maxSpeed = 100;

	const int immunityCooldown = 2;
	const int deathCooldown = 2;

	Ship init();
	void unload(Ship& ship);

	void accelerate(Ship& ship);
	void move(Ship& ship);
	void shoot(Ship& ship);

	void spawn(Ship& ship);
	void die(Ship& ship);

	Vector2 getDirection(Ship& ship);

	void draw(Ship& ship);
}