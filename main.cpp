#include <raylib.h>

int main()
{
	InitWindow(1024, 768, "Asteroids");

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}