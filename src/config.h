#pragma once
#include "raylib.h"

namespace config
{
	extern Vector2 res;
	extern Vector2 gamespace;

	void setGamespaceFromRes();
}