#include "GameHandler.h"
#include "graphics.h"
#include "constants.h"
#include "util.h"

void GameHandler::update()
{
	// actions on menu tab, transition to other tabs (game,info)
	if (mymenu) {
		mymenu->update();

		//get input from mouse
		graphics::getMouseState(mouse);

		if (mouse.button_left_pressed) {
			// action for "PVP" button
			if (clickButtonValidity(window2canvasX((float)mouse.cur_pos_x), window2canvasY((float)mouse.cur_pos_y), 125.0f, 194.167f, 400.833f, 600)) {
				delete mymenu;
				mymenu = nullptr;
				//make the game
				game = new Game(false);
			}
			//action for "PLAYER VS AI" button
			if (clickButtonValidity(window2canvasX((float)mouse.cur_pos_x), window2canvasY((float)mouse.cur_pos_y), 215.0f, 284.167f, 400.833f, 600)) {
				delete mymenu;
				mymenu = nullptr;
				//make the game vs AI
				game = new Game(true);
			}
			//action for "HOW TO PLAY" button
			if (clickButtonValidity(window2canvasX((float)mouse.cur_pos_x), window2canvasY((float)mouse.cur_pos_y), 305.0f, 374.167f, 400.833f, 600)) {
				graphics::playSound(click, 0.5f);
				delete mymenu;
				mymenu = nullptr;

				while (!textQueue.empty()) textQueue.pop();

				textQueue.push(std::string(HTP_0));
				textQueue.push(std::string(HTP_1));
				textQueue.push(std::string(HTP_2));
				textQueue.push(std::string(HTP_3));
				textQueue.push(std::string(HTP_4));
				textQueue.push(std::string(HTP_5));
				textQueue.push(std::string(HTP_6));
				textQueue.push(std::string(HTP_7));
				textQueue.push(std::string(HTP_8));
				textQueue.push(std::string(HTP_9));
				textQueue.push(std::string(HTP_10));
				info = new Info(145, 40, 20, textQueue, false);
			}
			//action for "CREDITS" button
			if (clickButtonValidity(window2canvasX((float)mouse.cur_pos_x), window2canvasY((float)mouse.cur_pos_y), 395.0f, 464.167f, 400.833f, 600)) {
				graphics::playSound(click, 0.5f);
				delete mymenu;
				mymenu = nullptr;

				while (!textQueue.empty()) textQueue.pop();
			
				textQueue.push(std::string(TEXT_1));
				textQueue.push(std::string(TEXT_2));
				textQueue.push(std::string(TEXT_3));
				info = new Info(154, 150, 30, textQueue, false);
			}
		}
	}

	//transition from info back to menu (HTP, CREDITS)
	if (info){
		info->update();

		infoBackToMenu = false;
		if (graphics::getKeyState(graphics::SCANCODE_BACKSPACE)) {
			infoBackToMenu = true;
		}

		graphics::getMouseState(mouse);
		if (mouse.button_left_pressed || infoBackToMenu) {
			if (clickBackButtonValidity(window2canvasX((float)mouse.cur_pos_x), window2canvasY((float)mouse.cur_pos_y)) || infoBackToMenu) {
				infoBackToMenu = false;
				graphics::playSound(click, 0.5f);
				delete info;
				info = nullptr;
				mymenu = new Menu();
			}
		}
	}
	//transition from game back to menu
	if (game) {
		game->update();

		gameBackToMenu = false;
		if (graphics::getKeyState(graphics::SCANCODE_BACKSPACE)) {
			gameBackToMenu = true;
		}

		graphics::getMouseState(mouse);
		if (mouse.button_left_pressed || gameBackToMenu) {
			if (clickBackButtonValidity(window2canvasX((float)mouse.cur_pos_x), window2canvasY((float)mouse.cur_pos_y)) || gameBackToMenu) {
				gameBackToMenu = false;
				graphics::playSound(click, 0.5f);
				delete game;
				game = nullptr;
				mymenu = new Menu();
			}
		}
	}

	//end of game when someone scores 5 goals
	if (game) {
		if (game->getGoalsPlayer1() == 5) {
			gameToDelete = true;

			graphics::playSound(std::string(ASSET_PATH) + std::string(END), 0.5f);
			while (!textQueue.empty()) textQueue.pop();
			textQueue.push(std::string(END_1));
			textQueue.push(std::string(END_3));
			info = new Info(50, 150, 25, textQueue, true);
		}
		if (game->getGoalsPlayer2() == 5) {
			gameToDelete = true;

			graphics::playSound(std::string(ASSET_PATH) + std::string(END), 0.5f);
			while (!textQueue.empty()) textQueue.pop();
			textQueue.push(std::string(END_2));
			textQueue.push(std::string(END_3));
			info = new Info(50, 150, 25, textQueue, true);
		}
		if (gameToDelete) {
			delete game;
			game = nullptr;
			gameToDelete = false;
		}
	}
}

void GameHandler::draw()
{
	if (mymenu) {
		mymenu->draw();
	}
	if (info) {
		info->draw();
	}
	if (game) {
		game->draw();
	}
}

void GameHandler::init()
{
	if (mymenu) {
		mymenu->init();
	}
}

GameHandler::GameHandler()
{
	mymenu = new Menu();
}

GameHandler::~GameHandler()
{
	if (mymenu) {
		delete mymenu; mymenu = nullptr;
	}
	if (info) {
		delete info; info = nullptr;
	}
	if (game) {
		delete game; game = nullptr;
	}
}
