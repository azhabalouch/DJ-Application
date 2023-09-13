#include "DjAudioPlayer.h"

DjAudioPlayer::DjAudioPlayer() {
    formatManager.registerBasicFormats();
}

DjAudioPlayer::~DjAudioPlayer() {
}

void DjAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void DjAudioPlayer::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) {
    resampleSource.getNextAudioBlock(bufferToFill);
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

void DjAudioPlayer::setGain(double gain) {
    transportSource.setGain(gain);
}

void DjAudioPlayer::setSpeed(double ratio) {
    resampleSource.setResamplingRatio(ratio);
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
