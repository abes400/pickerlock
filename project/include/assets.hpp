#pragma once
#include "raylib.h"
 
//a.y. 196B
namespace Assets {
    extern Texture2D    background,
                        logo,
                        start_btn,
                        start_btn_down,
                        btn, btn_down,
                        ui_box,
                        instruction;

    extern Font         uifont;
    extern short        tileRow,
                        tileCol;
    extern float        tileAnimOffset;
}