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
    static const AnimatedSpriteProp tileProp = AnimatedSpriteProp { &Assets::arrowtile, ARROW_HEIGHT, ARROW_FRAME_COUNT, ARROW_FRAME_TIME };
    float tileX                       = CENTER_X_WINDOW - Assets::arrowtile.width * (tileCount - 1) / 2;
    float tileY                       = CENTER_Y_WINDOW + 100;
    AnimatedSprite* tiles[tileCount];
    for(short i = 0; i < tileCount; i++) {
        tiles[i] = new AnimatedSprite(Vector2 {tileX, tileY}, &tileProp);
        tileX += Assets::arrowtile.width;
    }

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
        for(tile_i = 0; tile_i < tileCount; tile_i++) tiles[tile_i] -> draw();
        EndDrawing();
    }

    // De-init game vars in heap
    for(tile_i = 0; tile_i < tileCount; tile_i++) delete tiles[tile_i];
    delete lockAnim;
    
}