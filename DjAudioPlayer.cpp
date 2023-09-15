#include "DjAudioPlayer.h"

DjAudioPlayer::DjAudioPlayer() {
    formatManager.registerBasicFormats();
}

DjAudioPlayer::~DjAudioPlayer() {
}

void DjAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

    soundTouch.setSampleRate(sampleRate);
    soundTouch.setChannels(2);

}

void DjAudioPlayer::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) {
    resampleSource.getNextAudioBlock(bufferToFill);

    if (!bypassSoundTouch) {
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
        
}

void DjAudioPlayer::releaseResources() {
    transportSource.releaseResources();
    resampleSource.releaseResources();
}

void DjAudioPlayer::loadURL(URL audioURL) {
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr) {
        std::unique_ptr<AudioFormatReaderSource> newSource(new AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
    }

}

void DjAudioPlayer::setGain(float gain) {
    transportSource.setGain(gain);
}

void DjAudioPlayer::setSpeed(double ratio) {
    resampleSource.setResamplingRatio(ratio);
}

void DjAudioPlayer::setPitch(double pitchShiftAmount)
{
    if (pitchShiftAmount == 1.0f) {
        // Bypass SoundTouch processing
        bypassSoundTouch = true;
    }
    else {
        soundTouch.setPitch(pitchShiftAmount);
        bypassSoundTouch = false;
    }
}


void DjAudioPlayer::setPosition(double posInSecs) {
    transportSource.setPosition(posInSecs);
}

void DjAudioPlayer::setRelativePosition(double pos)
{
    double posInSecs = transportSource.getLengthInSeconds() * pos;
    setPosition(posInSecs);
}

void DjAudioPlayer::play() {
    transportSource.start();
}

void DjAudioPlayer::stop() {
    transportSource.stop();
}