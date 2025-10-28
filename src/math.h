#pragma once
#include <raylib.h>

namespace math
{
	float getRotation(Vector2 direction);
	Vector2 getDirection(Vector2 from, Vector2 to);
	Vector2 normalizeVector(Vector2 vector);

	Vector2 getResPointFromGamespace(Vector2 gsPoint);
	float getResValueFromGamespace(float value);
	Vector2 getGamespacePointFromRes(Vector2 resPoint);
}