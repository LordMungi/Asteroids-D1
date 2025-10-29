#pragma once
#include "shapes.h"
#include <string>
#include "render.h"

namespace label
{
	
	struct Label
	{
		std::string text = "";
		shape::Rectangle shape = { {} };
		render::TextAlign align = render::TextAlign::Center;
		Color color = WHITE;
	};

	Label init(std::string text, shape::Rectangle shape, render::TextAlign align, Color color);
	void updateText(Label& label, std::string text);
	void draw(Label label);
}