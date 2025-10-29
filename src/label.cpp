#include "label.h"

namespace label
{
	Label init(std::string text, shape::Rectangle shape, render::TextAlign align, Color color)
	{
		Label label;
		label.text = text;
		label.shape = shape;
		label.align = align;
		label.color = color;
		return label;
	}

	void updateText(Label& label, std::string text)
	{
		label.text = text;
	}

	void draw(Label label)
	{
		//render::rectangle(label.shape, { 255, 255, 255, 100 });
		render::text(label.text, label.shape.position, label.shape.size, label.color, label.align);
	}
}