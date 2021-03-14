#include "graphics.h"
#include "GameHandler.h"
#include "constants.h"
#include "util.h"

void resize(unsigned int w, unsigned int h) 
{
    setWindowDimensions(w, h);
}

// The custom callback function that the library calls 
// to check for and set the current application state.
void update(float ms)
{
    GameHandler * gh = reinterpret_cast<GameHandler*>(graphics::getUserData());
    gh->update();
}

// The window content drawing function.
void draw()
{
   GameHandler * gh = reinterpret_cast<GameHandler*>(graphics::getUserData());
    gh->draw(); 
}

int main()
{
    graphics::createWindow(WINDOW_W, WINDOW_H, GAME_N);

    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);
    graphics::setResizeFunction(resize);

    graphics::setCanvasSize(CANVAS_W, CANVAS_H);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    GameHandler gh;
    graphics::setUserData(&gh);

    graphics::startMessageLoop();
    graphics::destroyWindow();

    return 0;
}