#include <stdlib.h>
#include <time.h>
#include "arrowtile.hpp"

bool ArrowTile::inst_before_ = false;
Vector2 ArrowTile::frame_origin_;
float ArrowTile::width_, ArrowTile::height_;

ArrowTile::
ArrowTile(Vector2 position, const AnimatedSpriteProp* spriteProperty, Loopability loop)
: AnimatedSprite (position, spriteProperty, loop){
    if(!inst_before_) {
        srand(time(NULL));

        width_ = spriteProperty -> texture_ -> width;
        height_ = spriteProperty -> frameH_;

        frame_origin_ = {
            width_ / 2,
            height_ / 2
        };

        inst_before_ = true;
    }
}

// Randomly decides the direction of the tile
void ArrowTile::decideDirection() {
    direction = static_cast<Directions>(rand() % 4);
    rotation_  = 90 * static_cast<short>(direction);
}

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