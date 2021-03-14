#pragma once
#include "ball.h"
#include "constants.h"
#include "Player.h"
#include "Obstacle.h"
#include "util.h"

class Game 
{
	bool ai;
	Ball* ball = nullptr;
	
	Player* player1 = nullptr;
	Player* player2 = nullptr;
	Obstacle* obstacle = nullptr;

	graphics::Brush br;
	graphics::Brush button_br;
	float x_cord = 0;
	graphics::MouseState mouse;
	//score
	int goalsPlayer1 = 0;
	int goalsPlayer2 = 0;

	//obstacle collision
	bool collisionObstAvailable = true;
	float timeUntilNextObstColl = 0.0f;
	std::string angle = "";
	bool checkObstCollision();

	// speed power up
	int boostOnce, boostOnce2;
	//hide ball power up
	int hideOnce, hideOnce2;
	//height power up
	int heightOnce, heightOnce2;

	//players collision
	bool collisionAvailable = true;
	float timeUntilNextColl = 0.0f;
	bool checkP1Collision();
	bool checkP2Collision();

	void drawScore();
	void checkBall();
	void createBall();
public:
	void update();
	void draw();
	
	int getGoalsPlayer1() const{ return goalsPlayer1; }
	int getGoalsPlayer2() const{ return goalsPlayer2; }

	Game(bool ai);
	~Game();
};
