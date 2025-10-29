#include "credits.h"
#include "button.h"
#include "label.h"
#include "config.h"
#include "background.h"

namespace credits
{
	background::Background bg;

	enum class Labels
	{
		Title,
		Programmer,
		Artist,
		Music,
		SFX
	};
	const int maxLabels = 5;
	label::Label labels[maxLabels];

	button::Button exit;

	void init()
	{
		Vector2 position = { 10,10 };
		Vector2 position2 = position;
		Vector2 size = { 10,10 };
		float separation = 5;
		float margin = 5;

		labels[static_cast<int>(Labels::Title)] = label::init("Credits", { position, size }, render::TextAlign::Left, BLACK);
		position2 = { config::gamespace.x - size.x - margin, position.y };
		exit = button::init({ position2, size }, "X");
		position.y += size.y + separation;

		size = { 7, 7 };
		labels[static_cast<int>(Labels::Programmer)] = label::init("Programming - Santino Verrua", { position, size }, render::TextAlign::Left, BLACK);
		position.y += size.y + separation;
		labels[static_cast<int>(Labels::Artist)] = label::init("Art - Matilde Braumstein", { position, size }, render::TextAlign::Left, BLACK);
		position.y += size.y + separation;

		bg.picture = LoadTexture("resources/bg/game.jpg");
		bg.shape.position = { config::gamespace.x / 2, config::gamespace.y / 2 };
		bg.shape.size = { (21 * config::gamespace.y / 9), config::gamespace.y };
	}

	screen::Type update()
	{
		screen::Type nextScreen = screen::Type::Credits;
		if (button::update(exit))
			nextScreen = screen::Type::Menu;

		return nextScreen;
	}

	void draw()
	{
		BeginDrawing();
		ClearBackground(BLACK);
		render::sprite(bg.picture, bg.shape, 0);


		for (int i = 0; i < maxLabels; i++)
		{
			label::draw(labels[i]);
		}
		button::draw(exit);
		EndDrawing();
	}
}