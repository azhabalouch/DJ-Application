#include "DjAudioPlayer.h"

DjAudioPlayer::DjAudioPlayer(AudioFormatManager& _formatManager) : formatManager(_formatManager)
{
    // Initialize the reverb with no effect
    Reverb::Parameters parameters;

    parameters.wetLevel = 0.0; // Set the wet level of the reverb to 0 (no wet/reverberant sound)
    parameters.dryLevel = 1.0; // Set the dry level of the reverb to 1 (full dry/original sound)

    reverb.setParameters(parameters); // Set the reverb parameters
}

DjAudioPlayer::~DjAudioPlayer() {
}

void DjAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate); // Prepare the transport source for playback
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate); // Prepare the resample source for playback

    soundTouch.setSampleRate(sampleRate); // Set the sample rate for SoundTouch processing
    soundTouch.setChannels(2); // Set the number of audio channels to 2 (stereo)
}

void DjAudioPlayer::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) {
    resampleSource.getNextAudioBlock(bufferToFill); // Get the next audio block from the resample source

    if (bypassSoundTouch) {
        // Convert JUCE's AudioBuffer to SoundTouch's SAMPLETYPE
        // This will depend on your application and how you're using JUCE's AudioBuffer

        // Convert JUCE's AudioBuffer to SoundTouch's SAMPLETYPE
        auto* channelData = bufferToFill.buffer->getReadPointer(0, bufferToFill.startSample);

        // Put samples into SoundTouch processor
        soundTouch.putSamples(channelData, bufferToFill.numSamples);

        // Receive samples from SoundTouch processor
        auto* outputData = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
        int numSamples = soundTouch.receiveSamples(outputData, bufferToFill.numSamples);

        // If there are fewer samples than expected, clear the remaining part of the buffer
        if (numSamples < bufferToFill.numSamples) {
            bufferToFill.buffer->clear(numSamples, bufferToFill.numSamples - numSamples);
        }
    }

    // Process the audio buffer with the reverb
    auto* leftChannel = bufferToFill.buffer->getWritePointer(0);
    auto* rightChannel = bufferToFill.buffer->getWritePointer(1);
    reverb.processStereo(leftChannel, rightChannel, bufferToFill.buffer->getNumSamples());
}

void DjAudioPlayer::releaseResources() {
    transportSource.releaseResources(); // Release resources of the transport source
    resampleSource.releaseResources(); // Release resources of the resample source
}

void DjAudioPlayer::loadURL(URL audioURL) {
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr) {
        std::unique_ptr<AudioFormatReaderSource> newSource(new AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate); // Set the audio source for playback
        readerSource.reset(newSource.release()); // Release the ownership of the new audio source

        if (trackLoadedCallback)
        {
            String _trackTitles = File(audioURL.toString(true)).getFileNameWithoutExtension();
            DBG("Stored File: " + _trackTitles);
            String _storedFiles = audioURL.getLocalFile().getFullPathName();
            DBG("Stored File: " + _storedFiles);
            trackLoadedCallback(_trackTitles, _storedFiles);
        }
    }
}

void DjAudioPlayer::setGain(float gain) {
    transportSource.setGain(gain); // Set the playback gain/volume
}

void DjAudioPlayer::setSpeed(double ratio) {
    resampleSource.setResamplingRatio(ratio); // Set the speed/resampling ratio
}

void DjAudioPlayer::setPitch(double pitchShiftAmount)
{
    if (pitchShiftAmount == 1.0f) {
        // Bypass SoundTouch processing when pitch shift is set to 1.0 (no pitch shift)
        bypassSoundTouch = false;
    }
    else {
        soundTouch.setPitch(pitchShiftAmount); // Set the pitch shift amount
        bypassSoundTouch = true; // Enable SoundTouch processing
    }
}

void DjAudioPlayer::setPosition(double posInSecs) {
    transportSource.setPosition(posInSecs); // Set the playback position in seconds
}

void DjAudioPlayer::setRelativePosition(double pos)
{
    double posInSecs = transportSource.getLengthInSeconds() * pos; // Calculate the position in seconds
    setPosition(posInSecs); // Set the playback position
}

double DjAudioPlayer::getPositionRelative()
{
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds(); // Get the relative playback position
}

void DjAudioPlayer::play() {
    transportSource.start(); // Start audio playback
}

void DjAudioPlayer::stop() {
    transportSource.stop(); // Stop audio playback
}

void DjAudioPlayer::setReverbRoomSize(float roomSize)
{
    auto parameters = reverb.getParameters(); // Get the current reverb parameters
    parameters.damping = 0.5; // Set damping parameter
    parameters.wetLevel = 0.33; // Set wet level
    parameters.dryLevel = 0.4; // Set dry level
    parameters.width = 1.0; // Set width parameter
    parameters.freezeMode = false; // Disable freeze mode
    parameters.roomSize = roomSize; // Set room size
    reverb.setParameters(parameters); // Apply the updated reverb parameters
}

void DjAudioPlayer::setReverbToNoEffect()
{
    auto parameters = reverb.getParameters(); // Get the current reverb parameters
    parameters.wetLevel = 0.0; // Set wet level to 0 (no reverb effect)
    parameters.dryLevel = 1.0; // Set dry level to 1 (full original sound)
    reverb.setParameters(parameters); // Apply the updated reverb parameters
}
