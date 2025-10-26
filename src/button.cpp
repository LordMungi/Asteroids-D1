#include "button.h"
#include "render.h"

namespace button
{
	Button init(shape::Rectangle shape, std::string label)
	{
		Button button;

		button.label = label;
		button.shape = shape;
		button.isPressed = false;
		button.wasPressed = false;

		return button;
	}

	bool trigger(Button& button)
	{
		bool shouldTrigger;

		if (!button.isPressed && button.wasPressed)
			shouldTrigger = true;
		else
			shouldTrigger = false;

		button.wasPressed = button.isPressed;
		return shouldTrigger;
	}

	void draw(Button button)
	{
		if (button.isPressed)
			render::rectangle(button.shape, GRAY);
		else
			render::rectangle(button.shape, WHITE);

		render::text(button.label, button.shape.position, button.shape.size.y);
	}
}