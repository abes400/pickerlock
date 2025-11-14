#include "raylib.h"
#include "raymath.h"
#include "gamesetup.h"
#include "button.hpp"
#include <math.h>

#include <iostream>
using namespace std;

void TileBG(Texture2D&, int, int);

void LoopMainMenu() {
    
}

int main() {
    
    ChangeDirectory(GetApplicationDirectory());
    InitWindow(W_WINDOW, H_WINDOW, "Pickerlock");

    Texture2D background = LoadTexture("assets/texture/bg.png");
    const short tileRow = ceil(H_WINDOW / background.height) + 1;
    const short tileCol = ceil(W_WINDOW / background.width);

    // Initialize Game Objects
    Button* startButton = new Button("assets/texture/start.png", Vector2 {CENTER_X_WINDOW, H_WINDOW - 200});
    

    short scene = MAIN_MENU;
    while(!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(BLACK);
        TileBG(background, tileRow, tileCol);

        switch(scene) {
            case MAIN_MENU:
                // Event Handling
                
                // Draw
                startButton -> draw();


            break;

            case IN_GAME:
            break;

            case INSTRUCTIONS:
            break;

            case CREDITS:
            break;
        }

        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}


void TileBG(Texture2D& texture, int row, int col) {
    for(int i = 0; i < col; i++)
        for(int j = 0; j < row; j++)
            DrawTexture(texture, i * texture.width, j * texture.height, WHITE);
}