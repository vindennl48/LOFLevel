// RotaryKnob.h
#pragma once

#include <JuceHeader.h>
#include "BasicLabel.h"

class RotaryKnob : public juce::Slider
{
public:
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment; // must be destructed
    BasicLabel label;
    
    RotaryKnob(juce::String name, juce::AudioProcessorValueTreeState& p, juce::String valueTreeName)
    : label(name)
    {
        // Defaults
        setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 50);
        setTextValueSuffix(" db");
        
        // Attach to ValueTree
        attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(p, valueTreeName, *this);
        
        // Label
        addAndMakeVisible(label);
    }
    
    ~RotaryKnob()
    {
        attachment.reset();
    }
    
    
    void resized() override
    {
        juce::Slider::resized();
        SET_BOUNDS_FROM_CENTER(label,                                                   // component
                               getWidth() / 2,                                          // pos x
                               getHeight() / 2.5f,                                      // pos y
                               label.getFont().getStringWidth(label.getText()) + 10,    // width; not sure why but this is always too small
                               label.getFont().getHeight()                              // height
                               );
    }
};
