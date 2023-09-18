#pragma once // Preprocessor directive to ensure the header file is included only once

#include "../JuceLibraryCode/JuceHeader.h" // Include JUCE framework header files

#include "DjAudioPlayer.h" // Include the custom DjAudioPlayer header
#include "SpeedSliderTheme.h" // Include the custom SpeedSliderTheme header
#include "PitchSliderTheme.h" // Include the custom PitchSliderTheme header
#include "VolumeSliderTheme.h" // Include the custom VolumeSliderTheme header
#include "PitchToggleOffTheme.h" // Include the custom PitchToggleOffTheme header
#include "PitchToggleOnTheme.h" // Include the custom PitchToggleOnTheme header
#include "ButtonTheme.h" // Include the custom ButtonTheme header
#include "PositionSliderTheme.h" // Include the custom PositionSliderTheme header
#include "WaveformDisplay.h" // Include the custom WaveformDisplay header

using namespace juce; // Use the JUCE namespace

class DeckGUI : public Component, // Define the DeckGUI class, which inherits from Component
    public Button::Listener, // Implement the Button::Listener interface
    public Slider::Listener, // Implement the Slider::Listener interface
    public FileDragAndDropTarget, // Implement the FileDragAndDropTarget interface
    public Timer   // Implement the Timer interface
{
public:
    DeckGUI(DjAudioPlayer* djAudioPlayer, // Constructor for DeckGUI, taking a DjAudioPlayer pointer and other parameters
        AudioFormatManager& formatManagerToUse,
        AudioThumbnailCache& cacheToUse);

    ~DeckGUI() override; // Destructor for DeckGUI

    void paint(Graphics&) override; // Override the paint method to perform custom drawing
    void resized() override; // Override the resized method to handle component layout

    void buttonClicked(Button* button) override; // Handle button click events
    void sliderValueChanged(Slider* slider) override; // Handle slider value change events

    void togglePitch(); // Toggle the pitch slider's state

    bool isInterestedInFileDrag(const StringArray& files) override; // Determine if the component is interested in file drag events
    void filesDropped(const StringArray& files, int x, int y) override; // Handle files dropped onto the component

    void timerCallback() override; // Handle timer callback events

    void updateWaveform(URL audioURL);

    void _clearWaveform();

private:
    DjAudioPlayer* djAudioPlayer; // Pointer to the DjAudioPlayer
    WaveformDisplay waveformDisplay; // An instance of the custom WaveformDisplay class

    SpeedSliderTheme speedSliderTheme; // Custom theme for the speed slider
    PitchSliderTheme pitchSliderTheme; // Custom theme for the pitch slider
    VolumeSliderTheme volumeSliderTheme; // Custom theme for the volume slider
    PitchToggleOffTheme pToggleOffTheme; // Custom theme for the pitch toggle button when off
    PitchToggleOnTheme pToggleOnTheme; // Custom theme for the pitch toggle button when on
    ButtonTheme buttonTheme; // Custom theme for buttons
    PositionSliderTheme positionSliderTheme; // Custom theme for the position slider

    ImageComponent backgroundImageComponent; // Component for displaying a background image

    TextButton playButton{ "Play" }; // Play button with a label
    TextButton stopButton{ "Stop" }; // Stop button with a label
    TextButton loadButton{ "Load" }; // Load button with a label
    TextButton resetButton{ "Reset" }; // Reset button with a label

    TextButton pitchToggleButton{}; // A text button for toggling pitch adjustment

    Slider volumeSlider; // Volume slider
    Slider pitchSlider; // Pitch slider
    Slider speedSlider; // Speed slider
    Slider reverbSlider; // Reverb slider
    Slider positionSlider; // Position slider (temporary)

    FileChooser fChooser{ "Select a file..." }; // File chooser dialog

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI) // Macros to declare non-copyable and add leak detection
};
