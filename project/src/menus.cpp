#include <math.h>
#include <stdio.h>

#include "raylib.h"

#include "gamesetup.h"
#include "globals.h"
#include "commonvisuals.h"

#include "menustr.hpp"
#include "button.hpp"

#include "assets.hpp"
#include "sprite.hpp"


void MainMenu() {
    
    // Init logo coordinates
    short logoX = CENTER_X_WINDOW - Assets::logo.width / 2;
    short logoY = CENTER_Y_WINDOW - Assets::logo.height * 2;

    // Initialise MainMenu Elements
    Button* start = new Button(Vector2 {CENTER_X_WINDOW, CENTER_Y_WINDOW + 85  }, &Assets::start_btn,   &Assets::start_btn_down);
    Button* instr = new Button(Vector2 {CENTER_X_WINDOW, CENTER_Y_WINDOW + 150 }, &Assets::btn,         &Assets::btn_down);
    Button* crdts = new Button(Vector2 {CENTER_X_WINDOW, CENTER_Y_WINDOW + 210 }, &Assets::btn,         &Assets::btn_down);

    instr -> addLabel(MainMenuStr::inst, LIFT, 8);
    crdts -> addLabel(MainMenuStr::cred, LIFT, 8);

    // Initialize ByLine
    Vector2 bylineSize  = MeasureTextEx(Assets::uifont, MainMenuStr::byln, FONT_SIZE, 0);
    Vector2 bylinePos   = {
        static_cast<float>(CENTER_X_WINDOW - bylineSize.x / 2),
        static_cast<float>(H_WINDOW - bylineSize.y * 2 ),
    };

    Vector2 mousePos;
    bool    mousePressed;

    // Menu Loop
    while(Globals::scene == Globals::MAIN_MENU && !WindowShouldClose()) {

        // Handle Input Events
        mousePos         = GetMousePosition();
        mousePressed     = IsMouseButtonDown(MOUSE_BUTTON_LEFT);

        if      (start -> checkClick(mousePos, mousePressed)) { Globals::scene = Globals::DIFFICULTY;   break; }
        else if (instr -> checkClick(mousePos, mousePressed)) { Globals::scene = Globals::INSTRUCTIONS; break; }
        else if (crdts -> checkClick(mousePos, mousePressed)) { Globals::scene = Globals::CREDITS;      break; }

        // Draw elements
        BeginDrawing();
        ClearBackground(PL_YELLOW);
        tileBG();

        DrawTexture(Assets::logo, logoX, logoY, WHITE);
        start -> draw();
        instr -> draw();
        crdts -> draw();
        DrawTextEx(Assets::uifont, MainMenuStr::byln, bylinePos, FONT_SIZE, 0, BLACK);

        EndDrawing();
    }

    // Deallocate Buttons
    delete start;
    delete instr;
    delete crdts;
}

void Difficulty() {

    // Init text
    short boxX          = (W_WINDOW - Assets::ui_box.width)  / 2;
    short boxY          = (H_WINDOW - Assets::ui_box.height) / 2;

    Vector2 diffTxtSize = MeasureTextEx(Assets::uifont, DiffStr::diffTxt, FONT_SIZE, 0);
    Vector2 diffTxtPos  = {
        static_cast<float>(boxX + (Assets::ui_box.width - diffTxtSize.x) / 2),
        static_cast<float>(boxY + 100)
    };

    // Init btuttons
    Button* back = new Button(Vector2 {CENTER_X_WINDOW,       CENTER_Y_WINDOW + 155 }, &Assets::btn, &Assets::btn_down);
    Button* easy = new Button(Vector2 {CENTER_X_WINDOW - 160, CENTER_Y_WINDOW - 35  }, &Assets::btn, &Assets::btn_down);
    Button* medi = new Button(Vector2 {CENTER_X_WINDOW,       CENTER_Y_WINDOW - 35  }, &Assets::btn, &Assets::btn_down);
    Button* hard = new Button(Vector2 {CENTER_X_WINDOW + 160, CENTER_Y_WINDOW - 35  }, &Assets::btn, &Assets::btn_down);

    back -> addLabel(MiscMenuStr::back, LIFT, 8);
    easy -> addLabel(DiffStr::easy,     LIFT, 8);
    medi -> addLabel(DiffStr::medi,     LIFT, 8);
    hard -> addLabel(DiffStr::hard,     LIFT, 8);

    // Init scoreboard strings
    Vector2 scoreTxtSize = MeasureTextEx(Assets::uifont, DiffStr::scrs, FONT_SIZE, 0);
    Vector2 scoreTxtPos  = {
        static_cast<float>(CENTER_X_WINDOW - scoreTxtSize.x / 2),
        static_cast<float>(CENTER_Y_WINDOW + 30)
    };


    // allocate 15 char long string buffer for high score values
    char* hsStr = (char*) malloc(sizeof(char) * 15);
    snprintf(
        hsStr, 15, DiffStr::hscr,
        Globals::highscores[Globals::EASY  ],
        Globals::highscores[Globals::MEDIUM],
        Globals::highscores[Globals::HARD  ]
    );
    
    Vector2 scoreValSize = MeasureTextEx(Assets::uifont, DiffStr::hscr, FONT_SIZE, 0);
    Vector2 scoreValPos  = {
        scoreTxtPos.x + scoreTxtSize.x - scoreValSize.x,
        scoreTxtPos.y + scoreTxtSize.y - scoreValSize.y + 4
    };

    Vector2 mousePos;
    bool    mousePressed;

    while(Globals::scene == Globals::DIFFICULTY && !WindowShouldClose()) {

        // Handle Button Events
        mousePos        = GetMousePosition();
        mousePressed    = IsMouseButtonDown(MOUSE_BUTTON_LEFT);

        if (back -> checkClick(mousePos, mousePressed)) {
            Globals::scene = Globals::MAIN_MENU; break; 
        } else if (easy -> checkClick(mousePos, mousePressed)) {
            Globals::difficulty = Globals::EASY;
            Globals::scene      = Globals::IN_GAME;
            break;
        } else if (medi -> checkClick(mousePos, mousePressed)) {
            Globals::difficulty = Globals::MEDIUM;
            Globals::scene      = Globals::IN_GAME;
            break;
        } else if (hard -> checkClick(mousePos, mousePressed)) {
            Globals::difficulty = Globals::HARD;
            Globals::scene      = Globals::IN_GAME;
            break;
        }

        // Draw elements
        BeginDrawing();
        ClearBackground(PL_YELLOW);
        tileBG();

        DrawTexture(Assets::ui_box, boxX, boxY, WHITE);
        DrawTextEx(Assets::uifont, DiffStr::diffTxt, diffTxtPos, FONT_SIZE, 0, WHITE);
        DrawTextEx(Assets::uifont,  DiffStr::scrs, scoreTxtPos, FONT_SIZE, 0, WHITE);
        DrawTextEx(Assets::numfont, hsStr,   scoreValPos, FONT_SIZE, 0, PL_YELLOW);
        easy -> draw();
        medi -> draw();
        hard -> draw();
        back -> draw();
        
        EndDrawing();
    }

    delete back;
    delete easy;
    delete medi;
    delete hard;
    free(hsStr);

}

