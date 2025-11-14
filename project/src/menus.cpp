#include "gameloops.hpp"
#include "raylib.h"
#include <math.h>
#include "gamesetup.h"
#include "button.hpp"

extern Texture2D background;
extern short tileRow;
extern short tileCol;
extern short scene;

void TileBG(Texture2D&, int, int);

void init() {
    background = LoadTexture("assets/texture/bg.png");
    tileRow = ceil(H_WINDOW / background.height) + 1;
    tileCol = ceil(W_WINDOW / background.width);
}

void MainMenu() {
    Button* start = new Button("assets/texture/start.png", Vector2 {CENTER_X_WINDOW, H_WINDOW - 200});
    while(scene == MAIN_MENU && !WindowShouldClose()) {

        // Draw
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
            DrawTexture(texture, i * texture.width, j * texture.height, WHITE);
}