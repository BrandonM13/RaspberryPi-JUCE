/*
  ==============================================================================

    Battery_Disp.h
    Created: 22 Oct 2021 2:31:20pm
    Author:  Brandon.Munford

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Battery_Disp  : public juce::Component
{
public:
    Battery_Disp();
    ~Battery_Disp() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Battery_Disp)
};
