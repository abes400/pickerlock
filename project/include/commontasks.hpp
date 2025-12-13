#pragma once

void init();
void unload();
void tileBG();
void close();
void terminate(int code);
bool delayIsOver(float deltaTime, float* timer, float delayLength);