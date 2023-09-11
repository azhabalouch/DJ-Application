#include "MainComponent.h"

MainComponent::MainComponent()
{
    setSize(800, 600);
    if (juce::RuntimePermissions::isRequired(juce::RuntimePermissions::recordAudio)
        && !juce::RuntimePermissions::isGranted(juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request(juce::RuntimePermissions::recordAudio,
            [&](bool granted) { setAudioChannels(granted ? 2 : 0, 2); });
    }
    else
    {
        setAudioChannels(2, 2);
    }

    formatManager.registerBasicFormats();

    addAndMakeVisible(playButton);
    playButton.addListener(this);

    addAndMakeVisible(stopButton);
    stopButton.addListener(this);

    addAndMakeVisible(gainSlider);
    gainSlider.addListener(this);

    addAndMakeVisible(loadButton);
    loadButton.addListener(this);
    loadButton.setButtonText("LOAD");

    gainSlider.setRange(0, 1);

    DBG("MainComponent::resized");
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    playing = false;
    gain = 0.5;
    phase = 0;
    dphase = 0;

    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    if (!playing)
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }
    transportSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    transportSource.releaseResources();
}

void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    int rowH = getHeight() / 5;
    int colW = getWidth();

    playButton.setBounds(0, 0, colW, rowH);
    stopButton.setBounds(0, rowH, colW, rowH);
    loadButton.setBounds(0, rowH * 2, colW, rowH);
    gainSlider.setBounds(0, rowH * 3, colW, rowH);


    DBG("MainComponent::resized");
}

void MainComponent::buttonClicked(juce::Button* button)
{
    if (button == &playButton)
    {
        playing = true;
        dphase = 0;
        transportSource.setPosition(0);
        transportSource.start();
    }

    if (button == &stopButton)
    {
        playing = false;
        transportSource.stop();
    }

    if (button == &loadButton)
    {
        auto fileChooserFlags = juce::FileBrowserComponent::canSelectFiles;
        fChooser.launchAsync(fileChooserFlags,
            [this](const juce::FileChooser& chooser)
            {
                auto chosenFile = chooser.getResult();
                loadURL(juce::URL{ chosenFile });
            });
    }
}

void MainComponent::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &gainSlider)
    {
        gain = gainSlider.getValue();
        transportSource.setGain(gain);
    }

}

void MainComponent::loadURL(juce::URL audioURL)
{
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr)
    {
        std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
    }
    else
    {
        std::cout << "Something went wrong loading the file " << std::endl;
    }
}
