#pragma once
#include "raylib.h"
#include "sprite.h"

class AnimatedSprite : public SpriteV {
    private:
        float frame_time_init_;
        float frame_timer_;

    public:
        AnimatedSprite(Vector2 position, Texture2D* spriteSheet, float frameHeight, short frameCount, float frameTimeSecond, int frameIndex);
        void updateFrame(float deltaTime);

};