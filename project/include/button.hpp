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
    
        /**
         * Creates a new instance of Button.
         * @param position Position of where the button should be drawn.
         * @param texture Texture to be drawn for the button when idle. (User is responsible for its allocation).
         * @param texture_hold (OPTIONAL) Texture to be drawn for the button when held. (User is responsible for its allocation).
         * @return The address of the created button.
         */
        Button(Vector2 position, Texture2D* texture, Texture2D* texture_hold = nullptr);

        /**
         * Assigns a label for the Button (measures the alignment automatically).
         * @param label The label to be shown on the button.
         * @param lifted (OPTIONAL) Does the button have illusion of being un-lifted when held? Then set this as LIFT, otherwise, NO_LIFT.
         * @param lift_height Number of pixels to unlift the label when button is held (ignored if lifted is NO_LIFT).
         */
        void addLabel(const char* label = nullptr, bool lifted = false, short lift_height = 0);
        
        /**
         * Assigns a label for the Button without measuring its alignment automatically.
         * 
         * Recommended if you want to quickly change the label.
         * @param label The label to be shown on the button.
         */
        void addLabelWithoutMeasuring(const char* label);

        /**
         * Checks whether the button is clicked.
         * @param mousePos Position of the cursor.
         * @param mousePressed whether the mouse is held or not.
         * @return true if the button was clicked (press and release), false otherwise.
         */
        bool checkClick(Vector2& mousePos, bool mousePressed);

        /**
         * Draws the button on the set position.
         */
        void draw();
};