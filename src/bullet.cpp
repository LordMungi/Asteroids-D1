#include "bullet.h"

namespace bullet
{
	Bullet init()
	{
		Bullet bullet;
		bullet.position = { 0, 0 };
		bullet.velocity = { 0, 0 };
		bullet.isActive = false;
		return bullet;
	}

	void create(Bullet& bullet, Vector2 position, Vector2 direction)
	{
		bullet.isActive = true;
		bullet.position = position;
		bullet.velocity = direction;
	}

	void destroy(Bullet& bullet)
	{
		bullet.isActive = false;
		bullet.position = { 0, 0 };
		bullet.velocity = { 0, 0 };
	}

	void move(Bullet& bullet)
	{
		bullet.position.x += bullet.velocity.x * speed * GetFrameTime();
		bullet.position.y += bullet.velocity.y * speed * GetFrameTime();
	}

	void draw(Bullet bullet)
	{
		render::rectangle(bullet.position, { size, size }, WHITE);
	}

}