#include "MainComponent.h"

MainComponent::MainComponent()
{
    setSize(800, 600);
    if (RuntimePermissions::isRequired(RuntimePermissions::recordAudio)
        && !RuntimePermissions::isGranted(RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request(RuntimePermissions::recordAudio,
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

    addAndMakeVisible(speedSlider);
    speedSlider.addListener(this);

    addAndMakeVisible(loadButton);
    loadButton.addListener(this);
    loadButton.setButtonText("LOAD");

    gainSlider.setRange(0.0, 1.0);
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    phase = 0;
    dphase = 0;

    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
    resampleSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    resampleSource.releaseResources();
}

void MainComponent::paint(Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    int rowH = getHeight() / 5;
    int width = getWidth();

    playButton.setBounds(0, 0, width, rowH);
    stopButton.setBounds(0, rowH, width, rowH);
    loadButton.setBounds(0, rowH * 2, width, rowH);
    gainSlider.setBounds(0, rowH * 3, width, rowH);
    speedSlider.setBounds(0, rowH * 4, width, rowH);
}

void MainComponent::buttonClicked(Button* button)
{
    if (button == &playButton)
    {
        transportSource.start();
    }

    if (button == &stopButton)
    {
        transportSource.stop();
    }

    if (button == &loadButton)
    {
        auto fileChooserFlags = FileBrowserComponent::canSelectFiles;
        fChooser.launchAsync(fileChooserFlags,
            [this](const FileChooser& chooser)
            {
                auto chosenFile = chooser.getResult();
                loadURL(URL{ chosenFile });
            });
    }
}

void MainComponent::sliderValueChanged(Slider* slider)
{
    if (slider == &gainSlider)
    {
        transportSource.setGain(static_cast<float>(slider->getValue()));;
    }
    if (slider == &speedSlider)
    {
        resampleSource.setResamplingRatio(slider->getValue());
    }

}

void MainComponent::loadURL(URL audioURL)
{

    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr)
    {
        std::unique_ptr<AudioFormatReaderSource> newSource (new AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
    }
}
