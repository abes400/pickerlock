#include "raylib.h"
#include "sprite.hpp"

//=================== SPRITEV IMPLEMENTATION ========================//

/**
 * Creates a new instance of sprite.
 * @param position Position of where the sprite should be drawn.
 * @param spriteProperty Property struct to be used by this sprite (User is responsible for its allocation)
 * @return The address of the created sprite.
 */
SpriteV::SpriteV (Vector2 position, const SpriteVProp* spriteProperty)
: prop_(spriteProperty), 
  position_(position) {
    frame_crop_ = Rectangle {
        0, 0,
        static_cast<float>(prop_ -> texture_ -> width),
        prop_ -> frameH_
    };
}

/**
 * Sets the very center of the sprite as the origin.
 * 
 * Once called, the the coordinates of the sprite will be determined
 * with respect to the center instead of top-left corner.
 */
void SpriteV::setOriginAsCenter() {
    position_.x -= prop_ -> texture_ -> width/2;
    position_.y -= prop_ -> frameH_/2;
}

/**
 * Sets the frame of the sprite.
 * @param frame Frame index to be set.
 */
void SpriteV::setFrame(short frame) {
    current_frame_  = frame;
    frame_crop_.y   = current_frame_ * prop_ -> frameH_;
}

/**
 * Draws the sprite on the set position
 */
void SpriteV::draw() {
    DrawTextureRec(*(prop_ -> texture_), frame_crop_, position_, WHITE);
}




//=================== ANIMATEDSPRITE IMPLEMENTATION ========================//
/**
 * Creates a new instance of animated sprite.
 * @param position Position of where the sprite should be drawn.
 * @param spriteProperty Property struct to be used by this sprite (User is responsible for its allocation)
 * @param loopable (OPTIONAL) whether the sprite should loop after the final frame.
 * @return The address of the created sprite.
 */
AnimatedSprite::
AnimatedSprite(Vector2 position, const AnimatedSpriteProp* spriteProperty, Loopability loopable)
: SpriteV(position, spriteProperty),
  frame_timer_( spriteProperty -> frame_timer_second_),
  loop(loopable) {}


/**
 * Sets the frame of the sprite.
 * @param frame Frame index to be set.
 */
void AnimatedSprite::setFrame(short frame) {
    SpriteV::setFrame(frame);
    frame_timer_ = static_cast<const AnimatedSpriteProp*>(prop_) -> frame_timer_second_;
}

/**
 * Advances to the next frame if is_playing is true.
 * @param deltaTime The time that passed between the last frames.
 */
void AnimatedSprite::updateFrame(float deltaTime) {

    if(is_playing) {
        frame_timer_ -= deltaTime;
        while(frame_timer_ < 0) {
            frame_timer_ += static_cast<const AnimatedSpriteProp*>(prop_) -> frame_timer_second_;
            current_frame_ ++;
            
            if(current_frame_ >= prop_ -> frame_count_) {
                if(loop) current_frame_ = 0;
                else {
                    current_frame_ = prop_ -> frame_count_ - 1;
                    is_playing = PAUSE;
                }
            }
        }
        frame_crop_.y   = current_frame_ * prop_ -> frameH_;
    }
    
}