#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "raylib.h"

#define LIFT true
#define NO_LIFT false
class Button {
    private:
        Texture2D* texture_;
        Texture2D* texture_hold_;
        Texture2D* currentTexture_;
        Vector2 position_;
        bool hold_ = false;

        char* label_;
        short lift_height_;

        short current_label_offset_;
        short label_x_, label_y_;
        
    public:
        Button(Vector2 position, Texture2D* texture, Texture2D* texture_hold);
        void addLabel(char* label = nullptr, bool lifted = false, short lift_height = 0);
        void draw();
        bool checkClick(Vector2& mousePos, bool mousePressed);

        ~Button();
};
#endif