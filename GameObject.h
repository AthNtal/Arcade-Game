#pragma once
#include "util.h"

class DiskCollidable 
{
public:
	virtual Disk getCollisionHull() const = 0;
};

class RectCollidable
{
public:
	virtual Rect getCollisionHull() const = 0;
};

class GameObject 
{
protected:
	//info about the game goes to each game object
	const class Game & game;
public:
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void init() = 0;
	GameObject(const class Game & mygame);
};