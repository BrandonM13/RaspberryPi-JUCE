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
class RPM_Dial  : public juce::Component {
    public:
        RPM_Dial();
        ~RPM_Dial() override;

        void paint (juce::Graphics&) override;
        void resized() override;
        void setRPM(int _rpm);

    private:
        int rpm{ 0 };
        float needleAng{ 0 };
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RPM_Dial)
};
