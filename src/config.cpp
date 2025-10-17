#include "config.h"

namespace config
{
	Vector2 res = { 1024, 768 };
	Vector2 gamespace;

	void setGamespaceFromRes()
	{
		gamespace.y = 100;
		gamespace.x = res.x * gamespace.y / res.y;
	}
}