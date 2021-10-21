#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() {
    strcpy(ifr.ifr_name, "can0");
    ioctl(s, SIOCGIFINDEX, &ifr);

    memset(&addr, 0, sizeof(addr));
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    
    bind(s, (struct sockaddr*)&addr, sizeof(addr));

    setSize (600, 600);
    startTimerHz(60);
}

MainComponent::~MainComponent() { }

//==============================================================================
void MainComponent::paint (juce::Graphics& g) {
    g.fillAll (juce::Colours::black);
    
    auto area = getLocalBounds().toFloat().reduced(10.f);

    juce::Path dial, needle;
    dial.addArc(area.getX(), area.getY(), area.getWidth(), area.getHeight(), 3.f*juce::float_Pi/2.f, 5.f*juce::float_Pi/2.f, true);

    juce::ColourGradient gradient = juce::ColourGradient(juce::Colours::green, juce::Point<float>(area.getX(), area.getHeight()/2.f), juce::Colours::red, juce::Point<float>(area.getWidth(), area.getHeight()/2.f), false);
    gradient.addColour(0.5, juce::Colours::yellow);

    g.setGradientFill(gradient);
    g.strokePath(dial, juce::PathStrokeType(10.f));
    
    juce::Rectangle<float> needleRect(area.getWidth() / 2.f, area.getHeight() / 2.f, 1.f, 285.f);
    juce::AffineTransform rotation = juce::AffineTransform::rotation((needleAng * juce::float_Pi) + (juce::float_Pi / 2.f), area.getWidth() / 2.f, (area.getHeight() / 2.f) + 0.5);

    needle.addRectangle(needleRect);
    g.setColour(juce::Colours::white);
    g.fillPath(needle, rotation);

    g.setColour(juce::Colours::lightgrey);
    g.setFont(70.f);
    g.drawText("RPM", area.removeFromTop(area.getHeight()/2.f), juce::Justification::centred);

}

void MainComponent::resized() { }

void MainComponent::timerCallback() {
    read(s, &frame, sizeof(struct can_frame));

    int id = (frame.can_id << 1) >> 1; // chops the MSB off    
    if (id != 301072640) { return; }
    int rpm = (frame.data[3] << 8) + frame.data[4];
    if (!rpm) { return; }

    needleAng = rpm / 3000; // To get val between 0 and 1

    repaint();
}