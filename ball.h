#pragma once
#include "GameObject.h"
#include "graphics.h"
#include "util.h"

class Ball: public GameObject, public DiskCollidable
{
	float ball_center_x, ball_center_y, ball_radius,
		ball_direction_x, ball_direction_y, ball_speed,
		ball_future_center_x, ball_future_center_y;

	graphics::Brush br;

	//detects if there is a ball to the game
	bool activeBall = true;
	//who conceded the goal
	int playerConcededGoal = 0;
	//variables for player collision
	bool RColission;
	int player = 0;
	//variables for obstacle collision
	bool ObstCollision;

	std::string angle;
	bool speedUp = false;
	bool hide = false;
	int once;

	void ballMovement(float f1, float f2);

public:
	void update() override;
	void draw() override;
	void init() override;

	int getPlayerConcededGoal() const { return playerConcededGoal; }

	bool isActive() const { return activeBall; }

	Disk getCollisionHull() const override;

	//for players
	void setRCollision(bool flag, int p) { RColission = flag;  player = p;}
	//for obstacle
	void setObstCollision(bool flag) { ObstCollision = flag; }
	void setAngle(std::string a) { angle = a; }

	//speed power up
	void setSpeedUp(bool p) { speedUp = p; }
	//hide power up
	void setHide(bool h) { hide = h; }

	//for ai move
	float getBallX() const { return ball_center_x; }
	float getBallY() const { return ball_center_y; }

	Ball(const class Game & mygame, float speed);
	~Ball();
};