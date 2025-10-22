#include "game.h"
#include <cmath>
#include <iostream>
#include "render.h"
#include "ship.h"

namespace game
{
	struct Game
	{
		ship::Ship ship;
	};

	static void update(Game& game);
	static void draw(Game game);
	static void unload(Game& game);

	static Vector2 getShipDirection(Vector2 position);
	static float getShipRotation(Vector2 pos);

	void run()
	{
		render::startWindow();

		Game game;

		game.ship = ship::init();

		while (!WindowShouldClose())
		{
			update(game);
			draw(game);
		}

		unload(game);
		render::closeWindow();
	}

	static void update(Game& game)
	{
		game.ship.rotation = getShipRotation(game.ship.position);
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			ship::accelerate(game.ship, getShipDirection(game.ship.position));
		}
		ship::move(game.ship);

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
		render::sprite(game.ship.sprite, game.ship.position, { game.ship.size, game.ship.size }, game.ship.rotation);
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
	static float getShipRotation(Vector2 position)
	{
		Vector2 direction = getShipDirection(position);

		float rotation = atan(direction.y / direction.x) * (180 / PI);

		if (direction.x < 0) rotation += 180;
		else if (direction.y < 0) rotation += 360;

		return rotation;
	}
	
}