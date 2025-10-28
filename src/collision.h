#pragma once
#include "shapes.h"

namespace coll
{
	bool circleCircle(shape::Circle circle1, shape::Circle circle2);
	void correctCircleCircle(shape::Circle& circle1, shape::Circle circle2);
	bool pointRectangle(Vector2 point, shape::Rectangle rectangle);
	bool pointCircle(Vector2 point, shape::Circle circle);
}