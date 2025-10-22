#pragma once
#include "config.h"

namespace render
{
	void startWindow();
	void closeWindow();

	void rectangle(Vector2 pos, Vector2 size, Color color);
	void sprite(Texture2D texture, Vector2 pos, Vector2 size, float rotation);

	Vector2 getResFromGamespace(Vector2 gsPoint);
}