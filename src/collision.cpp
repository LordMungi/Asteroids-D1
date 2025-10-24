#include "collision.h"
#include <cmath>

namespace coll
{
	bool circleCircle(shape::Circle circle1, shape::Circle circle2)
	{
		Vector2 distance;

		distance.x = circle1.position.x - circle2.position.x;
		distance.y = circle1.position.y - circle2.position.y;
		
		float distVector = (distance.x * distance.x) + (distance.y * distance.y);
		
		return distVector <= (circle1.radius + circle2.radius)*(circle1.radius + circle2.radius);
	}

	void correctCircleCircle(shape::Circle& circle1, shape::Circle circle2)
	{
		Vector2 distance;
		distance.x = circle1.position.x - circle2.position.x;
		distance.y = circle1.position.y - circle2.position.y;

		float angle = atan(distance.y / distance.x) * (180 / PI);
		if (distance.x < 0)
			angle += 180;
		else if (distance.y < 0)
			angle += 360;

		float distVector = circle1.radius + circle2.radius;

		circle1.position.x = circle2.position.x + (distVector * cos(angle * (PI / 180)));
		circle1.position.y = circle2.position.y + (distVector * sin(angle * (PI / 180)));
	}
}