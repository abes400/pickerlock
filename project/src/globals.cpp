#include <cstdint>
#include "raylib.h"
#include "gamesetup.h"

namespace Assets {
    Texture2D   background,
                logo,
                start_btn,
                start_btn_down,
                btn, btn_down,
                ui_box,
                ui_box2,
                instruction,
                lockwindow,
                hand,
                arrowtile,
                cards,
                statbox,
                flymaplogo,
                jamlogo,
                cursor,
                checkbox;

    Font        uifont,
                numfont;

    Rectangle   bgRec;
    Vector2     bgPos;

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

    bool keepRunning = true;

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

    float winCenterX   = W_WINDOW / 2;
    float winCenterY   = H_WINDOW / 2;

    enum Scenes scene = MAIN_MENU;
    enum Difficulties difficulty;

    bool endless = false;
    uint16_t highscores[3]        = {9999, 9999, 9999};
    uint16_t highscoresEndless[3] = {9999, 9999, 9999};
}