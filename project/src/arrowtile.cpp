#include <stdlib.h>
#include <time.h>
#include "arrowtile.hpp"

bool ArrowTile::inst_before_ = false;
Vector2 ArrowTile::frame_origin_;
float ArrowTile::width_, ArrowTile::height_;

/**
 * Creates a new instance of ArrowTile
 * @param position Position of where the sprite should be drawn
 * @param spriteProperty Property struct to be used by this sprite (User is responsible for its allocation)
 * @param loop The sprite animation is to be looped or not. (either LOOPABLE, or NOT_LOOPABLE)
 * @return The address of the created tile.
 */
ArrowTile::
ArrowTile(Vector2 position, const AnimatedSpriteProp* spriteProperty, Loopability loop)
: AnimatedSprite (position, spriteProperty, loop) {
    if(!inst_before_) {
        srand(time(NULL));

        width_ = spriteProperty -> texture_ -> width;
        height_ = spriteProperty -> frameH_;

        frame_origin_ = Vector2 {
            width_ / 2,
            height_ / 2
        };

        inst_before_ = true;
    }
}

/**
 * Decides a random direction for the tile
 */
void ArrowTile::decideDirection() {
    direction = static_cast<Directions>(rand() % 4);
    rotation_  = 90 * static_cast<short>(direction);
}

/**
 * Draws the sprite on the set position
 */
void ArrowTile::draw() {
    DrawTexturePro(
        *(prop_ -> texture_),
        frame_crop_,
        Rectangle{position_.x, position_.y, width_, height_},
        frame_origin_,
        rotation_,
        WHITE
    );
}