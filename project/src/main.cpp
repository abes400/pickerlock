#include "raylib.h"
#include "raymath.h"
#include "gamesetup.h"
#include "button.hpp"
#include "gameloops.hpp"

#include <iostream>
using namespace std;

Texture2D background;
short tileRow;
short tileCol;
short scene;

int main() {
    
    ChangeDirectory(GetApplicationDirectory());
    InitWindow(W_WINDOW, H_WINDOW, "Pickerlock");
    init();

    
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