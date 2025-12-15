#include "raylib.h"
#include "gamesetup.h"
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
                arrowtile,
                cards,
                statbox,
                a400logo,
                jamlogo;

    Font        uifont,
                numfont;

    short       tileRow,
                tileCol;
    float       tileAnimOffset = 0;

    Sound       beep,
                buzzer,
                dial,
                grunt,
                slam,
                unlock,
                wohoo;
    Music       gameBgm,
                menuBgm;
}

namespace Globals {
    enum Scenes {
        MAIN_MENU,
        DIFFICULTY,
        IN_GAME,
        INSTRUCTIONS,
        OPTIONS,
        CREDITS
    };

    // 3+0 3+1 3+2
    enum Difficulties {
        EASY,
        MEDIUM,
        HARD
    };

    int   windowWidth  = W_WINDOW;
    int   windowHeight = H_WINDOW;
    float winCenterX   = windowWidth / 2;
    float winCenterY   = windowHeight / 2;

    enum Scenes scene = MAIN_MENU;
    enum Difficulties difficulty;

    int highscores[3] = {0, 0, 0};
}