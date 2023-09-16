#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DjAudioPlayer.h"
#include "SpeedSliderTheme.h"
#include "PitchSliderTheme.h"
#include "VolumeSliderTheme.h"
#include "PitchToggleOffTheme.h"
#include "PitchToggleOnTheme.h"
#include "ButtonTheme.h"
#include "WaveformDisplay.h"

using namespace juce;

class DeckGUI : public Component,
                public Button::Listener,
                public Slider::Listener,
                public FileDragAndDropTarget

{
    public:
        DeckGUI(DjAudioPlayer* djAudioPlayer,
                AudioFormatManager& formatManagerToUse,
                AudioThumbnailCache& cacheToUse);

        ~DeckGUI() override;

        void paint (Graphics&) override;
        void resized() override;

        void buttonClicked(Button* button) override;
        void sliderValueChanged(Slider* slider) override;

        void togglePitch();

        bool isInterestedInFileDrag(const StringArray& files) override;
        void filesDropped(const StringArray& files, int x, int y) override;

    private:
        DjAudioPlayer* djAudioPlayer;
        WaveformDisplay waveformDisplay;

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
        Slider positionSlider; // Temp

        FileChooser fChooser{ "Select a file..." };


        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
