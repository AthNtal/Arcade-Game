#include "util.h"
#include "graphics.h"
#include <cmath>

bool musicON = false;
graphics::Brush br;
unsigned int window_width = WINDOW_W,
window_height = WINDOW_H;

// checking whether the ON/OFF button is at game or at another tab
bool gameONOFF = true;

bool pressed;
float timeUntilNextPress = 0;

void musicAdjustment()
{
    pressed = false;
    if (graphics::getKeyState(graphics::SCANCODE_SPACE)) {
        if (graphics::getGlobalTime() - timeUntilNextPress > 500) {
            pressed = true;
        }
        timeUntilNextPress = graphics::getGlobalTime();
    }
    graphics::MouseState mouse;
    graphics::getMouseState(mouse);
    if (mouse.button_left_pressed || pressed) {
        if (clickMusicButtonValidity(window2canvasX((float)mouse.cur_pos_x), window2canvasY((float)mouse.cur_pos_y)) || pressed) {
            pressed = false;
            graphics::playSound(click, 0.5f);
            if (musicON) {
                graphics::stopMusic();
                musicON = false;
                drawMusicButton(30, 450, false);
            }else {
                graphics::playMusic(music, 0.5f, true, 2000);
                musicON = true;
                drawBackButton();
            }
        }
    }
}

//ON/OFF button
void drawMusicButton(float x, float y, bool flag)
{
    gameONOFF = flag;
    br.outline_opacity = 0.7f;
    br.fill_opacity = 0.7f;
    br.fill_color[0] = 1.0f;
    br.fill_color[1] = 1.0f;
    br.fill_color[2] = 1.0f;
    br.outline_color[0] = 0.0f;
    br.outline_color[1] = 0.0f;
    br.outline_color[2] = 0.0f;
   
    graphics::drawDisk(x, y, 25, br);
    
    br.fill_color[0] = 0.0f;
    br.fill_color[1] = 0.0f;
    br.fill_color[2] = 0.0f;
    br.outline_opacity = 0.0f;
    br.fill_opacity = 1.0f;
    
    if (musicON) {
       graphics::drawText(x-12, y+6, 20, "ON", br);
    }else {
       graphics::drawText(x-17, y+5, 18, "OFF", br);
    }
}

void drawBackButton() {
    br.outline_opacity = 0.7f;
    br.fill_opacity = 0.7f;
    br.fill_color[0] = 1.0f;
    br.fill_color[1] = 1.0f;
    br.fill_color[2] = 1.0f;
    br.outline_color[0] = 0.0f;
    br.outline_color[1] = 0.0f;
    br.outline_color[2] = 0.0f;

    graphics::drawDisk(85, 453, 25, br);

    br.fill_color[0] = 0.0f;
    br.fill_color[1] = 0.0f;
    br.fill_color[2] = 0.0f;
    br.outline_opacity = 0.0f;
    br.fill_opacity = 1.0f;
    graphics::drawText(62, 457, 18, "BACK", br);
}

//transformations for window's pixels
unsigned int getWindowWidth(){return window_width;}
unsigned int getWindowHeight(){ return window_height;}
float window2canvasX(float x){ return x * CANVAS_W / (float)window_width;}
float window2canvasY(float y){return y * CANVAS_H / (float)window_height;}
void setWindowDimensions(unsigned int w, unsigned int h)
{
    window_width = w;
    window_height = h;
}

bool clickMusicButtonValidity(float x, float y) {
    float cx, cy, r;
    if (!gameONOFF) {
        cx = 30;
        cy = 450;
        r = sqrt(pow(28.33 - cx, 2) + pow(430 - cy, 2));
        return (sqrt(pow(x - cx, 2) + pow(y - cy, 2)) <= r);
    }
    else {
        cx = 140;
        cy = 450;
        r = sqrt(pow(138.33 - cx, 2) + pow(430 - cy, 2));
        return (sqrt(pow(x - cx, 2) + pow(y - cy, 2)) <= r);
    }
}

bool clickBackButtonValidity(float x, float y) {
    float cx, cy, r;
    //center of BACK button
    cx = 85;
    cy = 450;
    r = sqrt(pow(85 - cx, 2) + pow(430 - cy, 2));
    return (sqrt(pow(x - cx, 2) + pow(y - cy, 2)) <= r);
}

bool clickButtonValidity(float x, float y, float lu, float ld, float ll, float lr) {
    float limit_up = lu;
    float limit_down = ld;
    float limit_left = ll;
    float limit_right = lr;
    return (x >= limit_left && x <= limit_right) && (y>= limit_up && y<= limit_down);
}