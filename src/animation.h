#pragma once
#include <raylib.h>

namespace anim
{
	struct Animation
	{
		int length;
		int currentFrame;
		Texture2D frames[10];
	};

	Animation init(int length);
	void unload(Animation& animation);
}