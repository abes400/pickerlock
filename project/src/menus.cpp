#include "gameloops.hpp"
#include "raylib.h"
#include <math.h>
#include <iostream>
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
    Button* start = new Button(Vector2 {CENTER_X_WINDOW, H_WINDOW - 200}, &start_btn, &start_btn_down);
    Button* instr = new Button(Vector2 {CENTER_X_WINDOW, H_WINDOW - 130}, &btn, &btn_down);
    
    Vector2 mousePos;
    bool mousePressed;
    while(scene == MAIN_MENU && !WindowShouldClose()) {

        mousePos = GetMousePosition();
        mousePressed = IsMouseButtonDown(MOUSE_BUTTON_LEFT);

        if(start -> checkClick(mousePos, mousePressed)) {
            std::cout << "start 1 clicked\n";
        }

        if(instr -> checkClick(mousePos, mousePressed)) {
            std::cout << "start 1 clicked\n";
        }

        // Draw elements
        BeginDrawing();
        TileBG();
        start -> draw();
        instr -> draw();
        EndDrawing();
    }

    delete start;
    delete instr;

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