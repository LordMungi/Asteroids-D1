#include "menu.h"
#include "button.h"
#include "config.h"
#include "collision.h"
#include "render.h"
#include "label.h"

namespace menu
{
	screen::Type nextScreen;

	enum class Options
	{
		Play,
		Settings,
		Credits,
		HowToPlay,
		Exit
	};
	const int maxButtons = 5;
	
	button::Button buttons[maxButtons];
	label::Label title;

	void init()
	{
		Vector2 position = { config::gamespace.x / 2, 50 };
		Vector2 size = { 50, 7 };
		float separation = 3;

		buttons[static_cast<int>(Options::Play)] = button::init({ position, size }, "Play");
		position.y += size.y + separation;
		
		buttons[static_cast<int>(Options::Settings)] = button::init({ position, size }, "Settings");
		position.y += size.y + separation;

		buttons[static_cast<int>(Options::Credits)] = button::init({ position, size }, "Credits");
		position.y += size.y + separation;

		buttons[static_cast<int>(Options::HowToPlay)] = button::init({position, size}, "How to play");
		position.y += size.y + separation;

		buttons[static_cast<int>(Options::Exit)] = button::init({position, size}, "Exit");
		position.y += size.y + separation;

		title = label::init("Penguin Revenge", { {position.x, 20}, size }, render::TextAlign::Center, WHITE);

	}

	screen::Type update()
	{
		nextScreen = screen::Type::Menu;

		if (button::update(buttons[static_cast<int>(Options::Play)]))
			nextScreen = screen::Type::Game;
		if (button::update(buttons[static_cast<int>(Options::Settings)]))
			nextScreen = screen::Type::Settings;
		if (button::update(buttons[static_cast<int>(Options::Exit)]))
			nextScreen = screen::Type::Null;

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
		label::draw(title);

		EndDrawing();
	}
}
