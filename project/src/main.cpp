#include "raylib.h"
#include "raymath.h"
#include "gamesetup.h"
#include "button.hpp"
#include "gameloops.hpp"

#include <iostream>
using namespace std;

Texture2D background;
Texture2D start_btn, start_btn_down, btn, btn_down, ui_box;
short tileRow;
short tileCol;
float tileAnimOffset = 0;
short scene;

void initTextures();

int main() {
    
    ChangeDirectory(GetApplicationDirectory());

    InitWindow(W_WINDOW, H_WINDOW, "Pickerlock");
    initTextures();

    
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
            break;

            case CREDITS:
            break;
        }

    }
    
    CloseWindow();
    return 0;
}

void initTextures() {
    background = LoadTexture("assets/texture/bg.png");
    start_btn = LoadTexture("assets/texture/start.png");
    start_btn_down = LoadTexture("assets/texture/start_down.png");
    
    tileRow = ceil(H_WINDOW / background.height) + 2;
    tileCol = ceil(W_WINDOW / background.width) + 1;
}