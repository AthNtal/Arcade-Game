#include "game.h"
#include "util.h"
#include "graphics.h"
#include "vecmath.h"
#include <algorithm>

void Game::update()
{
	musicAdjustment();
	checkBall();
	createBall();
	if (ball) {
		ball->update();
	}
	if (player1) {
		player1->update();
		if (ai) {
			player2->setBall(ball);
		}
		player2->update();
	}
	if (obstacle) {
		obstacle->update();
	}
	
	if (collisionObstAvailable) {
		if (checkObstCollision()) {
			ball->setObstCollision(true);
			collisionObstAvailable = false;
			timeUntilNextObstColl = graphics::getGlobalTime();
		}
	}

	if(collisionAvailable){
		if (checkP1Collision()) {
			ball->setRCollision(true, 1);
			collisionAvailable = false;
			timeUntilNextColl = graphics::getGlobalTime();
		}
			
		if (checkP2Collision()) {
			ball->setRCollision(true, 2);
			collisionAvailable = false;
			timeUntilNextColl = graphics::getGlobalTime();
		}
	}

	// this ensure us that the collision detection will not bug (first if statement is for the player, the second one is for the obstacle)
	if (graphics::getGlobalTime() - timeUntilNextColl > 500) {
		collisionAvailable = true;
	}
	if (graphics::getGlobalTime() - timeUntilNextObstColl > 500) {
		collisionObstAvailable = true;
	}

	if (!ai) {
		//for player on the left with buttons
		// action for "HIDE" button
		if (graphics::getKeyState(graphics::SCANCODE_1)) {
			if (hideOnce2 != 1) {
				hideOnce2 = 1;
				graphics::playSound(std::string(ASSET_PATH) + std::string(SIZEUP), 0.5f);
				ball->setHide(true);
			}
		}
		// action for "BOOST" button
		if (graphics::getKeyState(graphics::SCANCODE_2)) {
			if (boostOnce2 != 1) {
				boostOnce2 = 1;
				graphics::playSound(std::string(ASSET_PATH) + std::string(SIZEUP), 0.5f);
				ball->setSpeedUp(true);
			}
		}
		// action for "HEIGHT" button
		if (graphics::getKeyState(graphics::SCANCODE_3)) {
			if (heightOnce2 != 1) {
				heightOnce2 = 1;
				graphics::playSound(std::string(ASSET_PATH) + std::string(SIZEUP), 0.5f);
				player1->setHeightPB(true);
			}
		}

		//for player on the right with click 
		graphics::getMouseState(mouse);
		if (mouse.button_left_pressed) {
			// action for "HIDE" button
			if (clickButtonValidity(window2canvasX((float)mouse.cur_pos_x), window2canvasY((float)mouse.cur_pos_y), 15.833f, 43.33f, 671, 729)) {
				if (hideOnce != 1) {
					hideOnce = 1;
					graphics::playSound(std::string(ASSET_PATH) + std::string(SIZEUP), 0.5f);
					ball->setHide(true);
				}
			}
			// action for "BOOST" button
			if (clickButtonValidity(window2canvasX((float)mouse.cur_pos_x), window2canvasY((float)mouse.cur_pos_y), 15.833f, 43.33f, 735.833f, 794.167f)) {
				if (boostOnce != 1) {
					boostOnce = 1;
					graphics::playSound(std::string(ASSET_PATH) + std::string(SIZEUP), 0.5f);
					ball->setSpeedUp(true);
				}
			}
			// action for "HEIGHT" button
			if (clickButtonValidity(window2canvasX((float)mouse.cur_pos_x), window2canvasY((float)mouse.cur_pos_y), 15.833f, 43.33f, 801, 859.167f)) {
				if (heightOnce != 1) {
					heightOnce = 1;
					graphics::playSound(std::string(ASSET_PATH) + std::string(SIZEUP), 0.5f);
					player2->setHeightPB(true);
				}
			}
		}
	}
}

void Game::draw()
{
	//game background
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + std::string(INGAME);
	br.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_W / 2.0, CANVAS_H / 2.0, CANVAS_W, CANVAS_H, br);

	drawMusicButton(140, 450, true);
	drawBackButton();

	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	
	if (!ai) {
		//creating the buttons
		button_br.outline_opacity = 0.4f;
		button_br.gradient = false;
		button_br.fill_opacity = 0.1f;
		button_br.fill_color[0] = 0.0f;
		button_br.fill_color[1] = 0.0f;
		button_br.fill_color[2] = 0.0f;

		x_cord = 700;
		for (int i = 0; i < 3; i++) {
			//power up for p2
			graphics::drawRect(x_cord, 30, 60, 30, button_br);
			//power up for p1
			graphics::drawRect(x_cord - 600, 30, 60, 30, button_br);
			if (i == 0) {
				if (hideOnce == 1) br.fill_opacity = 0.1f;
				graphics::drawText(x_cord - 19, 30 + 5, 15, std::string(PBUTTON_1), br);
				br.fill_opacity = 1.0f;

				if (hideOnce2 == 1) br.fill_opacity = 0.1f;
				graphics::drawText(x_cord - 619, 30 + 5, 15, std::string(PBUTTON_1), br);
				br.fill_opacity = 1.0f;
			}
			else if (i == 1) {
				if (boostOnce == 1) br.fill_opacity = 0.1f;
				graphics::drawText(x_cord - 23, 30 + 5, 15, std::string(PBUTTON_2), br);
				br.fill_opacity = 1.0f;

				if (boostOnce2 == 1) br.fill_opacity = 0.1f;
				graphics::drawText(x_cord - 623, 30 + 5, 15, std::string(PBUTTON_2), br);
				br.fill_opacity = 1.0f;
			}
			else {
				if (heightOnce == 1) br.fill_opacity = 0.1f;
				graphics::drawText(x_cord - 29, 30 + 5, 15, std::string(PBUTTON_3), br);
				br.fill_opacity = 1.0f;

				if (heightOnce2 == 1) br.fill_opacity = 0.1f;
				graphics::drawText(x_cord - 629, 30 + 5, 15, std::string(PBUTTON_3), br);
				br.fill_opacity = 1.0f;
			}
			x_cord += 65;
		}
	}

	if (ball) {
		ball->draw();
		drawScore();
	}
	if (player1) {
		player1->draw();
		player2->draw();
	}
	if (obstacle) obstacle->draw();
}

