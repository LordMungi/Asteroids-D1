#include "math.h"
#include <raymath.h>
#include "config.h"

namespace math
{
	float getRotation(Vector2 direction)
	{
		float rotation = static_cast<float>(atan(direction.y / direction.x) * (180 / PI));

		if (direction.x < 0) rotation += 180;
		else if (direction.y < 0) rotation += 360;

		return rotation;
	}


	Vector2 getResPointFromGamespace(Vector2 gsPoint)
	{
		Vector2 resPoint;
		resPoint.x = gsPoint.x * config::res.x / config::gamespace.x;
		resPoint.y = gsPoint.y * config::res.y / config::gamespace.y;
		return resPoint;
	}
	float getResValueFromGamespace(float value)
	{
		return value * config::res.y / config::gamespace.y;
	}

	Vector2 getGamespacePointFromRes(Vector2 resPoint)
	{
		Vector2 gsPoint;
		gsPoint.x = resPoint.x * config::gamespace.x / config::res.x;
		gsPoint.y = resPoint.y * config::gamespace.y / config::res.y;
		return gsPoint;
	}
}