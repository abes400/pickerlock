#include "sprite.hpp"

AnimatedSprite::
AnimatedSprite(Vector2 position, Texture2D* spriteSheet, float frameHeight, short frameCount, float frameTimeSecond)
: SpriteV(position, spriteSheet, frameHeight, frameCount) {
    frame_time_init_ = frame_timer_ = frameTimeSecond;
}

void AnimatedSprite::updateFrame(float deltaTime) {
    frame_timer_ -= deltaTime;

    while(frame_timer_ < 0) {
        frame_timer_ += frame_time_init_;
        current_frame_ ++;
        
        if(current_frame_ >= frameCount_)
            current_frame_ = loop ? 0 : frameCount_ - 1;
    }

    frame_crop_.y = current_frame_ * frameH_;
}