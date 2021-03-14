#pragma once
#include "GameObject.h"
#include "graphics.h"

class Obstacle : public GameObject, RectCollidable
{
	bool up;
	graphics::Brush brush;
	float pos_x, pos_y , speed, size;
public:
	void update() override;
	void draw() override;
	void init() override;

	Rect getCollisionHull() const override;
	Obstacle(const class Game& mygame, bool flag);
	~Obstacle();
};