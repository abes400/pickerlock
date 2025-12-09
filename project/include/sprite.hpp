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
        SpriteV(Vector2 position, Texture2D* spriteSheet, float frameHeight, short frameCount);
        void setFrame(short frame);
        bool isLastFrame();
        void draw();
};

class AnimatedSprite : public SpriteV {
    private:
        float frame_time_init_;
        float frame_timer_;

    public:
        AnimatedSprite(Vector2 position, Texture2D* spriteSheet, float frameHeight, short frameCount, float frameTimeSecond);
        bool updateFrame(float deltaTime = GetFrameTime());

};