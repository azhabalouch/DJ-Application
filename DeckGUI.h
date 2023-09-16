#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "SpeedSliderTheme.h"
#include "PitchSliderTheme.h"
#include "VolumeSliderTheme.h"
#include "PitchToggleOffTheme.h"
#include "PitchToggleOnTheme.h"
#include "ButtonTheme.h"

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

        SpeedSliderTheme speedSliderTheme;
        PitchSliderTheme pitchSliderTheme;
        VolumeSliderTheme volumeSliderTheme;
        PitchToggleOffTheme pToggleOffTheme;
        PitchToggleOnTheme pToggleOnTheme;
        ButtonTheme buttonTheme;

        ImageComponent backgroundImageComponent;

        TextButton playButton{ "Play" };
        TextButton stopButton{ "Stop" };
        TextButton loadButton{ "Load" };

        TextButton pitchToggleButton{};

        Slider volumeSlider;
        Slider pitchSlider;
        Slider speedSlider;
        Slider reverbSlider;

        FileChooser fChooser{ "Select a file..." };


        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
