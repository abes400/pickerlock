#include "button.hpp"
#include <iostream>
using namespace std;

Button::Button(Vector2 position, Texture2D* texture, Texture2D* texture_hold) {
    texture_ = texture;
    currentTexture_ = texture_;
    texture_hold_ = texture_hold;
    position_ = position;
    position_.x -= texture_ -> width/2;
    position_.y -= texture_ -> height/2;
}

void Button::draw() {
    DrawTextureV(*currentTexture_, position_, WHITE);
}

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
      cout << "hold\n";
      hold_ = true;
      if (texture_hold_ != NULL)  currentTexture_ = texture_hold_;
    }
  } else {
    if (hold_) {
      cout << "release\n";
      hold_ = false;
      currentTexture_ = texture_;
      if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        return true;
    }
  }

  return false;
}