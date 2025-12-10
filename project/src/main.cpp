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
                instruction,
                lockwindow,
                hand,
                arrowtile;

    Font        uifont,
                numfont;

    short       tileRow,
                tileCol;
    float       tileAnimOffset = 0;
}

namespace Globals {
    enum Scenes {
        MAIN_MENU,
        DIFFICULTY,
        IN_GAME,
        INSTRUCTIONS,
        CREDITS
    };

    // 3+0 3+1 3+2
    enum Difficulties {
        EASY,
        MEDIUM,
        HARD
    };

    enum Scenes scene = MAIN_MENU;
    enum Difficulties difficulty;

    int highscores[3] = {0, 0, 0};
}

void init(); void unload();


int main() {
    
    ChangeDirectory(GetApplicationDirectory());

    // Init game window
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(W_WINDOW, H_WINDOW, "Pickerlock");
    init();

    Globals::scene = Globals::MAIN_MENU;
    while(!WindowShouldClose()) {

        switch(Globals::scene) {
            case Globals::MAIN_MENU:
            MainMenu();
            break;

            case Globals::DIFFICULTY:
            Difficulty();
            break;

            case Globals::IN_GAME:
            Game();
            break;

            case Globals::INSTRUCTIONS:
            Instructions();
            break;

            case Globals::CREDITS:
            Credits();
            break;
        }

    }
    
    unload();
    CloseWindow();
    return 0;
}