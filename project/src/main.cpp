#include "raylib.h"
#include "raymath.h"
#include "gamesetup.h"
#include "button.hpp"
#include "gameloops.hpp"

#include <iostream>
using namespace std;

Texture2D background;
Texture2D start_btn, start_btn_down, btn, btn_down, ui_box;
Texture2D instruction;
Font uifont;
short tileRow;
short tileCol;
float tileAnimOffset = 0;
short scene;

void initAssets();
void unloadAssets();

int main() {
    
    ChangeDirectory(GetApplicationDirectory());

    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(W_WINDOW, H_WINDOW, "Pickerlock");
    initAssets();

    
    // Initialize Game Objects
    //Button* startButton = new Button("assets/texture/start.png", Vector2 {CENTER_X_WINDOW, H_WINDOW - 200});
    

    scene = MAIN_MENU;
    while(!WindowShouldClose()) {

        switch(scene) {
            case MAIN_MENU:
            MainMenu();
            break;

            case IN_GAME:
            break;

            case INSTRUCTIONS:
            Instructions();
            break;

            case CREDITS:
            break;
        }

    }
    
    unloadAssets();
    CloseWindow();
    return 0;
}

void initAssets() {
    background = LoadTexture("assets/texture/bg.png");
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

void unloadAssets() {
    UnloadTexture(background);
    UnloadTexture(start_btn);
    UnloadFont(uifont);
    UnloadTexture(start_btn_down);
    UnloadTexture(btn);
    UnloadTexture(btn_down);
    UnloadTexture(ui_box);
    UnloadTexture(instruction);

    cout << "Assets Unloaded\n";

}