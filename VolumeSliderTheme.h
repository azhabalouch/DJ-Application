#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class VolumeSliderTheme : public LookAndFeel_V4
{
public:
    VolumeSliderTheme()
    {
        // Load your image here
        BarImage = ImageCache::getFromMemory(BinaryData::VolumeBar_png, BinaryData::VolumeBar_pngSize);
        BarKnobImage = ImageCache::getFromMemory(BinaryData::VerticalKnob_png, BinaryData::VerticalKnob_pngSize);

        //Custom color
        Colour gold(255, 215, 0);

        // Font color
        setColour(Slider::textBoxTextColourId, gold); // Set the text color
        setColour(Slider::textBoxOutlineColourId, gold); // Set the outline 
    }

    Font getLabelFont(Label&) override
    {
        return Font("Comic Sans MS", "Bold", 14.0f); // Set the font
    }

    void drawLinearSlider(Graphics& g, int x, int y, int width, int height,
        float sliderPos, float minSliderPos, float maxSliderPos,
        const Slider::SliderStyle style, Slider& slider) override
    {
        // Draw the bar image
        g.drawImage(BarImage, x, y, width, height,
            0, 0, BarImage.getWidth(), BarImage.getHeight());

        // Calculate the position of the knob
        int knobX = (x + (width - BarKnobImage.getWidth()) / 2) - 7 ;
        int knobY = static_cast<int>(sliderPos) - static_cast<int>(BarKnobImage.getHeight() / 2);

        // Draw the knob image
        g.drawImage(BarKnobImage, knobX, knobY,
            BarKnobImage.getWidth(), BarKnobImage.getHeight(),
            0, 0, BarKnobImage.getWidth(), BarKnobImage.getHeight());
    }


private:
    Image BarImage;
    Image BarKnobImage;
};
