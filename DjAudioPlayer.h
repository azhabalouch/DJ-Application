#pragma once
#include <JuceHeader.h>
#include "ea_soundtouch/ea_soundtouch.h"

using namespace juce;  // Add this line to simplify namespace usage

class DjAudioPlayer : public AudioSource {
public:
    DjAudioPlayer();
    ~DjAudioPlayer();

    // Load audio from a URL
    void loadURL(URL audioURL);

    // Play the audio
    void play();

    // Stop playback
    void stop();

    // Set the playback position in seconds
    void setPosition(double posInSecs);
    void setRelativePosition(double pos);

    // Set the gain (volume) between 0 and 1
    void setGain(float gain);

    // Set the playback speed ratio (1.0 is normal speed)
    void setSpeed(double ratio);

    // Set the pitch of the audio.
    void setPitch(double pitchShiftAmount);

    void setReverbRoomSize(float roomSize);
    void setReverbToNoEffect();

    // Implementations for the AudioSource interface
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

private:
    soundtouch::SoundTouch soundTouch;

    Reverb reverb;

    bool bypassSoundTouch = false;


    AudioFormatManager formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    ResamplingAudioSource resampleSource{ &transportSource, false, 2 };
};