#define FRAMETIMER_INIT 0.4
#define FRAME_COUNT     7
#define FRAME_HEIGHT    104

void Instructions() {

    // Init box coords.
    short boxX          = (W_WINDOW - Assets::ui_box.width ) / 2;
    short boxY          = (H_WINDOW - Assets::ui_box.height) / 2;

    // Calculate instr. text coords.
    Vector2 instTxtSize = MeasureTextEx(Assets::uifont, InstructionsStr::instTxt, FONT_SIZE, 0);
    Vector2 instTxtPos = {
        static_cast<float>(boxX + (Assets::ui_box.width - instTxtSize.x) / 2), 
        static_cast<float>(boxY + 50)
    };

    // Init visualization sprite
    AnimatedSprite* instructionVis = new AnimatedSprite(
        Vector2{CENTER_X_WINDOW, CENTER_Y_WINDOW - 20}, &Assets::instruction, FRAME_HEIGHT, FRAME_COUNT, FRAMETIMER_INIT, LOOPABLE
    );

    // Init back btn
    Button* back = new Button(Vector2 {CENTER_X_WINDOW, CENTER_Y_WINDOW + 155}, &Assets::btn, &Assets::btn_down);
    back -> addLabel(MiscMenuStr::back, LIFT, 8);

    Vector2 mousePos;

    while(Globals::scene == Globals::INSTRUCTIONS && !WindowShouldClose()) {

        // Handle Button Events
        mousePos = GetMousePosition();
        if(back -> checkClick(mousePos, IsMouseButtonDown(MOUSE_BUTTON_LEFT))) { Globals::scene = Globals::MAIN_MENU; break; }

        // Handle visualisation animation
        instructionVis -> updateFrame(GetFrameTime());

        // Draw elements
        BeginDrawing();
        ClearBackground(PL_YELLOW);
        tileBG();

        DrawTexture(Assets::ui_box, boxX, boxY, WHITE);
        DrawTextEx(Assets::uifont, InstructionsStr::instTxt, instTxtPos, FONT_SIZE, 0, WHITE);
        instructionVis -> draw();
        back -> draw();

        EndDrawing();
    }

    delete instructionVis;
    delete back;

}

void Credits() {

    // Init text
    short boxX = (W_WINDOW - Assets::ui_box.width) / 2;
    short boxY = (H_WINDOW - Assets::ui_box.height) / 2;
    
    Vector2 credTxtSize = MeasureTextEx(Assets::uifont, CreditsStr::credTxt, FONT_SIZE, 0);
    Vector2 credTxtPos  = {
        static_cast<float>(boxX + (Assets::ui_box.width  - credTxtSize.x) / 2),
        static_cast<float>(boxY + (Assets::ui_box.height - credTxtSize.y) / 2)
    };

    // Init back btn
    Button* back = new Button(Vector2 {CENTER_X_WINDOW, CENTER_Y_WINDOW + 155}, &Assets::btn, &Assets::btn_down);
    back -> addLabel(MiscMenuStr::back, LIFT, 8);

    Vector2 mousePos;

    while(Globals::scene == Globals::CREDITS && !WindowShouldClose()) {

        // Handle Button Events
        mousePos = GetMousePosition();
        if(back -> checkClick(mousePos, IsMouseButtonDown(MOUSE_BUTTON_LEFT))) { Globals::scene = Globals::MAIN_MENU; break; }

        // Draw elements
        BeginDrawing();
        ClearBackground(PL_YELLOW);
        tileBG();

        DrawTexture(Assets::ui_box, boxX, boxY, WHITE);
        DrawTextEx(Assets::uifont, CreditsStr::credTxt, credTxtPos, FONT_SIZE, 0, WHITE);
        back -> draw();
        
        EndDrawing();

    }

    delete back;
    
}