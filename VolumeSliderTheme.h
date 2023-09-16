#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class VolumeSliderTheme : public LookAndFeel_V4 // Define the VolumeSliderTheme class, inheriting from LookAndFeel_V4
{
public:
    VolumeSliderTheme() // Constructor for the VolumeSliderTheme class
    {
        // Load your image here
        BarImage = ImageCache::getFromMemory(BinaryData::VolumeBar_png, BinaryData::VolumeBar_pngSize); // Load an image for the slider bar from binary data
        BarKnobImage = ImageCache::getFromMemory(BinaryData::VerticalKnob_png, BinaryData::VerticalKnob_pngSize); // Load an image for the slider knob from binary data

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

    void drawLinearSlider(Graphics& g, int x, int y, int width, int height,
        float sliderPos, float minSliderPos, float maxSliderPos,
        const Slider::SliderStyle style, Slider& slider) override
    {
        // Draw the bar image
        g.drawImage(BarImage, x, y, width, height,
            0, 0, BarImage.getWidth(), BarImage.getHeight());

        // Calculate the position of the knob
        int knobX = (x + (width - BarKnobImage.getWidth()) / 2) - 5; // Calculate the horizontal position of the knob with an offset of 5
        int knobY = static_cast<int>(sliderPos) - static_cast<int>(BarKnobImage.getHeight() / 2); // Calculate the vertical position of the knob

        // Draw the knob image
        g.drawImage(BarKnobImage, knobX, knobY,
            BarKnobImage.getWidth(), BarKnobImage.getHeight(),
            0, 0, BarKnobImage.getWidth(), BarKnobImage.getHeight()); // Draw the knob image
    }

private:
    Image BarImage; // Declare an Image object to hold the slider bar image
    Image BarKnobImage; // Declare an Image object to hold the slider knob image
};
