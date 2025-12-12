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
#define LOCK_FRAME_TIME   0.03

#define ARROW_HEIGHT      100
#define ARROW_FRAME_COUNT 8
#define ARROW_FRAME_TIME  0.05

#define HAND_HEIGHT       311
#define HAND_FRAME_COUNT  6

enum GameState {
    GET_READY = 0,
    INPUT, ADVANCE, TIME_UP, DISQUALIFIED
};

void decideDirectionForAll (short tileCount, ArrowTile** arrowTiles) {
    for(short i = 0; i < tileCount; i++)
        arrowTiles[i] -> decideDirection();
}

Directions getDirectionFromKey (short* frameNumber) {
    if      (IsKeyPressed(KEY_UP)) {
        *frameNumber = 0;
        return UP;
    }     
    else if (IsKeyPressed(KEY_DOWN)) {
        *frameNumber = 0;
        return DOWN;
    }
    else if (IsKeyPressed(KEY_LEFT)) {
        *frameNumber = 3;
        return LEFT;
    }   
    else if (IsKeyPressed(KEY_RIGHT)) {
        *frameNumber = 2;
        return RIGHT;
    }  
}

void Game() {
    ////////////////////
    // Init game vars //
    ////////////////////

    // Initialize Lock Animation Sprite
    static const AnimatedSpriteProp lockProp = AnimatedSpriteProp { &Assets::lockwindow, LOCK_HEIGHT, LOCK_FRAME_COUNT, LOCK_FRAME_TIME };
    AnimatedSprite* lockAnim                 = new AnimatedSprite ( Vector2{CENTER_X_WINDOW, CENTER_Y_WINDOW - 100}, &lockProp, LOOPABLE );
    lockAnim -> setOriginAsCenter();
    lockAnim -> is_playing = PLAY;

    // Initialize Hand Animation Sprite
    static const SpriteVProp        handProp = SpriteVProp { &Assets::hand, HAND_HEIGHT, HAND_FRAME_COUNT };
    SpriteV* hand                            = new SpriteV(Vector2{CENTER_X_WINDOW + 120, CENTER_Y_WINDOW - 102}, &handProp); 
    hand -> setOriginAsCenter();

    // Initialize arrow tiles
    static const AnimatedSpriteProp tileProp = AnimatedSpriteProp { &Assets::arrowtile, ARROW_HEIGHT, ARROW_FRAME_COUNT, ARROW_FRAME_TIME };
    
    const short tileCount   = Globals::difficulty + 3;
    float       tileX       = CENTER_X_WINDOW - Assets::arrowtile.width * (tileCount - 1) / 2;
    float       tileY       = CENTER_Y_WINDOW + 80;
    
    ArrowTile* tiles[tileCount];
    for(short i = 0 ; i < tileCount ; i++) {
        tiles[i] = new ArrowTile(Vector2{tileX, tileY}, &tileProp);
        tileX   += Assets::arrowtile.width;
    }

    enum GameState gameState = INPUT;

    short tile_i;

    decideDirectionForAll(tileCount, tiles);

    // Game Loop
    while (Globals::scene == Globals::IN_GAME && !WindowShouldClose()) {

        switch(gameState) {
            case GET_READY:
            break;
            case INPUT:
                if(IsKeyPressed(KEY_SPACE)) {
                    hand -> setFrame(1);
                    gameState = ADVANCE;
                }
            break;
            case ADVANCE:
                lockAnim -> updateFrame();
                if(lockAnim -> isLastFrame()) {
                    lockAnim -> setFrame(0);
                    hand -> setFrame(0);
                    decideDirectionForAll(tileCount, tiles);
                    gameState = INPUT;
                }
            break;
            case TIME_UP:
            break;
            case DISQUALIFIED:
            break;
        }
                
        // Draw Elements
        BeginDrawing();
        tileBG();
        lockAnim -> draw();
        hand     -> draw();
        for(tile_i = 0 ; tile_i < tileCount; tile_i++)
            tiles[tile_i] -> draw();

        DrawFPS(0, 0);
        EndDrawing();
    }

    // De-init game vars in heap
    delete lockAnim;
    delete hand;
    for(tile_i = 0 ; tile_i < tileCount ; tile_i++)
        delete tiles[tile_i];
    
}