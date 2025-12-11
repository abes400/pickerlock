using namespace std;
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;
#include "arrowtile.hpp"

bool ArrowTile::inst_before_ = false;
Vector2 ArrowTile::frame_origin_;

ArrowTile::
ArrowTile(Vector2 position, AnimatedSpriteProp* spriteProperty, bool loop)
: AnimatedSprite (position, spriteProperty, loop){
    if(!inst_before_) {
        srand(time(NULL));

        frame_origin_ = {
            static_cast<float>(spriteProperty -> texture_ -> width) / 2,
            static_cast<float>(spriteProperty -> frameH_) / 2
        };

        inst_before_ = true;
        cout << "Since this was the first instance, the RNG seeded and frame origin calculated\n";
    }
}

void ArrowTile::decideDirection() {
    direction = static_cast<Directions>(rand() % 4);
    rotation_  = 90 * static_cast<short>(direction);
}