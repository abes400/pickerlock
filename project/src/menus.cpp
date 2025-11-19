#include "gameloops.hpp"
#include "raylib.h"
#include <math.h>
#include "gamesetup.h"
#include "button.hpp"
#include <iostream>
using namespace std;

#include "globals.h"
#include "menustr.hpp"

void TileBG();

void MainMenu() {
    
    // Init logo
    short logoX = (W_WINDOW - logo.width) / 2;

    // Initialise MainMenu Elements
    Button* start = new Button(Vector2 {CENTER_X_WINDOW, H_WINDOW - 205}, &start_btn, &start_btn_down);

    Button* instr = new Button(Vector2 {CENTER_X_WINDOW, H_WINDOW - 140}, &btn, &btn_down);
    instr -> addLabel(MainMenuStr::inst, LIFT, 8);

    Button* crdts = new Button(Vector2 {CENTER_X_WINDOW, H_WINDOW - 80}, &btn, &btn_down);
    crdts -> addLabel(MainMenuStr::cred, LIFT, 8);
    
    Vector2 mousePos;
    bool mousePressed;

    // Menu Loop
    while(scene == MAIN_MENU && !WindowShouldClose()) {

        // Handle Button Events
        mousePos = GetMousePosition();
        mousePressed = IsMouseButtonDown(MOUSE_BUTTON_LEFT);

        if(start -> checkClick(mousePos, mousePressed)) {
            scene = DIFFICULTY;
            break;
        }

        else if(instr -> checkClick(mousePos, mousePressed)) {
            scene = INSTRUCTIONS;
            break;
        }

        else if(crdts -> checkClick(mousePos, mousePressed)) {
            scene = CREDITS;
            break;
        }

        // Draw elements
        BeginDrawing();
        ClearBackground(PL_YELLOW);
        TileBG();
        DrawTexture(logo, logoX, 0, WHITE);
        start -> draw();
        instr -> draw();
        crdts -> draw();
        EndDrawing();
    }

    // Deallocate Buttons
    delete start;
    delete instr;
    delete crdts;

}

