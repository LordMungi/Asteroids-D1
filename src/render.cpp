#include "render.h"

namespace render
{
	static Vector2 res = { 1024, 768 };

	static void setGamespaceFromRes()
	{
		config::gamespace.y = 100;
		config::gamespace.x = res.x * config::gamespace.y / res.y;
	}

	static Vector2 getResFromGamespace(Vector2 gsPoint)
	{
		Vector2 resPoint;
		resPoint.x = gsPoint.x * res.x / config::gamespace.x;
		resPoint.y = gsPoint.y * res.y / config::gamespace.y;
		return resPoint;
	}

	void startWindow()
	{
		InitWindow(static_cast<int>(res.x), static_cast<int>(res.y), "Asteroids");
		setGamespaceFromRes();
	}

	void closeWindow()
	{
		CloseWindow();
	}

	void rectangle(Vector2 pos, Vector2 size, Color color)
	{
		Vector2 resPos = getResFromGamespace(pos);
		Vector2 resSize = getResFromGamespace(size);

		DrawRectangle(static_cast<int>(resPos.x), static_cast<int>(resPos.y), static_cast<int>(resSize.x), static_cast<int>(resSize.y), color);
	}
}