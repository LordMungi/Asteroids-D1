#pragma once
#include "screens.h"

namespace pause
{
	enum class DoNext
	{
		Resume,
		Exit,
		Null
	};

	void init();
	DoNext update();
	void draw();
}