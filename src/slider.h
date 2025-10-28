#pragma once
#include "shapes.h"

namespace slider
{
	struct Slider
	{
		shape::Rectangle shape;
		shape::Circle ball;
		float value;
		bool isSelected;
		float minPos;
		float maxPos;
	};

	Slider init(shape::Rectangle shape, float value);
	void update(Slider& slider);
	void draw(Slider slider);
}