/*
  ==============================================================================

    CAN_Interface.cpp
    Created: 22 Oct 2021 8:09:06am
    Author:  Brandon.Munford

  ==============================================================================
*/

#include "CAN_Interface.h"

CAN_Interface::CAN_Interface() : juce::Thread ("CAN Thread") {
    strcpy(ifr.ifr_name, "can0");
    ioctl(s, SIOCGIFINDEX, &ifr);

    memset(&addr, 0, sizeof(addr));
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    bind(s, (struct sockaddr*)&addr, sizeof(addr));

    startThread();
}

CAN_Interface::~CAN_Interface() { }

void CAN_Interface::run() {
    while (!threadShouldExit()) {
        readCAN();        
        wait(250);
    }
}

int CAN_Interface::getId() { return (frame.can_id << 1) >> 1; }
int CAN_Interface::readData(int idx) {
    
    return (frame.data[idx] << 8) + frame.data[idx + 1];

    //return frame.data[idx];

}

void CAN_Interface::readCAN() { read(s, &frame, sizeof(struct can_frame)); }