#include "../JuceLibraryCode/JuceHeader.h"
#include "WaveformDisplay.h"

WaveformDisplay::WaveformDisplay(AudioFormatManager& formatManagerToUse,
    AudioThumbnailCache& cacheToUse)
    :
    audioThumbnail(1000, formatManagerToUse, cacheToUse),
    fileLoaded(false),
    position(0)
{
    // Constructor for the WaveformDisplay class, with parameters for format manager and cache
    // Initialize the audioThumbnail with a maximum size of 1000 pixels, using the provided format manager and cache
    // Initialize the fileLoaded flag as false
    // Initialize the position as 0
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    audioThumbnail.addChangeListener(this); // Add this component as a change listener to the audioThumbnail
}

WaveformDisplay::~WaveformDisplay()
{
    // Destructor for the WaveformDisplay class
}

void WaveformDisplay::paint(Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    if (fileLoaded)
    {
        Colour gold(255, 215, 0); // Define a custom color as "gold"
        Colour random(210, 120, 0); // Define a custom color as "random"

        /*g.setColour(gold);
        audioThumbnail.drawChannel(g, getLocalBounds(), 0, audioThumbnail.getTotalLength(), 0, 1.0);*/

        // Draw played part
        g.setColour(random); // Set the drawing color to "random"
        audioThumbnail.drawChannel(g, getLocalBounds().withWidth(position * getWidth()), 0, position * audioThumbnail.getTotalLength(), 0, 1.0);
        // Draw the played part of the audio waveform

        // Draw unplayed part
        g.setColour(gold); // Set the drawing color to "gold"
        audioThumbnail.drawChannel(g, getLocalBounds().withTrimmedLeft(position * getWidth()), position * audioThumbnail.getTotalLength(), audioThumbnail.getTotalLength(), 0, 1.0);
        // Draw the unplayed part of the audio waveform

        // Draw knob line
        g.setColour(Colours::red); // Set the drawing color to red
        g.drawRect(position * getWidth(), 0, 2, getHeight()); // Draw a red line to indicate the current position

        // Draw TimeCode
        g.setColour(Colours::white); // Set the drawing color to white
        g.drawText(timeToTimecode(position * audioThumbnail.getTotalLength()), 10, 10, 100, 20, Justification::left, true);
        // Draw the timecode text based on the current position
    }
    else
    {
        g.setColour(Colours::grey); // Set the drawing color to grey
        g.drawRect(getLocalBounds(), 1);   // Draw an outline around the component

        Colour lightGold(241, 229, 172); // Define a custom color as "lightGold"
        g.setColour(lightGold); // Set the drawing color to "lightGold"
        g.setFont(Font("Metroscript", 40.0f, Font::bold)); // Set the font style
        g.drawText("Drag/Drop or use load button.", getLocalBounds(),
            Justification::centred, true);   // Draw some placeholder text
        // Display a message to indicate that no file is loaded
    }
}

void WaveformDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void WaveformDisplay::changeListenerCallback(ChangeBroadcaster* source)
{
    repaint();
    // Callback function to repaint the waveform display when there's a change in the audioThumbnail
}

void WaveformDisplay::loadURL(URL audioURL)
{
    audioThumbnail.clear(); // Clear the audioThumbnail
    fileLoaded = audioThumbnail.setSource(new URLInputSource(audioURL)); // Load the audio from the provided URL
}

void WaveformDisplay::setPositionRelative(double pos)
{
    if (pos != position)
    {
        position = pos; // Set the position to the provided relative position
        repaint(); // Repaint the waveform display
    }
}

String WaveformDisplay::timeToTimecode(double timeInSeconds) {
    int hours = timeInSeconds / 3600; // Calculate hours
    int minutes = (timeInSeconds - (hours * 3600)) / 60; // Calculate minutes
    int seconds = timeInSeconds - (hours * 3600) - (minutes * 60); // Calculate seconds
    return String::formatted("%02d:%02d:%02d", hours, minutes, seconds); // Format and return the timecode as a string
}
