#include "program.h"
#include <iostream>
#include <ctime>
#include "game.h"
#include "menu.h"
#include "render.h"
#include "settings.h"

namespace program
{


	screen::Type currentScene = screen::Type::Null;
	screen::Type previousScene = screen::Type::Null;

	static void init();
	static void update();
	static void draw();
	static void changeScene();
	static void close();

	void run()
	{
		init();

		while (!WindowShouldClose())
		{
			update();
			draw();

			if (currentScene != previousScene)
				changeScene();
		}
		
		close();
	}

	static void init()
	{
		srand(static_cast<int>(time(0)));
		render::startWindow();
		currentScene = screen::Type::Menu;
	}

	static void update()
	{
		switch (currentScene)
		{
		case screen::Type::Menu:
			currentScene = menu::update();
			break;
		case screen::Type::Game:
			currentScene = game::update();
			break;
		case screen::Type::Settings:
			currentScene = settings::update();
			break;
		}
	}

	static void draw()
	{
		switch (currentScene)
		{
		case screen::Type::Menu:
			menu::draw();
			break;
		case screen::Type::Game:
			game::draw();
			break;
		case screen::Type::Settings:
			settings::draw();
			break;
		}
	}
	
	static void changeScene()
	{
		switch (currentScene)
		{
		case screen::Type::Menu:
			menu::init();
			break;
		case screen::Type::Game:
			game::init();
			break;
		case screen::Type::Settings:
			settings::init();
			break;
		case screen::Type::Null:
			close();
			break;
		}

		previousScene = currentScene;
	}

	static void close()
	{
		game::unload();
		render::closeWindow();
	}
}