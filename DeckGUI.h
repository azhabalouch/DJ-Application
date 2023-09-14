#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"

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

private:
    DjAudioPlayer* djAudioPlayer;

    TextButton playButton{ "Play" };
    TextButton stopButton{ "Stop" };
    TextButton loadButton{ "Load" };
    Slider volumeSlider;
    Slider positionSlider;
    Slider speedSlider;
    FileChooser fChooser{ "Select a file..." };


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
