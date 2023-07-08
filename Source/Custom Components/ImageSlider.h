// ImageSlider.h
#pragma once

#include <JuceHeader.h>
#include "../Helpers.h"

class AddImageToSlider : public juce::LookAndFeel_v4
{
public:
    juce::Image image;
    
    AddImageToSlider(juce::Image newImage)
      : image(newImage)
    {}
    
    void drawLinearSlider (Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle, Slider &slider) override
    {
//        int cutoff = height * 0.75f;
        int cutoff = height * NORMALIZE(sliderPos, minSliderPos, maxSliderPos);
        g.drawImage(img_gainSlider,
                    x, (y+height)-cutoff,   // dest location
                    width, cutoff,          // dest size
                    0, height-cutoff,       // source location
                    width, cutoff,          // source size
                    false                   // use alpha channel
                    );
    }
};

class ImageSlider : public juce::Slider
{
public:
    AddImageToSlider addImageToSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment; // must be destructed
    
    ImageSlider(juce::AudioProcessorValueTreeState& p, juce::String valueTreeName, juce::Image newImage)
      : addImageToSlider(newImage)
    {
        // Defaults
//        setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        setLookAndFeel(addImageToSlider);
        setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
        
        // TextBox - add one later
        setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        // setTextValueSuffix(" db");
        
        // Attach to ValueTree
        attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(p, valueTreeName, *this);
    }
    
    ~ImageSlider()
    {
        attachment.reset();
    }
    
    
//    void resized() override {}
};
