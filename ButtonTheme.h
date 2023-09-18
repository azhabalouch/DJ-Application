#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class ButtonTheme : public LookAndFeel_V4
{
public:
    // Here, we define a new C++ class named `ButtonTheme`, which inherits from `LookAndFeel_V4`. This class is intended to customize the appearance of buttons in your application.

    ButtonTheme()
    {
        // Inside the `ButtonTheme` class, we have a constructor. When an instance of `ButtonTheme` is created, it sets the background color of a resizable window to black using the `setColour` function. This will affect the overall background color of your application.
        setColour(ResizableWindow::backgroundColourId, Colour::fromRGB(0, 0, 0));
    }

    // This function, `drawButtonBackground`, is an override of a virtual function from the `LookAndFeel_V4` class. It is responsible for customizing the appearance of the button's background.
    void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour, bool isMouseOverButton, bool isButtonDown) override
    {
        const int cornerSize = 10; // Here, a variable `cornerSize` is declared and set to 10. This variable represents the size of the rounded corners of the button.
        const Colour buttonColor = Colour::fromRGB(0, 0, 0); //This line defines a `buttonColor` variable and sets it to black using RGB values.

        //These conditional statements check whether the mouse is over the button or if the button is being pressed (isButtonDown). Depending on these conditions, the button's color is adjusted. When the mouse is over the button or it's being clicked, the color is made slightly brighter. Otherwise, it remains the same.
        if (isMouseOverButton || isButtonDown)
            g.setColour(buttonColor.brighter(0.2f));
        else
            g.setColour(buttonColor);

        //Finally, this line uses the `Graphics` object `g` to fill a rounded rectangle that represents the button's background. It uses the `buttonColor` and the `cornerSize` to determine the appearance of the button's background.
        g.fillRoundedRectangle(button.getLocalBounds().toFloat(), static_cast<float>(cornerSize));
    }

    //This function, `drawButtonText`, is another override from `LookAndFeel_V4`. It's responsible for customizing the appearance of the button's text.
    void drawButtonText(Graphics& g, TextButton& button, bool isMouseOverButton, bool isButtonDown) override
    {
        Colour lightGold(241, 229, 172); //Here, a `lightGold` color is defined with specific RGB values.

        g.setColour(lightGold); //This line sets the color used for drawing the button's text to the previously defined `lightGold` color.

        g.setFont(Font("Metroscript", 30.0f, Font::bold)); //This sets the font for the button's text. It uses the "Metroscript" font with a size of 40.0 and sets it to bold.

        //Finally, this line uses the `Graphics` object to draw the button's text. It uses the text obtained from `button.getButtonText()`, the bounds of the button, and centers the text within those bounds.
        g.drawText(button.getButtonText(), button.getLocalBounds(), Justification::centred);
    }
};
