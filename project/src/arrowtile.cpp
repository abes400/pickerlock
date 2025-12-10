using namespace std;
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;
#include "arrowtile.hpp"

bool ArrowTile::seeded_ = false;

ArrowTile::
ArrowTile(Vector2 position, Texture2D* spriteSheet, float frameHeight, short frameCount, float frameTimeSecond, bool loop)
: AnimatedSprite (position, spriteSheet, frameHeight, frameCount, frameTimeSecond, loop){
    if(!seeded_) {
        srand(time(NULL));
        cout << "RNG for direction decision is seeded\n";
        seeded_ = true;
    }
}

void ArrowTile::decideDirection() {
    direction = static_cast<Directions>(rand() % 4);
    rotation_  = 90 * static_cast<short>(direction);
}