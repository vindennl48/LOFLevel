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
    rotary_gain("Gain", p.valueTree, "gain"),
    rotary_target("Target", p.valueTree, "target"),
    rotary_threshold("Threshold", p.valueTree, "threshold"),
    btn_analyze("Analyze", p.valueTree, "analyze"),
    label_btn_reset("Standby..")
{
    // this will run every time the plugin window opens
    
    startTimer(100.0);  // update frequency for peak label
    
    // GAIN SLIDER
    addAndMakeVisible(rotary_gain);
    
    // TARGET SLIDER
    addAndMakeVisible(rotary_target);
    
    // THRESHOLD SLIDER
    addAndMakeVisible(rotary_threshold);
    
    // ANALYZE BUTTON
    addAndMakeVisible(btn_analyze);
    
    // RESET BUTTON
    btn_reset.setClickingTogglesState(false);
    btn_reset.onClick = [&]() { p.resetPeak(); };
    addAndMakeVisible(btn_reset);
    addAndMakeVisible(label_btn_reset);
    
    // WINDOW
    setSize (500, 500);
}

LOFLevelAudioProcessorEditor::~LOFLevelAudioProcessorEditor() {}

void LOFLevelAudioProcessorEditor::timerCallback()
{
    auto currentGain = TOG(rotary_gain.getValue());
    auto currentPeak = TOG(audioProcessor.getPeak());
    
    // no audio then dont process
    if (currentPeak <= 0.0f) {
        label_btn_reset.setText("NO SIGNAL", juce::dontSendNotification);
        return;
    }
    
    auto dbs = TOD(currentPeak * currentGain);
    
    label_btn_reset.setText(S2(dbs, " db peak"), juce::dontSendNotification);
}

//==============================================================================
void LOFLevelAudioProcessorEditor::paint (juce::Graphics& g)
{
    img_background = juce::ImageCache::getFromMemory(BinaryData::Background_png, BinaryData::Background_pngSize);
    g.drawImageWithin(img_background, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);
    
    img_gainSlider = juce::ImageCache::getFromMemory(BinaryData::GainSlider_png, BinaryData::GainSlider_pngSize);
    
    int cutoff = img_gainSlider.getHeight() * 0.75f;
    g.drawImage(img_gainSlider,
                7, 443-cutoff,                          // dest location
                img_gainSlider.getWidth(), cutoff,      // dest size
                0, img_gainSlider.getHeight()-cutoff,   // source location
                img_gainSlider.getWidth(), cutoff,      // source size
                false                                   // use alpha channel
                );
    
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    // g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // g.setColour (juce::Colours::white);
    // g.setFont (24.0f);
    // g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void LOFLevelAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    // set bounds in this function
    
    // GAIN SLIDER
    SET_BOUNDS_FROM_CENTER(rotary_gain,
                           GET_QPOS_X(2, 1),            // pos X
                           GET_QPOS_Y(2, 1),            // pos y
                           PAD(10, GET_QSIZE_X(2)),     // width
                           PAD(10, GET_QSIZE_Y(2))      // height
                           );
    
    // TARGET SLIDER
    SET_BOUNDS_FROM_CENTER(rotary_target,
                           GET_QPOS_X(2, 2),            // pos X
                           GET_QPOS_Y(2, 1),            // pos y
                           PAD(10, GET_QSIZE_X(2)),     // width
                           PAD(10, GET_QSIZE_Y(2))      // height
                           );
    
    // THRESHOLD SLIDER
    SET_BOUNDS_FROM_CENTER(rotary_threshold,
                           GET_QPOS_X(2, 1),            // pos X
                           GET_QPOS_Y(2, 2),            // pos y
                           PAD(10, GET_QSIZE_X(2)),     // width
                           PAD(10, GET_QSIZE_Y(2))      // height
                           );
    
    // ANALYZE BUTTON
    SET_BOUNDS_FROM_CENTER(btn_analyze,                 // component
                           GET_QPOS_X(2, 2),            // pos X
                           GET_QPOS_Y(4, 4),            // pos y
                           PAD(10, GET_QSIZE_X(2)),     // width
                           PAD(10, GET_QSIZE_Y(4))      // height
                           );
    
    // RESET BUTTON
    SET_BOUNDS_FROM_CENTER(btn_reset,                   // component
                           GET_QPOS_X(4, 4),            // pos X
                           GET_QPOS_Y(4, 3),            // pos y
                           PAD(10, GET_QSIZE_X(4)),     // width
                           PAD(10, GET_QSIZE_Y(6))      // height
                           );
    SET_BOUNDS_FROM_CENTER(label_btn_reset,             // component
                           GET_QPOS_X(4, 3),            // pos X
                           GET_QPOS_Y(4, 3),            // pos y
                           PAD(10, GET_QSIZE_X(4)),     // width
                           PAD(10, GET_QSIZE_Y(6))      // height
                           );
}
