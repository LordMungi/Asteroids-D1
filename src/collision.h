#pragma once
#include "shapes.h"

namespace coll
{
	bool circleCircle(shape::Circle circle1, shape::Circle circle2);
	void correctCircleCircle(shape::Circle& circle1, shape::Circle circle2);
}