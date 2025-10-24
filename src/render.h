#pragma once
#include "shapes.h"

namespace render
{
	void startWindow();
	void closeWindow();

	void rectangle(Vector2 pos, Vector2 size, Color color);
	void circle(Vector2 pos, float radius, Color color);
	void sprite(Texture2D texture, Vector2 pos, Vector2 size, float rotation);

	Vector2 getResPointFromGamespace(Vector2 gsPoint);
	float getResValueFromGamespace(float value);
}