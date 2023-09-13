#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DjAudioPlayer.h"

using namespace juce;

class MainComponent : public AudioAppComponent,
    public Button::Listener,
    public Slider::Listener
{
public:
    MainComponent();
    ~MainComponent() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void paint(Graphics& g) override;
    void resized() override;

    void buttonClicked(Button* button) override;
    void sliderValueChanged(Slider* slider) override;

private:
    DjAudioPlayer player1; // Adding DJAudioPlayer as a data member

    TextButton playButton{ "Play" };
    TextButton stopButton{ "Stop" };
    TextButton loadButton{ "Load" }; // Corrected the button text
    Slider gainSlider;
    Slider speedSlider;
    Slider posSlider;

    FileChooser fChooser{ "Select a file..." };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
