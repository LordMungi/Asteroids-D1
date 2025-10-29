#include "menu.h"
#include "button.h"
#include "config.h"
#include "collision.h"
#include "render.h"
#include "label.h"
#include "background.h"

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
	background::Background bg;

	void init()
	{
		Vector2 position = { 30 , 50 };
		Vector2 size = { 50, 7 };
		float separation = 3;

		buttons[static_cast<int>(Options::Play)] = button::init({ position, size }, "Play");
		position.y += size.y + separation;
		
		buttons[static_cast<int>(Options::Settings)] = button::init({ position, size }, "Settings");
		position.y += size.y + separation;

		buttons[static_cast<int>(Options::Credits)] = button::init({ position, size }, "Credits");
		position.y += size.y + separation;

		//buttons[static_cast<int>(Options::HowToPlay)] = button::init({position, size}, "How to play");
		//position.y += size.y + separation;

		buttons[static_cast<int>(Options::Exit)] = button::init({position, size}, "Exit");
		position.y += size.y + separation;

		title = label::init("Sail & Snow", { { 35, 20}, { size.x, 15} }, render::TextAlign::Left, BLACK);

		bg.picture = LoadTexture("resources/bg/illus.jpg");
		bg.shape.size = { (16 * config::gamespace.y / 9), config::gamespace.y };
		bg.shape.position = { config::gamespace.x / 2, config::gamespace.y / 2 };

	}

	screen::Type update()
	{
		nextScreen = screen::Type::Menu;

		if (button::update(buttons[static_cast<int>(Options::Play)]))
			nextScreen = screen::Type::Game;
		if (button::update(buttons[static_cast<int>(Options::Settings)]))
			nextScreen = screen::Type::Settings;
		if (button::update(buttons[static_cast<int>(Options::Credits)]))
			nextScreen = screen::Type::Credits;
		if (button::update(buttons[static_cast<int>(Options::Exit)]))
			nextScreen = screen::Type::Null;

		return nextScreen;
	}

	void draw()
	{
		BeginDrawing();
		ClearBackground(BLACK);
		render::sprite(bg.picture, bg.shape, 0);

		for (int i = 0; i < maxButtons; i++)
		{
			button::draw(buttons[i]);
		}
		label::draw(title);

		EndDrawing();
	}
}
