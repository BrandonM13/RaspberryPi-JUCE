#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() {
    setSize (800, 800);
    startTimer(16); // 16ms update - very fast for what it's actually doing
}

MainComponent::~MainComponent() { }

//==============================================================================
void MainComponent::paint (juce::Graphics& g) { // THIS METHOD CAN BE MADE WAY MORE EFFICIENT
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
    g.drawText("RPM: " + juce::String(rpm), area.removeFromTop(area.getHeight()/2.f), juce::Justification::centred);
}

void MainComponent::resized() { }

void MainComponent::timerCallback() {
    rpm = (canInterface.data[3] << 8) + canInterface.data[4]; // Pull the data from the canInterface
    needleAng = rpm / 3000.f;

    repaint();
}