#pragma once
#include "raylib.h"

struct SpriteVProp {
    const Texture2D* texture_;
    const float      frameH_;
    const short      frame_count_;
};

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

struct AnimatedSpriteProp : public SpriteVProp {
    const float frame_timer_second_;
};

enum Loopability { LOOPABLE = true, NOT_LOOPABLE = false };
enum PlayState   { PLAY     = true, PAUSE        = false };

class AnimatedSprite : public SpriteV {
private:
    float   frame_timer_;
    
public:
    enum Loopability    loop;
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