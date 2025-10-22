#include "game.h"

#include <cmath>
#include <iostream>

#include "ship.h"
#include "bullet.h"

namespace game
{
	struct Game
	{
		ship::Ship ship;
		bullet::Bullet bullets[bullet::maxBullets];
	};

	static Game init();
	static void update(Game& game);
	static void draw(Game game);
	static void unload(Game& game);

	static Vector2 getShipDirection(Vector2 position);
	static float getShipRotation(Vector2 direction);

	void run()
	{
		render::startWindow();

		Game game = init();

		while (!WindowShouldClose())
		{
			update(game);
			draw(game);
		}

		unload(game);
		render::closeWindow();
	}

	static Game init()
	{
		Game game;
		game.ship = ship::init();

		for (int i = 0; i < bullet::maxBullets; i++)
		{
			game.bullets[i] = bullet::init();
		}

		return game;
	}

	static void update(Game& game)
	{
		Vector2 direction = getShipDirection(game.ship.position);

		game.ship.rotation = getShipRotation(direction);
		
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
			ship::accelerate(game.ship, direction);

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			for (int i = 0; i < bullet::maxBullets; i++)
			{
				if (!game.bullets[i].isActive)
				{
					bullet::create(game.bullets[i], game.ship.position, direction);
					break;
				}
			}
		}

		ship::move(game.ship);

		for (int i = 0; i < bullet::maxBullets; i++)
			bullet::move(game.bullets[i]);

		// Return from the other side if leaving screen
		if (game.ship.position.x - game.ship.size / 2 > config::gamespace.x) 
			game.ship.position.x = 0 - game.ship.size/2;
		if (game.ship.position.y - game.ship.size / 2 > config::gamespace.y)
			game.ship.position.y = 0 - game.ship.size / 2;
		if (game.ship.position.x + game.ship.size / 2 < 0)
			game.ship.position.x = config::gamespace.x + game.ship.size / 2;
		if (game.ship.position.y + game.ship.size / 2 < 0)
			game.ship.position.y = config::gamespace.y + game.ship.size / 2;
	}

	static void draw(Game game)
	{
		BeginDrawing();
		ClearBackground(BLACK);
		ship::draw(game.ship);

		for (int i = 0; i < bullet::maxBullets; i++)
		{
			if (game.bullets[i].isActive)
				bullet::draw(game.bullets[i]);
		}
		EndDrawing();

	}

	static void unload(Game& game)
	{
		ship::unload(game.ship);
	}

	static Vector2 getShipDirection(Vector2 position)
	{
		Vector2 direction;

		Vector2 mousePosition = GetMousePosition();
		position = render::getResFromGamespace(position);

		direction.x = mousePosition.x - position.x;
		direction.y = mousePosition.y - position.y;

		float mag = sqrt((direction.x * direction.x) + (direction.y * direction.y));

		direction.x /= mag;
		direction.y /= mag;

		return direction;
	}
	static float getShipRotation(Vector2 direction)
	{
		float rotation = atan(direction.y / direction.x) * (180 / PI);

		if (direction.x < 0) rotation += 180;
		else if (direction.y < 0) rotation += 360;

		return rotation;
	}
	
}