#include "assets.hpp"
#include <math.h>
#include "gamesetup.h"

using namespace Assets;



void init() {
    background      = LoadTexture("assets/texture/bg.png");
    logo            = LoadTexture("assets/texture/logo.png");
    start_btn       = LoadTexture("assets/texture/start.png");
    start_btn_down  = LoadTexture("assets/texture/start_down.png");
    btn             = LoadTexture("assets/texture/button.png");
    btn_down        = LoadTexture("assets/texture/button_down.png");
    ui_box          = LoadTexture("assets/texture/uibox.png");
    instruction     = LoadTexture("assets/texture/inst_vis.png");
    lockwindow      = LoadTexture("assets/texture/lock.png");
    hand            = LoadTexture("assets/texture/hand.png");
    arrowtile       = LoadTexture("assets/texture/arrow.png");
    cards           = LoadTexture("assets/texture/cards.png");
    statbox          = LoadTexture("assets/texture/statbox.png");

    uifont          = LoadFont ("assets/font/uifont.png");
    numfont         = LoadFont ("assets/font/numfont.png");
    
    tileRow         = ceil(H_WINDOW / background.height) + 2;
    tileCol         = ceil(W_WINDOW / background.width ) + 2;
}

void unload() {
    UnloadTexture(background);
    UnloadTexture(logo);
    UnloadTexture(start_btn);
    UnloadTexture(start_btn_down);
    UnloadTexture(btn);
    UnloadTexture(btn_down);
    UnloadTexture(ui_box);
    UnloadTexture(instruction);
    UnloadTexture(lockwindow);
    UnloadTexture(hand);
    UnloadTexture(arrowtile);
    UnloadTexture(cards);
    UnloadTexture(statbox);

    UnloadFont(uifont);
    UnloadFont(numfont);
}

// Tiles the background texture in an animated manner
void tileBG() {
    for(short i = 0; i < tileCol; i++)
        for(short j = 0; j < tileRow; j++)
            DrawTexture(background, i * background.width - tileAnimOffset, j * background.height - tileAnimOffset, WHITE);
    tileAnimOffset = tileAnimOffset >= background.width ? 0 : tileAnimOffset + 40 * GetFrameTime();  
}

bool delayIsOver (float deltaTime, float* timer, float delayLength) {
    *timer -= deltaTime;
    if(*timer <= 0) {
        *timer += delayLength;
        return true;
    }
    return false;
}

#include<iostream>
using namespace std;

void close() {
    unload();
    CloseWindow();
}

void terminate(int code) {
    close();
    exit(code);
}