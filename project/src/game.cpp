#include "raylib.h"
#include "globals.h"
#include "commontasks.hpp"
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
#define ARROW_FRAME_TIME  0.03

#define HAND_HEIGHT       311
#define HAND_FRAME_COUNT  6

#define CARD_HEIGHT       100
#define CARD_FRAME_COUNT  3

#define READY_TIME 1
#define START_TIME 1
#define GMEND_TIME 3

enum GameState {
    GET_READY = 0,
    INPUT, ADVANCE, TIME_UP, DISQUALIFIED
};

void updateAllTiles         (short tileCount, ArrowTile** arrowTiles, float deltaTime);
void decideDirectionForAll  (short tileCount, ArrowTile** arrowTiles);
void resetAllTiles          (short tileCount, ArrowTile** arrowTiles);

Directions getDirectionFromKey (short* frameNumber);

void Game() {
    ////////////////////
    // Init game vars //
    ////////////////////

    // Initialize Lock Animation Sprite
    static const AnimatedSpriteProp lockProp = AnimatedSpriteProp { &Assets::lockwindow, LOCK_HEIGHT, LOCK_FRAME_COUNT, LOCK_FRAME_TIME };
    AnimatedSprite* lockAnim                 = new AnimatedSprite ( Vector2{CENTER_X_WINDOW, CENTER_Y_WINDOW - 100}, &lockProp );
    lockAnim -> setOriginAsCenter();

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

    // Initialize game cards
    static const SpriteVProp        cardProp = SpriteVProp { &Assets::cards, CARD_HEIGHT, CARD_FRAME_COUNT };
    SpriteV* card                            = new SpriteV( Vector2{CENTER_X_WINDOW, CENTER_Y_WINDOW+80}, &cardProp );
    card -> setOriginAsCenter();
    card -> setFrame(0);

    enum GameState gameState = GET_READY;

    short tile_i;
    short current_tile = 0;
    enum  Directions keyDirection = NONE;
    short handFrame = 0;
    float deltaTime;

    float cardTimer = READY_TIME;
    bool  cardVisible = true;

    bool  timerActive = false;
    short gameTimer = 20;
    float gameTimerDelay = 1;

    decideDirectionForAll(tileCount, tiles);
    resetAllTiles(tileCount, tiles);

    // Game Loop
    while (Globals::scene == Globals::IN_GAME && !WindowShouldClose()) {
        deltaTime = GetFrameTime();

        switch(gameState) {
            case GET_READY:
                if (delayIsOver(deltaTime, &cardTimer, READY_TIME)) {
                    cardVisible = false;
                    timerActive = true;
                    gameState = INPUT;
                }
            break;
            case INPUT:
                keyDirection = getDirectionFromKey(&handFrame);
                if(keyDirection != NONE) {
                    hand -> setFrame(handFrame);
                    if(tiles[current_tile] -> direction == keyDirection) {
                        tiles[current_tile] -> is_playing = PLAY;
                        current_tile++;

                        if(current_tile >= tileCount) {
                            current_tile = 0;
                            hand -> setFrame(1);
                            lockAnim -> is_playing = PLAY;
                            gameState = ADVANCE;
                        }
                    } else {
                        hand -> setFrame(5);
                        tiles[current_tile] -> setFrame(0);
                        card -> setFrame(3);
                        cardVisible = true;
                        timerActive = false;
                        cardTimer = GMEND_TIME;
                        gameState = DISQUALIFIED;
                    }
                }                
            break;
            case ADVANCE:
                lockAnim -> updateFrame(deltaTime);
                if(lockAnim -> is_playing == PAUSE) {
                    hand -> setFrame(0);
                    lockAnim -> setFrame(0);
                    decideDirectionForAll(tileCount, tiles);
                    resetAllTiles(tileCount, tiles);
                    gameState = INPUT;
                }

            break;
            case DISQUALIFIED: case TIME_UP:
                if(delayIsOver(deltaTime, &cardTimer, GMEND_TIME))
                    Globals::scene = Globals::DIFFICULTY;
            break;
        }

        updateAllTiles(tileCount, tiles, deltaTime);
        if(timerActive && delayIsOver(deltaTime, &gameTimerDelay, 1)) {
            gameTimer--;
            gameTimerDelay = 1;
            cout << "Update timer string to " << gameTimer << endl;
            if(gameTimer == 0) {
                timerActive = false;
                card -> setFrame(2);
                hand -> setFrame(4);
                cardVisible = true;
                cardTimer = GMEND_TIME;
                gameState = TIME_UP;
            }      
        }
                
        // Draw Elements
        BeginDrawing();
        tileBG();
        lockAnim -> draw();
        hand     -> draw();
        for(tile_i = 0 ; tile_i < tileCount; tile_i++)
            tiles[tile_i] -> draw();

        if(cardVisible)
            card -> draw();

        DrawFPS(0, 0);
        EndDrawing();
    }

    // De-init game vars in heap
    delete lockAnim;
    delete hand;
    delete card;
    for(tile_i = 0 ; tile_i < tileCount ; tile_i++)
        delete tiles[tile_i];
    
}


void decideDirectionForAll (short tileCount, ArrowTile** arrowTiles) {
    for(short i = 0; i < tileCount; i++)
        arrowTiles[i] -> decideDirection();
}

void updateAllTiles (short tileCount, ArrowTile** arrowTiles, float deltaTime) {
    for(short i = 0; i < tileCount; i++)
        arrowTiles[i] -> updateFrame(deltaTime);
}

void resetAllTiles (short tileCount, ArrowTile** arrowTiles) {
    for(short i = 0; i < tileCount; i++) {
        arrowTiles[i] -> is_playing = PAUSE;
        arrowTiles[i] -> setFrame(1);
    }   
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
    return NONE;
}