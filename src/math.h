#pragma once
#include <raylib.h>

namespace math
{
	float getRotation(Vector2 direction);

	Vector2 getResPointFromGamespace(Vector2 gsPoint);
	float getResValueFromGamespace(float value);
	Vector2 getGamespacePointFromRes(Vector2 resPoint);
}