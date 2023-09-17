#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <algorithm>
#include <cctype>
#include "DjAudioPlayer.h"
#include <vector>
#include "ButtonTheme.h" // Include the custom ButtonTheme header

using namespace juce;

struct TrackInfo
{
    std::string title;
    std::string length; // Store the track length as a string
};


class PlaylistComponent  : public Component,
                           public TableListBoxModel,
                           public Button::Listener,
                           public TextEditor::Listener,
                           public FileDragAndDropTarget
{
public:
    PlaylistComponent();
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

    void onTrackLoaded(const String& trackName);

private:
    ImageComponent backgroundImageComponent; // Component for displaying a background image

    DjAudioPlayer* djAudioPlayer;

    ButtonTheme buttonTheme;

    TextButton editButton{ "Edit" };
    TextEditor searchField;

    String searchQuery;
    std::vector<String> filteredTrackTitles;

    TableListBox tableComponent;

    std::vector<std::string> trackTitles;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
