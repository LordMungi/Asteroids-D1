#include "program.h"
#include <iostream>
#include <ctime>
#include "game.h"
#include "menu.h"
#include "render.h"
#include "settings.h"
#include "credits.h"

namespace program
{
	Music menuBGM;
	Music gameBGM;

	screen::Type currentScene = screen::Type::Null;
	screen::Type previousScene = screen::Type::Null;

	static void init();
	static void update();
	static void bgm();
	static void draw();
	static void changeScene();
	static void close();

	void run()
	{
		init();

		while (!WindowShouldClose())
		{
			update();
			bgm();
			draw();

			if (currentScene != previousScene)
				changeScene();
		}
		
		close();
	}

	static void init()
	{
		srand(static_cast<int>(time(0)));
		InitAudioDevice();
		render::startWindow();
		currentScene = screen::Type::Menu;

		gameBGM = LoadMusicStream("resources/music/DjPengu_loop.wav");
		menuBGM = LoadMusicStream("resources/music/winter_scenery.mp3");
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
		case screen::Type::Credits:
			currentScene = credits::update();
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
		case screen::Type::Credits:
			credits::draw();
			break;

		}
	}

	static void bgm()
	{
		if (currentScene == screen::Type::Game)
			UpdateMusicStream(gameBGM);
		else
			UpdateMusicStream(menuBGM);
	}
	
	static void changeScene()
	{
		switch (currentScene)
		{
		case screen::Type::Menu:
			menu::init();
			PlayMusicStream(menuBGM);
			break;
		case screen::Type::Game:
			PlayMusicStream(gameBGM);
			game::init();
			break;
		case screen::Type::Settings:
			PlayMusicStream(menuBGM);
			settings::init();
			break;
		case screen::Type::Credits:
			PlayMusicStream(menuBGM);
			credits::init();
			break;
		case screen::Type::Null:
			close();
			break;
		}

		previousScene = currentScene;
	}

	static void close()
	{
		UnloadMusicStream(gameBGM);
		UnloadMusicStream(menuBGM);
		CloseAudioDevice();
		game::unload();
		render::closeWindow();
	}
}