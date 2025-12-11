#include "raylib.h"
#include "globals.h"
#include "commonvisuals.h"
#include "assets.hpp"
#include "sprite.hpp"
#include "gamesetup.h"
#include "arrowtile.hpp"

#include <iostream>
using namespace std;

#define LOCK_HEIGHT       325
#define LOCK_FRAME_COUNT  7
#define LOCK_FRAME_TIME   0.05

#define ARROW_HEIGHT      100
#define ARROW_FRAME_COUNT 8
#define ARROW_FRAME_TIME  0.05

void Game() {
    ////////////////////
    // Init game vars //
    ////////////////////

    // Initialize Lock Animation Sprite
    static const AnimatedSpriteProp lockProp = AnimatedSpriteProp { &Assets::lockwindow, LOCK_HEIGHT, LOCK_FRAME_COUNT, LOCK_FRAME_TIME };
    AnimatedSprite* lockAnim                 = new AnimatedSprite ( Vector2{CENTER_X_WINDOW, CENTER_Y_WINDOW - 100}, &lockProp, LOOPABLE );
    lockAnim -> setOriginAsCenter();

    // Initialize arrow tiles
    static const AnimatedSpriteProp tileProp = AnimatedSpriteProp { &Assets::arrowtile, ARROW_HEIGHT, ARROW_FRAME_COUNT, ARROW_FRAME_TIME };
    
    const short tileCount   = Globals::difficulty + 3;
    float       tileX       = CENTER_X_WINDOW - Assets::arrowtile.width * (tileCount - 1) / 2;
    float       tileY       = CENTER_Y_WINDOW + 200;
    
    ArrowTile* tiles[tileCount];
    for(short i = 0 ; i < tileCount ; i++) {
        tiles[i] = new ArrowTile(Vector2{tileX, tileY}, &tileProp);
        tileX += Assets::arrowtile.width;
    }

    short tile_i;

    // Game Loop
    while (Globals::scene == Globals::IN_GAME && !WindowShouldClose()) {
        // Handle Input Events
        if(IsKeyPressed(KEY_SPACE))
            for(tile_i = 0 ; tile_i < tileCount; tile_i++) {
                tiles[tile_i] -> decideDirection();
                tiles[tile_i] -> setFrame(0);
            }
                

        // Update states
        lockAnim -> updateFrame();
        for(tile_i = 0 ; tile_i < tileCount; tile_i++)
            tiles[tile_i] -> updateFrame();
                
        // Draw Elements
        BeginDrawing();
        tileBG();
        lockAnim -> draw();
        for(tile_i = 0 ; tile_i < tileCount; tile_i++)
            tiles[tile_i] -> draw();
        EndDrawing();
    }

    // De-init game vars in heap
    delete lockAnim;
    for(tile_i = 0 ; tile_i < tileCount ; tile_i++)
        delete tiles[tile_i];
    
}