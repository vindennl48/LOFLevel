/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LOFLevelAudioProcessorEditor::LOFLevelAudioProcessorEditor (LOFLevelAudioProcessor& p)
  : AudioProcessorEditor (&p),
    audioProcessor (p),
    gainSlider(p.valueTree, "gain", juce::ImageCache::getFromMemory(BinaryData::GainSlider_png, BinaryData::GainSlider_pngSize)),
    targetSlider(p.valueTree, "target", juce::ImageCache::getFromMemory(BinaryData::TargetSlider_png, BinaryData::TargetSlider_pngSize)),
    thresholdSlider(p.valueTree, "threshold", juce::ImageCache::getFromMemory(BinaryData::ThresholdSlider_png, BinaryData::ThresholdSlider_pngSize)),
    analyzeButton("Analyze", p.valueTree, "analyze"),
    peakLabel("Standby..")
{
    // this will run every time the plugin window opens
    
    startTimer(100.0);  // update frequency for peak label
    
    // custom slider
    
    // GAIN SLIDER
    addAndMakeVisible(gainSlider);
    
//     TARGET SLIDER
    addAndMakeVisible(targetSlider);
    
    // THRESHOLD SLIDER
    addAndMakeVisible(thresholdSlider);
    
    // ANALYZE BUTTON
    addAndMakeVisible(analyzeButton);
    
    // RESET BUTTON
    resetButton.onClick = [&]() { p.resetPeak(); };
    addAndMakeVisible(resetButton);
    
    peakLabel.setFont(juce::Font("Chalkduster", 48.0f, 1));
    peakLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::black);
    addAndMakeVisible(peakLabel);
    
    // WINDOW
    setSize (500, 500);
}

LOFLevelAudioProcessorEditor::~LOFLevelAudioProcessorEditor() {}

void LOFLevelAudioProcessorEditor::timerCallback()
{
    auto currentGain = TOG(gainSlider.getValue());
    auto currentPeak = TOG(audioProcessor.getPeak());
    
    // no audio then dont process
    if (currentPeak <= 0.0f) {
        peakLabel.setText("N/A", juce::dontSendNotification);
        return;
    }
    
    auto dbs = juce::String(TOD(currentPeak * currentGain), 1);
    
    peakLabel.setText(dbs, juce::dontSendNotification);
}

//==============================================================================
void LOFLevelAudioProcessorEditor::paint (juce::Graphics& g)
{
    img_background = juce::ImageCache::getFromMemory(BinaryData::Background_png, BinaryData::Background_pngSize);
//    img_background = juce::ImageCache::getFromMemory(BinaryData::Background_Layout_png, BinaryData::Background_Layout_pngSize);
    g.drawImageWithin(img_background, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);
}

void LOFLevelAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    // set bounds in this function
    
    gainSlider.setBounds(6, 6, 101, 437);
    targetSlider.setBounds(6+113, 6, 101, 437);
    thresholdSlider.setBounds(6+113+113, 6, 101, 437);
    analyzeButton.setBounds(338, 247, 161, 204);
    resetButton.setBounds(344, 118, 149, 44);
    peakLabel.setBounds(344, 30, 149, 44);
}
