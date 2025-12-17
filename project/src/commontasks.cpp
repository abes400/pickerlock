
#include <math.h>
#include "globals.hpp"

using namespace Assets;



void init() {
    background      = LoadTexture("texture/bg.png");
    logo            = LoadTexture("texture/logo.png");
    start_btn       = LoadTexture("texture/start.png");
    start_btn_down  = LoadTexture("texture/start_down.png");
    btn             = LoadTexture("texture/button.png");
    btn_down        = LoadTexture("texture/button_down.png");
    ui_box          = LoadTexture("texture/uibox.png");
    instruction     = LoadTexture("texture/inst_vis.png");
    lockwindow      = LoadTexture("texture/lock.png");
    hand            = LoadTexture("texture/hand.png");
    arrowtile       = LoadTexture("texture/arrow.png");
    cards           = LoadTexture("texture/cards.png");
    statbox         = LoadTexture("texture/statbox.png");
    a400logo        = LoadTexture("texture/a400.png");
    jamlogo         = LoadTexture("texture/20sgj.png");
    cursor          = LoadTexture("texture/cursor.png");

    uifont          = LoadFont("font/uifont.png");
    numfont         = LoadFont("font/numfont.png");
    
    tileRow         = ceil(Globals::windowHeight / background.height) + 2;
    tileCol         = ceil(Globals::windowWidth / background.width ) + 2;

    beep            = LoadSound("audio/beep.wav");
    buzzer          = LoadSound("audio/buzzer.wav");
    dial            = LoadSound("audio/dial.wav");
    grunt           = LoadSound("audio/grunt.wav");
    slam            = LoadSound("audio/slam.wav");
    unlock          = LoadSound("audio/unlock.wav");
    beep            = LoadSound("audio/beep.wav");
    wohoo           = LoadSound("audio/wohoo.wav");

    gameBgm         = LoadMusicStream("audio/gamebgm.wav");
    menuBgm         = LoadMusicStream("audio/menubgm.wav");
    
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
    UnloadTexture(a400logo);
    UnloadTexture(jamlogo);
    UnloadTexture(cursor);

    UnloadFont(uifont);
    UnloadFont(numfont);

    UnloadSound(beep);
    UnloadSound(buzzer);
    UnloadSound(dial);
    UnloadSound(grunt);
    UnloadSound(slam);
    UnloadSound(unlock);
    UnloadSound(wohoo);

    UnloadMusicStream(gameBgm);
    UnloadMusicStream(menuBgm);

}

// Tiles the background texture in an animated manner
void tileBG(float deltaTime) {
    for(short i = 0; i < tileCol; i++)
        for(short j = 0; j < tileRow; j++)
            DrawTexture(background, i * background.width - tileAnimOffset, j * background.height - tileAnimOffset, WHITE);
    tileAnimOffset = tileAnimOffset >= background.width ? 0 : tileAnimOffset + 40 * deltaTime;  
}

bool delayIsOver (float* timer, float delayLength, float deltaTime) {
    *timer -= deltaTime;
    if(*timer <= 0) {
        *timer += delayLength;
        return true;
    }
    return false;
}

void close() {
    unload();
    CloseAudioDevice();
    CloseWindow();
}

void terminate(int code) {
    close();
    exit(code);
}