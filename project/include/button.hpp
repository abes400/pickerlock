#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "raylib.h"
class Button {
    private:
        Texture2D texture_, texture_hold_;
        Texture2D* currentTexture_;
        Vector2 position_;
        bool hold_ = false;
        bool hasHoldTexture_ = false;
    public:
        Button(Vector2 position, const char *image_path, const char *image_path_hold) ;
        ~Button();

        void draw();
        bool checkClick(Vector2& mousePos, bool mousePressed);
};
#endif