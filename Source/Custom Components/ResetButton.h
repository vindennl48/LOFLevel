// ResetButton.h
#pragma once

#include <JuceHeader.h>

class ResetButton : public juce::Button
{
public:
    ResetButton() : juce::Button("reset")
    {
        // Defaults
        setClickingTogglesState(false);
        
        // Custom Action
        // onClick = [&]() {};
    }
    
    ~ResetButton()
    {
    }
    
    // handles coloring and setting the text of the button to the correct state
    void paintButton (juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
    {
        if (shouldDrawButtonAsDown)
        {
            // show analyze highlight
            juce::Image image = juce::ImageCache::getFromMemory(BinaryData::reset_down_png, BinaryData::reset_down_pngSize);
            g.drawImage(image,
                        0, 0,                                   // dest location
                        getWidth(), getHeight(),                // dest size
                        0, 0,                                   // source location
                        image.getWidth(), image.getHeight(),    // source size
                        false                                   // use alpha channel
                        );
        }
        else if (shouldDrawButtonAsHighlighted)
        {
            // show analyzing non-highlight
            juce::Image image = juce::ImageCache::getFromMemory(BinaryData::reset_hover_png, BinaryData::reset_hover_pngSize);
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
            juce::Image image = juce::ImageCache::getFromMemory(BinaryData::reset_off_png, BinaryData::reset_off_pngSize);
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
