#include "settings.h"
#include "button.h"

namespace settings
{
	enum class Buttons
	{
		ResolutionLeft,
		ResolutionRight,
		Default,
		Exit
	};

	const int maxButtons = 4;
	button::Button buttons[maxButtons];

	void init()
	{
		//Vector2 position;
		//Vector2 size;
		//float separation;




	}
}