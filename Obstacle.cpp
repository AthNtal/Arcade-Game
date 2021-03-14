#include "Obstacle.h"
#include "graphics.h"
#include <random>

void Obstacle::update()
{
	if (up) pos_y += speed * graphics::getDeltaTime();
	if (pos_y >= CANVAS_H - 20) {
		pos_y = CANVAS_H - 20;
		up = false;
	}
	if(!up) pos_y -= speed * graphics::getDeltaTime();
	if (pos_y <= 20) {
		pos_y = 20;
		up = true;
	}
}

void Obstacle::draw()
{
	brush.texture = std::string(ASSET_PATH) + std::string(OBSTACLE);
	brush.fill_opacity = 1.0f;
	brush.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y, size, size + 10, brush);
	graphics::resetPose();
}

void Obstacle::init()
{
	pos_x = CANVAS_W / 2;
	pos_y = CANVAS_H + 1.1f * size;
	speed = 0.3f;
	size = 60;
}

Rect Obstacle::getCollisionHull() const
{
	Rect rect;
	rect.cx = pos_x;
	rect.cy = pos_y;
	rect.width = size;
	rect.height = size + 10;
	return rect;
}

Obstacle::Obstacle(const Game& mygame, bool flag): GameObject(mygame)
{
	up = flag;
	init();
}

Obstacle::~Obstacle(){}