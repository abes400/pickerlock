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
        void setFrame(short frame);
        bool isLastFrame();
        void draw();
};

struct AnimatedSpriteProp : public SpriteVProp {
    const float frame_timer_second_;
};

#define LOOPABLE true
#define NOT_LOOPABLE false

class AnimatedSprite : public SpriteV {
    private:
        float   frame_timer_;
        
    public:
        bool    loop = false;

        AnimatedSprite(Vector2 position, const AnimatedSpriteProp* spriteProperty, bool loop = NOT_LOOPABLE);
        void updateFrame(float deltaTime = GetFrameTime());

};