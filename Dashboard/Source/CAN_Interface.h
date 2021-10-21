/*
  ==============================================================================

    CAN_Interface.h
    Created: 22 Oct 2021 8:09:06am
    Author:  Brandon.Munford

  ==============================================================================
*/

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

class CAN_Interface : private juce::Thread {
    public:
        CAN_Interface(int id);
        ~CAN_Interface();

        unsigned char* data;

    private:
        int s = socket(PF_CAN, SOCK_RAW, CAN_RAW);
        struct sockaddr_can addr;
        struct ifreq ifr;
        struct can_frame frame;
        
        int id{ 0 };

        bool doLoop{ true };

        bool checkID();
        void readCAN();
        void run() override;
};