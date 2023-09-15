#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DjAudioPlayer.h"
#include "DeckGUI.h"

using namespace juce;

class MainComponent : public AudioAppComponent
{
public:
    MainComponent();
    ~MainComponent() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void paint(Graphics& g) override;
    void resized() override;

    

private:
    DjAudioPlayer player1;
    DeckGUI deck1{ &player1 };

    DjAudioPlayer player2;
    DeckGUI deck2{ &player2 };

    MixerAudioSource mixerSource;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
