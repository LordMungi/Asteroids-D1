#include "render.h"
#include <iostream>
#include "config.h"
#include "math.h"

namespace render
{
	double lastFrameUpdate;
	double fps = 0.08;
	int currentFrame;
	bool updatedThisFrame;


	static void setGamespaceFromRes();

	void startWindow()
	{
		InitWindow(static_cast<int>(config::res.x), static_cast<int>(config::res.y), "Asteroids");
		SetExitKey(KEY_NULL);
		setGamespaceFromRes();
	}

	void closeWindow()
	{
		CloseWindow();
	}


	void updateFrame() 
	{
		updatedThisFrame = false;
		if (GetTime() - lastFrameUpdate > fps)
		{
			currentFrame++;
			updatedThisFrame = true;
			lastFrameUpdate = GetTime();
		}
	}

	void rectangle(shape::Rectangle rectangle, Color color)
	{
		Vector2 resPos = math::getResPointFromGamespace(rectangle.position);
		Vector2 resSize = math::getResPointFromGamespace(rectangle.size);

		DrawRectangle(static_cast<int>(resPos.x - resSize.x / 2), static_cast<int>(resPos.y - resSize.y / 2), static_cast<int>(resSize.x), static_cast<int>(resSize.y), color);
	}

	void circle(shape::Circle circle, Color color)
	{
		Vector2 resPos = math::getResPointFromGamespace(circle.position);
		float resRadius = math::getResValueFromGamespace(circle.radius);

		DrawCircle(static_cast<int>(resPos.x), static_cast<int>(resPos.y), resRadius, color);
	}

	void sprite(Texture2D texture, shape::Rectangle rectangle, float rotation)
	{
		Vector2 resPos = math::getResPointFromGamespace(rectangle.position);
		Vector2 resSize = math::getResPointFromGamespace(rectangle.size);

		Rectangle source;
		source.x = 0;
		source.y = 0;
		source.width = static_cast<float>(texture.width);
		source.height = static_cast<float>(texture.height);

		Rectangle dest;
		dest.x = resPos.x;
		dest.y = resPos.y;
		dest.width = resSize.x;
		dest.height = resSize.y;

		Vector2 origin;
		origin.x = resSize.x / 2;
		origin.y = resSize.y / 2;

		DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
	}

	void sprite(Texture2D texture, shape::Circle circle, float rotation)
	{
		Vector2 resPos = math::getResPointFromGamespace(circle.position);
		float resRadius = math::getResValueFromGamespace(circle.radius);

		Rectangle source;
		source.x = 0;
		source.y = 0;
		source.width = static_cast<float>(texture.width);
		source.height = static_cast<float>(texture.height);

		Rectangle dest;
		dest.x = resPos.x;
		dest.y = resPos.y;
		dest.width = resRadius * 2;
		dest.height = resRadius * 2;

		Vector2 origin;
		origin.x = resRadius;
		origin.y = resRadius;

		DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
	}

	void text(std::string text, Vector2 position, float size, Color color)
	{
		position = math::getResPointFromGamespace(position);
		size = math::getResValueFromGamespace(size);

		position.y -= size / 2;
		position.x -= MeasureText(text.c_str(), static_cast<int>(size)) / 2;
		DrawText(text.c_str(), static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(size), color);
	}
	void text(std::string text, Vector2 position, Vector2 size, Color color, TextAlign align)
	{
		position = math::getResPointFromGamespace(position);
		size = math::getResPointFromGamespace(size);

		Vector2 textPosition = position;

		switch (align)
		{
		case render::TextAlign::Left:
			textPosition.x = position.x - size.x / 2;
			break;
		case render::TextAlign::Right:
			textPosition.x = position.x + size.x / 2 - MeasureText(text.c_str(), static_cast<int>(size.y));
			break;
		case render::TextAlign::Center:
			textPosition.x -= MeasureText(text.c_str(), static_cast<int>(size.y)) / 2;
			break;
		}
		textPosition.y -= size.y / 2;

		DrawText(text.c_str(), static_cast<int>(textPosition.x), static_cast<int>(textPosition.y), static_cast<int>(size.y), color);
	}

	void animation(anim::Animation& animation, shape::Rectangle rectangle, float rotation)
	{
		if(animation.length > 0)
			sprite(animation.frames[currentFrame % animation.length], rectangle, rotation);
		
	}

	void oneshot(anim::Animation& animation, shape::Rectangle rectangle, float rotation)
	{
		if (animation.currentFrame < animation.length)
		{
			sprite(animation.frames[animation.currentFrame], rectangle, rotation);
			if (updatedThisFrame)
				animation.currentFrame++;
		}
	}

	static void setGamespaceFromRes()
	{
		config::gamespace.y = 100;
		config::gamespace.x = config::res.x * config::gamespace.y / config::res.y;
	}
}