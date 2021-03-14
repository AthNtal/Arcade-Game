#include "Info.h"
#include "constants.h"
#include "util.h"

void Info::update() {
	musicAdjustment(); //from util.cpp
}

void Info::draw() {
	
	br.outline_opacity = 0.0f;
	br.fill_opacity = 0.5f;
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	br.gradient = true;
	if (winnerMode) {
		br.fill_color[0] = 0.67f;
		br.fill_color[0] = 0.58f;
		br.fill_color[0] = 0.50f;
	}
	graphics::drawRect(CANVAS_W / 2.0, (CANVAS_H / 2.0) - 100, CANVAS_W, CANVAS_W, br);

	displayInfo(getPosX(), getPosY(), getSize(), getQueue());

	//from util.cpp
	drawMusicButton(30, 450, false); 
	drawBackButton();
	
}

void Info::displayInfo(float pos_x, float pos_y, float size, std::queue<std::string> &textQueue) {
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	std::queue<std::string> tq= textQueue;
	float y = pos_y;
	int i = 0;
	while (!tq.empty()) {
		if (i == 3) {
			br.fill_color[1] = 0.0f;
			br.fill_color[2] = 0.0f;
			br.gradient = false;
			graphics::drawText(pos_x, y, size, tq.front(), br);
			br.fill_color[1] = 1.0f;
			br.fill_color[2] = 1.0f;
			br.gradient = true;
		}
		else if (i == 5) {
			br.fill_color[2] = 0.0f;
			br.gradient = false;
			graphics::drawText(pos_x, y, size, tq.front(), br);
			br.fill_color[2] = 1.0f;
			br.gradient = true;
		}
		else if (i == 9) {
			br.fill_color[1] = 0.0f;
			br.fill_color[2] = 0.0f;
			br.gradient = false;
			graphics::drawText(pos_x, y, size, tq.front(), br);
			br.fill_color[1] = 1.0f;
			br.fill_color[2] = 1.0f;
			br.gradient = true;
		}
		else {
			graphics::drawText(pos_x, y, size, tq.front(), br);
		}

		tq.pop();
		y += 40;
		i++;
	}
}

Info::Info(float pos_x, float pos_y, float size, std::queue<std::string> &textQueue, bool winnerMode): pos_x(pos_x), pos_y(pos_y), size(size), textQueue(textQueue), winnerMode(winnerMode){}

Info::~Info(){}