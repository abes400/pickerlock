#include "button.hpp"
#include <iostream>
using namespace std;

Button::Button(Vector2 position, const char *image_path, const char *image_path_hold = NULL) {
    texture_ = LoadTexture(image_path);
    currentTexture_ = &texture_;

    if(image_path_hold == NULL)
        hasHoldTexture_ = false;
    else {
        hasHoldTexture_ = true;
        texture_hold_ = LoadTexture(image_path_hold);
    }
    
    position_ = position;
    position_.x -= texture_.width/2;
    position_.y -= texture_.height/2;
}

Button::~Button() {
    UnloadTexture(texture_);
}

void Button::draw() {
    DrawTextureV(*currentTexture_, position_, WHITE);
}

bool Button::checkClick(Vector2& mousePos, bool mousePressed) {
    if( mousePressed &&
        CheckCollisionPointRec(
            mousePos,
            {
                position_.x,
                position_.y,
                static_cast<float>(texture_.width),
                static_cast<float>(texture_.height)
            }
        ) 
    ) {
        if(!hold_ && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            cout <<  "hold\n";
            hold_ = true;
            if(hasHoldTexture_) currentTexture_ = &texture_hold_;
        }
    } else {
        if(hold_) {
            cout <<  "release\n";
            hold_ = false;
            currentTexture_ = &texture_;
            if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                return true;
        }
    }

    return false;
}
