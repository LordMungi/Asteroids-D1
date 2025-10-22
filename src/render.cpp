#include "render.h"

namespace render
{
	static Vector2 res = { 1024, 768 };

	static void setGamespaceFromRes();
	static void loadTextures();
	static void unloadTextures();

	namespace tex
	{
		static Texture2D ship;
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

	void sprite(Texture2D texture, Vector2 pos, Vector2 size, float rotation)
	{
		Vector2 resPos = getResFromGamespace(pos);
		Vector2 resSize = getResFromGamespace(size);

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

	static void setGamespaceFromRes()
	{
		config::gamespace.y = 100;
		config::gamespace.x = res.x * config::gamespace.y / res.y;
	}
	Vector2 getResFromGamespace(Vector2 gsPoint)
	{
		Vector2 resPoint;
		resPoint.x = gsPoint.x * res.x / config::gamespace.x;
		resPoint.y = gsPoint.y * res.y / config::gamespace.y;
		return resPoint;
	}
}