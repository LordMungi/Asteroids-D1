#include "bullet.h"

namespace bullet
{
	Bullet init()
	{
		Bullet bullet;
		bullet.shape.position = { 0, 0 };
		bullet.shape.radius = 0.5f;
		bullet.velocity = { 0, 0 };
		bullet.isActive = false;
		return bullet;
	}

	void create(Bullet& bullet, Vector2 position, Vector2 direction)
	{
		bullet.isActive = true;
		bullet.shape.position = position;
		bullet.velocity = direction;
		bullet.activeTimer = GetTime();
	}

	void destroy(Bullet& bullet)
	{
		bullet.isActive = false;
		bullet.shape.position = { 0, 0 };
		bullet.velocity = { 0, 0 };
	}

	void move(Bullet& bullet)
	{
		bullet.shape.position.x += bullet.velocity.x * speed * GetFrameTime();
		bullet.shape.position.y += bullet.velocity.y * speed * GetFrameTime();
	}

	void draw(Bullet bullet)
	{
		render::circle(bullet.shape, WHITE);
	}

}