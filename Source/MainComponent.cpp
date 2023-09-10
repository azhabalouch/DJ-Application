#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }


    addAndMakeVisible(playButton);
    playButton.addListener(this);

    addAndMakeVisible(stopButton);
    stopButton.addListener(this);

    addAndMakeVisible(gainSlider);
    gainSlider.addListener(this);

    gainSlider.setRange(0, 1);

}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    playing = false;
    gain = 0.5;
    phase = 0;
    dphase = 0;
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    if (!playing)
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }

    auto* leftChannel = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
    auto* rightChannel = bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);
    
    for (auto i = 0; i < bufferToFill.numSamples; ++i)
    {
        auto sample = fmod(phase, 1.0f);
        phase += fmod(dphase, 0.01f);
        dphase += 0.0000005f;
        leftChannel[i] = sample * 0.125 * gain;
        rightChannel[i] = sample * 0.125 * gain;
    }

    //bufferToFill.clearActiveBufferRegion();
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.

    int rowH = getHeight() / 5;
    int colW = getWidth();

    playButton.setBounds(0, 0, colW, rowH);
    stopButton.setBounds(0, rowH, colW, rowH);
    gainSlider.setBounds(0, rowH * 2, colW, rowH);

    DBG("MainComponent::resized");
}

void MainComponent::buttonClicked(juce::Button* button)
{
    if (button == &playButton)
    {
        playing = true;
        dphase = 0;
    }
    if (button == &stopButton)
    {
        playing = false;
    }
}

void MainComponent::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &gainSlider)
    {
        gain = gainSlider.getValue();
    }

}