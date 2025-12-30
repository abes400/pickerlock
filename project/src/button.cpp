#include "button.hpp"
#include "globals.hpp"

/**
 * Creates a new instance of Button.
 * @param position Position of where the button should be drawn.
 * @param texture Texture to be drawn for the button when idle. (User is responsible for its allocation).
 * @param texture_hold (OPTIONAL) Texture to be drawn for the button when held. (User is responsible for its allocation).
 * @return The address of the created button.
 */
Button::Button(Vector2 position, Texture2D* texture, Texture2D* texture_hold)
: texture_(texture), 
  currentTexture_(texture), 
  texture_hold_(texture_hold),
  position_(position) {
    position_.x -= texture_ -> width/2;
    position_.y -= texture_ -> height/2;
}


/**
 * Assigns a label for the Button (measures the alignment automatically).
 * @param label The label to be shown on the button.
 * @param lifted (OPTIONAL) Does the button have illusion of being un-lifted when held? Then set this as LIFT, otherwise, NO_LIFT.
 * @param lift_height Number of pixels to unlift the label when button is held (ignored if lifted is NO_LIFT).
 */
void Button::addLabel(const char* label, bool lifted, short lift_height) {
    if(label != nullptr) {
        label_          = label;
        lift_height_    = lifted ? lift_height : 0;

        Vector2 labelSize   = MeasureTextEx(Assets::uifont, label, Assets::uifont.baseSize, 0);
        label_pos_          = Vector2 { position_.x + (texture_ -> width - labelSize.x) / 2.0f, 
                                        position_.y + (texture_ -> height - labelSize.y) / 2.0f - lift_height};

        labeled_ = true;
    } else
        labeled_ = false;
}

/**
 * Assigns a label for the Button without measuring its alignment automatically.
 * 
 * Recommended if you want to quickly change the label.
 * @param label The label to be shown on the button.
 */
void Button::addLabelWithoutMeasuring(const char* label) {
    if(label != nullptr) {
        label_   = label;
        labeled_ = true;
    } else
        labeled_ = false;
}

/**
 * Checks whether the button is clicked.
 * @param mousePos Position of the cursor.
 * @param mousePressed whether the mouse is held or not.
 * @return true if the button was clicked (press and release), false otherwise.
 */
void Button::draw() {
    DrawTextureV(*currentTexture_, position_, WHITE);
    if(labeled_) DrawTextEx(Assets::uifont, label_, label_pos_, Assets::uifont.baseSize, 0, WHITE);
}

// TODO: Reimplement this dogshoot

/**
 * Draws the button on the set position.
 */
bool Button::checkClick(Vector2& mousePos, bool mousePressed) {
    if (mousePressed &&
        CheckCollisionPointRec(
            mousePos, {
                position_.x,
                position_.y,
                static_cast <float> (texture_ -> width),
                static_cast <float> (texture_ -> height)
            }
        )
    ) {
    if (!hold_ && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        hold_ = true;
        if (texture_hold_ != nullptr) {
            currentTexture_ = texture_hold_;
            label_pos_.y += lift_height_;
        }  
    }
    } else {
        if (hold_) {
            hold_ = false;
            currentTexture_ = texture_;
            label_pos_.y -= lift_height_;
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                PlaySound(Assets::dial);
                return true;
            }
        }
    }

    return false;
}