#include "checkbox.hpp"
#include "globals.hpp"

/**
 * Creates a new instance of Checkbox.
 * @param position Position of where the checkbox should be drawn.
 * @param texture Texture to be drawn for the checkbox. (User is responsible for its allocation).
 * @param frameHeight Height of each frame.
 * @param checked Initial state of the checkbox.
 * @return The address of the created checkbox.
 */
Checkbox::Checkbox(Vector2 position, Texture2D* texture, const float frameHeight, bool checked)
: position_(position),
  texture_(texture),
  frameH_(frameHeight),
  isChecked(checked) {
    frame_crop_ = Rectangle {
        0, 
        checked ? frameH_ : 0,
        static_cast<float>(texture -> width),
        frameH_
    };
}

/**
 * Checks whether the checkbox is clicked.
 * @param mousePos Position of the cursor.
 * @return true if the checkbox was clicked (press and release), false otherwise.
 */
bool Checkbox::checkClick(Vector2& mousePos) {
    if( IsMouseButtonReleased(MOUSE_BUTTON_LEFT) &&
        CheckCollisionPointRec(
            mousePos,
            Rectangle {
                position_.x,
                position_.y,
                static_cast <float> (texture_ -> width),
                frameH_
            }
        )
    ) {
        PlaySound(Assets::dial);
        isChecked = !isChecked;
        frame_crop_.y = isChecked ? frameH_ : 0;
        return true;
    }
    return false;
}

/**
 * Draws the checkbox on the set position.
 */
void Checkbox::draw() {
    DrawTextureRec(*texture_, frame_crop_, position_, WHITE);
}