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
    // Current direction of the tile
    enum Directions direction = UP;

    /**
     * Creates a new instance of ArrowTile
     * @param position Position of where the sprite should be drawn
     * @param spriteProperty Property struct to be used by this sprite (User is responsible for its allocation)
     * @param loop The sprite animation is to be looped or not. (either LOOPABLE, or NOT_LOOPABLE)
     * @return The address of the created tile.
     */
    ArrowTile(Vector2 position, const AnimatedSpriteProp* spriteProperty, Loopability loop = NOT_LOOPABLE);

    /**
     * Decides a random direction for the tile
     */
    void decideDirection();

    /**
     * Draws the sprite on the set position
     */
    void draw();
};