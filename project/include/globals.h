#pragma once

#include "raylib.h"

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

    extern enum Scenes scene;
    extern enum Difficulties difficulty;

    extern int highscores[3];
}