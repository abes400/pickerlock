#include "raylib.h"

#include "gamesetup.h"
#include "button.hpp"
#include "globals.hpp"
#include "menustr.hpp"
#include "commontasks.hpp"

namespace Opts {
    bool sfx = true;
    bool msc = true;
    // TODO: add fullscreen support
}

void Options() {

    // Init text
    float boxX          = (Globals::windowWidth - Assets::ui_box.width)   / 2;
    float boxY          = (Globals::windowHeight - Assets::ui_box.height) / 2;

    Vector2 optsTxtPos  = { boxX + 231, boxY + 65 };

    // Init btuttons
    Button* back    = new Button(Vector2 {Globals::winCenterX,       Globals::winCenterY + 155 }, &Assets::btn, &Assets::btn_down);
    Button* music   = new Button(Vector2 {Globals::winCenterX + 50,  Globals::winCenterY - 35  }, &Assets::btn, &Assets::btn_down);
    Button* sfx     = new Button(Vector2 {Globals::winCenterX + 50,  Globals::winCenterY + 20  }, &Assets::btn, &Assets::btn_down);

    back    -> addLabel(MiscMenuStr::back, LIFT, 8);
    music   -> addLabel(Opts::msc ? OptsStr::enbl : OptsStr::dsbl,     LIFT, 8);
    sfx     -> addLabel(Opts::sfx ? OptsStr::enbl : OptsStr::dsbl,     LIFT, 8);

    Vector2 mousePos;
    bool    mousePressed;

    while(Globals::scene == Globals::OPTIONS && !WindowShouldClose()) {
        UpdateMusicStream(Assets::menuBgm);

        // Handle Button Events
        mousePos        = GetMousePosition();
        mousePressed    = IsMouseButtonDown(MOUSE_BUTTON_LEFT);

        if (back -> checkClick(mousePos, mousePressed)) {
            Globals::scene = Globals::MAIN_MENU; break; 
        } else if (music -> checkClick(mousePos, mousePressed)) {
            Opts::msc = !Opts::msc;
            music -> addLabelWithoutMeasuring(Opts::msc ? OptsStr::enbl : OptsStr::dsbl);
            float newVol = Opts::msc ? 1: 0;
            SetMusicVolume(Assets::gameBgm, newVol);
            SetMusicVolume(Assets::menuBgm, newVol);
        } else if (sfx -> checkClick(mousePos, mousePressed)) {
            Opts::sfx = !Opts::sfx;
            sfx -> addLabelWithoutMeasuring(Opts::sfx ? OptsStr::enbl : OptsStr::dsbl);
            float newVol = Opts::sfx ? 1: 0;

            SetSoundVolume(Assets::beep,    newVol);
            SetSoundVolume(Assets::buzzer,  newVol);
            SetSoundVolume(Assets::dial,    newVol);
            SetSoundVolume(Assets::grunt,   newVol);
            SetSoundVolume(Assets::slam,    newVol);
            SetSoundVolume(Assets::unlock,  newVol);
            SetSoundVolume(Assets::wohoo,   newVol);
        }

        // Draw elements
        BeginDrawing();
        ClearBackground(PL_YELLOW);
        tileBG();

        DrawTexture(Assets::ui_box, boxX, boxY, WHITE);
        DrawTextEx(Assets::uifont, OptsStr::optsTxt, optsTxtPos, Assets::uifont.baseSize, FONT_SPACING, WHITE);
        music -> draw();
        sfx   -> draw();
        back  -> draw();
        DrawTextureEx(Assets::cursor, mousePos, 0, 1, WHITE);
        
        EndDrawing();
    }

    delete back;
    delete music;
    delete sfx;
}