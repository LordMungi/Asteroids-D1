#include "bullet.h"
#include "math.h"

namespace bullet
{
	Bullet init()
	{
		Bullet bullet;

		bullet.collision.position = { 0, 0 };
		bullet.collision.radius = 0.5f;

		bullet.sprite = LoadTexture("resources/sprites/bullet/egg.png");
		bullet.shape.position = bullet.collision.position;
		bullet.shape.size = { 5, 5 };

		bullet.velocity = { 0, 0 };
		bullet.isActive = false;
		return bullet;
	}

	void create(Bullet& bullet, Vector2 position, Vector2 direction)
	{
		bullet.isActive = true;
		bullet.collision.position = position;
		bullet.velocity = direction;
		bullet.activeTimer = GetTime();
		bullet.rotation = math::getRotation(direction);
	}

	void destroy(Bullet& bullet)
	{
		bullet.isActive = false;
		bullet.collision.position = { 0, 0 };
		bullet.velocity = { 0, 0 };
	}

	void move(Bullet& bullet)
	{
		bullet.collision.position.x += bullet.velocity.x * speed * GetFrameTime();
		bullet.collision.position.y += bullet.velocity.y * speed * GetFrameTime();
		bullet.shape.position = bullet.collision.position;
	}

	void draw(Bullet bullet)
	{
		render::circle(bullet.collision, WHITE);
		render::sprite(bullet.sprite, bullet.shape, bullet.rotation);
	}

	void unload(Bullet& bullet)
	{
		UnloadTexture(bullet.sprite);
	}
}