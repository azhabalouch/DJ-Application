#pragma once

#pragma warning(disable: 4100) // Disable warning C4100 - Annoying warning for not using an argument which is used later. So I disabled it

#include "../JuceLibraryCode/JuceHeader.h"

class SpeedSliderTheme : public LookAndFeel_V4 // Define the SpeedSliderTheme class, inheriting from LookAndFeel_V4
{
public:
    SpeedSliderTheme() // Constructor for the SpeedSliderTheme class
    {
        knobImage = ImageCache::getFromMemory(BinaryData::SpeedDial_png, BinaryData::SpeedDial_pngSize); // Load an image for the slider knob from binary data

        //Custom color
        Colour gold(255, 215, 0); // Define a custom color as "gold"

        // Font color
        setColour(Slider::textBoxTextColourId, gold); // Set the text color to the custom gold color
        setColour(Slider::textBoxOutlineColourId, gold); // Set the outline color to the custom gold color
    }

    Font getLabelFont(Label&) override // Define the font for labels associated with this theme
    {
        return Font("Comic Sans MS", "Bold", 14.0f); // Set the font to "Comic Sans MS", bold, with a size of 14.0f
    }

    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
    {
        if (knobImage.isValid()) // Check if the knob image is valid
        {
            // Calculate the frame index based on the current value of the slider
            const double frames = knobImage.getHeight() / knobImage.getWidth();
            const double frameId = (int)std::ceil(sliderPos * ((double)frames - 1.0));

            // Calculate the center point of the knob
            const double centerX = x + width / 2;
            const double centerY = y + height / 2;

            // Calculate the angle for the rotating rectangle line
            const double angle = MathConstants<float>::twoPi * sliderPos;

            // Calculate the length and position of the rotating rectangle line
            const double lineLength = height / 2 - 5;
            const double lineX = centerX - lineLength * std::sin(angle);
            const double lineY = centerY + lineLength * std::cos(angle);

            //Custom color
            Colour gold(255, 215, 0); // Define the custom gold color

            // Draw the rotating rectangle line behind the knob
            g.setColour(gold); // Set the color to gold
            g.drawLine(static_cast<float>(centerX), static_cast<float>(centerY), static_cast<float>(lineX), static_cast<float>(lineY), 3.0f); // Draw the line

            // Draw the image frame on the slider
            g.drawImage(knobImage, x, y, width, height, 0, static_cast<int>(frameId * knobImage.getWidth()), knobImage.getWidth(), knobImage.getWidth()); // Draw the knob image
        }
    }

private:
    Image knobImage; // Declare an Image object to hold the slider knob image
};
