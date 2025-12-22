#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

#include "gamesetup.h"
#include "button.hpp"
#include "checkbox.hpp"
#include "globals.hpp"
#include "menustr.hpp"
#include "commontasks.hpp"

void Difficulty() {

    if(!IsMusicStreamPlaying(Assets::menuBgm)) PlayMusicStream(Assets::menuBgm);

    // Init text
    float boxX          = (GetScreenWidth()  - Assets::ui_box.width ) / 2;
    float boxY          = (GetScreenHeight() - Assets::ui_box.height) / 2;

    Vector2 diffTxtPos  = Vector2 { boxX + 231, boxY         + 140 };
    Vector2 modeDscPos  = Vector2 { boxX + 160, diffTxtPos.y + 30  };

    // Pointer for desc. text
    const char* currentModeDesc = Globals::endless ? DiffStr::mdDsc2 : DiffStr::mdDsc1;

    // Init btuttons
    Button*     back = new Button   (Vector2 {Globals::winCenterX,       Globals::winCenterY + 200 }, &Assets::btn, &Assets::btn_down);
    Button*     easy = new Button   (Vector2 {Globals::winCenterX - 170, diffTxtPos.y + 175  }, &Assets::btn, &Assets::btn_down);
    Button*     medi = new Button   (Vector2 {Globals::winCenterX,       diffTxtPos.y + 175  }, &Assets::btn, &Assets::btn_down);
    Button*     hard = new Button   (Vector2 {Globals::winCenterX + 170, diffTxtPos.y + 175  }, &Assets::btn, &Assets::btn_down);
    Checkbox*   edls = new Checkbox (Vector2 {diffTxtPos.x        + 201, diffTxtPos.y - 2    }, &Assets::checkbox, 19, Globals::endless);

    back -> addLabel(MiscMenuStr::back, LIFT, 8);
    easy -> addLabel(DiffStr::easy,     LIFT, 8);
    medi -> addLabel(DiffStr::medi,     LIFT, 8);
    hard -> addLabel(DiffStr::hard,     LIFT, 8);

    // Init scoreboard strings
    Vector2 scoreTxtPos         = { Globals::winCenterX  - 167, boxY                 + 30 };
    Vector2 scoreValPos         = { scoreTxtPos.x        + 95,  scoreTxtPos.y        + 16 };
    Vector2 scoreTxtPosEndless  = { scoreTxtPos.x        + 170, scoreTxtPos.y             };
    Vector2 scoreValPosEndless  = { scoreTxtPosEndless.x + 95,  scoreTxtPosEndless.y + 16 };

    // allocate 15 char long string buffer for high score values
    char* hsStr         = (char*) malloc(sizeof(char) * 15);
    char* hsStrEndls    = (char*) malloc(sizeof(char) * 15);

    // Clean up and kill the program if allocation fails
    // bc. it won't make any sense to run the process anymore at this point
    if(!hsStr || !hsStrEndls)  terminate(EXIT_FAILURE);

    snprintf(
        hsStr, 15, DiffStr::hscr,
        Globals::highscores[Globals::EASY  ],
        Globals::highscores[Globals::MEDIUM],
        Globals::highscores[Globals::HARD  ]
    );
    snprintf(
        hsStrEndls, 15, DiffStr::hscr,
        Globals::highscoresEndless[Globals::EASY  ],
        Globals::highscoresEndless[Globals::MEDIUM],
        Globals::highscoresEndless[Globals::HARD  ]
    );

    Vector2 mousePos;
    bool    mousePressed;

    while(Globals::scene == Globals::DIFFICULTY && !WindowShouldClose()) {
        UpdateMusicStream(Assets::menuBgm);

        // Handle Button Events
        mousePos        = GetMousePosition();
        mousePressed    = IsMouseButtonDown(MOUSE_BUTTON_LEFT);

        if (back -> checkClick(mousePos, mousePressed)) {
            Globals::scene = Globals::MAIN_MENU; break; 
        } else if (easy -> checkClick(mousePos, mousePressed)) {
            Globals::difficulty = Globals::EASY;
            Globals::scene      = Globals::IN_GAME;
            StopMusicStream(Assets::menuBgm);
            break;
        } else if (medi -> checkClick(mousePos, mousePressed)) {
            Globals::difficulty = Globals::MEDIUM;
            Globals::scene      = Globals::IN_GAME;
            StopMusicStream(Assets::menuBgm);
            break;
        } else if (hard -> checkClick(mousePos, mousePressed)) {
            Globals::difficulty = Globals::HARD;
            Globals::scene      = Globals::IN_GAME;
            StopMusicStream(Assets::menuBgm);
            break;
        } else if (edls -> checkClick(mousePos)) {
            Globals::endless = edls -> isChecked;
            currentModeDesc  = Globals::endless ? DiffStr::mdDsc2 : DiffStr::mdDsc1;
        }

        // Draw elements
        BeginDrawing();
        ClearBackground(PL_YELLOW);
        tileBG();

        DrawTexture(Assets::ui_box, boxX, boxY, WHITE);
        DrawTextEx(Assets::uifont,  DiffStr::diffTxt, diffTxtPos,         Assets::uifont.baseSize,  FONT_SPACING, WHITE);
        DrawTextEx(Assets::uifont,  currentModeDesc,  modeDscPos,         Assets::uifont.baseSize,  FONT_SPACING, SKYBLUE);
        DrawTextEx(Assets::uifont,  DiffStr::scrs,    scoreTxtPos,        Assets::uifont.baseSize,  FONT_SPACING, WHITE);
        DrawTextEx(Assets::uifont,  DiffStr::scrsE,   scoreTxtPosEndless, Assets::uifont.baseSize,  FONT_SPACING, WHITE);
        DrawTextEx(Assets::numfont, hsStr,            scoreValPos,        Assets::numfont.baseSize, NUMF_SPACING, WHITE);
        DrawTextEx(Assets::numfont, hsStrEndls,       scoreValPosEndless, Assets::numfont.baseSize, NUMF_SPACING, WHITE);
        edls -> draw();
        easy -> draw();
        medi -> draw();
        hard -> draw();
        back -> draw();
        DrawTextureEx(Assets::cursor, mousePos, 0, 1, WHITE);
        
        EndDrawing();
    }

    delete back;
    delete easy;
    delete medi;
    delete hard;
    delete edls;
    free(hsStr);
    free(hsStrEndls);

}