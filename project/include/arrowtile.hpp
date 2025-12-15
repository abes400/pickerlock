#pragma once
#include "sprite.hpp"


enum Directions { UP = 0, RIGHT, DOWN, LEFT, NONE };
class ArrowTile : public AnimatedSprite {
    private:
        
        // Shows if the first instance ever was ever created.
        static bool inst_before_;

        // To be used when deciding direction
        static Vector2 frame_origin_;
        static float width_, height_;
        
        float  rotation_ = 0;

    public:
        enum Directions direction = UP;
        ArrowTile(Vector2 position, const AnimatedSpriteProp* spriteProperty, Loopability loop = NOT_LOOPABLE);

        // Randomly decides the direction of the tile
        void decideDirection();
        void draw();
};