#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class PitchToggleOnTheme : public LookAndFeel_V4 // Define the PitchToggleOnTheme class, inheriting from LookAndFeel_V4
{
public:
    PitchToggleOnTheme() // Constructor for the PitchToggleOnTheme class
    {
        // Load your image to be displayed on the button here
        image = ImageFileFormat::loadFrom(BinaryData::ToggleOn_png, BinaryData::ToggleOn_pngSize); // Load an image from binary data
        image = image.rescaled(55, 30); // Resize the loaded image to specific dimensions
    }

    void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour, bool isMouseOverButton, bool isButtonDown) override
    {
        Colour gold(255, 215, 0); // Define a custom color (gold)

        if (isButtonDown)
            g.setColour(gold); // Change this color for the button when it's pressed
        else if (isMouseOverButton)
            g.setColour(gold); // Change this color for mouse hover

        g.fillRoundedRectangle(button.getLocalBounds().toFloat(), 15.0f); // Fill a rounded rectangle shape for the button background

        // Calculate coordinates to center the image on the button
        int x = (button.getWidth() - image.getWidth()) / 2; // Calculate the x-coordinate for image placement
        int y = (button.getHeight() - image.getHeight()) / 2; // Calculate the y-coordinate for image placement

        // Draw the image on the button
        g.drawImageAt(image, x, y); // Draw the loaded image at specified coordinates on the button
    }

private:
    Image image; // Declare an Image object to hold the button image
};
