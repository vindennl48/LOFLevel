// AnalyzeButton.h
#pragma once

#include <JuceHeader.h>

class AnalyzeButton : public juce::TextButton
{
public:
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> attachment; // must be destructed
    
    AnalyzeButton(juce::String name, juce::AudioProcessorValueTreeState& p, juce::String valueTreeName)
        : juce::TextButton(name)
    {
        // Defaults
        setClickingTogglesState(true);
        
        // Attach to ValueTree
        attachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(p, valueTreeName, *this);
        
        // Custom Action
        // onClick = [&]() {};
    }
    
    ~AnalyzeButton()
    {
        attachment.reset();
    }
    
    // handles coloring and setting the text of the button to the correct state
    void paintButton (juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
    {
        setButtonText("");
        
        if (getToggleState() && !shouldDrawButtonAsHighlighted)
        {
            // show processing non-highlight
            juce::Image image = juce::ImageCache::getFromMemory(BinaryData::ProcessingButton_on_png, BinaryData::ProcessingButton_on_pngSize);
            g.drawImage(image,
                        0, 0,                                   // dest location
                        getWidth(), getHeight(),                // dest size
                        0, 0,                                   // source location
                        image.getWidth(), image.getHeight(),    // source size
                        false                                   // use alpha channel
                        );
        }
        else if (getToggleState() && shouldDrawButtonAsHighlighted)
        {
            // show processing and highight image
            juce::Image image = juce::ImageCache::getFromMemory(BinaryData::ProcessingButton_on_hover_png, BinaryData::ProcessingButton_on_hover_pngSize);
            g.drawImage(image,
                        0, 0,                                   // dest location
                        getWidth(), getHeight(),                // dest size
                        0, 0,                                   // source location
                        image.getWidth(), image.getHeight(),    // source size
                        false                                   // use alpha channel
                        );
        }
        else if (!getToggleState() && shouldDrawButtonAsHighlighted)
        {
            // show analyze highlight
            juce::Image image = juce::ImageCache::getFromMemory(BinaryData::AnalyzeButton_hover_png, BinaryData::AnalyzeButton_hover_pngSize);
            g.drawImage(image,
                        0, 0,                                   // dest location
                        getWidth(), getHeight(),                // dest size
                        0, 0,                                   // source location
                        image.getWidth(), image.getHeight(),    // source size
                        false                                   // use alpha channel
                        );
        }
        else
        {
            // show analyzing non-highlight
            juce::Image image = juce::ImageCache::getFromMemory(BinaryData::AnalyzeButton_off_png, BinaryData::AnalyzeButton_off_pngSize);
            g.drawImage(image,
                        0, 0,                                   // dest location
                        getWidth(), getHeight(),                // dest size
                        0, 0,                                   // source location
                        image.getWidth(), image.getHeight(),    // source size
                        false                                   // use alpha channel
                        );
        }
    }
};
