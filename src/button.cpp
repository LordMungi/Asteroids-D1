#include "button.h"
#include "render.h"
#include "math.h"
#include "collision.h"

namespace button
{
	Button init(shape::Rectangle shape, std::string label)
	{
		Button button;

		button.label = label;
		button.shape = shape;
		button.isPressed = false;
		button.wasPressed = false;
		button.isSelected = false;

		return button;
	}

	static bool trigger(Button& button);

	bool update(Button& button)
	{
		bool shouldTrigger = false;
		button.isSelected = coll::pointRectangle(math::getGamespacePointFromRes(GetMousePosition()), button.shape);

		if (button.isSelected)
		{			
			button.isPressed = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
			shouldTrigger = trigger(button);
		}
		else
		{
			button.isPressed = false;
			button.wasPressed = false;
		}
		return shouldTrigger;
	}

	static bool trigger(Button& button)
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
			render::rectangle(button.shape, RED);
		else if (button.isSelected)
			render::rectangle(button.shape, GRAY);
		else
			render::rectangle(button.shape, WHITE);
		render::text(button.label, button.shape.position, button.shape.size.y, BLACK);
	}
}