#include "settings.h"
#include "button.h"
#include "label.h"
#include "checkbox.h"
#include "slider.h"
#include "config.h"

namespace settings
{
	const int maxResolutions = 7;
	Vector2 resolutions[maxResolutions] =
	{
		{ 640, 480 },
		{ 1024, 768 },
		{ 1280, 720 },
		{ 1600, 900 },
		{ 1920, 1080 },
		{ 2560, 1440 },
		{ 3840, 2160 }
	};

	enum class Buttons
	{
		ResolutionLeft,
		ResolutionRight,
		Default,
		Apply,
		Exit,
	};
	const int maxButtons = 5;
	button::Button buttons[maxButtons];

	enum class Labels
	{
		Title,
		Resolution,
		ResValue,
		Fullscreen,
		Volume,
		Music
	};
	const int maxLabels = 6;
	label::Label labels[maxLabels];

	enum class Checkboxes
	{
		Fullscreen,
		Music
	};
	const int maxCheckboxes = 2;
	checkbox::Checkbox checkboxes[maxCheckboxes];

	slider::Slider volumeSlider;

	screen::Type nextScreen;

	int newRes = 1;
	bool shouldFullscreen = false;
	bool shouldMusic = config::music;

	static void applySettings();
	static void defaultSettings();

	void init()
	{

		Vector2 position = { 10,10 };
		Vector2 position2 = position;
		Vector2 size = { 10,10 };
		float separation = 5;
		float margin = 5;

		labels[static_cast<int>(Labels::Title)] = label::init("Settings", { position, size }, render::TextAlign::Left, WHITE);
		position2 = { config::gamespace.x - size.x - margin, position.y };
		buttons[static_cast<int>(Buttons::Exit)] = button::init({ position2, size }, "X");
		position.y += size.y + separation;


		size = { 7, 7 };
		labels[static_cast<int>(Labels::Resolution)] = label::init("Resolution", { position, size }, render::TextAlign::Left, WHITE);

		position2 = { 50, position.y };
		buttons[static_cast<int>(Buttons::ResolutionLeft)] = button::init({ position2, size }, "<");
		position2 = { 75, position.y };
		labels[static_cast<int>(Labels::ResValue)] = label::init(std::to_string(static_cast<int>(resolutions[newRes].x)) + "x" + std::to_string(static_cast<int>(resolutions[newRes].y)), { position2, size }, render::TextAlign::Center, WHITE);
		position2 = { 100, position.y };
		buttons[static_cast<int>(Buttons::ResolutionRight)] = button::init({ position2, size }, ">");

		position.y += size.y + separation;
		labels[static_cast<int>(Labels::Fullscreen)] = label::init("Fullscreen", { position, size }, render::TextAlign::Left, WHITE);
		position2 = { 50, position.y };
		checkboxes[static_cast<int>(Checkboxes::Fullscreen)] = checkbox::init({ position2, size }, shouldFullscreen);
		position.y += size.y + separation;

		labels[static_cast<int>(Labels::Volume)] = label::init("Volume", { position, size }, render::TextAlign::Left, WHITE);
		position2 = { 72, position.y };
		volumeSlider = slider::init({ position2, {50, 3} }, config::volume);
		position.y += size.y + separation;

		labels[static_cast<int>(Labels::Music)] = label::init("Music", { position, size }, render::TextAlign::Left, WHITE);
		position2 = { 50, position.y };
		checkboxes[static_cast<int>(Checkboxes::Music)] = checkbox::init({ position2, size }, shouldMusic);
		position.y += size.y + separation;

		size = { 30, 8 };
		position2 = { config::gamespace.x - size.x / 2 - margin, config::gamespace.y - size.y / 2 - margin };
		buttons[static_cast<int>(Buttons::Apply)] = button::init({ position2, size }, "Apply");
		position2.x -= size.x + separation;
		buttons[static_cast<int>(Buttons::Default)] = button::init({ position2, size }, "Default");

	}

	screen::Type update()
	{
		nextScreen = screen::Type::Settings;

		// Resolution
		if (button::update(buttons[static_cast<int>(Buttons::ResolutionLeft)]))
		{
			newRes--;
			if (newRes < 0)
				newRes = maxResolutions - 1;
			while (resolutions[newRes].y > GetMonitorHeight(GetCurrentMonitor()))
				newRes--;
		}
		if (button::update(buttons[static_cast<int>(Buttons::ResolutionRight)]))
		{
			newRes++;
			while (resolutions[newRes].y > GetMonitorHeight(GetCurrentMonitor()))
				newRes++;

			if (newRes >= maxResolutions)
				newRes = 0;
		}
		label::updateText(labels[static_cast<int>(Labels::ResValue)], std::to_string(static_cast<int>(resolutions[newRes].x)) + "x" + std::to_string(static_cast<int>(resolutions[newRes].y)));

		shouldFullscreen = checkbox::update(checkboxes[static_cast<int>(Checkboxes::Fullscreen)]);
		shouldMusic = checkbox::update(checkboxes[static_cast<int>(Checkboxes::Music)]);

		slider::update(volumeSlider);

		if (button::update(buttons[static_cast<int>(Buttons::Apply)]))
			applySettings();

		if (button::update(buttons[static_cast<int>(Buttons::Default)]))
			defaultSettings();

		if (button::update(buttons[static_cast<int>(Buttons::Exit)]))
			nextScreen = screen::Type::Menu;

		return nextScreen;
	}

	void draw()
	{
		BeginDrawing();
		ClearBackground(BLACK);

		for (int i = 0; i < maxButtons; i++)
		{
			button::draw(buttons[i]);
		}
		for (int i = 0; i < maxLabels; i++)
		{
			label::draw(labels[i]);
		}
		for (int i = 0; i < maxCheckboxes; i++)
		{
			checkbox::draw(checkboxes[i]);
		}
		slider::draw(volumeSlider);

		EndDrawing();
	}

	static void applySettings()
	{
		if (shouldFullscreen)
			config::res = { static_cast<float>(GetMonitorWidth(GetCurrentMonitor())), static_cast<float>(GetMonitorHeight(GetCurrentMonitor())) };
		else
			config::res = resolutions[newRes];

		if (shouldFullscreen != IsWindowFullscreen())
			ToggleFullscreen();

		config::volume = volumeSlider.value;

		render::closeWindow();
		render::startWindow();

		init();
	}

	static void defaultSettings()
	{
		newRes = 1;
		shouldFullscreen = false;
		shouldMusic = true;
		volumeSlider.value = 50;
		applySettings();
	}
}