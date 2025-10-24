#include "collision.h"
#include <cmath>

namespace coll
{
	bool circleCircle(shape::Circle& circle1, shape::Circle circle2)
	{
		bool isColliding = false;
		
		Vector2 distance;

		distance.x = circle1.position.x - circle2.position.x;
		distance.y = circle1.position.y - circle2.position.y;
		
		float distVector = sqrt(distance.x * distance.x + distance.y * distance.y);
		
		isColliding = distVector <= circle1.radius + circle2.radius;

		if (isColliding)
		{
			// Corrección
			float angle = atan(distance.y / distance.x);
			distVector = circle1.radius + circle2.radius;

			circle1.position.x = circle2.position.x + (distVector * cos(angle));
			circle1.position.y = circle2.position.y + (distVector * sin(angle));
		}

		return isColliding;
	}
}