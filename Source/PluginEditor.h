/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Helpers.h"
#include "Basic Components/RotaryKnob.h"
#include "BasicLabel.h"
#include "Custom Components/AnalyzeButton.h"
#include "Custom Components/ImageSlider.h"

//==============================================================================
/**
*/
class LOFLevelAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Timer
{
public:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    LOFLevelAudioProcessor& audioProcessor;
//    ToggleButton btn_analyze;
    void timerCallback() final;

    LOFLevelAudioProcessorEditor (LOFLevelAudioProcessor&);
    ~LOFLevelAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Image img_background;
    ImageSlider gainSlider;
    ImageSlider targetSlider;
    ImageSlider thresholdSlider;
    
    RotaryKnob rotary_gain;
    
    RotaryKnob rotary_target;
    
    RotaryKnob rotary_threshold;
    
    AnalyzeButton btn_analyze;
    
    juce::TextButton btn_reset {"Reset"};
    BasicLabel label_btn_reset;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LOFLevelAudioProcessorEditor)
};
