#include "raylib.h"
#include "raymath.h"
#include "gamesetup.h"
#include <math.h>

#include <iostream>
using namespace std;

void TileBG(Texture2D&, int, int);

int main() {

    InitWindow(W_WINDOW, H_WINDOW, "Pickerlock");

    ChangeDirectory(GetApplicationDirectory());

    Texture2D background = LoadTexture("assets/texture/bg.png");
    const short tileRow = ceil(H_WINDOW / background.height) + 1;
    const short tileCol = ceil(W_WINDOW / background.width); 

    while(!WindowShouldClose()) {


        // DRAW
        BeginDrawing();
        ClearBackground(BLACK);
        //DrawTexture(background, 0, 0, WHITE);
        TileBG(background, tileRow, tileCol);

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