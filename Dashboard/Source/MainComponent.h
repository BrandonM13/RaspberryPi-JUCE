#pragma once

#include <JuceHeader.h>
#include "CAN_Interface.h"
#include "Dial.h"

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
        Dial rpm_dial{ "RPM", 3000.f };
        CAN_Interface rpmInterface{ 301072640 };

        Dial minCellVolt_dial{ "Min Cell Voltage", 5.f};
        CAN_Interface minCellVoltInterface{ 301077504 };

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
