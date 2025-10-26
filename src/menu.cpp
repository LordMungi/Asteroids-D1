#include "menu.h"
#include "button.h"
#include "config.h"

namespace menu
{
	screen::Type nextScreen;

	button::Button play;
	button::Button credits;
	button::Button exit;
	
	void init()
	{
		Vector2 position = { config::gamespace.x / 2, 50 };
		Vector2 size = { 40, 7 };
		float separation = 3;

		play = button::init({ position, size }, "Play");
		position.y += size.y + separation;
		
		credits = button::init({ position, size }, "Credits");
		position.y += size.y + separation;

		exit = button::init({ position, size }, "Exit");
		position.y += size.y + separation;

	}

	screen::Type update()
	{
		nextScreen = screen::Type::Menu;




		return nextScreen;
	}

	void draw()
	{
		BeginDrawing();
		ClearBackground(BLACK);

		button::draw(play);
		button::draw(credits);
		button::draw(exit);

		EndDrawing();
	}
}
