/*
  ==============================================================================

    Battery_Disp.cpp
    Created: 22 Oct 2021 2:31:20pm
    Author:  Brandon.Munford

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Battery_Disp.h"

//==============================================================================
Battery_Disp::Battery_Disp()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

Battery_Disp::~Battery_Disp()
{
}

void Battery_Disp::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("Battery_Disp", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void Battery_Disp::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
