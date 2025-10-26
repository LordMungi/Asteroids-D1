#include "menu.h"
#include "button.h"
#include "config.h"
#include "collision.h"
#include "render.h"

namespace menu
{
	screen::Type nextScreen;
	const int maxButtons = 3;

	button::Button buttons[maxButtons];

	enum class Options
	{
		Play,
		Credits,
		Exit
	};
	
	void init()
	{
		Vector2 position = { config::gamespace.x / 2, 50 };
		Vector2 size = { 40, 7 };
		float separation = 3;

		buttons[static_cast<int>(Options::Play)] = button::init({ position, size }, "Play");
		position.y += size.y + separation;
		
		buttons[static_cast<int>(Options::Credits)] = button::init({position, size}, "Credits");
		position.y += size.y + separation;

		buttons[static_cast<int>(Options::Exit)] = button::init({position, size}, "Exit");
		position.y += size.y + separation;

	}

	screen::Type update()
	{
		nextScreen = screen::Type::Menu;

		for (int i = 0; i < maxButtons; i++)
		{
			buttons[i].isPressed = false;
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
				buttons[i].isPressed = coll::pointRectangle(render::getGamespacePointFromRes(GetMousePosition()), buttons[i].shape);
		}

		if (button::trigger(buttons[static_cast<int>(Options::Play)]))
			nextScreen = screen::Type::Game;

		return nextScreen;
	}

	void draw()
	{
		BeginDrawing();
		ClearBackground(BLACK);

		for (int i = 0; i < maxButtons; i++)
		{
			button::draw(buttons[i]);
		}

		EndDrawing();
	}
}
