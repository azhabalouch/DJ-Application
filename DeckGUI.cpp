#include <JuceHeader.h>
#include "DeckGUI.h"


DeckGUI::DeckGUI(DjAudioPlayer* _djAudioPlayer) : djAudioPlayer{ _djAudioPlayer }
{
    // Load your image
    Image backgroundImage = ImageCache::getFromMemory(BinaryData::Background2_jpg, BinaryData::Background2_jpgSize);

    // Create a DrawableImage
    DrawableImage drawableImage;
    drawableImage.setImage(backgroundImage);

    // Set a semi-transparent black overlay colour
    drawableImage.setOverlayColour(Colour::fromRGBA(0, 0, 0, 127));  // RGBA values range from 0 to 255

    // Create a new image with the same size as the original one
    Image newImage(Image::RGB, backgroundImage.getWidth(), backgroundImage.getHeight(), true);

    // Create a Graphics context from the new image
    Graphics g(newImage);

    // Draw the DrawableImage onto the new image
    drawableImage.draw(g, 1.0f);

    // Now you can use newImage with your ImageComponent
    backgroundImageComponent.setImage(newImage);
    backgroundImageComponent.setBounds(getLocalBounds());
    backgroundImageComponent.setImagePlacement(RectanglePlacement::stretchToFit);
    addAndMakeVisible(backgroundImageComponent);
    
    //On or Off
    addAndMakeVisible(pitchToggleButton);
    pitchToggleButton.setLookAndFeel(&pToggleOffTheme);
    pitchToggleButton.onClick = [this] { togglePitch(); };


    //Pitch Slider
    addAndMakeVisible(pitchSlider);
    pitchSlider.setEnabled(false); // disable by default
    pitchSlider.setLookAndFeel(&pitchSliderTheme);
    pitchSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    pitchSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 30, 20);
    pitchSlider.setNumDecimalPlacesToDisplay(1);
    pitchSlider.setTextBoxIsEditable(true);
    pitchSlider.setRange(0.5, 2);
    pitchSlider.setValue(1.0);
    pitchSlider.addListener(this);

    //Volume Slider
    addAndMakeVisible(volumeSlider);
    volumeSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    volumeSlider.setLookAndFeel(&volumeSliderTheme);
    volumeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 30, 20);
    volumeSlider.setNumDecimalPlacesToDisplay(1);
    volumeSlider.setTextBoxIsEditable(true);
    volumeSlider.setRange(0.0, 10.0);
    volumeSlider.setValue(1.0); // Initial value
    volumeSlider.addListener(this);

    //Speed Slider
    addAndMakeVisible(speedSlider);
    speedSlider.setLookAndFeel(&speedSliderTheme);
    speedSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    speedSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 30, 20);
    speedSlider.setNumDecimalPlacesToDisplay(1);
    speedSlider.setTextBoxIsEditable(true);
    speedSlider.setRange(0.0, 10.0);
    speedSlider.setValue(1.0); // Initial value
    speedSlider.addListener(this);

    //Reverb Slider
    addAndMakeVisible(reverbSlider);
    reverbSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    reverbSlider.setLookAndFeel(&volumeSliderTheme); //Reusing the Volume Slider Theme as it should be same to
                                                     //achieve UI Design.
    reverbSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 30, 20);
    reverbSlider.setNumDecimalPlacesToDisplay(1);
    reverbSlider.setTextBoxIsEditable(true);
    reverbSlider.setRange(0.0, 1.0, 0.01);
    reverbSlider.setValue(0.0);  // Initial value
    reverbSlider.addListener(this);

    //Play Button
    addAndMakeVisible(playButton);
    playButton.setLookAndFeel(&buttonTheme);
    playButton.addListener(this);

    //Stop Button
    addAndMakeVisible(stopButton);
    stopButton.setLookAndFeel(&buttonTheme);
    stopButton.addListener(this);

    //Load Button
    addAndMakeVisible(loadButton);
    loadButton.setLookAndFeel(&buttonTheme);
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
    backgroundImageComponent.setBounds(getLocalBounds());

    // This method is where you should set the bounds of any child
    // components that your component contains..

    int rowH = getHeight() / 6;
    int buttonH = 50;
    int buttonW = 100;

    int buttonX = getWidth() / 2 - buttonW / 2;
    int buttonY = rowH * 4;

    int paddingH = 80;
    int paddingW = 70;

    int BarSliderH = (rowH + 2) * 2;
    int BarSliderW = 40;

    int SliderX = getWidth() / 2 + 30;
    int SliderY = rowH * 3;

    int rotateSlideH = 130;
    int rotateSlideW = 110;

    int tButtonH = 30;
    int tButtonW = 55;

    speedSlider.setBounds(SliderX, SliderY / 2, rotateSlideW, rotateSlideH);
    pitchSlider.setBounds(SliderX, SliderY - 50, rotateSlideW, rotateSlideH);
    pitchToggleButton.setBounds(SliderX + 125, SliderY, tButtonW, tButtonH);

    volumeSlider.setBounds(SliderX - 100, SliderY / 2, BarSliderW, BarSliderH);
    reverbSlider.setBounds(SliderX - 200, SliderY / 2, BarSliderW, BarSliderH);

    playButton.setBounds(buttonX - paddingW, buttonY + paddingH, buttonW, buttonH);
    stopButton.setBounds(buttonX + paddingW, buttonY + paddingH, buttonW, buttonH);
    loadButton.setBounds(buttonX, buttonY + 2 * paddingH, buttonW, buttonH);
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
    if (slider == &reverbSlider)
    {
        if (slider->getValue() == 0.0) {
            djAudioPlayer->setReverbToNoEffect();
        }
        else {
            djAudioPlayer->setReverbRoomSize(static_cast<float>(slider->getValue()));
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
        pitchToggleButton.setLookAndFeel(&pToggleOffTheme);
    }
    else
    {
        // Enable the pitch slider
        pitchSlider.setEnabled(true);
        pitchToggleButton.setLookAndFeel(&pToggleOnTheme);
    }

    sliderValueChanged(&pitchSlider);
}