/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class LOFLevelAudioProcessor
  : public juce::AudioProcessorValueTreeState::Listener,
    public juce::AudioProcessor
    #if JucePlugin_Enable_ARA
     , public juce::AudioProcessorARAExtension
    #endif
{
public:
    juce::AudioProcessorValueTreeState valueTree; // save settings
    float peak;
    
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    void resetPeak();
    float getPeak();
    // all of the buttons and DAW integration already update the valueTree.. This is just so that we can detect changes and cause things to happen when those changes occur.  When we have the events in the onClick on a button, it will only work if the GUI is open..  This will circumvent that issue.
    void parameterChanged(const juce::String& parameterID, float newValue) override;

    LOFLevelAudioProcessor();
    ~LOFLevelAudioProcessor() override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

// UNUSED
//==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LOFLevelAudioProcessor)
};
