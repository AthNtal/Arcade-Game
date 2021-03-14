#include "ball.h"
#include "vecmath.h"
#include <random>
#include "game.h"
#include "constants.h"


void Ball::update()
{
	ball_future_center_x = ball_center_x + ball_direction_x * ball_speed;
	ball_future_center_y = ball_center_y + ball_direction_y * ball_speed;

	if ((ball_future_center_x + ball_radius) >= CANVAS_W) {
		graphics::playSound(std::string(ASSET_PATH) + std::string(GOAL), 0.5f);
		activeBall = false;
		//score actions for player 2
		playerConcededGoal = 2;
	}
	else if ((ball_future_center_x - ball_radius) <= 0.0f) {
		graphics::playSound(std::string(ASSET_PATH) + std::string(GOAL), 0.5f);
		activeBall = false;
		//score actions for player 1
		playerConcededGoal = 1;
	}
	
	if ((ball_future_center_y + ball_radius) >= CANVAS_H) {
		graphics::playSound(std::string(ASSET_PATH) + std::string(OUTOFBOUNDS), 0.5f);
		ballMovement(0.0f, -1.0f);
	}
	else if ((ball_future_center_y - ball_radius) <= 0.0f) {
		graphics::playSound(std::string(ASSET_PATH) + std::string(OUTOFBOUNDS), 0.5f);
		ballMovement(0.0f, 1.0f);
	}

	// ball - player collision actions
	if (RColission) {
		
		if (player == 1) {
			ballMovement(1.0f, 0.0f);
			graphics::playSound(std::string(ASSET_PATH) + std::string(BEER_CLINK), 0.5f);
			ball_speed += 1.0f;
		}
		if (player == 2) {
			ballMovement(-1.0f, 0.0f);
			graphics::playSound(std::string(ASSET_PATH) + std::string(BEER_CLINK), 0.5f);
			ball_speed += 1.0f;
		}
		RColission = false;
	}

	// ball - obstacle collision actions
	if (ObstCollision) {
		if (angle == "left") {
			graphics::playSound(std::string(ASSET_PATH) + std::string(BARREL), 0.5f);
			ballMovement(-1.0f, 0.0f);
		}else if (angle == "right") {
			graphics::playSound(std::string(ASSET_PATH) + std::string(BARREL), 0.5f);
			ballMovement(1.0f, 0.0f);
		}else if (angle == "top") {
			graphics::playSound(std::string(ASSET_PATH) + std::string(BARREL), 0.5f);
			ballMovement(0.0f, 1.0f);
		}else if (angle == "bottom") {
			graphics::playSound(std::string(ASSET_PATH) + std::string(BARREL), 0.5f);
			ballMovement(0.0f, -1.0f);
		}
		ObstCollision = false;
	}
	
	if (speedUp && once!=1) {
		once = 1;
		ball_speed += 4.0f;
	}

	ball_center_x += ball_direction_x * ball_speed;
	ball_center_y += ball_direction_y * ball_speed;
}

void Ball::draw()
{
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	if (hide) {
		br.fill_opacity = 0.0f;
	}else {
		br.fill_opacity = 1.0f;
	}
	if (speedUp) {
		br.fill_color[0] = 1.0f;
	}
	br.outline_opacity = 0.0f;
	graphics::drawDisk(ball_center_x, ball_center_y, ball_radius, br);
}

void Ball::init()
{
	ball_center_x = CANVAS_W / 2;
	ball_center_y = CANVAS_H / 2;
	ball_radius = 10.0f;
	ball_direction_x = 1.0f;
	ball_direction_y = 0.0f;
	ball_future_center_x = 0.0f;
	ball_future_center_y = 0.0f;
	
	// number random generator for initiating the ball randomly
	std::random_device seed; 
	std::default_random_engine generator(seed());
	std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);

	 ball_direction_x = distribution(generator);
	 // avoid infinite loop with ball
	 if (ball_direction_x >= -0.3f && ball_direction_x <= 0.3f) {
		 if (ball_direction_x <= 0) ball_direction_x = -0.4f;
		 else ball_direction_x = 0.4f;
	 }

	ball_direction_y = distribution(generator);

	// Normalization
	float length = std::sqrt(ball_direction_x * ball_direction_x + ball_direction_y * ball_direction_y);
	ball_direction_x /= length;
	ball_direction_y /= length;
}

Disk Ball::getCollisionHull() const
{
	Disk disk;
	disk.cx = ball_center_x;
	disk.cy = ball_center_y;
	disk.radius = ball_radius;
	return disk;
}

void Ball::ballMovement(float f1, float f2)
{
	math::vec2 dir{ ball_direction_x, ball_direction_y };
	math::vec2 normal = { f1, f2 };
	math::vec2 reflection = math::reflect(dir, normal);
	ball_direction_x = reflection.x;
	ball_direction_y = reflection.y;
}

Ball::Ball(const Game& mygame, float speed) : GameObject(mygame), ball_speed(speed)
{
	init();
}

Ball::~Ball()
{
}
