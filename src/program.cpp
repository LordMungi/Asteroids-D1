#include "program.h"
#include <iostream>
#include <ctime>
#include "game.h"
#include "render.h"

namespace program
{
	enum class Scenes
	{
		Menu,
		Game,
		Null
	};

	Scenes currentScene = Scenes::Null;
	Scenes previousScene = Scenes::Null;

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
		currentScene = Scenes::Game;
	}

	static void update()
	{
		switch (currentScene)
		{
		case program::Scenes::Menu:
			break;
		case program::Scenes::Game:
			game::update();
			break;
		}
	}

	static void draw()
	{
		switch (currentScene)
		{
		case program::Scenes::Menu:
			break;
		case program::Scenes::Game:
			game::draw();
			break;
		}
	}
	
	static void changeScene()
	{
		switch (currentScene)
		{
		case program::Scenes::Menu:
			break;
		case program::Scenes::Game:
			game::init();
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