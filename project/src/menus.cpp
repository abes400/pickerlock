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
extern short tileAnimOffset;
extern short scene;

void TileBG(Texture2D&, int, int);

void MainMenu() {
    Button* start = new Button(Vector2 {CENTER_X_WINDOW, H_WINDOW - 200}, &start_btn, &start_btn_down);
    
    Vector2 mousePos;
    bool mousePressed, mouseReleased;
    while(scene == MAIN_MENU && !WindowShouldClose()) {

        mousePos = GetMousePosition();
        mousePressed = IsMouseButtonDown(MOUSE_BUTTON_LEFT);

        if(start -> checkClick(mousePos, mousePressed)) {
            std::cout << "start 1 clicked\n";
        }


        // Draw elements
        BeginDrawing();
        TileBG(background, tileRow, tileCol);
        start -> draw();
        EndDrawing();
    }

    delete start;

}


void Instructions() {

}

void Credits() {

}

void TileBG(Texture2D& texture, int row, int col) {
    for(int i = 0; i < col; i++)
        for(int j = 0; j < row; j++)
            DrawTexture(texture, i * texture.width - tileAnimOffset, j * texture.height - tileAnimOffset, WHITE);
    //tileAnimOffset = tileAnimOffset == texture.width ? 0 : tileAnimOffset + 1;
            
}