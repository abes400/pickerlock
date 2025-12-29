#pragma once
#include <cstdint>
#include "raylib.h"

namespace Assets {
    extern Texture2D    background,
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

    extern Font         uifont,
                        numfont;
                        
    extern Rectangle    bgRec;
    extern Vector2      bgPos;

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
    
    extern bool  keepRunning;

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

    extern float winCenterX;
    extern float winCenterY;

    extern enum Scenes scene;
    extern enum Difficulties difficulty;

    extern bool endless;
    extern uint16_t highscores[3];
    extern uint16_t highscoresEndless[3];
}