#include <JuceHeader.h>
#include "DeckGUI.h"

DeckGUI::DeckGUI(DjAudioPlayer* _djAudioPlayer) : djAudioPlayer{ _djAudioPlayer }
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    
    //On or Off
    addAndMakeVisible(pitchToggleButton);
    pitchToggleButton.onClick = [this] { togglePitch(); };

    //Pitch Slider
    addAndMakeVisible(pitchSlider);
    pitchSlider.setEnabled(false); // disable by default
    pitchSlider.setLookAndFeel(&customLookAndFeel2);
    pitchSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    pitchSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 30, 20);
    pitchSlider.setNumDecimalPlacesToDisplay(1);
    pitchSlider.setTextBoxIsEditable(true);
    pitchSlider.setRange(0.5, 2);
    pitchSlider.addListener(this);

    //Volume Slider
    addAndMakeVisible(volumeSlider);
    volumeSlider.addListener(this);

    //Speed Slider
    addAndMakeVisible(speedSlider);
    speedSlider.setLookAndFeel(&customLookAndFeel);
    speedSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    speedSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 30, 20);
    speedSlider.setNumDecimalPlacesToDisplay(0);
    speedSlider.setTextBoxIsEditable(true);
    speedSlider.setRange(0.0, 10.0);
    speedSlider.addListener(this);

    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
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

    speedSlider.setBounds(0, rowH * 2, 120, 130);

    pitchSlider.setBounds(0, rowH * 3, 120, 130);
    pitchToggleButton.setBounds(100, rowH * 3, 150, 90);

    volumeSlider.setBounds(0, rowH * 4, getWidth(), rowH);

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
    if (slider == &pitchSlider)
    {
        if (pitchSlider.isEnabled()) {
            djAudioPlayer->setPitch(slider->getValue());
        }
        else
        {
            djAudioPlayer->setPitch(1.0f);
        }
    }
    /*if (slider == &positionSlider)
    {
        djAudioPlayer->setRelativePosition(slider->getValue());
    }*/
}

void DeckGUI::togglePitch() {
    if (pitchSlider.isEnabled())
    {
        // Disable the pitch slider
        pitchSlider.setEnabled(false);
    }
    else
    {
        // Enable the pitch slider
        pitchSlider.setEnabled(true);
    }

    sliderValueChanged(&pitchSlider);
}