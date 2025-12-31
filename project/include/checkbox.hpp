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
    /**
     * Current state of the checkbox
     */
    bool isChecked = false;

    /**
     * Creates a new instance of Checkbox.
     * @param position Position of where the checkbox should be drawn.
     * @param texture Texture to be drawn for the checkbox. (User is responsible for its allocation).
     * @param frameHeight Height of each frame.
     * @param checked Initial state of the checkbox.
     * @return The address of the created checkbox.
     */
    Checkbox(Vector2 position, Texture2D* texture, const float frameHeight, bool checked = UNCHECKED);

    /**
     * Checks whether the checkbox is clicked.
     * @param mousePos Position of the cursor.
     * @return true if the checkbox was clicked (press and release), false otherwise.
     */
    bool checkClick(Vector2& mousePos);

    /**
     * Draws the checkbox on the set position.
     */
    void draw();
};