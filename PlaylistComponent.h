#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <algorithm>
#include <cctype>
#include "DjAudioPlayer.h"
#include "Meter.h"
#include "PadsTheme.h"
#include "DeckGUI.h"
#include <vector>
#include "ButtonTheme.h" // Include the custom ButtonTheme header

using namespace juce;

class PlaylistComponent  : public Component,
                           public TableListBoxModel,
                           public Button::Listener,
                           public TextEditor::Listener,
                           public FileDragAndDropTarget
{
public:
    PlaylistComponent(AudioFormatManager& _formatManager);
    ~PlaylistComponent() override;

    void paint (Graphics&) override;
    void resized() override;

    int getNumRows() override;

    void paintRowBackground(Graphics&,
        int rowNumber,
        int width,
        int height,
        bool rowIsSelected) override;

    void paintCell(Graphics&,
        int rowNumber,
        int columnId,
        int width,
        int height,
        bool rowIsSelected) override;

    Component* refreshComponentForCell(int rowNumber,
                                       int columnId,
                                       bool isRowSelected,
                                       Component* existingComponentToUpdate) override;

    virtual void cellClicked(int rowNumber, int columnId, const MouseEvent&) override;

    bool isInterestedInFileDrag(const StringArray& files) override;
    void filesDropped(const StringArray& files, int x, int y) override;

    void buttonClicked(Button* button) override;

    void textEditorTextChanged(TextEditor& editor);

    bool containsIgnoreCase(const std::string& str, const std::string& searchQuery);

    //==============================================================================
    /**Placeholder function override for Audio Source component to tell the source to prepare for playing*/
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    /**Placeholder function override for Audio Source component to fetch subsequent blocks of audio data*/
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill);
    /**Placeholder function override for Audio Source component to release anything it no longer needs*/
    void releaseResources();

    void onTrackLoaded(const String& _trackTitle, const String& _filepath);

    // Add methods to set the DjAudioPlayer instances
    void setPlayer1(DjAudioPlayer* player) { player1 = player; }
    void setPlayer2(DjAudioPlayer* player) { player2 = player; }

    // Add methods to set the DjAudioPlayer instances
    void setDeck1(DeckGUI* player) { deck1 = player; }
    void setDeck2(DeckGUI* player) { deck2 = player; }

private:
    AudioFormatManager& formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;

    ImageComponent backgroundImageComponent; // Component for displaying a background image

    // Add pointers to the DjAudioPlayer instances
    DjAudioPlayer* player1 = nullptr;
    DjAudioPlayer* player2 = nullptr;


    // Add pointers to the DjAudioPlayer instances
    DeckGUI* deck1 = nullptr;
    DeckGUI* deck2 = nullptr;


    DjAudioPlayer* djAudioPlayer;

    ButtonTheme buttonTheme;

    Meter lookAndFeel_ImageMeter;
    PadsTheme lookAndFeel_Pads;

    TextButton headerImage;

    TextButton pad1;
    TextButton pad2;
    TextButton pad3;
    TextButton pad4;
    TextButton pad5;
    TextButton pad6;

    TextEditor searchField;

    String searchQuery;
    std::vector<String> filteredTrackTitles;

    TableListBox tableComponent;

    std::vector<std::string> trackTitles;
    std::vector<std::string> storedFiles;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
