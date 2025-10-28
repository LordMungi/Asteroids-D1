#include "checkbox.h"
#include "collision.h"
#include "render.h"

namespace checkbox
{
	Checkbox init(shape::Rectangle shape)
	{
		Checkbox checkbox;
		checkbox.shape = shape;
		checkbox.isSelected = false;
		checkbox.isChecked = false;
		return checkbox;
	}

	bool update(Checkbox& checkbox)
	{
		checkbox.isSelected = coll::pointRectangle(render::getGamespacePointFromRes(GetMousePosition()), checkbox.shape);

		if (checkbox.isSelected && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			checkbox.isChecked = !checkbox.isChecked;
		return checkbox.isChecked;
	}
}