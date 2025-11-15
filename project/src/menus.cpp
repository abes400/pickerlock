#include "gameloops.hpp"
#include "raylib.h"
#include <math.h>
#include "gamesetup.h"
#include "button.hpp"

extern Texture2D background;
extern Texture2D start_btn, start_btn_down, btn, btn_down, ui_box;
extern short tileRow;
extern short tileCol;
extern float tileAnimOffset;
extern short scene;

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
        }

        else if(instr -> checkClick(mousePos, mousePressed)) {
        }

        else if(crdts -> checkClick(mousePos, mousePressed)) {
        }

        // Draw elements
        BeginDrawing();
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


void Instructions() {

}

void Credits() {

}

// Tiles the background texture in an animated manner
void TileBG() {
    for(int i = 0; i < tileCol; i++)
        for(int j = 0; j < tileRow; j++)
            DrawTexture(background, i * background.width - tileAnimOffset, j * background.height - tileAnimOffset, WHITE);
    tileAnimOffset = tileAnimOffset >= background.width ? 0 : tileAnimOffset + 40 * GetFrameTime();  
}