/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Helpers.h"

//==============================================================================
LOFLevelAudioProcessor::LOFLevelAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor (
        BusesProperties()
        #if ! JucePlugin_IsMidiEffect
          #if ! JucePlugin_IsSynth
            .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
          #endif
            .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
        #endif
    ),
    valueTree (
        *this, nullptr,
        "Parameters",
        createParameterLayout()
    ),
    peak(0.0f)
#endif
{
    valueTree.state = juce::ValueTree("MyAudioProcessor");
    valueTree.addParameterListener("analyze", this);
}

LOFLevelAudioProcessor::~LOFLevelAudioProcessor()
{
    valueTree.removeParameterListener("analyze", this);
}

// Create the parameter layout
juce::AudioProcessorValueTreeState::ParameterLayout LOFLevelAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    layout.add( std::make_unique<juce::AudioParameterFloat>( juce::ParameterID { "gain",  1 }, "Gain",  -24.0f,  12.0f, 0.0f) );
    layout.add( std::make_unique<juce::AudioParameterFloat>( juce::ParameterID { "target",  2 }, "Target",  -24.0f,  12.0f, 0.0f) );
    layout.add( std::make_unique<juce::AudioParameterFloat>( juce::ParameterID { "threshold",  3 }, "Threshold",  -24.0f,  12.0f, 0.0f) );
    layout.add( std::make_unique<juce::AudioParameterBool>( juce::ParameterID { "analyze", 4 }, "Analyze", false ) );
    return layout;
}

void LOFLevelAudioProcessor::parameterChanged(const juce::String& parameterID, float newValue) {
  if (parameterID == "analyze") {
      if ((bool)newValue) {
          resetPeak();
      } else {
          float peak_db = getPeak();
          if (peak_db > -100.0f) {
              // failsafe in case there is no audio above threshold
              auto slider_target = GET("target");
//              DBG2("Slider Target: ", slider_target);
//              DBG2("peak_db: ", peak_db);
              SET("gain", slider_target - peak_db);
          }
      }
  }
}

void LOFLevelAudioProcessor::resetPeak() { peak = 0.0f; };

float LOFLevelAudioProcessor::getPeak() { return TOD(peak); };

void LOFLevelAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    // grab raw volume value
//    float rawVolume = juce::Decibels::decibelsToGain(valueTree.getRawParameterValue("gain")->load());
    float rawVolume = TOG(GET_DSP("gain"));
    
    // grab threshold amount
//    float threshold = juce::Decibels::decibelsToGain(valueTree.getRawParameterValue("threshold")->load());
    float threshold = TOG(GET_DSP("threshold"));

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the stat e if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
        
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample )
        {
            // get peak value
            auto s = std::abs(buffer.getSample(channel, sample));
            if (s > threshold && s > peak) peak = s;
//            DBG2("peak: ", peak);
            
            channelData[sample] = buffer.getSample(channel, sample) * rawVolume;
        }
    }
}

//==============================================================================
void LOFLevelAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
  // You should use this method to store your parameters in the memory block.
  // You could do that either as raw data, or use the XML or ValueTree classes
  // as intermediaries to make it easy to save and load complex data.

  // Write the state of the AudioProcessorValueTreeState to a memory stream
  juce::MemoryOutputStream stream(destData, true);
  valueTree.state.writeToStream(stream);
}

void LOFLevelAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
  // You should use this method to restore your parameters from this memory block,
  // whose contents will have been created by the getStateInformation() call.

  // Read the state from the data and replace the AudioProcessorValueTreeState state
  auto tree = juce::ValueTree::readFromData(data, size_t(sizeInBytes));
  if (tree.isValid()) {
      valueTree.replaceState(tree);
      SET("analyze", false);  // make sure analyze button always starts off false
  }
}
