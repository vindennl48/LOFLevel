// RotaryKnob.h
#pragma once

#include <JuceHeader.h>

class RotaryKnob : public juce::Slider
{
public:
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment; // must be destructed
    
    RotaryKnob(juce::AudioProcessorValueTreeState& p, juce::String valueTreeName)
    {
        // Defaults
        setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 50);
        setTextValueSuffix(" db");
        
        // Attach to ValueTree
        attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(p, valueTreeName, *this);
    }
    
    ~RotaryKnob()
    {
        attachment.reset();
    }
};
