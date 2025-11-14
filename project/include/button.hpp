#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "raylib.h"
class Button {
    private:
        Texture2D texture_;
        Vector2 position_;
    public:
        Button(const char* image_path, Vector2 position);
        ~Button();

        void draw();
};
#endif