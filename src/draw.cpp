#include "draw.h"

namespace draw
{
	static Vector2 getResFromGamespace(Vector2 gsPoint)
	{
		Vector2 resPoint;
		resPoint.x = gsPoint.x * config::res.x / config::gamespace.x;
		resPoint.y = gsPoint.y * config::res.y / config::gamespace.y;
		return resPoint;
	}

	void rectangle(Vector2 pos, Vector2 size, Color color)
	{
		Vector2 resPos = getResFromGamespace(pos);
		Vector2 resSize = getResFromGamespace(size);

		DrawRectangle(static_cast<int>(resPos.x), static_cast<int>(resPos.y), static_cast<int>(resSize.x), static_cast<int>(resSize.y), color);
	}
}