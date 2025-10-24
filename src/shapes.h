#pragma once
#include <raylib.h>

namespace shape
{
	struct Circle
	{
		Vector2 position;
		float radius;
	};

	struct Rectangle
	{
		Vector2 position;
		Vector2 size;
	};
}