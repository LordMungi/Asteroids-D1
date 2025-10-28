#include "seal.h"
#include "render.h"
#include "math.h"

namespace seal
{
	Seal init()
	{
		Seal seal;

		seal.isActive = false;

		seal.collision.position = { 0,0 };
		seal.collision.radius = 7;

		seal.animation = anim::init(3);
		seal.animation.frames[0] = LoadTexture("resources/sprites/enemies/seal/seal1color.png");
		seal.animation.frames[1] = LoadTexture("resources/sprites/enemies/seal/seal2color.png");
		seal.animation.frames[2] = LoadTexture("resources/sprites/enemies/seal/seal3color.png");
		seal.shape.position = seal.collision.position;
		seal.shape.size = { seal.collision.radius * 4, seal.collision.radius * 4 };

		seal.velocity = { 0,0 };
		seal.rotation = 0;
		
		seal.health = 100;
		return seal;
	}

	void create(Seal& seal)
	{
		seal.isActive = true;
	}

	void move(Seal& seal, Vector2 direction)
	{
		seal.velocity = direction;
		seal.collision.position.x += seal.velocity.x * speed * GetFrameTime();
		seal.collision.position.y += seal.velocity.y * speed * GetFrameTime();
		seal.shape.position = seal.collision.position;
		seal.rotation = math::getRotation(direction);
	}

	void draw(Seal seal)
	{
		render::animation(seal.animation, seal.shape, seal.rotation);
		//render::circle(seal.collision, RED);
	}

	void destroy(Seal& seal)
	{
		seal.isActive = false;
	}

	void unload(Seal& seal)
	{
		for (int i = 0; i < seal.animation.length; i++)
		{
			UnloadTexture(seal.animation.frames[i]);
		}
	}
}