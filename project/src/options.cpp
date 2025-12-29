#include "raylib.h"

#include "globals.hpp"
#include "commontasks.hpp"
#include "options.hpp"

namespace Opts {
    bool sfx = true;
    bool msc = true;
    bool fsc = false;
}
#include<stdio.h>
/**
 * Applies the music setting according to value of Opts::msc
 */
void applyMusic() {
    printf("msc: %d", Opts::msc);
    float newVol = Opts::msc ? 1: 0;
    SetMusicVolume(Assets::gameBgm, newVol);
    SetMusicVolume(Assets::menuBgm, newVol);
}

/**
 * Applies the music setting according to value of Opts::sfx
 */
void applySfx() {
    float newVol = Opts::sfx ? 1: 0;
    SetSoundVolume(Assets::beep,    newVol);
    SetSoundVolume(Assets::buzzer,  newVol);
    SetSoundVolume(Assets::dial,    newVol);
    SetSoundVolume(Assets::grunt,   newVol);
    SetSoundVolume(Assets::slam,    newVol);
    SetSoundVolume(Assets::unlock,  newVol);
    SetSoundVolume(Assets::wohoo,   newVol);
}

/**
 * Properly toggles fullscreen
 */
void toggleProperFullscreen() {
    #ifdef __APPLE__
    ToggleFullscreen();
    #else
    ToggleBorderlessWindowed();
    #endif
    adaptResolution(Opts::fsc);
}