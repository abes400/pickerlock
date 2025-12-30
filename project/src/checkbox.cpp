#include "checkbox.hpp"
#include "globals.hpp"

Checkbox::Checkbox(Vector2 position, Texture2D* texture, const float frameHeight, bool checked)
: position_(position),
  texture_(texture),
  frameH_(frameHeight),
  isChecked(checked) {
    frame_crop_ = Rectangle {
        0, 
        checked ? frameH_ : 0,
        static_cast<float>(texture -> width),
        frameH_
    };
}

bool Checkbox::checkClick(Vector2& mousePos) {
    if( IsMouseButtonReleased(MOUSE_BUTTON_LEFT) &&
        CheckCollisionPointRec(
            mousePos,
            Rectangle {
                position_.x,
                position_.y,
                static_cast <float> (texture_ -> width),
                frameH_
            }
        )
    ) {
        PlaySound(Assets::dial);
        isChecked = !isChecked;
        frame_crop_.y = isChecked ? frameH_ : 0;
        return true;
    }
    return false;
}


void Checkbox::draw() {
    DrawTextureRec(*texture_, frame_crop_, position_, WHITE);
}