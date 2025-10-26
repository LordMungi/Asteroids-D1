#pragma once
#include "screens.h"

namespace game
{
	enum class State
	{
		Playing,
		Won,
		Lost,
		Paused
	};

	struct Stats
	{
		State gamestate;
		int lives;
	};

	void init();
	screen::Type update();
	void draw();
	void unload();
}