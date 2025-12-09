#pragma once
#include "raylib.h"

class SpriteV {
    private:
        Texture2D* texture_;

    protected:
        Vector2 position_;
        float frameH_;
        short frameCount_;
        short current_frame_ = 0;

        Rectangle frame_crop_;

    public:
        SpriteV(Vector2 position, Texture2D* spriteSheet, float frameHeight, short frameCount, short frameIndex);
        void setFrame(short frame);
        void draw();

};