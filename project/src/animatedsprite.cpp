#include "animatedsprite.hpp"

AnimatedSprite::AnimatedSprite(Vector2 position, Texture2D* spriteSheet, 
    float frameHeight, short frameCount, float frameTimeSecond, int frameIndex = 0)
: SpriteV(position, spriteSheet, frameHeight, frameCount, frameIndex) {
    frame_time_init_ = frame_timer_ = frameTimeSecond;
}

void AnimatedSprite::updateFrame(float deltaTime = GetFrameTime()) {
    frame_timer_ -= deltaTime;
    if(frame_timer_ < 0) {
        frame_timer_ = frame_time_init_;
        current_frame_ ++;
        if(current_frame_ >= frameCount_)
            current_frame_ = 0;

        frame_crop_.y = current_frame_ * frameH_;
    }
}