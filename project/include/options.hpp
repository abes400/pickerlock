#pragma once
namespace Opts {
    extern bool sfx;
    extern bool msc;
    extern bool fsc;
}

/**
 * Applies the music setting according to value of Opts::msc
 */
void applyMusic();

/**
 * Applies the music setting according to value of Opts::sfx
 */
void applySfx();

/**
 * Properly toggles fullscreen
 */
void toggleProperFullscreen();