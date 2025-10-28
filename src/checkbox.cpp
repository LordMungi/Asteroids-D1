#include "checkbox.h"
#include "collision.h"
#include "render.h"
#include "math.h"

namespace checkbox
{
	Checkbox init(shape::Rectangle shape, bool isChecked)
	{
		Checkbox checkbox;
		checkbox.shape = shape;
		checkbox.isSelected = false;
		checkbox.isChecked = isChecked;
		return checkbox;
	}

	bool update(Checkbox& checkbox)
	{
		checkbox.isSelected = coll::pointRectangle(math::getGamespacePointFromRes(GetMousePosition()), checkbox.shape);

		if (checkbox.isSelected && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			checkbox.isChecked = !checkbox.isChecked;
		return checkbox.isChecked;
	}

	void draw(Checkbox& checkbox)
	{
		render::rectangle(checkbox.shape, WHITE);
		render::rectangle({checkbox.shape.position, {checkbox.shape.size.x - 1, checkbox.shape.size.y - 1}}, BLACK);
		if (checkbox.isChecked)
			render::rectangle({ checkbox.shape.position, {checkbox.shape.size.x - 2, checkbox.shape.size.y - 2} }, WHITE);

	}
}