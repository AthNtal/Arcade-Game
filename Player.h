#pragma once
#include "GameObject.h"
#include "graphics.h"
#include "ball.h"

class Player : public GameObject, public RectCollidable
{
	graphics::Brush br;
	Ball* ball = nullptr;

	float pos_y, pos_x, speed, width, h;
	bool player1Constructor;

	//variables for size up power up
	float height = 1.0f;
	float powerUpStart = 0.f;
	bool timeStamp = true;
	bool heightPressed = false;

	bool ai= false;
	bool up=true;

	void size_up();
	void movePlayer();
public:
	void update() override;
	void draw() override;
	void init() override;

	void reset();

	Rect getCollisionHull() const override;

	void setHeightPB(bool flag) { heightPressed = flag; }

	void setBall(Ball* b) { ball = b;}
	void deleteBall() {
		delete ball; ball = nullptr;
	}
	
	Player(const class Game& mygame, bool flag, bool a);
	~Player();
};
