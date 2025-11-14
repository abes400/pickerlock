#include "button.hpp"

Button::Button(const char *image_path, Vector2 position) {
    texture_ = LoadTexture(image_path);
    position_ = position;
    position_.x -= texture_.width/2;
    position_.y -= texture_.height/2;
}

Button::~Button() {
    UnloadTexture(texture_);
}

void Button::draw() {
    DrawTextureV(texture_, position_, WHITE);
}
