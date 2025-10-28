#include "render.h"
#include <iostream>
#include "config.h"

namespace render
{
	double lastFrameUpdate;
	double fps = 0.08;
	int currentFrame;
	bool updatedThisFrame;

	static Vector2 res = { 1024, 768 };

	static void setGamespaceFromRes();

	void startWindow()
	{
		InitWindow(static_cast<int>(res.x), static_cast<int>(res.y), "Asteroids");
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
		Vector2 resPos = getResPointFromGamespace(rectangle.position);
		Vector2 resSize = getResPointFromGamespace(rectangle.size);

		DrawRectangle(static_cast<int>(resPos.x - resSize.x / 2), static_cast<int>(resPos.y - resSize.y / 2), static_cast<int>(resSize.x), static_cast<int>(resSize.y), color);
	}

	void circle(shape::Circle circle, Color color)
	{
		Vector2 resPos = getResPointFromGamespace(circle.position);
		float resRadius = getResValueFromGamespace(circle.radius);

		DrawCircle(static_cast<int>(resPos.x), static_cast<int>(resPos.y), resRadius, color);
	}

	void sprite(Texture2D texture, shape::Rectangle rectangle, float rotation)
	{
		Vector2 resPos = getResPointFromGamespace(rectangle.position);
		Vector2 resSize = getResPointFromGamespace(rectangle.size);

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
		Vector2 resPos = getResPointFromGamespace(circle.position);
		float resRadius = getResValueFromGamespace(circle.radius);

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

	void text(std::string text, Vector2 position, float size)
	{
		position = getResPointFromGamespace(position);
		size = getResValueFromGamespace(size);

		position.y -= size / 2;
		position.x -= MeasureText(text.c_str(), static_cast<int>(size)) / 2;
		DrawText(text.c_str(), static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(size), RED);
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
		config::gamespace.x = res.x * config::gamespace.y / res.y;
	}


	Vector2 getResPointFromGamespace(Vector2 gsPoint)
	{
		Vector2 resPoint;
		resPoint.x = gsPoint.x * res.x / config::gamespace.x;
		resPoint.y = gsPoint.y * res.y / config::gamespace.y;
		return resPoint;
	}
	float getResValueFromGamespace(float value)
	{
		return value * res.y / config::gamespace.y;
	}

	Vector2 getGamespacePointFromRes(Vector2 resPoint)
	{
		Vector2 gsPoint;
		gsPoint.x = resPoint.x * config::gamespace.x / res.x;
		gsPoint.y = resPoint.y * config::gamespace.y / res.y;
		return gsPoint;
	}


}