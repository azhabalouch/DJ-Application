#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

using namespace juce;

class WaveformDisplay : public Component, // Declare the WaveformDisplay class, inheriting from Component
    public ChangeListener // Implement the ChangeListener interface
{
public:
    WaveformDisplay(AudioFormatManager& formatManagerToUse, // Constructor for the WaveformDisplay class, taking formatManager and cache as parameters
        AudioThumbnailCache& cacheToUse);
    ~WaveformDisplay() override; // Destructor for the WaveformDisplay class

    void paint(Graphics&) override; // Override the paint method for custom rendering
    void resized() override; // Override the resized method for handling component resizing

    void loadURL(URL audioURL); // Method to load audio from a URL
    void changeListenerCallback(ChangeBroadcaster* source) override; // Callback method for handling changes

    void setPositionRelative(double pos); // Method to set the position relative to the waveform

    String timeToTimecode(double timeInSeconds); // Method to convert time in seconds to timecode format

private:
    AudioThumbnail audioThumbnail; // Create an AudioThumbnail object for displaying audio waveforms

    double position; // Store the current position

    bool fileLoaded; // Flag to indicate whether a file is loaded or not

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformDisplay) // Prevent copying and add leak detection
};
