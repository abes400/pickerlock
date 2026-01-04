#include "raylib.h"

#include "gamesetup.h"
#include "button.hpp"
#include "globals.hpp"
#include "menustr.hpp"
#include "commontasks.hpp"

void MainMenu() {
    if(!IsMusicStreamPlaying(Assets::menuBgm))
        PlayMusicStream(Assets::menuBgm);
    
    // Init logo coordinates
    float logoX = Globals::winCenterX - Assets::logo.width / 2;
    float logoY = Globals::winCenterY - Assets::logo.height * 2 + 26;

    // Initialise MainMenu Elements
    Button* start = new Button(Vector2 {Globals::winCenterX, Globals::winCenterY - 30  }, &Assets::start_btn,   &Assets::start_btn_down);
    Button* instr = new Button(Vector2 {Globals::winCenterX, Globals::winCenterY + 45  }, &Assets::btn,         &Assets::btn_down);
    Button* optns = new Button(Vector2 {Globals::winCenterX, Globals::winCenterY + 105 }, &Assets::btn,         &Assets::btn_down);
    Button* crdts = new Button(Vector2 {Globals::winCenterX, Globals::winCenterY + 165 }, &Assets::btn,         &Assets::btn_down);
    Button* exit  = new Button(Vector2 {Globals::winCenterX, Globals::winCenterY + 225 }, &Assets::btn,         &Assets::btn_down);

    instr -> addLabel(MainMenuStr::inst, LIFT, 8);
    optns -> addLabel(MainMenuStr::opts, LIFT, 8);
    crdts -> addLabel(MainMenuStr::cred, LIFT, 8);
    exit  -> addLabel(MainMenuStr::exit, LIFT, 8);

    // Initialize ByLine
    Vector2 bylinePos   = { logoX - 20, GetScreenHeight() - 32.0f };

    Vector2 mousePos;
    bool    mousePressed;

    // Menu Loop
    while(Globals::scene == Globals::MAIN_MENU && !WindowShouldClose()) {
        UpdateMusicStream(Assets::menuBgm);

        // Handle Input Events
        mousePos         = GetMousePosition();
        mousePressed     = IsMouseButtonDown(MOUSE_BUTTON_LEFT);

        if      (start -> checkClick(mousePos, mousePressed)) { Globals::scene = Globals::DIFFICULTY;   break; }
        else if (instr -> checkClick(mousePos, mousePressed)) { Globals::scene = Globals::INSTRUCTIONS; break; }
        else if (optns -> checkClick(mousePos, mousePressed)) { Globals::scene = Globals::OPTIONS;      break; }
        else if (crdts -> checkClick(mousePos, mousePressed)) { Globals::scene = Globals::CREDITS;      break; }
        else if (exit  -> checkClick(mousePos, mousePressed)) { Globals::keepRunning = false;           break; }
        
        // Draw elements
        BeginDrawing();
        ClearBackground(PL_YELLOW);
        tileBG();

        DrawTexture(Assets::logo, logoX, logoY, WHITE);
        start -> draw();
        instr -> draw();
        optns -> draw();
        crdts -> draw();
        exit  -> draw();
        DrawTextEx(Assets::uifont, MainMenuStr::byln, bylinePos, Assets::uifont.baseSize, FONT_SPACING, WHITE);
        DrawTextureEx(Assets::cursor, mousePos, 0, 1, WHITE);

        EndDrawing();


        // Escape key input is caught here
        // I know it sounds stupid but otherwise, the input is caught even if you return from another menu.
        if(IsKeyPressed(KEY_ESCAPE)) { Globals::keepRunning = false;           break; }
    }

    // Deallocate Buttons
    delete start;
    delete instr;
    delete optns;
    delete crdts;
    delete exit;
}