void Game::drawScore()
{
	if (ball->getPlayerConcededGoal() == 1) {
		goalsPlayer2++;
		player1->reset();
		player2->reset();
	}
	if (ball->getPlayerConcededGoal() == 2) {
		goalsPlayer1++;
		player1->reset();
		player2->reset();
	}
	
	graphics::Brush br;
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	graphics::drawText(CANVAS_W / 2 - 200, 35, 25, "Score: " + std::to_string(goalsPlayer1) + " - " + std::to_string(goalsPlayer2), br);
}

void Game::checkBall()
{
	if (ball && !ball->isActive()) {
		delete ball;
		ball = nullptr;
	}
}

void Game::createBall()
{
	if (!ball) {
		//1vs1 mode performs lower than the ai mode so the ball must be faster to cover this
		if (ai) {
			ball = new Ball(*this, 6.0f);
			graphics::playSound(std::string(ASSET_PATH) + std::string(KICKOFF), 0.5f);
		}
		else {
			ball = new Ball(*this, 10.0f);
			graphics::playSound(std::string(ASSET_PATH) + std::string(KICKOFF), 0.5f);
		}
	}
}

bool Game::checkObstCollision()
{
	if (!obstacle || !ball) {
		return false;
	}
	Rect r1 = obstacle->getCollisionHull();
	Disk d1 = ball->getCollisionHull();
	float testX = d1.cx;
	float testY = d1.cy;

	if (d1.cx < r1.cx) {
		testX = r1.cx;
		angle = "left";
	}
	else if (d1.cx > r1.cx + r1.width) {
		testX = r1.cx + r1.width;
		angle = "right";
	}

	if (d1.cy < r1.cy - 30) {
		testY = r1.cy - 30;
		angle = "top";
	}
	else if (d1.cy > r1.cy - 30 + r1.height) {
		testY = r1.cy - 30 + r1.height;
		angle = "bottom";
	}

	float distX = d1.cx - testX;
	float distY = d1.cy - testY;
	float distance =sqrt((distX * distX) + (distY * distY));
	if (distance <= d1.radius) {
		ball->setAngle(angle);
		return true;
	}
	else {
		return false;
	}
}

bool Game::checkP1Collision()
{
	if (!player1 || !ball ) {
		return false;
	}
	Disk d1 = ball->getCollisionHull();
	Rect r1 = player1->getCollisionHull();

	float testX = d1.cx;
	float testY = d1.cy ;

	if (d1.cx < r1.cx) {
		testX = r1.cx;
	}
	else if (d1.cx > r1.cx + r1.width) {
		testX = r1.cx + r1.width;
	}

	if (d1.cy < r1.cy - 30) {
		testY = r1.cy - 30;
	}
	else if (d1.cy > r1.cy - 30 + r1.height) {
		testY = r1.cy - 30 + r1.height;
	}

	float distX = d1.cx - testX;
	float distY = d1.cy - testY;
	float distance =sqrt((distX * distX) + (distY * distY));
	if (distance <= d1.radius) {
		return true;
	}
	else {
		return false;
	}
}

bool Game::checkP2Collision()
{
	if (!player2 || !ball) {
		return false;
	}
	Disk d1 = ball->getCollisionHull();
	Rect r1 = player2->getCollisionHull();

	float testX = d1.cx;
	float testY = d1.cy;

	if (d1.cx < r1.cx) {
		testX = r1.cx;
	}
	else if (d1.cx > r1.cx + r1.width) {
		testX = r1.cx + r1.width;
	}

	if (d1.cy < r1.cy - 30) {
		testY = r1.cy - 30;
	}
	else if (d1.cy > r1.cy - 30 + r1.height) {
		testY = r1.cy - 30 + r1.height;
	}

	float distX = d1.cx - testX;
	float distY = d1.cy - testY;
	float distance = sqrt((distX * distX) + (distY * distY));
	if (distance <= d1.radius) {
		return true;
	}
	else {
		return false;
	}
}

Game::Game(bool ai):ai(ai), boostOnce(0), heightOnce(0), hideOnce(0), boostOnce2(0), heightOnce2(0), hideOnce2(0)
{
	if (!player1) {
		if (ai) {
			player1 = new Player(*this, true, true);
			player2 = new Player(*this, false, true);
		}
		else {
			player1 = new Player(*this, true, false);
			player2 = new Player(*this, false, false);
		}
	}
	if (!obstacle) obstacle = new Obstacle(*this, true);
}

Game::~Game()
{
	if (ball) {
		if (ai) {
			player2->deleteBall();
		}
		else {
			delete ball; ball = nullptr;
		}
	}
	if (player1) {
		delete player1; player1 = nullptr;
	}
	if (player2) {
		delete player2; player2 = nullptr;
	}
	if (obstacle) {
		delete obstacle; obstacle = nullptr;
	}
}