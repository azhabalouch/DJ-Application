#pragma once

#include <JuceHeader.h>

using namespace juce;  // Add this line to simplify namespace usage

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
    TextButton playButton{ "Play" };
    TextButton stopButton{ "Stop" };
    TextButton loadButton;
    Slider gainSlider;
    AudioTransportSource transportSource;
    AudioFormatManager formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    FileChooser fChooser{ "Select a file..." };
    Slider speedSlider;
    ResamplingAudioSource resampleSource{ &transportSource, false, 2 };

    void loadURL(URL audioURL);

    float phase;
    double dphase;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
