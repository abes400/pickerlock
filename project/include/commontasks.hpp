#pragma once
#include "raylib.h"

/**
 * Loads assets on assets directory.
 */
void loadAssets();

/**
 * Unloads the assets
 */
void unloadAssets();

/**
 * Sets the proper resolution depending on the Fullscreen state and calculates the center of the window.
 * 
 * If fullScreen is true, the resolution is set for the native screen.
 * 
 * Otherwise, it is 800 by 600.
 * @param fullScreen Whether the resolution is adapted for the fullscreen or not.
 */
void adaptResolution (bool fullScreen);

/**
 * Tiles the background texture in an animated manner.
 * @param deltaTime The time that passed between the last frames.
 */
void tileBG(float deltaTime = GetFrameTime());

/**
 * "Asynchronously" holds delay and returns whether it is over.
 * @param timer The variable to hold the time with
 * @param delayLength How long the delay should be
 * @param deltaTime The time that passed between the last frames.
 * @return Whether the timer had reached 0 or not.
 */
bool delayIsOver(float* timer, float delayLength, float deltaTime = GetFrameTime());

/**
 * Prepares the process for the proper closing of the Application.
 * 
 * Unloads the assets and closes the window.
 */
void closeApplication();

/**
 * Prepares the process for the proper closing of the Application if something goes wrong.
 * 
 * No need to call closeApplication() since it is called here as well
 * 
 * @param code The error code to end the process with.
 */
void terminate(int code);
