#include "Player.h"
#include "graphics.h"
#include "constants.h"
#include "util.h"

void Player::update()
{
	movePlayer();
	size_up(); // power up button
}

void Player::draw()
{
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	graphics::setScale(height, height);
	br.texture = std::string(ASSET_PATH) + std::string(PLAYER);
	br.outline_opacity = 0.0f;
	graphics::drawRect(pos_x , pos_y , width, h, br);
	graphics::resetPose();
}

void Player::init()
{
	pos_y = CANVAS_H / 2;
	if (player1Constructor) {
		pos_x = 20;
	}
	else {
		pos_x = CANVAS_W - 20;
	}
	speed = 5.0f;
	width = 30;
	h = 100;
	//size up
	height = 1.0f;
	powerUpStart = 0.0f;
}

void Player::size_up()
{
	if(heightPressed){
		powerUpStart = graphics::getGlobalTime();
		height = 2.5f;
		graphics::playSound(std::string(ASSET_PATH) + std::string(SIZEUP), 0.5f);
		heightPressed = false;
	}
	//this means that size up button has been pressed - retains the power up for 10 seconds
	if (powerUpStart != 0) {
		if (timeStamp) {
			br.fill_color[0] = 1.0f;
			br.fill_color[1] = 0.0f;
			br.fill_color[2] = 0.0f;
			if (player1Constructor) {
				graphics::drawText(80, 80, 25, "Size up time: " + std::to_string(int((graphics::getGlobalTime() - powerUpStart) / 1000.0f)), br);
			}
			else {
				graphics::drawText(680, 80, 25, "Size up time: " + std::to_string(int((graphics::getGlobalTime() - powerUpStart) / 1000.0f)), br);
			}
		}

		if (graphics::getGlobalTime() - powerUpStart > 10000) {
			height = 1.0f;
			timeStamp = false;
		}
	}
	//---------------------------------------------------------------------
}

void Player::movePlayer()
{
	// player vs AI
	if (player1Constructor && ai) {
		if (graphics::getKeyState(graphics::SCANCODE_UP)) {
			pos_y -= speed * graphics::getDeltaTime() / 10.0f;
		}
		if (graphics::getKeyState(graphics::SCANCODE_DOWN)) {
			pos_y += speed * graphics::getDeltaTime() / 10.0f;
		}
	}

	if (!player1Constructor && ai) {
		float limitup;
		float limitdown;
		if (ball != nullptr) {
			float ball_x = ball->getBallX();
			if (ball_x >= CANVAS_W / 2) {
				float ball_y = ball->getBallY();
				if (ball_y >= 3 * CANVAS_H / 4) {
					limitup = CANVAS_H - 40;
					limitdown = 3 * CANVAS_H / 4;

					if (up) pos_y += speed * graphics::getDeltaTime() / 20.0f;
					if (pos_y >= limitup) {
						pos_y = limitup;
						up = false;
					}
					if (!up) pos_y -= speed * graphics::getDeltaTime() / 20.0f;
					if (pos_y <= limitdown) {
						pos_y = limitdown;
						up = true;
					}
				}
				else if (ball_y >= CANVAS_H / 2) {
					limitup = 3 * CANVAS_H / 4;
					limitdown = CANVAS_H / 2;
					if (up) pos_y += speed * graphics::getDeltaTime() / 20.0f;
					if (pos_y >= limitup) {
						pos_y = limitup;
						up = false;
					}
					if (!up) pos_y -= speed * graphics::getDeltaTime() / 20.0f;
					if (pos_y <= limitdown) {
						pos_y = limitdown;
						up = true;
					}
				}
				else if (ball_y >= CANVAS_H / 4) {
					limitup = CANVAS_H / 2;
					limitdown = CANVAS_H / 4;

					if (up) pos_y += speed * graphics::getDeltaTime() / 20.0f;
					if (pos_y >= limitup) {
						pos_y = limitup;
						up = false;
					}
					if (!up) pos_y -= speed * graphics::getDeltaTime() / 20.0f;
					if (pos_y <= limitdown) {
						pos_y = limitdown;
						up = true;
					}
				}
				else {
					limitup = CANVAS_H / 4;
					limitdown = 40;

					if (up) pos_y += speed * graphics::getDeltaTime() / 20.0f;
					if (pos_y >= limitup) {
						pos_y = limitup;
						up = false;
					}
					if (!up) pos_y -= speed * graphics::getDeltaTime() / 20.0f;
					if (pos_y <= limitdown) {
						pos_y = limitdown;
						up = true;
					}
				}
			}
		}
	}//end player vs AI 
	
	// one vs one
	if (player1Constructor && !ai) {
		if (graphics::getKeyState(graphics::SCANCODE_W)) {
			pos_y -= speed * graphics::getDeltaTime() / 10.0f;
		}
		if (graphics::getKeyState(graphics::SCANCODE_S)) {
			pos_y += speed * graphics::getDeltaTime() / 10.0f;
		}
	}
	if (!player1Constructor && !ai) {
		if (graphics::getKeyState(graphics::SCANCODE_UP)) {
			pos_y -= speed * graphics::getDeltaTime() / 10.0f;
		}
		if (graphics::getKeyState(graphics::SCANCODE_DOWN)) {
			pos_y += speed * graphics::getDeltaTime() / 10.0f;
		}
	}
	
	if (pos_y < 40) pos_y = 40;
	if (pos_y > CANVAS_H - 40) pos_y = CANVAS_H - 40;
	// end of one vs one
}

Rect Player::getCollisionHull() const
{
	Rect rect;
	rect.cx = pos_x;
	rect.cy = pos_y;
	rect.width = width;
	rect.height = h;
	return rect;
}

void Player::reset() {
	pos_y = CANVAS_H / 2;
}

Player::Player(const Game& mygame, bool flag, bool a): GameObject(mygame), player1Constructor(flag), ai(a)
{
	init();
}

Player::~Player()
{
}