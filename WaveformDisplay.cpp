#include <JuceHeader.h>
#include "WaveformDisplay.h"

WaveformDisplay::WaveformDisplay(AudioFormatManager& formatManagerToUse,
                                 AudioThumbnailCache& cacheToUse)
                                 : 
                                 audioThumbnail(1000, formatManagerToUse, cacheToUse),
                                 fileLoaded(false)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    audioThumbnail.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    if (fileLoaded)
    {
        Colour gold(255, 215, 0);
        g.setColour(gold);
        audioThumbnail.drawChannel(g, getLocalBounds(), 0, audioThumbnail.getTotalLength(), 0, 1.0);

        g.drawRect(getLocalBounds(), 1);   // draw an outline around the component
    }
    else
    {
        g.setColour(Colours::grey);
        g.drawRect(getLocalBounds(), 1);   // draw an outline around the component
        
        Colour lightGold(241, 229, 172);
        g.setColour(lightGold);
        g.setFont(Font("Metroscript", 40.0f, Font::bold));
        g.drawText("Drag/Drop or use load button.", getLocalBounds(),
            Justification::centred, true);   // draw some placeholder text
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
}


void WaveformDisplay::loadURL(URL audioURL)
{
    audioThumbnail.clear();
    fileLoaded = audioThumbnail.setSource(new URLInputSource(audioURL));
}
