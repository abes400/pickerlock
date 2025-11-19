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

        const char* label_ = nullptr;
        short lift_height_;
        bool labeled_ = false;
        Vector2 label_pos_;
        
    public:
        Button(Vector2 position, Texture2D* texture, Texture2D* texture_hold = nullptr);
        void addLabel(const char* label = nullptr, bool lifted = false, short lift_height = 0);
        void draw();
        bool checkClick(Vector2& mousePos, bool mousePressed);

        ~Button();
};
#endif