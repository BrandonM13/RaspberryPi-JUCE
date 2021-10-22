#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() {
    addAndMakeVisible(rpm_dial);
    addAndMakeVisible(minCellVolt_dial);
    addAndMakeVisible(slider);

    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);

    setSize (800, 800);
    startTimerHz(60); // 60fps - very fast for what it's actually doing
}

MainComponent::~MainComponent() { }

void MainComponent::paint(juce::Graphics& g) { g.fillAll(juce::Colours::black); } // Background

void MainComponent::resized() { // temp positioning function
    auto area = getLocalBounds();
    auto leftSide = area.removeFromLeft(area.getWidth() / 2);

    slider.setBounds(leftSide.reduced(20));

    rpm_dial.setBounds(area.removeFromBottom(area.getHeight() / 2));
    minCellVolt_dial.setBounds(area);
}

void MainComponent::timerCallback() {
    int rpm = (rpmInterface.data[3] << 8) + rpmInterface.data[4]; // Pull the data from the canInterface
    if (rpm) { rpm_dial.setValue(rpm); }

    int volt = (minCellVoltInterface.data[2] << 8) + minCellVoltInterface.data[1];
    if (volt) { minCellVolt_dial.setValue(volt / 1000.f); }
}