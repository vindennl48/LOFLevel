// CustomLabel.h
#pragma once

#include <JuceHeader.h>

class BasicLabel : public juce::Label
{
public:
    BasicLabel(juce::String text)
    {
        // Defaults
        setText(text, juce::dontSendNotification);
        setJustificationType(juce::Justification(4|32));    // vert & horiz alignment
        setMinimumHorizontalScale(1.0f);                    // prevent text from squishing
    }
    
    ~BasicLabel(){}
};
