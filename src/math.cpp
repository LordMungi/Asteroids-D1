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

	Vector2 getDirection(Vector2 from, Vector2 to)
	{
		Vector2 direction;

		direction.x = to.x - from.x;
		direction.y = to.y - from.y;

		return normalizeVector(direction);
	}

	Vector2 normalizeVector(Vector2 vector)
	{
		float mag = static_cast<float>(sqrt((vector.x * vector.x) + (vector.y * vector.y)));

		vector.x /= mag;
		vector.y /= mag;

		return vector;
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