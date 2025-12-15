#include "raylib.h"

#include "gamesetup.h"
#include "button.hpp"
#include "sprite.hpp"
#include "globals.hpp"
#include "menustr.hpp"
#include "commontasks.hpp"

#define FRAMETIMER_INIT 0.4
#define FRAME_COUNT     7
#define FRAME_HEIGHT    101

void Instructions() {

    // Init box coords.
    float boxX          = (Globals::windowWidth - Assets::ui_box.width ) / 2;
    float boxY          = (Globals::windowHeight - Assets::ui_box.height) / 2;

    // Calculate instr. text coords.
    Vector2 instTxtPos = { boxX + 23, boxY + 30 };

    // Init visualization sprite
    static const AnimatedSpriteProp instProp = AnimatedSpriteProp { 
        &Assets::instruction, FRAME_HEIGHT, FRAME_COUNT, FRAMETIMER_INIT
    };
    AnimatedSprite* instAnim = new AnimatedSprite(Vector2{Globals::winCenterX, Globals::winCenterY - 20}, &instProp, LOOPABLE);
    instAnim -> setOriginAsCenter();
    instAnim -> is_playing = PLAY;

    // Init back btn
    Button* back = new Button(Vector2 {Globals::winCenterX, Globals::winCenterY + 155}, &Assets::btn, &Assets::btn_down);
    back -> addLabel(MiscMenuStr::back, LIFT, 8);

    Vector2 mousePos;

    float deltaTime;

    while(Globals::scene == Globals::INSTRUCTIONS && !WindowShouldClose()) {
        UpdateMusicStream(Assets::menuBgm);
        deltaTime = GetFrameTime();

        // Handle Button Events
        mousePos = GetMousePosition();
        if(back -> checkClick(mousePos, IsMouseButtonDown(MOUSE_BUTTON_LEFT))) { Globals::scene = Globals::MAIN_MENU; break; }

        // Handle visualisation animation
        instAnim -> updateFrame(deltaTime);

        // Draw elements
        BeginDrawing();
        ClearBackground(PL_YELLOW);
        tileBG(deltaTime);

        DrawTexture(Assets::ui_box, boxX, boxY, WHITE);
        DrawTextEx(Assets::uifont, InstructionsStr::instTxt, instTxtPos, Assets::uifont.baseSize, FONT_SPACING, WHITE);
        instAnim -> draw();
        back -> draw();
        DrawTextureEx(Assets::cursor, mousePos, 0, 1, WHITE);

        EndDrawing();
    }

    delete instAnim;
    delete back;

}

void Credits() {

    // Init text
    float boxX = (Globals::windowWidth - Assets::ui_box.width) / 2;
    float boxY = (Globals::windowHeight - Assets::ui_box.height) / 2;

    float logoX = boxX + Assets::ui_box.width - Assets::jamlogo.width - 30;
    float logoY = boxY + 20;
    
    Vector2 credTxtPos  = { boxX + 22, boxY + 32 };

    // Init back btn
    Button* back = new Button(Vector2 {Globals::winCenterX, Globals::winCenterY + 155}, &Assets::btn, &Assets::btn_down);
    back -> addLabel(MiscMenuStr::back, LIFT, 8);

    Vector2 mousePos;

    while(Globals::scene == Globals::CREDITS && !WindowShouldClose()) {
        UpdateMusicStream(Assets::menuBgm);

        // Handle Button Events
        mousePos = GetMousePosition();
        if(back -> checkClick(mousePos, IsMouseButtonDown(MOUSE_BUTTON_LEFT))) { Globals::scene = Globals::MAIN_MENU; break; }

        // Draw elements
        BeginDrawing();
        ClearBackground(PL_YELLOW);
        tileBG();

        DrawTexture(Assets::ui_box, boxX, boxY, WHITE);
        DrawTexture(Assets::jamlogo, logoX, logoY, WHITE);
        DrawTextEx(Assets::uifont, CreditsStr::credTxt, credTxtPos, Assets::uifont.baseSize, FONT_SPACING, WHITE);
        back -> draw();
        DrawTextureEx(Assets::cursor, mousePos, 0, 1, WHITE);
        
        EndDrawing();

    }

    delete back;
    
}