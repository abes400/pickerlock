
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
    ui_box2          = LoadTexture("texture/uibox2.png");
    instruction     = LoadTexture("texture/inst_vis.png");
    lockwindow      = LoadTexture("texture/lock.png");
    hand            = LoadTexture("texture/hand.png");
    arrowtile       = LoadTexture("texture/arrow.png");
    cards           = LoadTexture("texture/cards.png");
    statbox         = LoadTexture("texture/statbox.png");
    flymaplogo      = LoadTexture("texture/flymap.png");
    jamlogo         = LoadTexture("texture/20sgj.png");
    cursor          = LoadTexture("texture/cursor.png");
    checkbox        = LoadTexture("texture/checkbox.png");

    uifont          = LoadFont("font/uifont.png");
    numfont         = LoadFont("font/numfont.png");

    bgRec           = Rectangle{
        0, 0, 
        Globals::windowWidth + background.width,
        Globals::windowHeight + background.height
    };
    
    bgPos           = Vector2 {0, 0};

    SetTextureWrap(background, TEXTURE_WRAP_REPEAT);

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
    UnloadTexture(ui_box2);
    UnloadTexture(instruction);
    UnloadTexture(lockwindow);
    UnloadTexture(hand);
    UnloadTexture(arrowtile);
    UnloadTexture(cards);
    UnloadTexture(statbox);
    UnloadTexture(flymaplogo);
    UnloadTexture(jamlogo);
    UnloadTexture(cursor);
    UnloadTexture(checkbox);

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
    DrawTextureRec(background, bgRec, bgPos, WHITE);
    bgPos.x = bgPos.x <= - background.width ? 0 : bgPos.x - 40 * deltaTime;  
    bgPos.y = bgPos.y <= - background.height ? 0 : bgPos.y - 40 * deltaTime;  
    DrawFPS(0, 0);
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