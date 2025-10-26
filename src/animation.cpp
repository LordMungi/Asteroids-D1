#include "animation.h"

namespace anim
{
	Animation init(int length)
	{
		Animation animation;
		animation.length = length;
		animation.currentFrame = 0;
		return animation;
	}

	void unload(Animation& animation)
	{
		for (int i = 0; i < animation.length; i++)
		{
			UnloadTexture(animation.frames[i]);
		}
	}
}