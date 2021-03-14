#pragma once
#include <graphics.h>
#include <queue>

class Info {
	float pos_x, pos_y, size;
	const std::string text;
	graphics::Brush br;
	std::queue<std::string>textQueue;
	bool winnerMode;

	void displayInfo(float pos_x, float pos_y, float size, std::queue<std::string>& textQueue);
public:
	void update();
	void draw();
	Info(float pos_x, float pos_y, float size,  std::queue<std::string> &textQueue, bool winnerMode);
	~Info();
	float getPosX() const { return pos_x; }
	float getPosY() const { return pos_y; }
	float getSize() const { return size; }
	std::queue<std::string> &getQueue() { return textQueue; }
};