#pragma once
#include "shapes.h"
#include <string>

namespace render
{
	void startWindow();
	void closeWindow();

	void rectangle(shape::Rectangle rectangle, Color color);
	void circle(shape::Circle circle, Color color);
	void sprite(Texture2D texture, shape::Rectangle rectangle, float rotation);
	void sprite(Texture2D texture, shape::Circle circle, float rotation);
	void text(std::string text, Vector2 position, float size);

	Vector2 getResPointFromGamespace(Vector2 gsPoint);
	float getResValueFromGamespace(float value);
	Vector2 getGamespacePointFromRes(Vector2 resPoint);
}