#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "ea_soundtouch/ea_soundtouch.h"

using namespace juce;

class DjAudioPlayer : public AudioSource {
public:
    // Constructor taking an AudioFormatManager reference
    DjAudioPlayer(AudioFormatManager& _formatManager);

    // Destructor
    ~DjAudioPlayer();

    // Load audio from a URL
    void loadURL(URL audioURL);

    // Play the audio
    void play();

    // Stop playback
    void stop();

    // Set the playback position in seconds
    void setPosition(double posInSecs);

    // Set the playback position relative to the current position
    void setRelativePosition(double pos);

    // Get the current playback position relative to the audio duration
    double getPositionRelative();

    // Set the gain (volume) between 0 and 1
    void setGain(float gain);

    // Set the playback speed ratio (1.0 is normal speed)
    void setSpeed(double ratio);

    // Set the pitch of the audio.
    void setPitch(double pitchShiftAmount);

    // Set the reverb room size (0.0 to 1.0)
    void setReverbRoomSize(float roomSize);

    // Disable the reverb effect
    void setReverbToNoEffect();

    // Implementations for the AudioSource interface

    // Prepare the audio player for playback
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;

    // Fill the audio buffer with the next audio block
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;

    // Release any allocated resources
    void releaseResources() override;

    // Flush any pending audio data
    void flush();

    // Callback function to notify when a track is loaded
    std::function<void(const String&, const String&)> trackLoadedCallback;

private:
    soundtouch::SoundTouch soundTouch; // SoundTouch processor for pitch shifting
    Reverb reverb; // Reverb processor for adding reverb effect
    bool bypassSoundTouch = false; // Flag to bypass SoundTouch processing
    AudioFormatManager& formatManager; // Reference to an AudioFormatManager
    std::unique_ptr<AudioFormatReaderSource> readerSource; // Pointer to an audio format reader source
    AudioTransportSource transportSource; // Audio transport source for playback control
    ResamplingAudioSource resampleSource{ &transportSource, false, 2 }; // Resampling audio source for playback
};
