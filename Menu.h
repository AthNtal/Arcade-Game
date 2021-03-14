#pragma once
#include"graphics.h"
#include "constants.h"

class Menu 
{
	//music
	const std::string mus = std::string(ASSET_PATH) + std::string(BACK_MUSIC);

	//brushes
	graphics::Brush br;
	graphics::Brush button_br;

	//used for placing menu buttons
	float y_cord = 0; 
public:
	void update();
	void draw();
	void init();
	Menu();
	~Menu();
};

