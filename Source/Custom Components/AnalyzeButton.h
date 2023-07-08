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
    void paintButton (juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override {
      auto& lf = getLookAndFeel();

      if (getToggleState()) {
        lf.drawButtonBackground (
          g,
          *this,
          juce::Colours::red,
          shouldDrawButtonAsHighlighted,
          shouldDrawButtonAsDown
        );
        setButtonText("Processing..");
      } else {
        lf.drawButtonBackground (
          g,
          *this,
          findColour (getToggleState() ? buttonOnColourId : buttonColourId),
          shouldDrawButtonAsHighlighted,
          shouldDrawButtonAsDown
        );
        setButtonText("Analyze");
      }
      lf.drawButtonText (g, *this, shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);
    }
};
