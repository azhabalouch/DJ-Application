#include "MainComponent.h"

MainComponent::MainComponent() // Constructor for the MainComponent class
{
    setSize(1024, 768); // Set the size of the component to 1024x768 pixels

    // Check if recording audio permission is required and not granted
    if (RuntimePermissions::isRequired(RuntimePermissions::recordAudio)
        && !RuntimePermissions::isGranted(RuntimePermissions::recordAudio))
    {
        // Request the recording audio permission and set audio channels accordingly
        RuntimePermissions::request(RuntimePermissions::recordAudio,
            [&](bool granted) { setAudioChannels(granted ? 2 : 0, 2); });
    }
    else
    {
        // Set audio channels to 2 (stereo) if permission is already granted
        setAudioChannels(2, 2);
    }

    // Add and make visible the deck1 and deck2 components
    addAndMakeVisible(deck1);
    addAndMakeVisible(deck2);

    formatManager.registerBasicFormats(); // Register basic audio formats
}

MainComponent::~MainComponent() // Destructor for the MainComponent class
{
    shutdownAudio(); // Shutdown the audio system
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    mixerSource.addInputSource(&player1, false); // Add player1 as an input to the mixer
    mixerSource.addInputSource(&player2, false); // Add player2 as an input to the mixer
    mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate); // Prepare the mixer for playback
}

void MainComponent::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
    mixerSource.getNextAudioBlock(bufferToFill); // Get the next audio block from the mixer
}

void MainComponent::releaseResources()
{
    mixerSource.removeAllInputs(); // Remove all inputs from the mixer
    mixerSource.releaseResources(); // Release resources used by the mixer
    player1.releaseResources(); // Release resources used by player1
    player2.releaseResources(); // Release resources used by player2
}

void MainComponent::resized()
{
    // Set the bounds of deck1 to occupy the left half of the component
    deck1.setBounds(0, 0, getWidth() / 2, getHeight());

    // Set the bounds of deck2 to occupy the right half of the component
    deck2.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight());
}