void Difficulty() {
    // Init text
    short boxX = (W_WINDOW - ui_box.width) / 2;
    short boxY = (H_WINDOW - ui_box.height) / 2;

    
    Vector2 instTxtSize = MeasureTextEx(uifont, DiffStr::diffTxt, FONT_SIZE, 0);
    short txtX = boxX + (ui_box.width - instTxtSize.x) / 2;
    short txtY = boxY + 100;

    // Init btuttons
    Button* back = new Button(Vector2 {CENTER_X_WINDOW, H_WINDOW - 140}, &btn, &btn_down);
    back -> addLabel(MiscMenuStr::back, LIFT, 8);

    Button* easy = new Button(Vector2 {CENTER_X_WINDOW - 160, CENTER_Y_WINDOW}, &btn, &btn_down);
    easy -> addLabel(DiffStr::easy, LIFT, 8);

    Button* medi = new Button(Vector2 {CENTER_X_WINDOW, CENTER_Y_WINDOW}, &btn, &btn_down);
    medi -> addLabel(DiffStr::medi, LIFT, 8);

    Button* hard = new Button(Vector2 {CENTER_X_WINDOW + 160, CENTER_Y_WINDOW}, &btn, &btn_down);
    hard -> addLabel(DiffStr::hard, LIFT, 8);

    Vector2 mousePos;

    while(scene == DIFFICULTY && !WindowShouldClose()) {
        // Handle Button Events
        mousePos = GetMousePosition();

        if(back -> checkClick(mousePos, IsMouseButtonDown(MOUSE_BUTTON_LEFT))) {
            scene = MAIN_MENU;
            break;
        }

        // Draw elements
        BeginDrawing();
        ClearBackground(PL_YELLOW);
        TileBG();

        DrawTexture(ui_box, boxX, boxY, WHITE);
        DrawTextEx(uifont, DiffStr::diffTxt, {static_cast<float>(txtX), static_cast<float>(txtY)}, FONT_SIZE, 0, WHITE);

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
#define FRAME_COUNT 7
#define FRAME_HEIGHT 104
void Instructions() {

    // Init text
    short boxX = (W_WINDOW - ui_box.width) / 2;
    short boxY = (H_WINDOW - ui_box.height) / 2;

    Vector2 instTxtSize = MeasureTextEx(uifont, InstructionsStr::instTxt, FONT_SIZE, 0);

    short txtX = boxX + (ui_box.width - instTxtSize.x) / 2;
    short txtY = boxY + 50;

    // Init visualization
    float frameTimer = FRAMETIMER_INIT;
    short frameIndex = FRAME_COUNT;
    Vector2 framePos = {static_cast<float>((W_WINDOW - instruction.width)/2), static_cast<float>((H_WINDOW - FRAME_HEIGHT)/2 - 20)};
    Rectangle frameCrop = {0, 0, static_cast<float>(instruction.width), FRAME_HEIGHT};


    // Init back btn
    Button* back = new Button(Vector2 {CENTER_X_WINDOW, H_WINDOW - 140}, &btn, &btn_down);
    back -> addLabel(MiscMenuStr::back, LIFT, 8);

    Vector2 mousePos;


    while(scene == INSTRUCTIONS && !WindowShouldClose()) {

        // Handle Button Events
        mousePos = GetMousePosition();

        if(back -> checkClick(mousePos, IsMouseButtonDown(MOUSE_BUTTON_LEFT))) {
            scene = MAIN_MENU;
            break;
        }

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
        TileBG();

        DrawTexture(ui_box, boxX, boxY, WHITE);
        DrawTextEx(uifont, InstructionsStr::instTxt, {static_cast<float>(txtX), static_cast<float>(txtY)}, FONT_SIZE, 0, WHITE);
        DrawTextureRec(instruction, frameCrop, framePos, WHITE);
        back -> draw();

        EndDrawing();
    }

    delete back;

}

void Credits() {
    // Init text
    short boxX = (W_WINDOW - ui_box.width) / 2;
    short boxY = (H_WINDOW - ui_box.height) / 2;
    
    Vector2 instTxtSize = MeasureTextEx(uifont, CreditsStr::credTxt, FONT_SIZE, 0);
    short txtX = boxX + (ui_box.width - instTxtSize.x) / 2;
    short txtY = boxY + (ui_box.height - instTxtSize.y) / 2;

    // Init back btn
    Button* back = new Button(Vector2 {CENTER_X_WINDOW, H_WINDOW - 140}, &btn, &btn_down);
    back -> addLabel(MiscMenuStr::back, LIFT, 8);

    Vector2 mousePos;

    while(scene == CREDITS && !WindowShouldClose()) {
        // Handle Button Events
        mousePos = GetMousePosition();

        if(back -> checkClick(mousePos, IsMouseButtonDown(MOUSE_BUTTON_LEFT))) {
            scene = MAIN_MENU;
            break;
        }

        // Draw elements
        BeginDrawing();
        ClearBackground(PL_YELLOW);
        TileBG();

        DrawTexture(ui_box, boxX, boxY, WHITE);
        DrawTextEx(uifont, CreditsStr::credTxt, {static_cast<float>(txtX), static_cast<float>(txtY)}, FONT_SIZE, 0, WHITE);
        back -> draw();
        
        EndDrawing();

    }

    delete back;

}

// Tiles the background texture in an animated manner
void TileBG() {
    for(int i = 0; i < tileCol; i++)
        for(int j = 0; j < tileRow; j++)
            DrawTexture(background, i * background.width - tileAnimOffset, j * background.height - tileAnimOffset, WHITE);
    tileAnimOffset = tileAnimOffset >= background.width ? 0 : tileAnimOffset + 40 * GetFrameTime();  
}