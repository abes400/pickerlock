#include "raylib.h"
#include "sprite.hpp"

/////////////////// IMPLEMENTATION OF SPRITEV ///////////////////
SpriteV::SpriteV (Vector2 position, const SpriteVProp* spriteProperty) {

    prop_ = spriteProperty;
    position_   = position;

    frame_crop_ = {0, 0, static_cast<float>(prop_ -> texture_ -> width), prop_ -> frameH_};
}

void SpriteV::setOriginAsCenter() {
    position_.x -= prop_ -> texture_ -> width/2;
    position_.y -= prop_ -> frameH_/2;
}


void SpriteV::setFrame(short frame) {
    current_frame_  = frame;
    frame_crop_.y   = current_frame_ * prop_ -> frameH_;
}

void SpriteV::draw() {
    DrawTextureRec(*(prop_ -> texture_), frame_crop_, position_, WHITE);
}
/////////////////////////////////////////////////////////////////


/////////////////// IMPLEMENTATION OF ANIMATEDSPRITE ///////////////////
AnimatedSprite::
AnimatedSprite(Vector2 position, const AnimatedSpriteProp* spriteProperty, Loopability loopable)
: SpriteV(position, spriteProperty) {
    frame_timer_ = spriteProperty -> frame_timer_second_;
    loop = loopable;
}

void AnimatedSprite::setFrame(short frame) {
    SpriteV::setFrame(frame);
    frame_timer_ = static_cast<const AnimatedSpriteProp*>(prop_) -> frame_timer_second_;
}

void AnimatedSprite::updateFrame(float deltaTime) {

    if(is_playing) {
        frame_timer_ -= deltaTime;
        while(frame_timer_ < 0) {
            frame_timer_ += static_cast<const AnimatedSpriteProp*>(prop_) -> frame_timer_second_;
            current_frame_ ++;
            
            if(current_frame_ >= prop_ -> frame_count_) {
                if(loop) {
                    current_frame_ = 0;
                }
                else {
                    current_frame_ = prop_ -> frame_count_ - 1;
                    is_playing = PAUSE;
                }
            }
        }
        frame_crop_.y   = current_frame_ * prop_ -> frameH_;
    }
    
}
////////////////////////////////////////////////////////////////////////