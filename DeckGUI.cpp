#include "../JuceLibraryCode/JuceHeader.h"
#include "DeckGUI.h"

#include "DeckGUI.h"

/*********class DeckGUI*********/
// Constructor for the DeckGUI class
DeckGUI::DeckGUI(DjAudioPlayer* _djAudioPlayer,
    AudioFormatManager& formatManagerToUse,
    AudioThumbnailCache& cacheToUse)
    :
    djAudioPlayer(_djAudioPlayer),  // Initialize DjAudioPlayer pointer
    waveformDisplay(formatManagerToUse, cacheToUse)  // Initialize waveformDisplay
{
    startTimer(200); // Start a timer with a 200-millisecond interval

    // Setting Background image

    // Load an image from memory (likely for the GUI background)
    Image backgroundImage = ImageCache::getFromMemory(BinaryData::Background2_jpg, BinaryData::Background2_jpgSize);

    DrawableImage drawableImage; // Create a DrawableImage
    drawableImage.setImage(backgroundImage); // Set the image for the drawableImage

    // Set an overlay color for the image
    drawableImage.setOverlayColour(Colour::fromRGBA(0, 0, 0, 127));  // RGBA values range from 0 to 255

    // Create a new image (possibly for rendering)
    Image newImage(Image::RGB, backgroundImage.getWidth(), backgroundImage.getHeight(), true);

    Graphics g(newImage); // Create a Graphics context for the new image
    drawableImage.draw(g, 1.0f); // Draw the drawableImage onto the new image

    // Now you can use newImage with your ImageComponent
    backgroundImageComponent.setImage(newImage); // Set the background image for the GUI
    backgroundImageComponent.setBounds(getLocalBounds()); // Set bounds for the background image component
    backgroundImageComponent.setImagePlacement(RectanglePlacement::stretchToFit); // Set image placement
    addAndMakeVisible(backgroundImageComponent); // Add the background image component to the GUI

    // Custom colour
    Colour lightGold(241, 229, 172);

    // On or Off toggle button

    addAndMakeVisible(pitchToggleButton); // Add the pitchToggleButton to the GUI
    pitchToggleButton.setLookAndFeel(&pToggleOffTheme); // Set the look and feel for the toggle button
    pitchToggleButton.onClick = [this] { togglePitch(); }; // Define a click callback for the toggle button

    // Pitch Slider

    addAndMakeVisible(pitchSlider); // Add the pitchSlider to the GUI
    pitchSlider.setEnabled(false); // Disable the pitch slider by default
    pitchSlider.setLookAndFeel(&pitchSliderTheme); // Set the look and feel for the pitch slider
    pitchSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag); // Set slider style
    pitchSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 30, 20); // Set text box style
    pitchSlider.setNumDecimalPlacesToDisplay(1); // Set decimal places for display
    pitchSlider.setTextBoxIsEditable(true); // Allow editing the text box
    pitchSlider.setRange(0.5, 2); // Set the range of the pitch slider
    pitchSlider.setValue(1.0); // Set the initial value of the pitch slider
    pitchSlider.addListener(this); // Add the DeckGUI as a listener for slider events

    addAndMakeVisible(pitchTitle);
    pitchTitle.setFont(Font("Metroscript", 20.0f, Font::bold));
    pitchTitle.setText("Pitch", dontSendNotification);
    pitchTitle.setColour(Label::textColourId, lightGold);
    pitchTitle.setJustificationType(Justification::centred);

    // Volume Slider

    addAndMakeVisible(volumeSlider); // Add the volumeSlider to the GUI
    volumeSlider.setSliderStyle(Slider::SliderStyle::LinearVertical); // Set slider style
    volumeSlider.setLookAndFeel(&volumeSliderTheme); // Set the look and feel for the volume slider
    volumeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 30, 20); // Set text box style
    volumeSlider.setNumDecimalPlacesToDisplay(1); // Set decimal places for display
    volumeSlider.setTextBoxIsEditable(true); // Allow editing the text box
    volumeSlider.setRange(0.0, 10.0); // Set the range of the volume slider
    volumeSlider.setValue(1.0); // Set the initial value of the volume slider
    volumeSlider.addListener(this); // Add the DeckGUI as a listener for slider events

    addAndMakeVisible(volumeTitle);
    volumeTitle.setFont(Font("Metroscript", 20.0f, Font::bold));
    volumeTitle.setText("Volume", dontSendNotification);
    volumeTitle.setColour(Label::textColourId, lightGold);
    volumeTitle.setJustificationType(Justification::centred);

    // Speed Slider

    addAndMakeVisible(speedSlider); // Add the speedSlider to the GUI
    speedSlider.setLookAndFeel(&speedSliderTheme); // Set the look and feel for the speed slider
    speedSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag); // Set slider style
    speedSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 30, 20); // Set text box style
    speedSlider.setNumDecimalPlacesToDisplay(1); // Set decimal places for display
    speedSlider.setTextBoxIsEditable(true); // Allow editing the text box
    speedSlider.setRange(0.0, 10.0); // Set the range of the speed slider
    speedSlider.setValue(1.0); // Set the initial value of the speed slider
    speedSlider.addListener(this); // Add the DeckGUI as a listener for slider events

    addAndMakeVisible(speedTitle);
    speedTitle.setFont(Font("Metroscript", 20.0f, Font::bold));
    speedTitle.setText("Speed", dontSendNotification);
    speedTitle.setColour(Label::textColourId, lightGold);
    speedTitle.setJustificationType(Justification::centred);

    // Reverb Slider

    addAndMakeVisible(reverbSlider); // Add the reverbSlider to the GUI
    reverbSlider.setSliderStyle(Slider::SliderStyle::LinearVertical); // Set slider style
    reverbSlider.setLookAndFeel(&volumeSliderTheme); // Set the look and feel for the reverb slider (reuse volume slider theme)
    reverbSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 30, 20); // Set text box style
    reverbSlider.setNumDecimalPlacesToDisplay(1); // Set decimal places for display
    reverbSlider.setTextBoxIsEditable(true); // Allow editing the text box
    reverbSlider.setRange(0.0, 1.0, 0.01); // Set the range of the reverb slider
    reverbSlider.setValue(0.0);  // Set the initial value of the reverb slider
    reverbSlider.addListener(this); // Add the DeckGUI as a listener for slider events

    addAndMakeVisible(reverbTitle);
    reverbTitle.setFont(Font("Metroscript", 20.0f, Font::bold));
    reverbTitle.setText("Reverb", dontSendNotification);
    reverbTitle.setColour(Label::textColourId, lightGold);
    reverbTitle.setJustificationType(Justification::centred);

    // Waveform Display

    addAndMakeVisible(waveformDisplay); // Add the waveformDisplay to the GUI

    // Position Slider

    addAndMakeVisible(positionSlider); // Add the positionSlider to the GUI
    positionSlider.setLookAndFeel(&positionSliderTheme); // Set the look and feel for the position slider
    positionSlider.setRange(0.0, 1.0, 0.01); // Set the range of the position slider
    positionSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0); // Set text box style to no text box
    positionSlider.addListener(this); // Add the DeckGUI as a listener for slider events

    // Play Button

    addAndMakeVisible(playButton); // Add the playButton to the GUI
    playButton.setLookAndFeel(&buttonTheme); // Set the look and feel for the play button
    playButton.addListener(this); // Add the DeckGUI as a listener for button events

    // Stop Button

    addAndMakeVisible(stopButton); // Add the stopButton to the GUI
    stopButton.setLookAndFeel(&buttonTheme); // Set the look and feel for the stop button
    stopButton.addListener(this); // Add the DeckGUI as a listener for button events

    // Load Button

    addAndMakeVisible(loadButton); // Add the loadButton to the GUI
    loadButton.setLookAndFeel(&buttonTheme); // Set the look and feel for the load button
    loadButton.addListener(this); // Add the DeckGUI as a listener for button events

    addAndMakeVisible(resetButton); // Add the loadButton to the GUI
    resetButton.setLookAndFeel(&buttonTheme); // Set the look and feel for the load button
    resetButton.addListener(this); // Add the DeckGUI as a listener for button events
}

