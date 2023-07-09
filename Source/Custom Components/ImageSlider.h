// ImageSlider.h
#pragma once

#include <JuceHeader.h>
#include "../Helpers.h"

class AddImageToSlider : public juce::LookAndFeel_V4
{
public:
    juce::Image image;
    
    AddImageToSlider(juce::Image newImage)
      : image(newImage)
    {}
    
    void drawLinearSlider (juce::Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle ss, juce::Slider &slider) override
    {
        int cutoff = height - (sliderPos - 1);
        
        g.drawImage(image,
                    x, (y+height)-cutoff,       // dest location
                    width, cutoff,              // dest size
                    0, height-cutoff,           // source location
                    image.getWidth(), cutoff,   // source size
                    false                       // use alpha channel
                    );
        
        g.setColour (juce::Colours::antiquewhite);
        g.setFont(juce::Font("Chalkduster", 20.0f, 0));
        g.drawFittedText(S2(juce::String(slider.getValue(), 1), " db"), 0, height-25, width, 25, juce::Justification::centred, 1);
        
        // NOTE: I made changes in the juce_Slider.cpp file to remove the borders for both the Slider
        //  component and the label that is inside the Slider component.  This gives a seamless
        //  transition between the slider and the background image.
        //  If you search for 'CHANGEDHERE' in juce_Slider.cpp, you can find the changes.
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
        setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
        setLookAndFeel(&addImageToSlider);
        
        // TextBox - add one later
//        setTextBoxStyle(juce::Slider::NoTextBox, false, 113, 50);
        setTextBoxStyle(juce::Slider::TextBoxBelow, false, 113, 50);
        setTextValueSuffix(" db");
        
        // Attach to ValueTree
        attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(p, valueTreeName, *this);
        
        // Made this change in the juce_Slider.cpp file to make the label text opaque.  this still lets us open the
        //  text editor box to type in values but hides the text.
//        juce::Slider->valueBox->setColour(juce::Label::textColourId, juce::Colours::transparentBlack);
    }
    
    ~ImageSlider()
    {
        attachment.reset();
        setLookAndFeel(nullptr);
    }
    
    void mouseDoubleClick(const juce::MouseEvent& event) override
    {
        DBG("DBLCLICK");
        showTextBox();
    }
    
    
//    void resized() override {}
};
