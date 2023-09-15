#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "CustomLookAndFeel.h"
#include "CustomLookAndFeel2.h"
#include "CustomLookAndFeel3.h"

using namespace juce;

class DeckGUI : public Component,
                public Button::Listener,
                public Slider::Listener
{
public:
    DeckGUI(DjAudioPlayer* _djAudioPlayer);
    ~DeckGUI() override;

    void paint (Graphics&) override;
    void resized() override;

    void buttonClicked(Button* button) override;
    void sliderValueChanged(Slider* slider) override;

    void togglePitch();


private:
    DjAudioPlayer* djAudioPlayer;

    CustomLookAndFeel customLookAndFeel;

    CustomLookAndFeel2 customLookAndFeel2;

    CustomLookAndFeel3 customLookAndFeel3;

    ImageComponent backgroundImageComponent;

    TextButton playButton{ "Play" };
    TextButton stopButton{ "Stop" };
    TextButton loadButton{ "Load" };

    TextButton pitchToggleButton{ "Toggle Pitch" };

    Slider volumeSlider;
    Slider pitchSlider;
    Slider speedSlider;

    FileChooser fChooser{ "Select a file..." };


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
