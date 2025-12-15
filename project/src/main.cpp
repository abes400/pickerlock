#include "raylib.h"

#include "globals.hpp"
#include "gameloops.hpp"
#include "commontasks.hpp"

int main(int argc, char** argv) {
    
    ChangeDirectory(GetApplicationDirectory());

    // Init game window
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(Globals::windowWidth, Globals::windowHeight, "Pickerlock");

    // Cursor not hidden in web build since it malfunctions
    // Instead, the cursor is hidden in shell.html by CSS
    #ifndef PLATFORM_WEB
    HideCursor();
    #endif

    // Init audio device
    InitAudioDevice();

    // Initialize texture structs
    init();

    // Show splash screen
    Splash();

    // Game loop
    Globals::scene = Globals::MAIN_MENU;
    while(!WindowShouldClose()) {

        switch(Globals::scene) {
            case Globals::MAIN_MENU:
            MainMenu();
            break;
            case Globals::DIFFICULTY:
            Difficulty();
            break;
            case Globals::IN_GAME:
            Game();
            break;
            case Globals::INSTRUCTIONS:
            Instructions();
            break;
            case Globals::OPTIONS:
            Options();
            break;
            case Globals::CREDITS:
            Credits();
            break;
        }

    }
    close();
    return 0;
}