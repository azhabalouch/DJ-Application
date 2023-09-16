#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

using namespace juce;

class WaveformDisplay  : public Component,
                         public ChangeListener
{
public:
    WaveformDisplay(AudioFormatManager& formatManagerToUse,
                    AudioThumbnailCache& cacheToUse);
    ~WaveformDisplay() override;

    void paint (Graphics&) override;
    void resized() override;

    void loadURL(URL audioURL);
    void changeListenerCallback(ChangeBroadcaster* source) override;

private:
    AudioThumbnail audioThumbnail;

    bool fileLoaded;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
