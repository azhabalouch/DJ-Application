#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class PositionSliderTheme : public LookAndFeel_V4 // Define the PositionSliderTheme class, inheriting from LookAndFeel_V4
{
public:
    PositionSliderTheme() // Constructor for the PositionSliderTheme class
    {
        BarKnobImage = ImageCache::getFromMemory(BinaryData::HorizontalBarKnob_png, BinaryData::HorizontalBarKnob_pngSize); // Load an image for the slider knob from binary data
        BarImage = ImageCache::getFromMemory(BinaryData::HorizontalBar_png, BinaryData::HorizontalBar_pngSize); // Load an image for the slider bar from binary data
    }

    void drawLinearSlider(Graphics& g, int x, int y, int width, int height,
        float sliderPos, float minSliderPos, float maxSliderPos,
        const Slider::SliderStyle style, Slider& slider) override
    {
        // Draw the bar image
        g.drawImage(BarImage, x, y, width, height,
            0, 0, BarImage.getWidth(), BarImage.getHeight());

        // Calculate the position of the knob
        int knobY = (y + (height - BarKnobImage.getHeight()) / 2); // Calculate the vertical position of the knob
        int knobX = static_cast<int>(sliderPos) - static_cast<int>(BarKnobImage.getWidth() / 2); // Calculate the horizontal position of the knob

        // Draw the knob image
        g.drawImage(BarKnobImage, knobX, knobY,
            BarKnobImage.getWidth(), BarKnobImage.getHeight(),
            0, 0, BarKnobImage.getWidth(), BarKnobImage.getHeight());
    }

private:
    Image BarKnobImage; // Declare an Image object to hold the slider knob image
    Image BarImage; // Declare an Image object to hold the slider bar image
};