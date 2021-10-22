/*
  ==============================================================================

    RPM_Dial.h
    Created: 22 Oct 2021 2:30:22pm
    Author:  Brandon.Munford

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Dial  : public juce::Component {
    public:
        Dial(juce::String _name, float _maxValue);
        ~Dial() override;

        void setValue(float _value);

        void paint (juce::Graphics&) override;
        void resized() override;

    private:
        juce::String name{ "" };
        float currentValue{ 0 };
        float maxValue{ 0 };

        float needlePos{ 0 };

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Dial)
};
