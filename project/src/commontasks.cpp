#include "assets.hpp"
#include <math.h>
#include "gamesetup.h"

using namespace Assets;



void init() {
    background = LoadTexture("assets/texture/bg.png");
    logo = LoadTexture("assets/texture/logo.png");
    start_btn = LoadTexture("assets/texture/start.png");
    uifont = LoadFont("assets/font/uifont.ttf");
    start_btn_down = LoadTexture("assets/texture/start_down.png");
    btn = LoadTexture("assets/texture/button.png");
    btn_down = LoadTexture("assets/texture/button_down.png");
    ui_box = LoadTexture("assets/texture/uibox.png");
    instruction = LoadTexture("assets/texture/inst_vis.png");
    
    tileRow = ceil(H_WINDOW / background.height) + 2;
    tileCol = ceil(W_WINDOW / background.width) + 1;
}

void unload() {
    UnloadTexture(background);
    UnloadTexture(logo);
    UnloadTexture(start_btn);
    UnloadFont(uifont);
    UnloadTexture(start_btn_down);
    UnloadTexture(btn);
    UnloadTexture(btn_down);
    UnloadTexture(ui_box);
    UnloadTexture(instruction);

}

// Tiles the background texture in an animated manner
void tileBG() {
    for(int i = 0; i < tileCol; i++)
        for(int j = 0; j < tileRow; j++)
            DrawTexture(background, i * background.width - tileAnimOffset, j * background.height - tileAnimOffset, WHITE);
    tileAnimOffset = tileAnimOffset >= background.width ? 0 : tileAnimOffset + 40 * GetFrameTime();  
}