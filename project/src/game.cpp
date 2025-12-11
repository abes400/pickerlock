#include "raylib.h"
#include "globals.h"
#include "commonvisuals.h"
#include "assets.hpp"
#include "sprite.hpp"
#include "gamesetup.h"

#include <iostream>
using namespace std;

#define LOCK_HEIGHT       325
#define LOCK_FRAME_COUNT  7
#define LOCK_FRAME_TIME   0.05

#define ARROW_HEIGHT      100
#define ARROW_FRAME_COUNT 7
#define ARROW_FRAME_TIME  0.05

void Game() {
    ////////////////////
    // Init game vars //
    ////////////////////

    // Initialize Lock Animation Sprite
    static const AnimatedSpriteProp lockProp = AnimatedSpriteProp { &Assets::lockwindow, LOCK_HEIGHT, LOCK_FRAME_COUNT, LOCK_FRAME_TIME };
    AnimatedSprite* lockAnim                 = new AnimatedSprite ( Vector2{CENTER_X_WINDOW, CENTER_Y_WINDOW - 100}, &lockProp, LOOPABLE );

    // Initialize arrow tiles
    const  short tileCount = Globals::difficulty + 3;

    short tile_i;

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