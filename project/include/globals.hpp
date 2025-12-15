#pragma once

#include "raylib.h"

namespace Assets {
    extern Texture2D    background,
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

    extern Font         uifont,
                        numfont;
                        
    extern short        tileRow,
                        tileCol;
    extern float        tileAnimOffset;

    extern Sound        beep,
                        buzzer,
                        dial,
                        grunt,
                        slam,
                        unlock,
                        wohoo;
    extern Music        gameBgm,
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

    extern int   windowWidth;
    extern int   windowHeight;
    extern float winCenterX;
    extern float winCenterY;

    extern enum Scenes scene;
    extern enum Difficulties difficulty;

    extern int highscores[3];
}