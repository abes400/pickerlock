#include <math.h>
#include <stdio.h>

#include "raylib.h"

#include "gamesetup.h"
#include "globals.h"
#include "commontasks.hpp"

#include "menustr.hpp"
#include "button.hpp"

#include "assets.hpp"
#include "sprite.hpp"

#include<iostream>
using namespace std;

void MainMenu() {
    
    // Init logo coordinates
    float logoX = Globals::winCenterX - Assets::logo.width / 2;
    float logoY = Globals::winCenterY - Assets::logo.height * 2;

    // Initialise MainMenu Elements
    Button* start = new Button(Vector2 {Globals::winCenterX, Globals::winCenterY + 85  }, &Assets::start_btn,   &Assets::start_btn_down);
    Button* instr = new Button(Vector2 {Globals::winCenterX, Globals::winCenterY + 150 }, &Assets::btn,         &Assets::btn_down);
    Button* crdts = new Button(Vector2 {Globals::winCenterX, Globals::winCenterY + 210 }, &Assets::btn,         &Assets::btn_down);

    instr -> addLabel(MainMenuStr::inst, LIFT, 8);
    crdts -> addLabel(MainMenuStr::cred, LIFT, 8);

    // Initialize ByLine
    Vector2 bylinePos   = { static_cast<float>(Globals::winCenterX - 230), static_cast<float>(Globals::windowHeight - 32) };

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
        DrawTextEx(Assets::uifont, MainMenuStr::byln, bylinePos, Assets::uifont.baseSize, FONT_SPACING, WHITE);

        EndDrawing();
    }

    // Deallocate Buttons
    delete start;
    delete instr;
    delete crdts;
}

void Difficulty() {

    // Init text
    float boxX          = (Globals::windowWidth - Assets::ui_box.width)  / 2;
    float boxY          = (Globals::windowHeight - Assets::ui_box.height) / 2;

    Vector2 diffTxtPos  = { boxX + 231, boxY + 50 };

    // Init btuttons
    Button* back = new Button(Vector2 {Globals::winCenterX,       Globals::winCenterY + 155 }, &Assets::btn, &Assets::btn_down);
    Button* easy = new Button(Vector2 {Globals::winCenterX - 170, Globals::winCenterY - 35  }, &Assets::btn, &Assets::btn_down);
    Button* medi = new Button(Vector2 {Globals::winCenterX,       Globals::winCenterY - 35  }, &Assets::btn, &Assets::btn_down);
    Button* hard = new Button(Vector2 {Globals::winCenterX + 170, Globals::winCenterY - 35  }, &Assets::btn, &Assets::btn_down);

    back -> addLabel(MiscMenuStr::back, LIFT, 8);
    easy -> addLabel(DiffStr::easy,     LIFT, 8);
    medi -> addLabel(DiffStr::medi,     LIFT, 8);
    hard -> addLabel(DiffStr::hard,     LIFT, 8);

    // Init scoreboard strings
    Vector2 scoreTxtPos  = { Globals::winCenterX - 77, Globals::winCenterY + 30};

    // allocate 15 char long string buffer for high score values
    char* hsStr = (char*) malloc(sizeof(char) * 15);

    // Clean up and kill the program if allocation fails
    // bc. it won't make any sense to run the process anymore at this point
    if(!hsStr) 
        terminate(EXIT_FAILURE);

    snprintf(
        hsStr, 15, DiffStr::hscr,
        Globals::highscores[Globals::EASY  ],
        Globals::highscores[Globals::MEDIUM],
        Globals::highscores[Globals::HARD  ]
    );
    
    Vector2 scoreValPos  = { scoreTxtPos.x + 105, scoreTxtPos.y + 16 };

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
        DrawTextEx(Assets::uifont, DiffStr::diffTxt, diffTxtPos, Assets::uifont.baseSize, FONT_SPACING, WHITE);
        DrawTextEx(Assets::uifont,  DiffStr::scrs, scoreTxtPos, Assets::uifont.baseSize, FONT_SPACING, WHITE);
        DrawTextEx(Assets::numfont, hsStr,   scoreValPos, Assets::numfont.baseSize, NUMF_SPACING, WHITE);
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
#define FRAME_HEIGHT    101

void Instructions() {

    // Init box coords.
    float boxX          = (Globals::windowWidth - Assets::ui_box.width ) / 2;
    float boxY          = (Globals::windowHeight - Assets::ui_box.height) / 2;

    // Calculate instr. text coords.
    Vector2 instTxtPos = { boxX + 23, boxY + 30 };

    // Init visualization sprite
    static const AnimatedSpriteProp instProp = AnimatedSpriteProp { 
        &Assets::instruction, FRAME_HEIGHT, FRAME_COUNT, FRAMETIMER_INIT
    };
    AnimatedSprite* instAnim = new AnimatedSprite(Vector2{Globals::winCenterX, Globals::winCenterY - 20}, &instProp, LOOPABLE);
    instAnim -> setOriginAsCenter();
    instAnim -> is_playing = PLAY;

    // Init back btn
    Button* back = new Button(Vector2 {Globals::winCenterX, Globals::winCenterY + 155}, &Assets::btn, &Assets::btn_down);
    back -> addLabel(MiscMenuStr::back, LIFT, 8);

    Vector2 mousePos;

    while(Globals::scene == Globals::INSTRUCTIONS && !WindowShouldClose()) {

        // Handle Button Events
        mousePos = GetMousePosition();
        if(back -> checkClick(mousePos, IsMouseButtonDown(MOUSE_BUTTON_LEFT))) { Globals::scene = Globals::MAIN_MENU; break; }

        // Handle visualisation animation
        instAnim -> updateFrame();

        // Draw elements
        BeginDrawing();
        ClearBackground(PL_YELLOW);
        tileBG();

        DrawTexture(Assets::ui_box, boxX, boxY, WHITE);
        DrawTextEx(Assets::uifont, InstructionsStr::instTxt, instTxtPos, Assets::uifont.baseSize, FONT_SPACING, WHITE);
        instAnim -> draw();
        back -> draw();

        EndDrawing();
    }

    delete instAnim;
    delete back;

}

void Credits() {

    // Init text
    float boxX = (Globals::windowWidth - Assets::ui_box.width) / 2;
    float boxY = (Globals::windowHeight - Assets::ui_box.height) / 2;
    
    Vector2 credTxtPos  = { boxX + 142, boxY + 70 };

    // Init back btn
    Button* back = new Button(Vector2 {Globals::winCenterX, Globals::winCenterY + 155}, &Assets::btn, &Assets::btn_down);
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
        DrawTextEx(Assets::uifont, CreditsStr::credTxt, credTxtPos, Assets::uifont.baseSize, FONT_SPACING, WHITE);
        back -> draw();
        
        EndDrawing();

    }

    delete back;
    
}