/*********destructor ~DeckGUI*********/
// Destructor for the DeckGUI class
DeckGUI::~DeckGUI()
{
    stopTimer(); // Stop the timer when the GUI component is destroyed
}

/*********method paint*********/
// Override the paint method to perform custom drawing
void DeckGUI::paint(juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

/*********method resized*********/
// Override the resized method to handle component layout
void DeckGUI::resized()
{
    backgroundImageComponent.setBounds(getLocalBounds()); // Set the background image component's bounds to fill the entire component

    // Define various layout parameters for GUI components
    int rowH = getHeight() / 8; // Calculate the height of a row
    int buttonH = 50; // Set the height of buttons
    int buttonW = 90; // Set the width of buttons
    int buttonX = getWidth() / 2 - buttonW / 2; // Calculate the horizontal position for buttons
    int buttonY = rowH * 6; // Calculate the vertical position for buttons
    int paddingH = 50; // Vertical padding value
    int paddingW = 50; // Horizontal padding value
    int BarSliderH = (rowH * 2) + 10; // Calculate the height of Bar slider
    int BarSliderW = 32; // Width of Bar slider
    int SliderX = getWidth() / 2; // Calculate the horizontal position for sliders
    int SliderY = rowH * 3; // Calculate the vertical position for sliders
    int rotateSlideH = 130; // Height of rotary sliders
    int rotateSlideW = 110; // Width of rotary sliders
    int wavePadding = 20; // Padding for the waveform display
    int pSliderH = 30; // Padding height of a pitch slider
    int tButtonH = 30; // Height of a toggle button
    int tButtonW = 55; // Width of a toggle button

    // Set the bounds for various GUI components
    waveformDisplay.setBounds(wavePadding - 5, wavePadding, getWidth() - (wavePadding + 10), (rowH * 2) - wavePadding); // Set bounds for the waveform display
    positionSlider.setBounds(wavePadding - 5, rowH * 2 + 15, getWidth() - (wavePadding + 2), pSliderH); // Set bounds for the position slider

    volumeTitle.setBounds(SliderX - 90, SliderY + 200, 70, 40);
    volumeSlider.setBounds(SliderX - 75, SliderY, BarSliderW, BarSliderH); // Set bounds for the volume slider

    reverbTitle.setBounds(SliderX - 160, SliderY + 200, 70, 40);
    reverbSlider.setBounds(SliderX - 145, SliderY, BarSliderW, BarSliderH); // Set bounds for the reverb slider

    playButton.setBounds(buttonX - buttonW + 20, buttonY + 35, buttonW, buttonH); // Set bounds for the play button
    stopButton.setBounds(buttonX + paddingW + 10, buttonY + 35, buttonW, buttonH); // Set bounds for the stop button
    loadButton.setBounds(buttonX - buttonW + 20, buttonY + 2 * paddingH, buttonW, buttonH); // Set bounds for the load button
    resetButton.setBounds(buttonX + paddingW + 10, buttonY + 2 * paddingH, buttonW, buttonH); // Set bounds for the load button

    speedTitle.setBounds(SliderX + 70, SliderY + 20, rotateSlideW, rotateSlideH);
    speedSlider.setBounds(SliderX, SliderY - 20, rotateSlideW, rotateSlideH); // Set bounds for the speed slider

    pitchTitle.setBounds(SliderX + 95, SliderY + 195, 60, 50);
    pitchSlider.setBounds(SliderX, SliderY + 125, rotateSlideW, rotateSlideH); // Set bounds for the pitch slider
    pitchToggleButton.setBounds(SliderX + 100, SliderY + 175, tButtonW, tButtonH); // Set bounds for the pitch toggle button
}

/*********method buttonClicked*********/
// Handle button click events
void DeckGUI::buttonClicked(Button* button)
{
    if (button == &playButton) // Check if the clicked button is the play button
    {
        djAudioPlayer->setPosition(0); // Set the audio player's position to the beginning
        djAudioPlayer->play(); // Start playing audio
    }

    if (button == &stopButton) // Check if the clicked button is the stop button
    {
        djAudioPlayer->stop(); // Stop audio playback
    }

    if (button == &loadButton) // Check if the clicked button is the load button
    {
        auto fileChooserFlags = FileBrowserComponent::canSelectFiles; // Define file chooser flags

        // Launch a file chooser dialog asynchronously
        fChooser.launchAsync(fileChooserFlags,
            [this](const FileChooser& chooser)
            {
                URL audioURL = URL{ chooser.getResult() }; // Get the selected file's URL
                djAudioPlayer->loadURL(audioURL); // Load the selected audio file in the audio player
                updateWaveform(audioURL); // Load the same audio file in the waveform display
            });
    }

    if (button == &resetButton) // Check if the clicked button is the stop button
    {
        _clearWaveform(); // Stop audio playback
    }
}

/*********method sliderValueChanged*********/
// Handle slider value change events
void DeckGUI::sliderValueChanged(Slider* slider)
{
    if (slider == &volumeSlider) // Check if the changed slider is the volume slider
    {
        djAudioPlayer->setGain(static_cast<float>(slider->getValue())); // Set the audio player's gain based on the slider value
    }
    if (slider == &speedSlider) // Check if the changed slider is the speed slider
    {
        djAudioPlayer->setSpeed(slider->getValue()); // Set the audio player's speed based on the slider value
    }
    if (slider == &pitchSlider) // Check if the changed slider is the pitch slider
    {
        if (pitchSlider.isEnabled()) // Check if the pitch slider is enabled
        {
            djAudioPlayer->setPitch(slider->getValue()); // Set the audio player's pitch based on the slider value
        }
        else
        {
            djAudioPlayer->setPitch(1.0f); // Set the pitch to 1.0 if the slider is disabled
        }
    }
    if (slider == &reverbSlider) // Check if the changed slider is the reverb slider
    {
        if (slider->getValue() == 0.0) // Check if the reverb slider value is 0.0
        {
            djAudioPlayer->setReverbToNoEffect(); // Set no reverb effect in the audio player
        }
        else
        {
            djAudioPlayer->setReverbRoomSize(static_cast<float>(slider->getValue())); // Set the reverb room size based on the slider value
        }
    }
    if (slider == &positionSlider) // Check if the changed slider is the position slider
    {
        djAudioPlayer->setRelativePosition(slider->getValue()); // Set the audio player's relative position based on the slider value
    }
}

/*********method togglePitch*********/
// Toggle the pitch slider's enabled state
void DeckGUI::togglePitch() {
    if (pitchSlider.isEnabled()) // Check if the pitch slider is enabled
    {
        // Disable the pitch slider
        pitchSlider.setEnabled(false);
        pitchToggleButton.setLookAndFeel(&pToggleOffTheme); // Set the look and feel for the pitch toggle button when disabled
    }
    else
    {
        // Enable the pitch slider
        pitchSlider.setEnabled(true);
        pitchToggleButton.setLookAndFeel(&pToggleOnTheme); // Set the look and feel for the pitch toggle button when enabled
    }

    sliderValueChanged(&pitchSlider); // Trigger a value change event to update pitch immediately
}

bool DeckGUI::isInterestedInFileDrag(const StringArray& files)
{
    for (const auto& file : files)
    {
        if (file.containsIgnoreCase(".mp3") || file.containsIgnoreCase(".wav"))
            return true;
    }
    return false;
}

void DeckGUI::filesDropped(const StringArray& files, int x, int y)
{
    for (String filename : files) // Iterate through the dropped files
    {
        URL fileURL = URL{ File{filename} }; // Create a URL from the dropped file
        djAudioPlayer->loadURL(fileURL); // Load the dropped audio file in the audio player
        updateWaveform(fileURL);
    }
}

void DeckGUI::updateWaveform(URL audioURL)
{
    waveformDisplay.loadURL(audioURL); // Load the same audio file in the waveform display
}

void DeckGUI::_clearWaveform()
{
    djAudioPlayer->flush();
    waveformDisplay.clearWaveform();
}

void DeckGUI::timerCallback()
{
    waveformDisplay.setPositionRelative(djAudioPlayer->getPositionRelative()); // Update the waveform display's position based on the audio player's relative position
}
