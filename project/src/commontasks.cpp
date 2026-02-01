
#include <math.h>
#include "gamesetup.h"
#include "globals.hpp"

using namespace Assets;

/**
 * Loads assets on assets directory.
 */
void loadAssets() {
    // Textures
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

    // Fonts
    uifont          = LoadFont("font/uifont.png");
    numfont         = LoadFont("font/numfont.png");

    bgRec           = Rectangle{
        0, 0, 
        static_cast<float>(GetScreenWidth() + background.width),
        static_cast<float>(GetScreenHeight() + background.height)
    };
    
    bgPos           = Vector2 {0, 0};

    SetTextureWrap(background, TEXTURE_WRAP_REPEAT);

    // Sounds
    beep            = LoadSound("audio/beep.wav");
    buzzer          = LoadSound("audio/buzzer.wav");
    dial            = LoadSound("audio/dial.wav");
    grunt           = LoadSound("audio/grunt.wav");
    slam            = LoadSound("audio/slam.wav");
    unlock          = LoadSound("audio/unlock.wav");
    beep            = LoadSound("audio/beep.wav");
    wohoo           = LoadSound("audio/wohoo.wav");

    // Music
    gameBgm         = LoadMusicStream("audio/gamebgm.wav");
    menuBgm         = LoadMusicStream("audio/menubgm.wav");
    
}

/**
 * Unloads the assets
 */
void unloadAssets() {
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

/**
 * Sets the proper resolution depending on the Fullscreen state and calculates the center of the window.
 * 
 * If fullScreen is true, the resolution is set for the native screen.
 * 
 * Otherwise, it is 800 by 600.
 * @param fullScreen Whether the resolution is adapted for the fullscreen or not.
 */
void adaptResolution(bool fullScreen) {
    float newWidth, newHeight;
    if(fullScreen) {
        int monitor = GetCurrentMonitor();
        newWidth = GetMonitorWidth(monitor);
        newHeight = GetMonitorHeight(monitor);
    } else {
        newWidth = W_WINDOW;
        newHeight = H_WINDOW;
    }
    Globals::winCenterX = newWidth / 2;
    Globals::winCenterY = newHeight / 2;
    bgRec.width = newWidth + background.width;
    bgRec.height = newHeight + background.height;

    SetWindowSize(newWidth, newHeight);
}

/**
 * Tiles the background texture in an animated manner.
 * @param deltaTime The time that passed between the last frames.
 */
void tileBG(float deltaTime) {
    DrawTextureRec(background, bgRec, bgPos, WHITE);
    bgPos.x = bgPos.x <= - background.width ? 0 : bgPos.x - 40 * deltaTime;  
    bgPos.y = bgPos.y <= - background.height ? 0 : bgPos.y - 40 * deltaTime;  
    //DrawFPS(0, 0);
}

/**
 * "Asynchronously" holds delay and returns whether it is over.
 * @param timer The variable to hold the time with
 * @param delayLength How long the delay should be
 * @param deltaTime The time that passed between the last frames.
 * @return Whether the timer had reached 0 or not.
 */
bool delayIsOver (float* timer, float delayLength, float deltaTime) {
    *timer -= deltaTime;
    if(*timer <= 0) {
        *timer += delayLength;
        return true;
    }
    return false;
}

/**
 * Prepares the process for the proper closing of the Application.
 * 
 * Unloads the assets and closes the window.
 */
void closeApplication() {
    unloadAssets();
    CloseAudioDevice();
    CloseWindow();
}

/**
 * Prepares the process for the proper closing of the Application if something goes wrong.
 * 
 * No need to call closeApplication() since it is called here as well
 * 
 * @param code The error code to end the process with.
 */
void terminate(int code) {
    closeApplication();
    exit(code);
}