#pragma once
#include "raylib.h"

class Checkbox {
    private:
        Texture2D*  texture_;
        Vector2     position_;
        Rectangle   frame_crop_;
        const float frameH_;

    public:
        bool isChecked = false;
        Checkbox(Vector2 position, Texture2D* texture);
        bool checkClick(Vector2& mousePos, bool mousePressed);
        void draw();
};