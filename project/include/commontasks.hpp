#pragma once
#include "raylib.h"

void init();
void unload();
void tileBG(float deltaTime = GetFrameTime());
void close();
void terminate(int code);
bool delayIsOver(float* timer, float delayLength, float deltaTime = GetFrameTime());