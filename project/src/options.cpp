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
}

void Options() {

    // Init text
    float boxX          = (GetScreenWidth() - Assets::ui_box2.width)   / 2;
    float boxY          = (GetScreenHeight() - Assets::ui_box2.height) / 2;

    Vector2 optsTxtPos  = { boxX + 72, boxY + 22  };
    Vector2 rsetTxtPos  = { boxX + 52, boxY + 190 };

    // Init btuttons
    Button* back    = new Button(Vector2 {Globals::winCenterX,       Globals::winCenterY + 120 }, &Assets::btn, &Assets::btn_down);
    Button* rset    = new Button(Vector2 {Globals::winCenterX,       Globals::winCenterY + 25  }, &Assets::btn, &Assets::btn_down);

    Checkbox* music = new Checkbox(Vector2 {Globals::winCenterX + 44,  Globals::winCenterY - 70  }, &Assets::checkbox, 19, Opts::msc);
    Checkbox* sfx   = new Checkbox(Vector2 {Globals::winCenterX + 44,  Globals::winCenterY - 51  }, &Assets::checkbox, 19, Opts::sfx);
    Checkbox* fscr  = new Checkbox(Vector2 {Globals::winCenterX + 44,  Globals::winCenterY - 32  }, &Assets::checkbox, 19, Opts::fsc);

    back    -> addLabel(MiscMenuStr::back, LIFT, 8);
    rset    -> addLabel(OptsStr::rsHS, LIFT, 8);

    // Decides whether the "Message Deleted" info is shown
    bool didReset = false;

    Vector2 mousePos;
    bool    mousePressed;

    while(Globals::scene == Globals::OPTIONS && !WindowShouldClose()) {
        UpdateMusicStream(Assets::menuBgm);

        // Handle Button Events
        mousePos        = GetMousePosition();
        mousePressed    = IsMouseButtonDown(MOUSE_BUTTON_LEFT);

        if (back -> checkClick(mousePos, mousePressed)) {
            Globals::scene = Globals::MAIN_MENU; break; 
        } else if (rset -> checkClick(mousePos, mousePressed)) {
            for(short mode = Globals::EASY; mode <= Globals::HARD; mode++)
                Globals::highscores[mode] = Globals::highscoresEndless[mode] = 0;
            didReset = true;
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
            ToggleBorderlessWindowed();
            adaptResolution(Opts::fsc);
            break;
        }

        // Draw elements
        BeginDrawing();
        ClearBackground(PL_YELLOW);
        tileBG();

        DrawTexture(Assets::ui_box2, boxX, boxY, WHITE);
        DrawTextEx(Assets::uifont, OptsStr::optsTxt, optsTxtPos, Assets::uifont.baseSize, FONT_SPACING, WHITE);
        if(didReset) DrawTextEx(Assets::uifont, OptsStr::rsInf,   rsetTxtPos, Assets::uifont.baseSize, FONT_SPACING, RED);
        music -> draw();
        sfx   -> draw();
        fscr  -> draw();
        rset  -> draw();
        back  -> draw();
        DrawTextureEx(Assets::cursor, mousePos, 0, 1, WHITE);
        
        EndDrawing();
    }

    delete back;
    delete rset;
    delete music;
    delete sfx;
    delete fscr;
}