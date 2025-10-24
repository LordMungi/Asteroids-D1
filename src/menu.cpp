#include "menu.h"
#include "render.h"
#include "config.h"

namespace menu
{
	static void draw();

	void run()
	{
		render::startWindow();

		while (!WindowShouldClose())
		{
			draw();
		}

		render::closeWindow();

	}

	static void draw()
	{
		Vector2 middle = { config::gamespace.x / 2, config::gamespace.y / 2 };
		BeginDrawing();
		ClearBackground(BLACK);
		Vector2 optionSize = { 50, 10 };
		Vector2 optionPos = { middle.x - optionSize.x / 2, middle.y - optionSize.y / 2 };
		float optionSpace = 5;

		render::rectangle(optionPos, optionSize, WHITE);
		optionPos.y += optionSize.y + optionSpace;
		render::rectangle(optionPos, optionSize, WHITE);
		optionPos.y += optionSize.y + optionSpace;
		render::rectangle(optionPos, optionSize, WHITE);
		EndDrawing();
	}
}
