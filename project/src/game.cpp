#include <stdlib.h>
#include <stdio.h>

#include "raylib.h"

#include "gamesetup.h"
#include "globals.hpp"
#include "sprite.hpp"
#include "arrowtile.hpp"
#include "gamestr.hpp"
#include "commontasks.hpp"

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

#define SCORE_STR_LEN 5
#define TIME_STR_LEN  3

enum GameState { GET_READY = 0, START, INPUT, ADVANCE, WRONG_MOVE, TIME_UP, DISQUALIFIED };

void updateAllTiles         (short tileCount, ArrowTile** arrowTiles, float deltaTime);
void decideDirectionForAll  (short tileCount, ArrowTile** arrowTiles);
void resetAllTiles          (short tileCount, ArrowTile** arrowTiles);
void drawAllTiles           (short tileCount, ArrowTile** arrowTiles);

Directions getDirectionFromKey (short* frameNumber);

struct GameSprites {

};

void Game() {

    // Coordinates for the stat box. 
    // Stored as variables since it has to adapt to different screen resolutions.
    float boxX = Globals::winCenterX - Assets::statbox.width  / 2;
    float boxY = Globals::winCenterY + 150;

    Vector2 statTxtPos  = Vector2{boxX + 70, boxY + 35 };
    Vector2 timeTxtPos  = Vector2{statTxtPos.x + 80, statTxtPos.y};
    Vector2 scoreTxtPos = Vector2{timeTxtPos.x, timeTxtPos.y + 19 };

    // Initialize Sprite Properties
    static const AnimatedSpriteProp lockProp = AnimatedSpriteProp   { &Assets::lockwindow, LOCK_HEIGHT, LOCK_FRAME_COUNT, LOCK_FRAME_TIME };
    static const AnimatedSpriteProp tileProp = AnimatedSpriteProp   { &Assets::arrowtile, ARROW_HEIGHT, ARROW_FRAME_COUNT, ARROW_FRAME_TIME };
    static const SpriteVProp        handProp = SpriteVProp          { &Assets::hand, HAND_HEIGHT, HAND_FRAME_COUNT };
    static const SpriteVProp        cardProp = SpriteVProp          { &Assets::cards, CARD_HEIGHT, CARD_FRAME_COUNT };

    // Initialize Sprite Objects
    AnimatedSprite* lockAnim     = new AnimatedSprite   ( Vector2{Globals::winCenterX, Globals::winCenterY - 100}, &lockProp );
    SpriteV*        hand         = new SpriteV          ( Vector2{Globals::winCenterX + 120, Globals::winCenterY - 102}, &handProp); 
    SpriteV*        card         = new SpriteV          ( Vector2{Globals::winCenterX, Globals::winCenterY+80}, &cardProp );

    // Centralize Origins
    lockAnim    -> setOriginAsCenter();
    hand        -> setOriginAsCenter();
    card        -> setOriginAsCenter();
    card        -> setFrame(0);
    
    // Initialize Tiles (Do not centralize origins as theirs are kinda done automatically)
    const short tileCount   = Globals::difficulty + 3;
    float       tileX       = Globals::winCenterX - Assets::arrowtile.width * (tileCount - 1) / 2;
    float       tileY       = Globals::winCenterY + 80;
    
    ArrowTile* tiles[5];
    for(short i = 0 ; i < tileCount ; i++) {
        tiles[i] = new ArrowTile(Vector2{tileX, tileY}, &tileProp);
        tileX   += Assets::arrowtile.width;
    }


    // Game Context (ntbcw. "OpenGL context") variables
    enum  GameState  gameState      = GET_READY;
    enum  Directions keyDirection   = NONE;

    float deltaTime;

    short current_tile      = 0;
    short handFrame         = 0;

    float cardTimer         = READY_TIME;
    bool  cardVisible       = true;

    // The overall gameplay time is stored as discrete integer.
    // It has nothing to do with delays.
    // Actual inter-frame delays are held by gameTimerDelay variable.
    bool  timerActive       = false;
    float gameTimerDelay    = 1;

    short gameTimer         = 20;
    int   score             = 0;


    // Allocating string buffers to be fed into RayLib to show timer and score
    char* scoreStr = (char*) malloc(sizeof(char) * 5);
    char* timeStr  = (char*) malloc(sizeof(char) * 5);
    
    // Clean up and kill the program if allocation fails
    // bc. it won't make any sense to run the process anymore at this point
    if(!scoreStr || !timeStr) 
        terminate(EXIT_FAILURE);

    snprintf(scoreStr, SCORE_STR_LEN, GameStr::scoref, score    );
    snprintf(timeStr,  TIME_STR_LEN,  GameStr::timef,  gameTimer);

    decideDirectionForAll(tileCount, tiles);
    resetAllTiles(tileCount, tiles);

    PlaySound(Assets::beep);
    PlayMusicStream(Assets::gameBgm);

    // Game Loop
    while (Globals::scene == Globals::IN_GAME && !WindowShouldClose()) {
        UpdateMusicStream(Assets::gameBgm);
        deltaTime = GetFrameTime();

        switch(gameState) {
            case GET_READY:
                if (delayIsOver(&cardTimer, READY_TIME, deltaTime)) {
                    card -> setFrame(1);
                    PlaySound(Assets::slam);
                    gameState = START;
                }
            break;
            case START:
                if (delayIsOver(&cardTimer, START_TIME, deltaTime)) {
                        cardVisible = false;
                        timerActive = true;
                        gameState = INPUT;
                }
            break;
            case INPUT:
                keyDirection = getDirectionFromKey(&handFrame);
                if(keyDirection != NONE) {
                    PlaySound(Assets::dial);
                    hand -> setFrame(handFrame);
                    if(tiles[current_tile] -> direction == keyDirection) {
                        tiles[current_tile] -> is_playing = PLAY;
                        current_tile++;

                        if(current_tile >= tileCount) {
                            snprintf(scoreStr, SCORE_STR_LEN, GameStr::scoref, ++score);
                            current_tile = 0;
                            hand -> setFrame(1);
                            lockAnim -> is_playing = PLAY;
                            PlaySound(Assets::unlock);
                            gameState = ADVANCE;
                        }
                    } else {
                        tiles[current_tile] -> setFrame(0);
                        timerActive = false;
                        StopMusicStream(Assets::gameBgm);
                        PlaySound(Assets::buzzer);
                        gameState = WRONG_MOVE;
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
            case WRONG_MOVE:
                if(delayIsOver(&cardTimer, GMEND_TIME, deltaTime)) {
                    hand -> setFrame(5);
                    card -> setFrame(3);
                    cardVisible = true;
                    cardTimer = GMEND_TIME;
                    PlaySound(Assets::grunt);
                    gameState = DISQUALIFIED;
                }
            break;
            case DISQUALIFIED: case TIME_UP:
                if(delayIsOver(&cardTimer, GMEND_TIME, deltaTime)) {
                    StopMusicStream(Assets::gameBgm);
                    Globals::scene = Globals::DIFFICULTY;
                }
                    
            break;
        }

        updateAllTiles(tileCount, tiles, deltaTime);
        if(timerActive && delayIsOver(&gameTimerDelay, 1, deltaTime)) {
            gameTimer--;
            gameTimerDelay = 1;
            snprintf(timeStr,  TIME_STR_LEN,  GameStr::timef,  gameTimer);
            if(gameTimer == 0) {
                timerActive = false;
                if(score > Globals::highscores[Globals::difficulty])
                    Globals::highscores[Globals::difficulty] = score;
                card -> setFrame(2);
                hand -> setFrame(4);
                cardVisible = true;
                PlaySound(Assets::wohoo);
                cardTimer = GMEND_TIME;
                gameState = TIME_UP;
            }      
        }
                
        // Draw Elements
        BeginDrawing();
        ClearBackground(PL_YELLOW);
        tileBG();

        lockAnim -> draw();
        hand     -> draw();

        drawAllTiles(tileCount, tiles);

        DrawTexture (Assets::statbox, boxX, boxY, WHITE);
        DrawTextEx  (Assets::uifont, GameStr::statTxt, statTxtPos, Assets::uifont.baseSize, FONT_SPACING, WHITE);
        DrawTextEx  (Assets::numfont, timeStr, timeTxtPos, Assets::numfont.baseSize, NUMF_SPACING, PL_YELLOW);
        DrawTextEx  (Assets::numfont, scoreStr, scoreTxtPos, Assets::numfont.baseSize, NUMF_SPACING, WHITE);

        if(cardVisible) card -> draw();
        DrawFPS(0, 0);
        
        EndDrawing();
    }

    // Clean heap
    free (scoreStr);
    free (timeStr );

    delete lockAnim;
    delete hand;
    delete card;
    for(short i = 0 ; i < tileCount ; i++)
        delete tiles[i];
    
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

void drawAllTiles (short tileCount, ArrowTile** arrowTiles) {
    for(short i = 0; i < tileCount; i++)
        arrowTiles[i] -> draw();
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
