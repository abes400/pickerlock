#pragma once
#include "sprite.hpp"


enum Directions { UP = 0, RIGHT, DOWN, LEFT };
class ArrowTile : public AnimatedSprite {
    private:
        static bool inst_before_;
        static Vector2 frame_origin_;
        float  rotation_ = 0;

    public:
        enum Directions direction = UP;
        ArrowTile(Vector2 position, AnimatedSpriteProp* spriteProperty, bool loop = NOT_LOOPABLE);
        void decideDirection();
};