#include <JuceHeader.h>
#include "DeckGUI.h"

DeckGUI::DeckGUI(DjAudioPlayer* _djAudioPlayer) : djAudioPlayer{ _djAudioPlayer }
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(volumeSlider);
    addAndMakeVisible(positionSlider);
    addAndMakeVisible(speedSlider);

    playButton.addListener(this);
    stopButton.addListener(this);
    volumeSlider.addListener(this);
    positionSlider.addListener(this);
    speedSlider.addListener(this);
    loadButton.addListener(this);

    speedSlider.setRange(0.0, 10.0);
    volumeSlider.setRange(0.0, 2.0);
}

DeckGUI::~DeckGUI()
{
}

void DeckGUI::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void DeckGUI::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    int rowH = getHeight() / 6;

    playButton.setBounds(0, 0, getWidth(), rowH);
    stopButton.setBounds(0, rowH, getWidth(), rowH);
    volumeSlider.setBounds(0, rowH * 2, getWidth(), rowH);
    speedSlider.setBounds(0, rowH * 3, getWidth(), rowH);
    positionSlider.setBounds(0, rowH * 4, getWidth(), rowH);
    loadButton.setBounds(0, rowH * 5, getWidth(), rowH);
}

void DeckGUI::buttonClicked(Button* button)
{
    if (button == &playButton)
    {
        djAudioPlayer->setPosition(0);
        djAudioPlayer->play();

    }

    if (button == &stopButton)
    {
        djAudioPlayer->stop();
    }

    if (button == &loadButton)
    {
        auto fileChooserFlags = FileBrowserComponent::canSelectFiles;

        fChooser.launchAsync(fileChooserFlags,
            [this](const FileChooser& chooser)
            {
                URL audioURL = URL{ chooser.getResult() };
                djAudioPlayer->loadURL(audioURL);
            });
    }
}

void DeckGUI::sliderValueChanged(Slider* slider)
{
    if (slider == &volumeSlider)
    {
        djAudioPlayer->setGain(static_cast<float>(slider->getValue()));
    }
    if (slider == &speedSlider)
    {
        djAudioPlayer->setSpeed(slider->getValue());
    }
    if (slider == &positionSlider)
    {
        djAudioPlayer->setRelativePosition(slider->getValue());
    }
}
