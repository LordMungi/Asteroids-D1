#pragma once
#include "shapes.h"

namespace render
{
	void startWindow();
	void closeWindow();

	void rectangle(shape::Rectangle rectangle, Color color);
	void circle(shape::Circle circle, Color color);
	void sprite(Texture2D texture, shape::Rectangle rectangle, float rotation);
	void sprite(Texture2D texture, shape::Circle circle, float rotation);

	Vector2 getResPointFromGamespace(Vector2 gsPoint);
	float getResValueFromGamespace(float value);
}