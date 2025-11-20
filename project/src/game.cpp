#include "raylib.h"
#include "globals.h"
#include "commonvisuals.h"

#include <iostream>
using namespace std;

void Game() {
    cout << "GAME LOOP: \n";

    // Init game vars

    // Game Loop
    while (Globals::scene == Globals::IN_GAME && !WindowShouldClose()) {
        // Handle Input Events


        // Draw Elements
        BeginDrawing();
        tileBG();
        EndDrawing();
    }
    
}