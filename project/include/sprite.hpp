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
        SpriteV(Vector2 position, const SpriteVProp* spriteProperty);
        void setOriginAsCenter();
        void setFrame(short frame);
        bool isLastFrame();
        void draw();
        ~SpriteV();
};

struct AnimatedSpriteProp : public SpriteVProp {
    const float frame_timer_second_;
};

enum Loopability { LOOPABLE = true, NOT_LOOPABLE = false };

class AnimatedSprite : public SpriteV {
    private:
        float   frame_timer_;
        
    public:
        enum Loopability    loop;

        AnimatedSprite(Vector2 position, const AnimatedSpriteProp* spriteProperty, Loopability loopable = NOT_LOOPABLE);
        void setFrame(short frame);
        void updateFrame(float deltaTime = GetFrameTime());

};