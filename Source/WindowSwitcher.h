/*
  ==============================================================================

    WindowSwitcher.h
    Created: 7 Jul 2023 11:17:17pm
    Author:  Mitchell Woodbine

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Window.h"

class WindowSwitcher : public juce::Component
{
public:
//    std::vector<Window> windows;
    juce::String activeWindow = "none";
    Window mainWindow;
    Window subWindow;
    
    WindowSwitcher() : subWindow("sub")
    {
        addChildComponent(mainWindow);
        addChildComponent(subWindow);
    }
    // findChildWithID()
    ~WindowSwitcher() {}
    
    void switchTo(juce::String name)
    {
        activeWindow = "none";
        auto children = getChildren();
        for(int i=0; i<children.size(); i++) {
            if (juce::String(children[i]->getComponentID()) == name) {
                children[i]->setVisible(true);
                activeWindow = name;
            } else {
                children[i]->setVisible(false);
            }
        }
    }
    
//    void paint (juce::Graphics&) override {}

    void resized() override
    {
        mainWindow.setBounds(0, 0, getWidth(), getHeight());
        subWindow.setBounds(0, 0, getWidth(), getHeight());
    }
};
