#include "sprite.hpp"

/////////////////// IMPLEMENTATION OF SPRITEVPROP ///////////////////
template<typename T>
SpriteVProp<T>::SpriteVProp(Texture2D* spriteSheet, float frameHeight, short frameCount)
: texture_(spriteSheet), frameH_(frameHeight), frameCount_(frameCount) {}

/////////////////////////////////////////////////////////////////////


/////////////////// IMPLEMENTATION OF SPRITEV ///////////////////
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
/////////////////////////////////////////////////////////////////


/////////////////// IMPLEMENTATION OF ANIMATEDSPRITE ///////////////////
AnimatedSprite::
AnimatedSprite(Vector2 position, Texture2D* spriteSheet, float frameHeight, short frameCount, float frameTimeSecond, bool loop)
: SpriteV(position, spriteSheet, frameHeight, frameCount) {
    frame_time_init_ = frame_timer_ = frameTimeSecond;
    this -> loop = loop;
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
////////////////////////////////////////////////////////////////////////