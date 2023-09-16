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

    void resized() override;

private:
    AudioFormatManager formatManager;
    AudioThumbnailCache thumbCache{ 1000 };

    DjAudioPlayer player1;
    DeckGUI deck1{ &player1, formatManager, thumbCache };

    DjAudioPlayer player2;
    DeckGUI deck2{ &player2, formatManager, thumbCache };
    
    MixerAudioSource mixerSource;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
