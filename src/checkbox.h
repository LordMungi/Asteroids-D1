#pragma once
#include "shapes.h"

namespace checkbox
{
	struct Checkbox
	{
		shape::Rectangle shape;
		bool isSelected;
		bool isChecked;
	};

	Checkbox init(shape::Rectangle shape);
	bool update(Checkbox& checkbox);
	void draw(Checkbox& checkbox);
}