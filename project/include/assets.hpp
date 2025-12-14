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
                        statbox;

    extern Font         uifont,
                        numfont;
                        
    extern short        tileRow,
                        tileCol;
    extern float        tileAnimOffset;

    extern Sound        buttonSnd,
                        dialSnd,
                        unlockSnd;
    extern Music        bgMusic;
}