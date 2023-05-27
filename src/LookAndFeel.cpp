#include "LookAndFeel.hpp"

CustomLookAndFeel::CustomLookAndFeel()
{
    setColourScheme(getGreyColourScheme());
    getCurrentColourScheme().setUIColour(ColourScheme::widgetBackground, juce::Colours::black);
    setColour(juce::ComboBox::backgroundColourId, juce::Colours::red);
    setColour(juce::DocumentWindow::backgroundColourId, juce::Colours::black);
    setColour(juce::ComboBox::backgroundColourId, juce::Colours::black);
    setColour(juce::TextEditor::backgroundColourId, juce::Colours::black);
    setColour(juce::ResizableWindow::backgroundColourId, juce::Colours::black);
}

DarkLookAndFeel::DarkLookAndFeel() { setColourScheme(getGreyColourScheme()); }

LightLookAndFeel::LightLookAndFeel() { setColourScheme(getLightColourScheme()); }
