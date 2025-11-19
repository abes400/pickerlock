#include <math.h>
#include <stdio.h>

#include "raylib.h"

#include "gamesetup.h"
#include "globals.h"
#include "commonvisuals.h"

#include "menustr.hpp"
#include "button.hpp"

#include "assets.hpp"


void MainMenu() {
    
    // Init logo coordinates
    short logoX = (W_WINDOW - Assets::logo.width) / 2;

    // Initialise MainMenu Elements
    Button* start = new Button(Vector2 {CENTER_X_WINDOW, H_WINDOW - 177}, &Assets::start_btn,   &Assets::start_btn_down);
    Button* instr = new Button(Vector2 {CENTER_X_WINDOW, H_WINDOW - 115}, &Assets::btn,         &Assets::btn_down);
    Button* crdts = new Button(Vector2 {CENTER_X_WINDOW, H_WINDOW - 60 }, &Assets::btn,         &Assets::btn_down);

    instr -> addLabel(MainMenuStr::inst, LIFT, 8);
    crdts -> addLabel(MainMenuStr::cred, LIFT, 8);

    // Init scoreboard strings
    Vector2 scoreTxtSize = MeasureTextEx(Assets::uifont, MainMenuStr::scrs, FONT_SIZE, 0);
    Vector2 scoreTxtPos  = {
        static_cast<float>(logoX + (Assets::ui_box.width - scoreTxtSize.x) / 2),
        static_cast<float>(Assets::logo.height + 5)
    };

    int HSeasy = 4, HSmedium = 8, HShard = 120;

    // allocate 15 char long string buffer for high score values
    char* hsStr = (char*) malloc(sizeof(char) * 15);
    sprintf(hsStr, MainMenuStr::hscr, HSeasy, HSmedium, HShard);
    
    Vector2 scoreValSize = MeasureTextEx(Assets::uifont, MainMenuStr::hscr, FONT_SIZE, 0);
    Vector2 scoreValPos  = {
        scoreTxtPos.x + scoreTxtSize.x - scoreValSize.x,
        scoreTxtPos.y + scoreTxtSize.y/4
    };
    
    Vector2 mousePos;
    bool    mousePressed;

    // Menu Loop
    while(scene == MAIN_MENU && !WindowShouldClose()) {

        // Handle Input Events
        mousePos         = GetMousePosition();
        mousePressed     = IsMouseButtonDown(MOUSE_BUTTON_LEFT);

        if      (start -> checkClick(mousePos, mousePressed)) { scene = DIFFICULTY;   break; }
        else if (instr -> checkClick(mousePos, mousePressed)) { scene = INSTRUCTIONS; break; }
        else if (crdts -> checkClick(mousePos, mousePressed)) { scene = CREDITS;      break; }

        // Draw elements
        BeginDrawing();
        ClearBackground(PL_YELLOW);
        tileBG();

        DrawTexture(Assets::logo, logoX, 0, WHITE);
        DrawTextEx(Assets::uifont, MainMenuStr::scrs, scoreTxtPos, FONT_SIZE, 0, BLACK);
        DrawTextEx(Assets::uifont, hsStr,   scoreValPos, FONT_SIZE, 0, BLACK);
        start -> draw();
        instr -> draw();
        crdts -> draw();

        EndDrawing();
    }

    // Deallocate Buttons
    delete start;
    delete instr;
    delete crdts;
    free(hsStr);
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
    Button* easy = new Button(Vector2 {CENTER_X_WINDOW - 160, CENTER_Y_WINDOW       }, &Assets::btn, &Assets::btn_down);
    Button* medi = new Button(Vector2 {CENTER_X_WINDOW,       CENTER_Y_WINDOW       }, &Assets::btn, &Assets::btn_down);
    Button* hard = new Button(Vector2 {CENTER_X_WINDOW + 160, CENTER_Y_WINDOW       }, &Assets::btn, &Assets::btn_down);

    back -> addLabel(MiscMenuStr::back, LIFT, 8);
    easy -> addLabel(DiffStr::easy,     LIFT, 8);
    medi -> addLabel(DiffStr::medi,     LIFT, 8);
    hard -> addLabel(DiffStr::hard,     LIFT, 8);

    Vector2 mousePos;
    bool    mousePressed;

    while(scene == DIFFICULTY && !WindowShouldClose()) {

        // Handle Button Events
        mousePos        = GetMousePosition();
        mousePressed    = IsMouseButtonDown(MOUSE_BUTTON_LEFT);

        if      (back -> checkClick(mousePos, mousePressed)) { scene = MAIN_MENU; break; }
        else if (easy -> checkClick(mousePos, mousePressed)) {  }
        else if (medi -> checkClick(mousePos, mousePressed)) {  }
        else if (hard -> checkClick(mousePos, mousePressed)) {  }

        // Draw elements
        BeginDrawing();
        ClearBackground(PL_YELLOW);
        tileBG();

        DrawTexture(Assets::ui_box, boxX, boxY, WHITE);
        DrawTextEx(Assets::uifont, DiffStr::diffTxt, diffTxtPos, FONT_SIZE, 0, WHITE);
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

    // Init visualization animation
    float frameTimer    = FRAMETIMER_INIT;
    short frameIndex    = FRAME_COUNT;
    Rectangle frameCrop = {0, 0, static_cast<float>(Assets::instruction.width), FRAME_HEIGHT};
    Vector2 framePos    = {
        static_cast<float>((W_WINDOW - Assets::instruction.width) / 2),
        static_cast<float>((H_WINDOW - FRAME_HEIGHT)/2 - 20)
    };

    // Init back btn
    Button* back = new Button(Vector2 {CENTER_X_WINDOW, CENTER_Y_WINDOW + 155}, &Assets::btn, &Assets::btn_down);
    back -> addLabel(MiscMenuStr::back, LIFT, 8);

    Vector2 mousePos;

    while(scene == INSTRUCTIONS && !WindowShouldClose()) {

        // Handle Button Events
        mousePos = GetMousePosition();
        if(back -> checkClick(mousePos, IsMouseButtonDown(MOUSE_BUTTON_LEFT))) { scene = MAIN_MENU; break; }

        // Handle visualisation animation
        frameTimer -= GetFrameTime();
        if(frameTimer < 0) {
            frameTimer = FRAMETIMER_INIT;
            frameIndex++;
            if(frameIndex >= FRAME_COUNT)
                frameIndex = 0;
            frameCrop.y = frameIndex * FRAME_HEIGHT;
        }

        // Draw elements
        BeginDrawing();
        ClearBackground(PL_YELLOW);
        tileBG();

        DrawTexture(Assets::ui_box, boxX, boxY, WHITE);
        DrawTextEx(Assets::uifont, InstructionsStr::instTxt, instTxtPos, FONT_SIZE, 0, WHITE);
        DrawTextureRec(Assets::instruction, frameCrop, framePos, WHITE);
        back -> draw();

        EndDrawing();
    }

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

    while(scene == CREDITS && !WindowShouldClose()) {

        // Handle Button Events
        mousePos = GetMousePosition();
        if(back -> checkClick(mousePos, IsMouseButtonDown(MOUSE_BUTTON_LEFT))) { scene = MAIN_MENU; break; }

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