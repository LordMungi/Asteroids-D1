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
		case program::Scenes::Null:
			break;
		default:
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
		case program::Scenes::Null:
			break;
		default:
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
		case program::Scenes::Null:
			break;
		default:
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