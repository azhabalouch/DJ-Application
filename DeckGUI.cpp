#include "../JuceLibraryCode/JuceHeader.h"
#include "DeckGUI.h"


DeckGUI::DeckGUI(DjAudioPlayer* _djAudioPlayer,
    AudioFormatManager& formatManagerToUse,
    AudioThumbnailCache& cacheToUse)
    : djAudioPlayer(_djAudioPlayer),
      waveformDisplay(formatManagerToUse, cacheToUse)
{
    // Setting Background image
    Image backgroundImage = ImageCache::getFromMemory(BinaryData::Background2_jpg, BinaryData::Background2_jpgSize);
    DrawableImage drawableImage;
    drawableImage.setImage(backgroundImage);
    drawableImage.setOverlayColour(Colour::fromRGBA(0, 0, 0, 127));  // RGBA values range from 0 to 255
    Image newImage(Image::RGB, backgroundImage.getWidth(), backgroundImage.getHeight(), true);
    Graphics g(newImage);
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

    //WaveForm Display
    addAndMakeVisible(waveformDisplay);

    //Position Slider
    addAndMakeVisible(positionSlider);
    positionSlider.setRange(0.0, 1.0, 0.01);
    positionSlider.addListener(this);

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

    int rowH = getHeight() / 8;
    int buttonH = 50;
    int buttonW = 100;

    int buttonX = getWidth() / 2 - buttonW / 2;
    int buttonY = rowH * 6;

    int paddingH = 50;
    int paddingW = 70;

    int BarSliderH = (rowH + 2) * 2;
    int BarSliderW = 40;

    int SliderX = getWidth() / 2 + 30;
    int SliderY = rowH * 3;

    int rotateSlideH = 130;
    int rotateSlideW = 110;

    int wavePadding = 15;

    int tButtonH = 30;
    int tButtonW = 55;

    waveformDisplay.setBounds(wavePadding, wavePadding, getWidth() - 2*wavePadding, (rowH * 2) - wavePadding);
    positionSlider.setBounds(wavePadding, rowH * 2, getWidth() - wavePadding, rowH - wavePadding);

    speedSlider.setBounds(SliderX, SliderY, rotateSlideW, rotateSlideH);
    pitchSlider.setBounds(SliderX, SliderY + 125, rotateSlideW, rotateSlideH);
    pitchToggleButton.setBounds(SliderX + 125, SliderY + 175, tButtonW, tButtonH);

    volumeSlider.setBounds(SliderX - 100, SliderY, BarSliderW, BarSliderH);
    reverbSlider.setBounds(SliderX - 200, SliderY, BarSliderW, BarSliderH);

    playButton.setBounds(buttonX - paddingW, buttonY + paddingH, buttonW, buttonH);
    stopButton.setBounds(buttonX + paddingW, buttonY + paddingH, buttonW, buttonH);
    loadButton.setBounds(buttonX, buttonY + (2 * paddingH) + 20, buttonW, buttonH);
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
                waveformDisplay.loadURL(URL{ chooser.getResult() });
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
    if (slider == &positionSlider)
    {
        djAudioPlayer->setRelativePosition(slider->getValue());
    }
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

bool DeckGUI::isInterestedInFileDrag(const StringArray& files)
{
    return true;
}

void DeckGUI::filesDropped(const StringArray& files, int x, int y)
{
    for (String filename : files)
    {
        URL fileURL = URL{ File{filename} };
        djAudioPlayer->loadURL(fileURL);
    }
}

