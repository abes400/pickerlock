#pragma once
#include "raylib.h"

void loadAssets();
void unloadAssets();
void adaptResolution (bool fullScreen);
void tileBG(float deltaTime = GetFrameTime());
void closeApplication();
void terminate(int code);
bool delayIsOver(float* timer, float delayLength, float deltaTime = GetFrameTime());