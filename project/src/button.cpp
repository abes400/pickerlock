#include "gamesetup.h"
#include "button.hpp"

#include <iostream>
using namespace std;

extern Font uifont;

Button::Button(Vector2 position, Texture2D* texture, Texture2D* texture_hold) {
    texture_        = currentTexture_ = texture;
    texture_hold_   = texture_hold;
    position_       = position;

    position_.x -= texture_ -> width/2;
    position_.y -= texture_ -> height/2;
}

void Button::addLabel(const char* label, bool lifted, short lift_height) {
    if(label != nullptr) {
        label_          = label;
        lift_height_    = lifted ? lift_height : 0;

        Vector2 labelSize   = MeasureTextEx(uifont, label, FONT_SIZE, 0);
        label_pos_          = Vector2 { static_cast<float>(position_.x + (texture_ -> width - labelSize.x) / 2), 
                                        static_cast<float>(position_.y + (texture_ -> height - labelSize.y) / 2 - lift_height)};

        labeled_ = true;
    } else
        labeled_ = false;

    cout << labeled_ << endl;
}

void Button::draw() {
    DrawTextureV(*currentTexture_, position_, WHITE);
    if(labeled_) DrawTextEx(uifont, label_, label_pos_, FONT_SIZE, 0, BLACK);
}

// TODO: Reimplement this dogshoot
bool Button::checkClick(Vector2& mousePos, bool mousePressed) {
    if (mousePressed &&
        CheckCollisionPointRec(
            mousePos, {
                position_.x,
                position_.y,
                static_cast <float> (texture_ -> width),
                static_cast <float> (texture_ -> height)
            }
        )
    ) {
    if (!hold_ && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        hold_ = true;
        if (texture_hold_ != nullptr) {
            currentTexture_ = texture_hold_;
            label_pos_.y += lift_height_;
        }  
    }
    } else {
        if (hold_) {
            hold_ = false;
            currentTexture_ = texture_;
            label_pos_.y -= lift_height_;
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                return true;
        }
    }

    return false;
}

Button::~Button() {
    cout << "APP: Button deallocated\n";
}