#include "../JuceLibraryCode/JuceHeader.h"
#include "PlaylistComponent.h"

PlaylistComponent::PlaylistComponent(AudioFormatManager& _formatManager)
                                    : formatManager(_formatManager)
{
    /************************************************************
    *************  Setting Background image  ********************
    *************************************************************/

    Image backgroundImage = ImageCache::getFromMemory(BinaryData::Background2_jpg, BinaryData::Background2_jpgSize);

    DrawableImage drawableImage;
    drawableImage.setImage(backgroundImage);

    drawableImage.setOverlayColour(Colour::fromRGBA(0, 0, 0, 127));

    Image newImage(Image::RGB, backgroundImage.getWidth(), backgroundImage.getHeight(), true);

    Graphics g(newImage);
    drawableImage.draw(g, 1.0f);

    backgroundImageComponent.setImage(newImage);
    backgroundImageComponent.setBounds(getLocalBounds());
    backgroundImageComponent.setImagePlacement(RectanglePlacement::stretchToFit);
    addAndMakeVisible(backgroundImageComponent);

    /************************************************************************************************************************/

    addAndMakeVisible(tableComponent);
    tableComponent.setModel(this);
    tableComponent.setVisible(false);

    tableComponent.getHeader().addColumn("Track title", 1, 265);
    tableComponent.getHeader().addColumn("Left Deck", 2, 60);
    tableComponent.getHeader().addColumn("Right Deck", 3, 60);
    tableComponent.getHeader().addColumn("Delete", 4, 40);

    addAndMakeVisible(editButton);
    editButton.setLookAndFeel(&buttonTheme);
    editButton.addListener(this);

    addAndMakeVisible(searchField);
    searchField.setVisible(false);
    searchField.addListener(this);
}

PlaylistComponent::~PlaylistComponent()
{
}

void PlaylistComponent::paint(Graphics& g)
{
    Colour lightGold(241, 229, 172);
    g.setColour(lightGold);
    g.drawRect(getLocalBounds(), 1);

    g.setColour(Colours::white);
    g.setFont(14.0f);
    g.drawText("PlaylistComponent", getLocalBounds(), Justification::centred, true);
}

void PlaylistComponent::resized()
{
    backgroundImageComponent.setBounds(getLocalBounds());

    int buttonH = 50;
    int buttonW = 90;
    int buttonX = getWidth() / 2 - buttonW / 2;
    int buttonY = (getHeight() / 8) * 5;
    int paddingH = 30;
    int paddingW = 50;
    int padding = 10;

    editButton.setBounds(buttonX - 2 * paddingW, buttonY + paddingH, buttonW, buttonH);
    searchField.setBounds(padding, (getHeight() / 8) * 6 + 10, getWidth() - (2 * padding), 25);
    tableComponent.setBounds(padding, (getHeight() / 5) * 4, getWidth() - (2 * padding), getHeight() / 5 - padding);
}

int PlaylistComponent::getNumRows()
{
    // Use the filtered track list when searching, otherwise use the original list
    return searchQuery.isEmpty() ? static_cast<int>(trackTitles.size()) : static_cast<int>(filteredTrackTitles.size());
}

void PlaylistComponent::paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    // Just highlight selected rows
    if (rowIsSelected)
    {
        g.fillAll(Colours::orange);
    }
    else
    {
        g.fillAll(Colours::darkgrey);
    }
}

void PlaylistComponent::paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    std::string trackTitle;

    // Use the filtered track list when searching, otherwise use the original list
    if (searchQuery.isEmpty())
    {
        trackTitle = trackTitles[rowNumber];
    }
    else
    {
        if (rowNumber < filteredTrackTitles.size())
        {
            trackTitle = filteredTrackTitles[rowNumber].toStdString();
        }
    }

    g.drawText(trackTitle, 2, 0, width - 4, height, Justification::centredLeft, true);

}


Component* PlaylistComponent::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate)
{
    if (columnId == 2)
    {
        if (existingComponentToUpdate == nullptr)
        {
            TextButton* btn = new TextButton("Add L");
            btn->addListener(this);
            existingComponentToUpdate = btn;

            String id{ std::to_string(rowNumber) };
            btn->setComponentID(id);
        }
    }
    if (columnId == 3)
    {
        if (existingComponentToUpdate == nullptr)
        {
            TextButton* btn = new TextButton("Add R");
            btn->addListener(this);
            existingComponentToUpdate = btn;

            String id{ std::to_string(rowNumber) };
            btn->setComponentID(id);
        }
    }
    if (columnId == 4)
    {
        if (existingComponentToUpdate == nullptr)
        {
            TextButton* btn = new TextButton("X");
            btn->addListener(this);
            existingComponentToUpdate = btn;

            String id{ std::to_string(rowNumber) };
            btn->setComponentID(id);
        }
    }
    return existingComponentToUpdate;
}

void PlaylistComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {}
void PlaylistComponent::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) {}
void PlaylistComponent::releaseResources() {}

void PlaylistComponent::cellClicked(int rowNumber, int columnId, const MouseEvent&)
{
    // Handle cell click event if needed
}

void PlaylistComponent::buttonClicked(Button* button)
{
    if (button == &editButton)
    {
        if (tableComponent.isVisible())
        {
            tableComponent.setVisible(false);
            searchField.setVisible(false);
            editButton.setButtonText("Edit");
        }
        else
        {
            tableComponent.setVisible(true);
            searchField.setVisible(true);
            editButton.setButtonText("Done");
        }

        searchField.clear();
        searchQuery = "";
        tableComponent.updateContent();
    }
    else
    {
        int id = std::stoi(button->getComponentID().toStdString());

        // Check if the ID is within the range of storedFiles
        if (id >= 0 && id < static_cast<int>(storedFiles.size()))
        {
            String filePath = storedFiles[id];

            // Create a File object from the file path
            File audioFile = File(filePath);

            // Convert the file to a URL
            URL audioURL = URL(audioFile);

            // Load the track into the appropriate deck based on which button was clicked
            if (button->getButtonText() == "Add L")
            {
                player1->loadURL(audioURL);
            }
            else if (button->getButtonText() == "Add R")
            {
                player2->loadURL(audioURL);
            }
        }

        // Check if the button label is "X"
        if (button->getButtonText() == "X")
        {
            if (id >= 0 && id < static_cast<int>(trackTitles.size()))
            {
                trackTitles.erase(trackTitles.begin() + id);
                tableComponent.updateContent();
            }
        }
    }
}


bool PlaylistComponent::isInterestedInFileDrag(const StringArray& files)
{
    for (const auto& file : files)
    {
        if (file.containsIgnoreCase(".mp3") || file.containsIgnoreCase(".wav"))
            return true;
    }
    return false;
}

void PlaylistComponent::filesDropped(const StringArray& files, int x, int y)
{
    for (const String& filename : files)
    {
        File file(filename);
        if (file.hasFileExtension(".wav") || file.hasFileExtension(".mp3") || file.hasFileExtension(".flac"))
        {
            String trackName = file.getFileNameWithoutExtension();
            trackTitles.push_back(trackName.toStdString());
            storedFiles.push_back(file.getFullPathName().toStdString());

            DBG("Stored File in filesDropped: " + file.getFullPathName().toStdString());
        }
    }

    tableComponent.updateContent();
}


void PlaylistComponent::textEditorTextChanged(TextEditor& editor)
{
    searchQuery = editor.getText().toStdString();

    filteredTrackTitles.clear();

    for (const std::string& title : trackTitles)
    {
        if (searchQuery.isEmpty() || containsIgnoreCase(title, searchQuery.toStdString()))
        {
            filteredTrackTitles.push_back(title);
        }
    }

    tableComponent.updateContent();
}

bool PlaylistComponent::containsIgnoreCase(const std::string& str, const std::string& searchQuery)
{
    // Convert the strings to iterators
    auto strBegin = str.begin();
    auto strEnd = str.end();
    auto searchBegin = searchQuery.begin();
    auto searchEnd = searchQuery.end();

    // Use std::search with the iterators
    auto it = std::search(
        strBegin, strEnd,
        searchBegin, searchEnd,
        [](char ch1, char ch2) { return std::toupper(ch1) == std::toupper(ch2); }
    );

    return (it != strEnd);
}

//void PlaylistComponent::onTrackLoaded(const String& trackName)
//{
//    trackTitles.push_back(trackName.toStdString());
//    tableComponent.updateContent();
//}

void PlaylistComponent::onTrackLoaded(const String& _trackTitle, const String& _storedFiles)
{
    // Check if the track is already in the table
    if (std::find(trackTitles.begin(), trackTitles.end(), _trackTitle) == trackTitles.end())
    {
        // If the track is not in the table, add it
        trackTitles.push_back(_trackTitle.toStdString());
        storedFiles.push_back(_storedFiles.toStdString());
        tableComponent.updateContent();
    }
}