/*
  ==============================================================================

    RPM_Dial.cpp
    Created: 22 Oct 2021 2:30:22pm
    Author:  Brandon.Munford

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Dial.h"

//==============================================================================
Dial::Dial(juce::String _name, float _maxValue) : name(_name), maxValue(_maxValue){ }

Dial::~Dial() { }

void Dial::setValue(float _value) {
    currentValue = _value;
    needlePos = currentValue / maxValue;
    repaint();
}

void Dial::paint (juce::Graphics& g){
    auto area      = getLocalBounds().toFloat().reduced(10.f);
    float width    = area.getWidth();
    float height   = area.getHeight();
    float width_2  = width / 2.f;
    float height_2 = height / 2.f;

    juce::Path dial, needle;

    dial.addArc(area.getX(), area.getY(), width, height, 3.f * juce::float_Pi / 2.f, 5.f * juce::float_Pi / 2.f, true);

    juce::ColourGradient gradient = juce::ColourGradient(juce::Colours::green, juce::Point<float>(area.getX(), height_2), juce::Colours::red, juce::Point<float>(width, height_2), false);
    gradient.addColour(0.5, juce::Colours::yellow);

    g.setGradientFill(gradient);
    g.strokePath(dial, juce::PathStrokeType(10.f));

    juce::Rectangle<float> needleRect(width_2, height_2, 1.f, height_2);
    juce::AffineTransform rotation = juce::AffineTransform::rotation((needlePos * juce::float_Pi) + (juce::float_Pi / 2.f), width_2, height_2);

    needle.addRectangle(needleRect);
    g.setColour(juce::Colours::white);
    g.fillPath(needle, rotation);

    g.setColour(juce::Colours::lightgrey);
    g.setFont(70.f);
    g.drawText(name + ": " + juce::String(currentValue), area.removeFromTop(height_2), juce::Justification::centred);
}

void Dial::resized() { }
