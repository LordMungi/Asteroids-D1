#pragma once
#include "shapes.h"
#include <string>

namespace button
{
	struct Button
	{
		std::string label;
		shape::Rectangle shape;
		bool wasPressed;
		bool isPressed;
	};

	Button init(shape::Rectangle shape, std::string label);
	bool trigger(Button& button);
	void draw(Button button);
}