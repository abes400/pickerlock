#include "raylib.h"
#include "globals.h"
#include "commonvisuals.h"
#include "assets.hpp"
#include "sprite.hpp"
#include "gamesetup.h"

#include <iostream>
using namespace std;

void Game() {
    // Init game vars
    short tileCount = Globals::difficulty + 3;
    
    cout << "The difficulty is " << Globals::difficulty << " so the tile count will be " << tileCount << endl;


    AnimatedSprite* lockSprite = new AnimatedSprite(
        Vector2{CENTER_X_WINDOW, CENTER_Y_WINDOW - 100}, &Assets::lockwindow, 325, 7, 0.05
    );

    // Game Loop
    while (Globals::scene == Globals::IN_GAME && !WindowShouldClose()) {
        // Handle Input Events


        // Update states
        


        // Draw Elements
        BeginDrawing();
        tileBG();
        lockSprite -> draw();
        EndDrawing();
    }

    // De-init game vars in heap
    delete lockSprite;
    
}