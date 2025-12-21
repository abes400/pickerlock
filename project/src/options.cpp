#include "raylib.h"

#include "gamesetup.h"
#include "button.hpp"
#include "checkbox.hpp"
#include "globals.hpp"
#include "menustr.hpp"
#include "commontasks.hpp"

namespace Opts {
    bool sfx = true;
    bool msc = true;
    bool fsc = false;
    // TODO: add fullscreen support
}

void Options() {

    // Init text
    float boxX          = (Globals::windowWidth - Assets::ui_box2.width)   / 2;
    float boxY          = (Globals::windowHeight - Assets::ui_box2.height) / 2;

    Vector2 optsTxtPos  = { boxX + 72, boxY + 22 };

    // Init btuttons
    Button* back    = new Button(Vector2 {Globals::winCenterX,       Globals::winCenterY + 155 }, &Assets::btn, &Assets::btn_down);

    Checkbox* music = new Checkbox(Vector2 {Globals::winCenterX + 50,  Globals::winCenterY - 55  }, &Assets::checkbox, 18, Opts::msc);
    Checkbox* sfx   = new Checkbox(Vector2 {Globals::winCenterX + 50,  Globals::winCenterY - 36  }, &Assets::checkbox, 18, Opts::sfx);
    Checkbox* fscr  = new Checkbox(Vector2 {Globals::winCenterX + 50,  Globals::winCenterY - 17  }, &Assets::checkbox, 18, Opts::fsc);

    back    -> addLabel(MiscMenuStr::back, LIFT, 8);

    Vector2 mousePos;
    bool    mousePressed;

    while(Globals::scene == Globals::OPTIONS && !WindowShouldClose()) {
        UpdateMusicStream(Assets::menuBgm);

        // Handle Button Events
        mousePos        = GetMousePosition();
        mousePressed    = IsMouseButtonDown(MOUSE_BUTTON_LEFT);

        if (back -> checkClick(mousePos, mousePressed)) {
            Globals::scene = Globals::MAIN_MENU; break; 
        } else if (music -> checkClick(mousePos)) {

            Opts::msc = music -> isChecked;
            float newVol = Opts::msc ? 1: 0;
            SetMusicVolume(Assets::gameBgm, newVol);
            SetMusicVolume(Assets::menuBgm, newVol);

        } else if (sfx -> checkClick(mousePos)) {
            Opts::sfx = sfx -> isChecked;
            float newVol = Opts::sfx ? 1: 0;
            SetSoundVolume(Assets::beep,    newVol);
            SetSoundVolume(Assets::buzzer,  newVol);
            SetSoundVolume(Assets::dial,    newVol);
            SetSoundVolume(Assets::grunt,   newVol);
            SetSoundVolume(Assets::slam,    newVol);
            SetSoundVolume(Assets::unlock,  newVol);
            SetSoundVolume(Assets::wohoo,   newVol);

        } else if (fscr -> checkClick(mousePos)) {
            Opts::fsc = fscr -> isChecked;
            ToggleFullscreen();

            windowHeight = 
        }

        // Draw elements
        BeginDrawing();
        ClearBackground(PL_YELLOW);
        tileBG();

        DrawTexture(Assets::ui_box2, boxX, boxY, WHITE);
        DrawTextEx(Assets::uifont, OptsStr::optsTxt, optsTxtPos, Assets::uifont.baseSize, FONT_SPACING, WHITE);
        music -> draw();
        sfx   -> draw();
        fscr  -> draw();
        back  -> draw();
        DrawTextureEx(Assets::cursor, mousePos, 0, 1, WHITE);
        
        EndDrawing();
    }

    delete back;
    delete music;
    delete sfx;
    delete fscr;
}