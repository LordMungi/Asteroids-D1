#pragma once
#include "shapes.h"
#include "animation.h"
#include <string>

namespace render
{
	enum class TextAlign
	{
		Left,
		Right,
		Center
	};

	void startWindow();
	void closeWindow();

	void updateFrame();

	void rectangle(shape::Rectangle rectangle, Color color);
	void circle(shape::Circle circle, Color color);
	void sprite(Texture2D texture, shape::Rectangle rectangle, float rotation);
	void sprite(Texture2D texture, shape::Circle circle, float rotation);
	void animation(anim::Animation& animation, shape::Rectangle rectangle, float rotation);
	void oneshot(anim::Animation& animation, shape::Rectangle rectangle, float rotation);
	void text(std::string text, Vector2 position, float size, Color color);
	void text(std::string text, Vector2 position, Vector2 size, Color color, TextAlign align);
}