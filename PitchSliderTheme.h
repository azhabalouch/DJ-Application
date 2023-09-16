#pragma once

#pragma warning(disable: 4100) // Disable warning C4100 - Annoying warning for not
                               // using an argument which is used later. So I disabled it

#include "../JuceLibraryCode/JuceHeader.h" // Include JUCE framework headers

class PitchSliderTheme : public LookAndFeel_V4 // Define the PitchSliderTheme class, inheriting from LookAndFeel_V4
{
public:
    PitchSliderTheme() // Constructor for the PitchSliderTheme class
    {
        // Load your image here
        knobImage = ImageCache::getFromMemory(BinaryData::VolumeDial_png, BinaryData::VolumeDial_pngSize); // Load an image from memory using ImageCache

        // Custom color
        Colour gold(255, 215, 0); // Define a custom color (gold)

        // Font color
        setColour(Slider::textBoxTextColourId, gold); // Set the text color for the Slider
        setColour(Slider::textBoxOutlineColourId, gold); // Set the outline color for the Slider
    }

    Font getLabelFont(Label&) override // Override the getLabelFont function to customize the font for labels
    {
        return Font("Comic Sans MS", "Bold", 14.0f); // Return a custom font (Comic Sans MS, Bold, size 14.0)
    }

    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
    {
        if (knobImage.isValid()) // Check if the loaded image is valid
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
            const double lineLength = height / 2 - 20; // Adjust the line length as needed
            const double lineX = centerX + lineLength * std::sin(angle);
            const double lineY = centerY - lineLength * std::cos(angle);

            // Custom color
            Colour gold(255, 215, 0); // Define a custom color (gold)

            // Draw the rotating rectangle line behind the knob
            g.setColour(gold); // Set the current drawing color to gold
            g.drawLine(static_cast<float>(centerX), static_cast<float>(centerY), static_cast<float>(lineX), static_cast<float>(lineY), 3.0f); // Draw a line with specified thickness

            // Draw the image frame on the slider
            g.drawImage(knobImage, x, y, width, height, 0, static_cast<int>(frameId * knobImage.getWidth()), knobImage.getWidth(), knobImage.getWidth());
        }
    }

private:
    Image knobImage; // Declare an Image object to hold the knob image
};
