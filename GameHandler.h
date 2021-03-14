#pragma once
#include "Menu.h"
#include "Info.h"
#include "game.h"
#include "graphics.h"
#include <queue>

class GameHandler {
	Menu* mymenu = nullptr;
	Info* info = nullptr;
	Game* game = nullptr;

	//CREDITS, HOW TO PLAY queue with text
	std::queue <std::string> textQueue;

	graphics::MouseState mouse;
	bool gameToDelete = false;
	bool infoBackToMenu, gameBackToMenu;
public:
	void update();
	void draw();
	void init();
	GameHandler();
	~GameHandler();
};
