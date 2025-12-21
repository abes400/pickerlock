#pragma once
#include "raylib.h"

#define UNCHECKED false
#define CHECKED   true

class Checkbox {
    private:
        Texture2D*  texture_;
        Vector2     position_;
        Rectangle   frame_crop_;
        const float frameH_;

    public:
        bool isChecked = false;
        Checkbox(Vector2 position, Texture2D* texture, const float frameHeight, bool checked = UNCHECKED);
        bool checkClick(Vector2& mousePos);
        void draw();
        ~Checkbox();
};