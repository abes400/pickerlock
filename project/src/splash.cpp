#include "raylib.h"
#include "globals.hpp"
#include "commontasks.hpp"
#include "gamesetup.h"

#define SPLASH_TIME 1
#define START_DELAY 2
#define END_DELAY 0.5
#define LOGO_GAP 100
#define LIFT 25
void Splash() {

    // Calculate logo coordinates

    short ttlW  = Assets::a400logo.width + Assets::jamlogo.width + LOGO_GAP;
    short a400X = Globals::winCenterX - ttlW / 2;
    short a400Y = Globals::winCenterY - LIFT - Assets::a400logo.height / 2;

    short gJamX = a400X + Assets::jamlogo.width + LOGO_GAP;
    short gJamY = Globals::winCenterY - LIFT - Assets::jamlogo.height  / 2;

    Vector2 presPos = {Globals::winCenterX - 50, Globals::winCenterY + 50};

    float timer = START_DELAY;

    while (!WindowShouldClose() && !delayIsOver(&timer, START_DELAY)) {
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
    }

    timer = SPLASH_TIME;
    PlaySound(Assets::unlock);

    while (!WindowShouldClose() && !delayIsOver(&timer, SPLASH_TIME)) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(Assets::a400logo, a400X, a400Y, WHITE);
        DrawTexture(Assets::jamlogo , gJamX, gJamY, WHITE);
        DrawTextEx(Assets::uifont, "Present...", presPos, Assets::uifont.baseSize, FONT_SPACING, WHITE);
        EndDrawing();
    }

    timer = END_DELAY;
    while (!WindowShouldClose() && !delayIsOver(&timer, END_DELAY)) {
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
    }
}