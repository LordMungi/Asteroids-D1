#include "random.h"
#include <iostream>

namespace random
{
	bool coinFlip()
	{
		return rand() % 2;
	}

	int intRange(int min, int max)
	{
		int range = max + 1 - min;
		return rand() % range + min;
	}

	float floatRange(int min, int max)
	{
		int range = max - min;
		return rand() % (range * 10000) / 10000.0f + min;
	}
}