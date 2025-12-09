#include "sprite.hpp"

SpriteV::SpriteV(Vector2 position, Texture2D* spriteSheet, float frameHeight, short frameCount) {
    texture_    = spriteSheet;
    position_   = position;
    frameH_     = frameHeight;
    frameCount_ = frameCount;
    frame_crop_ = {0, 0, static_cast<float>(texture_ -> width), frameH_};

    position_.x -= texture_ -> width/2;
    position_.y -= frameH_/2;
}


void SpriteV::setFrame(short frame) {
    current_frame_  = frame;
    frame_crop_.y   = current_frame_ * frameH_;
}

bool SpriteV::isLastFrame() {
    return current_frame_ == frameCount_ - 1;
}

void SpriteV::draw() {
    DrawTextureRec(*texture_, frame_crop_, position_, WHITE);
}

