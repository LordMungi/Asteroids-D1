#pragma once
#include "config.h"

namespace render
{
	void startWindow();
	void closeWindow();

	void rectangle(Vector2 pos, Vector2 size, Color color);
}