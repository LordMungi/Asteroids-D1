#include "hud.h"
#include "render.h"
#include "config.h"
#include <string>

namespace hud
{
	void draw(game::Stats gameStats)
	{
		switch (gameStats.gamestate)
		{
		case game::State::Playing:
		{
			render::text(std::to_string(gameStats.lives), { 5, 5 }, 5);
			break;
		}
		case game::State::Won:
		{
			render::text("Winner!", {config::gamespace.x / 2, config::gamespace.y / 2 }, 10);
			break;
		}
		case game::State::Lost:
		{
			render::text("Game Over", { config::gamespace.x / 2, config::gamespace.y / 2 }, 10);
			break;
		}

		}
	}
}