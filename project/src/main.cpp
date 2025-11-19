#include "raylib.h"

#include "gamesetup.h"
#include "gameloops.hpp"

#include <iostream>
using namespace std;

namespace Assets {
    Texture2D   background,
                logo,
                start_btn,
                start_btn_down,
                btn, btn_down,
                ui_box,
                instruction;

    Font        uifont;
    short       tileRow,
                tileCol;
    float       tileAnimOffset = 0;
}


short scene;

void init(); void unload();


int main() {
    
    ChangeDirectory(GetApplicationDirectory());

    // Init game window
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(W_WINDOW, H_WINDOW, "Pickerlock");
    init();

    scene = MAIN_MENU;
    while(!WindowShouldClose()) {

        switch(scene) {
            case MAIN_MENU:
            MainMenu();
            break;

            case DIFFICULTY:
            Difficulty();
            break;

            case IN_GAME:
            break;

            case INSTRUCTIONS:
            Instructions();
            break;

            case CREDITS:
            Credits();
            break;
        }

    }
    
    unload();
    CloseWindow();
    return 0;
}