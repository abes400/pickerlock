#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "raylib.h"
class Button {
    private:
        Texture2D* texture_;
        Texture2D* texture_hold_;
        Texture2D* currentTexture_;
        Vector2 position_;
        bool hold_ = false;

    public:
        Button(Vector2 position, Texture2D* texture, Texture2D* texture_hold) ;
        void draw();
        bool checkClick(Vector2& mousePos, bool mousePressed);
};
#endif