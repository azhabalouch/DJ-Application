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

/*********class DeckGUI*********/
// Define the DeckGUI class, which inherits from Component
class DeckGUI : public Component,
    public Button::Listener, // Implement the Button::Listener interface
    public Slider::Listener, // Implement the Slider::Listener interface
    public FileDragAndDropTarget, // Implement the FileDragAndDropTarget interface
    public Timer   // Implement the Timer interface
{
public:
    /*********constructor DeckGUI*********/
    // Constructor for DeckGUI, taking a DjAudioPlayer pointer and other parameters
    DeckGUI(DjAudioPlayer* djAudioPlayer,
        AudioFormatManager& formatManagerToUse,
        AudioThumbnailCache& cacheToUse);

    /*********destructor ~DeckGUI*********/
    // Destructor for DeckGUI
    ~DeckGUI() override;

    /*********method paint*********/
    // Override the paint method to perform custom drawing
    void paint(Graphics&) override;

    /*********method resized*********/
    // Override the resized method to handle component layout
    void resized() override;

    /*********method buttonClicked*********/
    // Handle button click events
    void buttonClicked(Button* button) override;

    /*********method sliderValueChanged*********/
    // Handle slider value change events
    void sliderValueChanged(Slider* slider) override;

    /*********method togglePitch*********/
    // Toggle the pitch slider's state
    void togglePitch();

    /*********method isInterestedInFileDrag*********/
    // Determine if the component is interested in file drag events
    bool isInterestedInFileDrag(const StringArray& files) override;

    /*********method filesDropped*********/
    // Handle files dropped onto the component
    void filesDropped(const StringArray& files, int x, int y) override;

    /*********method timerCallback*********/
    // Handle timer callback events
    void timerCallback() override;

    /*********method updateWaveform*********/
    // Update the waveform display with the given audio URL
    void updateWaveform(URL audioURL);

    /*********method _clearWaveform*********/
    // Clear the waveform display
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

    

    Label volumeTitle;
    Slider volumeSlider; // Volume slider

    Label pitchTitle;
    Slider pitchSlider; // Pitch slider
    TextButton pitchToggleButton{}; // A text button for toggling pitch adjustment

    Label speedTitle;
    Slider speedSlider; // Speed slider
    
    Label reverbTitle;
    Slider reverbSlider; // Reverb slider
    
    Slider positionSlider; // Position slider (temporary)

    FileChooser fChooser{ "Select a file..." }; // File chooser dialog

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI) // Macros to declare non-copyable and add leak detection
};
