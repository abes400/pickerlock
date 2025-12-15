#pragma once
#include "raylib.h"

void init();
void unload();
void tileBG();
void close();
void terminate(int code);
bool delayIsOver(float* timer, float delayLength, float deltaTime = GetFrameTime());