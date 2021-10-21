#pragma once

#include <JuceHeader.h>
#include "CAN_Interface.h"

class MainComponent  : public juce::Component, public juce::Timer {
    public:
        //==============================================================================
        MainComponent();
        ~MainComponent() override;

        //==============================================================================
        void paint (juce::Graphics&) override;
        void resized() override;
        void timerCallback();

    private:
        int rpm = 0;
        float needleAng = 0.f;

        CAN_Interface canInterface{ 301072640 };

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
