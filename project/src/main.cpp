#include <stdio.h>
#include <stdlib.h>
#include <climits>
#include "raylib.h"

#include "gamesetup.h"
#include "globals.hpp"
#include "options.hpp"
#include "gameloops.hpp"
#include "commontasks.hpp"
#include "savepath.hpp"
#include "fileoperations.hpp"

int main(int argc, char** argv) {

    // TODO : Prevent multiple instance loading
    // Generate the Path to the SAVE FILE and try loading from it
    initSavePath();
    loadFile();

    // Change app directory to Resources folder on MacOS
    #ifdef __APPLE__
    char* macOSPath = (char*) malloc(sizeof(char) * PATH_MAX);
    if(macOSPath) {
        snprintf(macOSPath, PATH_MAX, "%s/../Resources", GetApplicationDirectory());
        ChangeDirectory(macOSPath);
        free(macOSPath);
    } else return EXIT_FAILURE;
    #else
    ChangeDirectory(GetApplicationDirectory());
    #endif

    // Init game window
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(W_WINDOW, H_WINDOW, "Pickerlock");
    
    #ifdef _WIN32
    Image winIcon = LoadImage("texture/icon.png");
    SetWindowIcon(winIcon);
    UnloadImage(winIcon);
    #endif

    HideCursor();
    SetExitKey(KEY_NULL);

    // Init audio device
    InitAudioDevice();

    // Initialize texture structs
    loadAssets();

    // Apply settings
    applyMusic();
    applySfx();
    if(Opts::fsc) toggleProperFullscreen();

    // Show splash screen
    //Splash();

    // Game loop
    Globals::scene = Globals::MAIN_MENU;
    while(Globals::keepRunning && !WindowShouldClose()) {

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
    closeApplication();
    saveFile();
    return 0;
}