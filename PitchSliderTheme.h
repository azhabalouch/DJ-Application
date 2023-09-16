#pragma once
#pragma warning(disable: 4100) // Disable warning C4100 _ Annoying warning for not
                               // using an argument which is used later. So I disabled it

#include "../JuceLibraryCode/JuceHeader.h"

class PitchSliderTheme : public LookAndFeel_V4
{
public:
    PitchSliderTheme()
    {
        // Load your image here
        knobImage = ImageCache::getFromMemory(BinaryData::VolumeDial_png, BinaryData::VolumeDial_pngSize);

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

    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
    {
        if (knobImage.isValid())
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
            const double lineLength = height / 2 - 20;
            const double lineX = centerX + lineLength * std::sin(angle);
            const double lineY = centerY - lineLength * std::cos(angle);

            //Custom color
            Colour gold(255, 215, 0);

            // Draw the rotating rectangle line behind the knob
            g.setColour(gold);
            g.drawLine(static_cast<float>(centerX), static_cast<float>(centerY), static_cast<float>(lineX), static_cast<float>(lineY), 3.0f); // Adjust the line thickness as needed


            // Draw the image frame on the slider
            g.drawImage(knobImage, x, y, width, height, 0, static_cast<int>(frameId * knobImage.getWidth()), knobImage.getWidth(), knobImage.getWidth());
        }
    }

private:
    Image knobImage;
};
