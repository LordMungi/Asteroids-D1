#include "pause.h"
#include "button.h"
#include "config.h"

namespace pause
{
	button::Button resume;
	button::Button exit;

	void init()
	{
		Vector2 position = { config::gamespace.x / 2, 40 };
		Vector2 size = { 50, 8 };

		resume = button::init({ position, size }, "Resume");
		position = { config::gamespace.x / 2, 60 };
		exit = button::init({ position, size }, "Exit");
	}

	DoNext update()
	{
		DoNext next = DoNext::Null;

		if (button::update(resume))
			next = DoNext::Resume;
		if (button::update(exit))
			next = DoNext::Exit;

		return next;
	}


	void draw()
	{		
		button::draw(resume);
		button::draw(exit);
	}

}