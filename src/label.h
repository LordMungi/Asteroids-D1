#pragma once
#include "shapes.h"
#include <string>
#include "render.h"

namespace label
{
	
	struct Label
	{
		std::string text;
		shape::Rectangle shape;
		render::TextAlign align;
		Color color;
	};

	Label init(std::string text, shape::Rectangle shape, render::TextAlign align, Color color);
	void updateText(Label& label, std::string text);
	void draw(Label label);
}