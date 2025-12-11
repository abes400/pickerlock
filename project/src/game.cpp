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

    // Initialize Lock Animation Sprite
    static const AnimatedSpriteProp lockProp = AnimatedSpriteProp {
        &Assets::lockwindow, 325, 7, 0.05
    };

    AnimatedSprite* lockAnim = new AnimatedSprite(Vector2{CENTER_X_WINDOW, CENTER_Y_WINDOW - 100}, &lockProp, LOOPABLE);

    // Initialize arrow tiles


    // Game Loop
    while (Globals::scene == Globals::IN_GAME && !WindowShouldClose()) {
        // Handle Input Events


        // Update states
        lockAnim -> updateFrame();
        


        // Draw Elements
        BeginDrawing();
        tileBG();
        lockAnim -> draw();
        EndDrawing();
    }

    // De-init game vars in heap
    delete lockAnim;
    
}