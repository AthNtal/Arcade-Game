#include "Menu.h"
#include "graphics.h"
#include "constants.h"
#include "util.h"

void Menu::update(){
    musicAdjustment(); //from util.cpp
}

void Menu::draw()
{
	//setting the initial background
	br.texture = std::string(ASSET_PATH) + std::string(BACKGROUND);
	br.outline_opacity = 0.0f;
    br.fill_color[0] = 1.0f;
    br.fill_color[1] = 1.0f;
    br.fill_color[2] = 1.0f;
	graphics::drawRect(CANVAS_W/2.0, (CANVAS_H/2.0)-100, CANVAS_W, CANVAS_W, br);

	//setting the title
    br.texture = "";
    br.fill_color[0] = 0.0f;
    br.fill_color[1] = 0.0f;
    br.fill_color[2] = 0.0f;
    graphics::drawText(335, 80, 70, GAME_N, br);
   
    br.fill_color[0] = 1.0f;
    br.fill_color[1] = 1.0f;
    br.fill_color[2] = 0.0f;

    //creating the buttons
	button_br.outline_opacity = 0.4f;
    button_br.gradient = true;
	button_br.fill_opacity = 0.7f;
    button_br.fill_color[0] = 0.0f;
    button_br.fill_color[1] = 0.0f;
    button_br.fill_color[2] = 0.0f;

    y_cord = 160; 
    for (int i = 0; i < 4; i++) {
        graphics::drawRect(CANVAS_W/2, y_cord, 200, 70, button_br);
        if (i == 0) {
            graphics::drawText(434, y_cord + 10, 25, std::string(BUTTON_1), br);
        }
        else if (i == 1) {
            graphics::drawText(415, y_cord + 10, 25, std::string(BUTTON_2), br);
        }
        else if (i == 2) {
            graphics::drawText(423, y_cord + 10, 25, std::string(BUTTON_3), br);
        }
        else {
            graphics::drawText(445, y_cord + 10, 25, std::string(BUTTON_4), br);
        }
        y_cord += 90;
    }

    //ON/OFF
    drawMusicButton(30, 450, false);//from util.cpp
}

void Menu::init() {
    //setting font
    graphics::setFont(std::string(ASSET_PATH) + std::string(GAME_FONT));
}

Menu::Menu(){
    init();
}
Menu::~Menu(){}