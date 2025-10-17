#include "draw.h"

int main()
{
	InitWindow((int)config::res.x, (int)config::res.y, "Asteroids");
	config::setGamespaceFromRes();

	Vector2 size = { 10, 10 };
	Vector2 pos = { 1, config::gamespace.y / 2 - size.y / 2 };
	while (!WindowShouldClose())
	{
		pos.x += 50 * GetFrameTime();
		if (pos.x > config::gamespace.x) pos.x = 0;

		BeginDrawing();
		ClearBackground(BLACK);
		draw::rectangle(pos, size, WHITE);
		EndDrawing();
	}


	CloseWindow();
}