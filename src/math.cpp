#include "math.h"
#include <raymath.h>

namespace math
{
	float getRotation(Vector2 direction)
	{
		float rotation = static_cast<float>(atan(direction.y / direction.x) * (180 / PI));

		if (direction.x < 0) rotation += 180;
		else if (direction.y < 0) rotation += 360;

		return rotation;
	}
}