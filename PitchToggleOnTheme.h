#pragma once

#include <JuceHeader.h>

class PitchToggleOnTheme : public LookAndFeel_V4
{
public:
    PitchToggleOnTheme()
    {
        // Load your image to be displayed on the button here
        image = ImageFileFormat::loadFrom(BinaryData::ToggleOn_png, BinaryData::ToggleOn_pngSize);
        image = image.rescaled(55, 30);
    }

    void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour, bool isMouseOverButton, bool isButtonDown) override
    {
        Colour gold(255, 215, 0);

        if (isButtonDown)
            g.setColour(gold); // Change this color for the button when it's pressed
        else if (isMouseOverButton)
            g.setColour(gold); // Change this color for mouse hover


        g.fillRoundedRectangle(button.getLocalBounds().toFloat(), 15.0f);

        // Calculate coordinates to center the image on the button
        int x = (button.getWidth() - image.getWidth()) / 2;
        int y = (button.getHeight() - image.getHeight()) / 2;

        // Draw the image on the button
        g.drawImageAt(image, x, y); // Adjust the coordinates for image placement
    }

private:
    Image image;
};