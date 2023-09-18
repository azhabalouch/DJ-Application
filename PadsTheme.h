#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class PadsTheme : public LookAndFeel_V4
{
public:
    PadsTheme()
    {
        image = ImageFileFormat::loadFrom(BinaryData::Pad_png, BinaryData::Pad_pngSize); // Load an image from binary data
        image = image.rescaled(90, 90); // Resize the loaded image to specific dimensions
    }

    // Override the drawButtonBackground function
    void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour,
        bool isMouseOverButton, bool isButtonDown) override
    {
        g.fillRoundedRectangle(button.getLocalBounds().toFloat(), 40.0f); // Fill a rounded rectangle shape for the button background

        // Calculate coordinates to center the image on the button
        int x = (button.getWidth() - image.getWidth()) / 2; // Calculate the x-coordinate for image placement
        int y = (button.getHeight() - image.getHeight()) / 2; // Calculate the y-coordinate for image placement

        // Draw the image on the button
        g.drawImageAt(image, x, y); // Draw the loaded image at specified coordinates on the button
    }
private:
    // Load your custom images here
    Image image;
};
