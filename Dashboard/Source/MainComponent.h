#pragma once

#include <JuceHeader.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

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
        float needleAng = 0.f;

        int s;
        struct sockaddr_can addr;
        struct ifreq ifr;
        struct can_frame frame;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
