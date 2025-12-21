#include "raylib.h"

#include "globals.hpp"
#include "gameloops.hpp"
#include "commontasks.hpp"

#include <iostream>
using namespace std;

int main(int argc, char** argv) {

    // TODO : Prevent multiple instance loading

    // Change app directory to Resources folder on MacOS
    #ifdef __APPLE__
    cout << "----------------------------------> macOS\n";
    char* macOSPath = (char*) malloc(sizeof(char) * PATH_MAX);
    if(macOSPath) {
        snprintf(macOSPath, PATH_MAX, "%s/../Resources", GetApplicationDirectory());
        ChangeDirectory(macOSPath);
        free(macOSPath);
    } else return EXIT_FAILURE;
    #else
    cout << "----------------------------------> NOT macOS\n";
    ChangeDirectory(GetApplicationDirectory());
    #endif

    // Init game window
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(Globals::windowWidth, Globals::windowHeight, "Pickerlock");
    
    #ifdef _WIN32
    cout << "----------------------------------> Windows\n";
    Image winIcon = LoadImage("texture/icon.png");
    SetWindowIcon(winIcon);
    UnloadImage(winIcon);
    #endif

    HideCursor();

    // Init audio device
    InitAudioDevice();

    // Initialize texture structs
    init();

    // Show splash screen
    //Splash();

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