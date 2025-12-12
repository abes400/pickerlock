#pragma once
#include "sprite.hpp"


enum Directions { UP = 0, RIGHT, DOWN, LEFT };
class ArrowTile : public AnimatedSprite {
    private:
        static bool inst_before_;
        static Vector2 frame_origin_;
        static float width_, height_;
        float  rotation_ = 0;

    public:
        enum Directions direction = UP;
        ArrowTile(Vector2 position, const AnimatedSpriteProp* spriteProperty, Loopability loop = NOT_LOOPABLE);
        void decideDirection();
        void draw();
};