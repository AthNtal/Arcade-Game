#pragma once
#include "constants.h"
#include <string>

//sounds
const std::string music = std::string(ASSET_PATH) + std::string(BACK_MUSIC);
const std::string click = std::string(ASSET_PATH) + std::string(CLICK_BUTTON);

//music actions
void musicAdjustment();
void drawMusicButton(float x, float y, bool flag);
void drawBackButton();
bool clickMusicButtonValidity(float x, float y);

//back button check
bool clickBackButtonValidity(float x, float y);

//validity for rectangle shapes
bool clickButtonValidity(float x, float y, float lu, float ld, float ll, float lr);

//transforming window to canvas pixels
unsigned int getWindowWidth();
unsigned int getWindowHeight();
float window2canvasX(float x);
float window2canvasY(float y);
void setWindowDimensions(unsigned int w, unsigned int h);

struct Disk {
	float cx, cy;
	float radius;
};

struct Rect {
	float cx, cy, width, height;
};