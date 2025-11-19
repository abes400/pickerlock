#pragma once
#include "raylib.h"
 
namespace Assets {
    extern Texture2D background, logo;
    extern Texture2D start_btn, start_btn_down, btn, btn_down, ui_box;
    extern Texture2D instruction;
    extern Font uifont;
    extern short tileRow;
    extern short tileCol;
    extern float tileAnimOffset;

initAssets();
unloadAssets();
}