#pragma once

#include <JuceHeader.h>

class ButtonTheme : public LookAndFeel_V4
{
public:
    ButtonTheme()
    {
        setColour(ResizableWindow::backgroundColourId, Colour::fromRGB(0, 0, 0)); // Set the background color to black
    }

    void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour, bool isMouseOverButton, bool isButtonDown) override
    {
        const int cornerSize = 10; // Adjust the corner size to your preference for rounded borders
        const Colour buttonColor = Colour::fromRGB(0, 0, 0); // Set the button color to black

        if (isMouseOverButton || isButtonDown)
            g.setColour(buttonColor.brighter(0.2f)); // Darken the color on mouse hover or click
        else
            g.setColour(buttonColor);

        g.fillRoundedRectangle(button.getLocalBounds().toFloat(), static_cast<float>(cornerSize));
    }

    void drawButtonText(Graphics& g, TextButton& button, bool isMouseOverButton, bool isButtonDown) override
    {
        const Colour textColor = Colours::white; // Set the text color
        g.setColour(textColor);

        g.setFont(Font("Metroscript", 20.0f, Font::bold)); // Set the Metroscript font and size

        g.drawText(button.getButtonText(), button.getLocalBounds(), Justification::centred);
    }
};
