#include "gameloops.hpp"
#include "raylib.h"
#include <math.h>
#include "gamesetup.h"
#include "button.hpp"
#include <iostream>
using namespace std;

extern Texture2D background;
extern Texture2D start_btn, start_btn_down, btn, btn_down, ui_box;
extern Texture2D instruction;
extern short tileRow;
extern short tileCol;
extern float tileAnimOffset;
extern short scene;
extern Font uifont;

void TileBG();

void MainMenu() {

    // Initialise MainMenu Elements
    Button* start = new Button(Vector2 {CENTER_X_WINDOW, H_WINDOW - 220}, &start_btn, &start_btn_down);

    Button* instr = new Button(Vector2 {CENTER_X_WINDOW, H_WINDOW - 140}, &btn, &btn_down);
    instr -> addLabel("Instructions", LIFT, 8);

    Button* crdts = new Button(Vector2 {CENTER_X_WINDOW, H_WINDOW - 60}, &btn, &btn_down);
    crdts -> addLabel("Credits", LIFT, 8);
    
    Vector2 mousePos;
    bool mousePressed;

    // Menu Loop
    while(scene == MAIN_MENU && !WindowShouldClose()) {

        // Handle Button Events
        mousePos = GetMousePosition();
        mousePressed = IsMouseButtonDown(MOUSE_BUTTON_LEFT);

        if(start -> checkClick(mousePos, mousePressed)) {
            scene = IN_GAME;
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
        ClearBackground(BLACK);
        TileBG();
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

#define FRAMETIMER_INIT 0.4
#define FRAME_COUNT 7
#define FRAME_HEIGHT 104
void Instructions() {

    // Init text
    short boxX = (W_WINDOW - ui_box.width) / 2;
    short boxY = (H_WINDOW - ui_box.height) / 2;

    char* instTxt = "Objective: \n"
                    "You are in a lock picking contest. \n"
                    "You are tasked to pick as many locks as you can in 20 seconds. \n\n\n\n\n\n\n\n"

                    "Instructions: \n"
                    "Press the arrow keys in the order given on screen to pick each lock. \n"
                    "As you successfully break a lock, you will be given the next one. \n"
                    "If you press the wrong button, you'll get disqualified.";

    Vector2 instTxtSize = MeasureTextEx(uifont, instTxt, FONT_SIZE, 0);

    short txtX = boxX + (ui_box.width - instTxtSize.x) / 2;
    short txtY = boxY + 50;

    // Init visualization
    float frameTimer;
    short frameIndex = FRAME_COUNT;
    Vector2 framePos = {static_cast<float>((W_WINDOW - instruction.width)/2), static_cast<float>((H_WINDOW - FRAME_HEIGHT)/2 - 20)};
    Rectangle frameCrop = {0, 0, static_cast<float>(instruction.width), FRAME_HEIGHT};


    // Init back btn
    Button* back = new Button(Vector2 {CENTER_X_WINDOW, H_WINDOW - 140}, &btn, &btn_down);
    back -> addLabel("Back", LIFT, 8);

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
        ClearBackground(BLACK);
        TileBG();

        DrawTexture(ui_box, boxX, boxY, WHITE);
        DrawTextEx(uifont, instTxt, {static_cast<float>(txtX), static_cast<float>(txtY)}, FONT_SIZE, 0, WHITE);
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

    char* instTxt =
                    "Pickerlock 1.0 \n\n"
                    "---- CREDITS ---- \n"
                    "Concept, Programming and Artwork : Abes400 \n\n"
                    "Sound effects (Probably) Obtained from ZapSplat. \n"
                    "Distributed under MIT License. \n\n"
                    "Made for 20 Seconds GameJam 2025\n";
    
    Vector2 instTxtSize = MeasureTextEx(uifont, instTxt, FONT_SIZE, 0);
    short txtX = boxX + (ui_box.width - instTxtSize.x) / 2;
    short txtY = boxY + (ui_box.height - instTxtSize.y) / 2;

    // Init back btn
    Button* back = new Button(Vector2 {CENTER_X_WINDOW, H_WINDOW - 140}, &btn, &btn_down);
    back -> addLabel("Back", LIFT, 8);

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
        ClearBackground(BLACK);
        TileBG();

        DrawTexture(ui_box, boxX, boxY, WHITE);
        DrawTextEx(uifont, instTxt, {static_cast<float>(txtX), static_cast<float>(txtY)}, FONT_SIZE, 0, WHITE);
        back -> draw();
        
        EndDrawing();

    }

}

// Tiles the background texture in an animated manner
void TileBG() {
    for(int i = 0; i < tileCol; i++)
        for(int j = 0; j < tileRow; j++)
            DrawTexture(background, i * background.width - tileAnimOffset, j * background.height - tileAnimOffset, WHITE);
    tileAnimOffset = tileAnimOffset >= background.width ? 0 : tileAnimOffset + 40 * GetFrameTime();  
}