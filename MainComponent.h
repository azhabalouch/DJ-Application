#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DjAudioPlayer.h"
#include "DeckGUI.h"

using namespace juce; // Use the juce namespace for convenience

class MainComponent : public AudioAppComponent // Define the MainComponent class inheriting from AudioAppComponent
{
public:
    MainComponent(); // Constructor for the MainComponent class
    ~MainComponent() override; // Destructor for the MainComponent class

    // Override functions from the AudioAppComponent class
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void resized() override; // Override the resized() function

private:
    AudioFormatManager formatManager; // Manage audio formats
    AudioThumbnailCache thumbCache{ 1000 }; // Cache for audio thumbnails

    DjAudioPlayer player1{ formatManager }; // Create DjAudioPlayer instance with formatManager
    DeckGUI deck1{ &player1, formatManager, thumbCache }; // Create DeckGUI instance associated with player1

    DjAudioPlayer player2{ formatManager }; // Create another DjAudioPlayer instance with formatManager
    DeckGUI deck2{ &player2, formatManager, thumbCache }; // Create another DeckGUI instance associated with player2

    MixerAudioSource mixerSource; // Create a MixerAudioSource for mixing audio

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent) // Macro for non-copyable class with leak detection
};
