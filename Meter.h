#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class Meter : public LookAndFeel_V4
{
public:
    Meter()
    {
        yourNormalImage = ImageFileFormat::loadFrom(BinaryData::Meter_png, BinaryData::Meter_pngSize); // Load an image from binary data
        yourPressedImage = ImageFileFormat::loadFrom(BinaryData::Meter_png, BinaryData::Meter_pngSize); // Load an image from binary data
    }

    // Override the drawButtonBackground function
    void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour,
        bool isMouseOverButton, bool isButtonDown) override
    {
        // Check if the button is down or not
        if (isButtonDown)
        {
            // Replace this with your image when the button is pressed
            g.drawImage(yourPressedImage, button.getLocalBounds().toFloat());
        }
        else
        {
            // Replace this with your image when the button is not pressed
            g.drawImage(yourNormalImage, button.getLocalBounds().toFloat());
        }
    }

private:
    // Load your custom images here
    Image yourNormalImage;    // Replace with your image
    Image yourPressedImage;   // Replace with your image
};
