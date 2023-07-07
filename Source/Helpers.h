// Helpers.h

#pragma once

// Conversions ---------------------------------------
#define S(x)                juce::String(x)
#define S2(x1, x2)          S(x1) + S(x2)
#define S3(x1, x2, x3)      S(x1) + S(x2) + S(x3)
#define S4(x1, x2, x3, x4)  S(x1) + S(x2) + S(x3) + S(x4)

#define DBG2(x1, x2)            DBG(S2(x1, x2))
#define DBG3(x1, x2, x3)        DBG(S3(x1, x2, x3))
#define DBG4(x1, x2, x3, x4)    DBG(S4(x1, x2, x3, x4))

#define TOD(x) juce::Decibels::gainToDecibels((x))
#define TOG(x) juce::Decibels::decibelsToGain((x))

#define NORMALIZE(value, min, max)   (((value) - (min)) / ((max) - (min)))
#define DENORMALIZE(value, min, max) ((value) * ((max) - (min)) + (min))

// ValueTree Get/Set ---------------------------------
/*
 * The valueTree stores a normalized variable between 0 and 1, however,
 * we usually want the actual denormalized value.  These macros build in
 * the normalizing and denormalizing.  Except for the raw parameter value..
 * For what ever reason.. THAT command pulls the right value out..  But
 * that one can only be used inside the audio processor block.
 *
 * These macros should ONLY be used in the PluginProcessor class.
 * PluginEditor class should find other ways to communicate with the valueTree.
 */
#define GET(name) DENORMALIZE(valueTree.getParameter(name)->getValue(), valueTree.getParameter(name)->getNormalisableRange().start, valueTree.getParameter(name)->getNormalisableRange().end)
#define GET_DSP(name) valueTree.getRawParameterValue(name)->load()
#define SET(name, x) valueTree.getParameter(name)->setValueNotifyingHost(NORMALIZE((x), valueTree.getParameter(name)->getNormalisableRange().start, valueTree.getParameter(name)->getNormalisableRange().end))

#define SET_QUIET(name, x) valueTree.getParameter(name)->setValue((x))

// Graphics and Interface ----------------------------
#define GET_CENTER(component) (component.getX()+(component.getWidth()/2)), (component.getY()+(component.getHeight()/2))
#define GET_CENTER_X(component) (component.getX()+(component.getWidth()/2))
#define GET_CENTER_Y(component) (component.getY()+(component.getHeight()/2))
#define SET_LOCATION_FROM_CENTER(component, x, y) component.setTopLeftPosition((x)-((w)/2), (y)-((h)/2))
#define SET_SIZE(component, w, h) component.setSize((w), (h))
#define SET_BOUNDS_FROM_CENTER(component, x, y, w, h) component.setBounds((x)-((w)/2), (y)-((h)/2), (w), (h))

// Move our component to a specific quadrant
//                                             init move to center of quad 1   move to quad number (start at 1)
#define GET_QPOS(windowSize, numQuads, quadPos) ( (((windowSize)/(numQuads)/2) + ((windowSize)/(numQuads)) * (quadPos < 1 ? 0 : quadPos-1)) )
#define GET_QPOS_X(numQuads, quadPos) GET_QPOS(getWidth(), numQuads, quadPos)
#define GET_QPOS_Y(numQuads, quadPos) GET_QPOS(getHeight(), numQuads, quadPos)
#define GET_QSIZE(windowSize, numQuads) ((windowSize)/(numQuads))
#define GET_QSIZE_X(numQuads) GET_QSIZE(getWidth(), numQuads)
#define GET_QSIZE_Y(numQuads) GET_QSIZE(getHeight(), numQuads)
#define PAD(pad, size) (size-(pad*2))

// Boilerplate and Examples ==========================
#ifdef IGNORE

/*
 * Parameter Layout Example
 *
 * The numbers 1,2,3,4 represent the order in which they show up in the DAW list for midi mapping
 */
juce::AudioProcessorValueTreeState::ParameterLayout LOFLevelAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    layout.add( std::make_unique<juce::AudioParameterFloat>( juce::ParameterID { "gain",  1 }, "Gain",  -24.0f,  12.0f, 0.0f) );
    layout.add( std::make_unique<juce::AudioParameterFloat>( juce::ParameterID { "target",  2 }, "Target",  -24.0f,  12.0f, 0.0f) );
    layout.add( std::make_unique<juce::AudioParameterFloat>( juce::ParameterID { "threshold",  3 }, "Threshold",  -24.0f,  12.0f, 0.0f) );
    layout.add( std::make_unique<juce::AudioParameterBool>( juce::ParameterID { "analyze", 4 }, "Analyze", false ) );
    return layout;
}

#endif
