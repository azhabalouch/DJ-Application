#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "ea_soundtouch/ea_soundtouch.h"

using namespace juce;

class DjAudioPlayer : public AudioSource {
public:
    DjAudioPlayer(AudioFormatManager& _formatManager); // Constructor taking an AudioFormatManager reference
    ~DjAudioPlayer(); // Destructor

    // Load audio from a URL
    void loadURL(URL audioURL);

    // Play the audio
    void play();

    // Stop playback
    void stop();

    // Set the playback position in seconds
    void setPosition(double posInSecs);
    void setRelativePosition(double pos);
    double getPositionRelative();

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

    std::function<void(const String&)> trackLoadedCallback;

private:
    soundtouch::SoundTouch soundTouch; // SoundTouch processor for pitch shifting
    Reverb reverb; // Reverb processor for adding reverb effect
    bool bypassSoundTouch = false; // Flag to bypass SoundTouch processing
    AudioFormatManager& formatManager; // Reference to an AudioFormatManager
    std::unique_ptr<AudioFormatReaderSource> readerSource; // Pointer to an audio format reader source
    AudioTransportSource transportSource; // Audio transport source for playback control
    ResamplingAudioSource resampleSource{ &transportSource, false, 2 }; // Resampling audio source for playback
};