#include "slider.h"
#include <string>
#include "collision.h"
#include "math.h"
#include "render.h"

namespace slider
{
	Slider init(shape::Rectangle shape, float value)
	{
		Slider slider;
		slider.shape = shape;
		slider.value = value;

		slider.minPos = slider.shape.position.x - slider.shape.position.x / 3;
		slider.maxPos = slider.shape.position.x + slider.shape.position.x / 3;

		slider.ball = { slider.shape.position, slider.shape.size.y};
		slider.ball.position.x = (value * (slider.maxPos - (slider.shape.position.x - slider.shape.size.x / 2)) / 100) + slider.minPos;
		slider.isSelected = false;
		return slider;
	}

	void update(Slider& slider)
	{

		slider.isSelected = coll::pointCircle(math::getGamespacePointFromRes(GetMousePosition()), slider.ball);

		if (slider.isSelected && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			slider.ball.position.x = math::getGamespacePointFromRes(GetMousePosition()).x;

			if (slider.ball.position.x > slider.maxPos)
				slider.ball.position.x = slider.maxPos;

			if (slider.ball.position.x < slider.minPos)
				slider.ball.position.x = slider.minPos;

		}
		slider.value = 100 * (slider.ball.position.x - slider.minPos) / (slider.maxPos - (slider.shape.position.x - slider.shape.size.x / 2));
	}

	void draw(Slider slider)
	{
		render::rectangle(slider.shape, WHITE);
		render::circle(slider.ball, WHITE);
		//render::text(std::to_string(slider.value), slider.shape.position, slider.shape.size.y, BLUE);
	}
}