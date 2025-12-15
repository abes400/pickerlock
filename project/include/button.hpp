#pragma once
#include "raylib.h"

#define LIFT true
#define NO_LIFT false
class Button {
    private:
        Texture2D*  texture_;
        Texture2D*  texture_hold_;
        Texture2D*  currentTexture_;
        Vector2     position_;
        bool        hold_ = false;

        
        Vector2     label_pos_;
        short       lift_height_;
        const char* label_          = nullptr;
        bool        labeled_        = false;
         
    public:
    
        Button(Vector2 position, Texture2D* texture, Texture2D* texture_hold = nullptr);
        void addLabel(const char* label = nullptr, bool lifted = false, short lift_height = 0);
        void addLabelWithoutMeasuring(const char* label);
        void draw();
        bool checkClick(Vector2& mousePos, bool mousePressed);
};