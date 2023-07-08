/*
  ==============================================================================

    Window.h
    Created: 7 Jul 2023 11:17:26pm
    Author:  Mitchell Woodbine

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

/*
 * This should be used as a template. Create a new header for each window.
 */
class Window : public juce::Component
{
public:
    juce::String name = "main";
    
    juce::TextButton btn_test {"Test"};
    
    Window()
    {
        setComponentID(name);
        btn_test.setClickingTogglesState(true);
        addAndMakeVisible(btn_test);
    }
    
    Window(juce::String newName)
    {
        name = newName;
        btn_test.setButtonText("Test2");
        setComponentID(name);
        btn_test.setClickingTogglesState(true);
        addAndMakeVisible(btn_test);
    }
    
//    void paint (juce::Graphics&) override {}

    void resized() override
    {
        if (name == "sub")
            btn_test.setBounds(50, 50, 100, 50);
        else
            btn_test.setBounds(10, 10, 100, 50);
    }
};



#ifdef IGNORE

/*
 * This should be used as a template. Create a new header for each window.
 */
class Window : public juce::Component
{
public:
    juce::String name = "default";
    
    Window(){}
    
    ~Window(){}
    
    void paint (juce::Graphics&) override
    {}

    void resized() override
    {}
};


#endif
