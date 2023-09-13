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

    addAndMakeVisible(playButton);
    playButton.addListener(this);

    addAndMakeVisible(stopButton);
    stopButton.addListener(this);

    addAndMakeVisible(gainSlider);
    gainSlider.addListener(this);

    addAndMakeVisible(speedSlider);
    speedSlider.addListener(this);

    addAndMakeVisible(posSlider);
    posSlider.addListener(this);

    addAndMakeVisible(loadButton);
    loadButton.addListener(this);

    gainSlider.setRange(0.0, 1.0);
    posSlider.setRange(0.0, 1.0);
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate); // Delegating to DJAudioPlayer
}

void MainComponent::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
    player1.getNextAudioBlock(bufferToFill); // Delegating to DJAudioPlayer
}

void MainComponent::releaseResources()
{
    player1.releaseResources(); // Delegating to DJAudioPlayer
}

void MainComponent::paint(Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    int rowH = getHeight() / 6;
    int width = getWidth();

    playButton.setBounds(0, 0, width, rowH);
    stopButton.setBounds(0, rowH, width, rowH);
    gainSlider.setBounds(0, rowH * 2, width, rowH);
    speedSlider.setBounds(0, rowH * 3, width, rowH);
    posSlider.setBounds(0, rowH * 4, width, rowH);
    loadButton.setBounds(0, rowH * 5, width, rowH);
}

void MainComponent::buttonClicked(Button* button)
{
    if (button == &playButton)
    {
        player1.play(); // Delegating to DJAudioPlayer
    }

    if (button == &stopButton)
    {
        player1.stop(); // Delegating to DJAudioPlayer
    }

    if (button == &loadButton)
    {
        auto fileChooserFlags = FileBrowserComponent::canSelectFiles;
        
        fChooser.launchAsync(fileChooserFlags,
            [this](const FileChooser& chooser)
            {
                URL audioURL = URL{ chooser.getResult() };
                player1.loadURL(audioURL);
            });
    }
}

void MainComponent::sliderValueChanged(Slider* slider)
{
    if (slider == &gainSlider)
    {
        player1.setGain(static_cast<float>(slider->getValue())); // Delegating to DJAudioPlayer
    }
    if (slider == &speedSlider)
    {
        player1.setSpeed(slider->getValue()); // Delegating to DJAudioPlayer
    }
    if (slider == &posSlider)
    {
        player1.setRelativePosition(slider->getValue()); // Delegating to DJAudioPlayer
    }
}