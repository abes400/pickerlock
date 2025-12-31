#pragma once
#include "raylib.h"

/**
 * Struct for holding common properties shared by similar SpriteV sprites.
 * Made for efficiency. User is responsible for the allocation/deallocation
 * 
 * The spritesheet to be fed as the texture should contain the frames VERTICALLY
 */
struct SpriteVProp {
    const Texture2D* texture_;
    const float      frameH_;
    const short      frame_count_;
};

/**
 * Class for Sprite Objects with multiple indexed frames and positions.
 * V is for Vertical since the frames should be arranged VERTICALLY
 */
class SpriteV {
protected:
    const SpriteVProp* prop_;
    Vector2 position_;
    short current_frame_ = 0;

    Rectangle frame_crop_;

public:
    /**
     * Creates a new instance of sprite.
     * @param position Position of where the sprite should be drawn.
     * @param spriteProperty Property struct to be used by this sprite (User is responsible for its allocation)
     * @return The address of the created sprite.
     */
    SpriteV(Vector2 position, const SpriteVProp* spriteProperty);

    /**
     * Sets the very center of the sprite as the origin.
     * 
     * Once called, the the coordinates of the sprite will be determined
     * with respect to the center instead of top-left corner.
     */
    void setOriginAsCenter();

    /**
     * Sets the frame of the sprite.
     * @param frame Frame index to be set.
     */
    void setFrame(short frame);

    /**
     * Draws the sprite on the set position
     */
    void draw();
};


/**
 * Struct for holding common properties shared by similar Animated Sprites.
 * Made for efficiency. User is responsible for the allocation/deallocation
 * 
 * The spritesheet to be fed as the texture should contain the frames VERTICALLY
 */
struct AnimatedSpriteProp : public SpriteVProp {
    const float frame_timer_second_;
};


enum Loopability { LOOPABLE = true, NOT_LOOPABLE = false };
enum PlayState   { PLAY     = true, PAUSE        = false };



/**
 * Class for Animated Sprite Objects with multiple indexed frames and positions.
 * V is for Vertical since the frames should be arranged VERTICALLY
 * 
 * Unlike SpriteV, AnimatedSprite's frame can be advanced with updateFrame()
 * function called every time in the game loop.
 */
class AnimatedSprite : public SpriteV {
private:
    float   frame_timer_;
    
public:
    /**
     * Decides whether the sprite should loop after the final frame.
     * LOOPABLE: Can loop when the last frame is advanced.
     * NOT_LOOPABLE: is_playing is set to PAUSE and hence, the sprite pauses.
     */
    enum Loopability    loop;

    /**
     * PLAY: the frame advances as the updateFrame() is called.
     * PAUSE: the frame doesn't advance as the updateFrame() is called.
     */
    enum PlayState      is_playing = PAUSE;

    /**
     * Creates a new instance of animated sprite.
     * @param position Position of where the sprite should be drawn.
     * @param spriteProperty Property struct to be used by this sprite (User is responsible for its allocation)
     * @param loopable (OPTIONAL) whether the sprite should loop after the final frame.
     * @return The address of the created sprite.
     */
    AnimatedSprite(Vector2 position, const AnimatedSpriteProp* spriteProperty, Loopability loopable = NOT_LOOPABLE);

    /**
     * Sets the frame of the sprite.
     * @param frame Frame index to be set.
     */
    void setFrame(short frame);

    /**
     * Advances to the next frame if is_playing is true.
     * @param deltaTime The time that passed between the last frames.
     */
    void updateFrame(float deltaTime = GetFrameTime());

};