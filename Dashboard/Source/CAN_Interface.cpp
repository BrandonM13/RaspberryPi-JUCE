/*
  ==============================================================================

    CAN_Interface.cpp
    Created: 22 Oct 2021 8:09:06am
    Author:  Brandon.Munford

  ==============================================================================
*/

#include "CAN_Interface.h"

CAN_Interface::CAN_Interface(int assignedID) : juce::Thread ("CAN Thread"), id(assignedID) {
    strcpy(ifr.ifr_name, "can0");
    ioctl(s, SIOCGIFINDEX, &ifr);

    memset(&addr, 0, sizeof(addr));
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    bind(s, (struct sockaddr*)&addr, sizeof(addr));

    startThread();
}

CAN_Interface::~CAN_Interface() { stopThread(100); }

void CAN_Interface::run() {
    while (!threadShouldExit()) {
        readCAN();        
        wait(100);
    }
}

bool CAN_Interface::checkID() {
    DBG("" << ((frame.can_id << 1) >> 1));
    return id == ((frame.can_id << 1) >> 1);
}

void CAN_Interface::readCAN() {
    while (true) {
        read(s, &frame, sizeof(struct can_frame));
        if (checkID()) { data = frame.data; }
    }
}