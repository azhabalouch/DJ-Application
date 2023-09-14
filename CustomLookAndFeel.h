#pragma once

class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
    CustomLookAndFeel()
    {
        // Load your image here
        knobImage = juce::ImageCache::getFromMemory(BinaryData::SpeedDial_png, BinaryData::SpeedDial_pngSize);
    }

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) override
    {
        if (knobImage.isValid())
        {
            // Calculate the frame index based on the current value of the slider
            const int frames = knobImage.getHeight() / knobImage.getWidth();
            const int frameId = (int)std::ceil(sliderPos * ((double)frames - 1.0));

            // Draw the image frame on the slider
            g.drawImage(knobImage, x, y, width, height, 0, frameId * knobImage.getWidth(), knobImage.getWidth(), knobImage.getWidth());
        }
    }

private:
    juce::Image knobImage;
};
