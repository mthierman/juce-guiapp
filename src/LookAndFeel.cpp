#include "LookAndFeel.hpp"

LookAndFeel::LookAndFeel() {}

void LookAndFeel::SetColours()
{
    setColour(juce::DocumentWindow::textColourId,
              getCurrentColourScheme().getUIColour(ColourScheme::defaultText));

    setColour(juce::ResizableWindow::backgroundColourId,
              getCurrentColourScheme().getUIColour(ColourScheme::windowBackground));

    setColour(juce::ComboBox::backgroundColourId,
              getCurrentColourScheme().getUIColour(ColourScheme::menuBackground));
    setColour(juce::ComboBox::textColourId,
              getCurrentColourScheme().getUIColour(ColourScheme::menuText));
    setColour(juce::ComboBox::arrowColourId,
              getCurrentColourScheme().getUIColour(ColourScheme::outline));
    setColour(juce::ComboBox::outlineColourId,
              getCurrentColourScheme().getUIColour(ColourScheme::outline));
    setColour(juce::ComboBox::focusedOutlineColourId,
              getCurrentColourScheme().getUIColour(ColourScheme::highlightedText));
    setColour(juce::ComboBox::buttonColourId,
              getCurrentColourScheme().getUIColour(ColourScheme::highlightedText));

    setColour(juce::PopupMenu::backgroundColourId,
              getCurrentColourScheme().getUIColour(ColourScheme::menuBackground));

    setColour(juce::TextEditor::backgroundColourId,
              getCurrentColourScheme().getUIColour(ColourScheme::menuBackground));
    setColour(juce::TextEditor::textColourId,
              getCurrentColourScheme().getUIColour(ColourScheme::menuText));
    setColour(juce::TextEditor::outlineColourId,
              getCurrentColourScheme().getUIColour(ColourScheme::menuBackground));
    setColour(juce::TextEditor::focusedOutlineColourId,
              getCurrentColourScheme().getUIColour(ColourScheme::menuBackground));
}

CustomTheme::CustomTheme()
{
    setColourScheme(getGreyColourScheme());
    getCurrentColourScheme().setUIColour(ColourScheme::windowBackground, juce::Colours::darkblue);
    getCurrentColourScheme().setUIColour(ColourScheme::widgetBackground, juce::Colours::darkblue);
    getCurrentColourScheme().setUIColour(ColourScheme::menuBackground, juce::Colours::darkblue);
    getCurrentColourScheme().setUIColour(ColourScheme::outline, juce::Colours::white);
    getCurrentColourScheme().setUIColour(ColourScheme::defaultText, juce::Colours::white);
    getCurrentColourScheme().setUIColour(ColourScheme::defaultFill, juce::Colours::blue);
    getCurrentColourScheme().setUIColour(ColourScheme::highlightedText, juce::Colours::lightblue);
    getCurrentColourScheme().setUIColour(ColourScheme::highlightedFill, juce::Colours::lightblue);
    getCurrentColourScheme().setUIColour(ColourScheme::menuText, juce::Colours::white);
    SetColours();
}

juce::Font CustomTheme::getComboBoxFont(juce::ComboBox& comboBox)
{
    return juce::Font("Segoe UI Variable", 20.0f, juce::Font::italic);
}

DarkTheme::DarkTheme()
{
    setColourScheme(getDarkColourScheme());
    getCurrentColourScheme().setUIColour(ColourScheme::windowBackground, juce::Colours::black);
    getCurrentColourScheme().setUIColour(ColourScheme::widgetBackground, juce::Colours::black);
    getCurrentColourScheme().setUIColour(ColourScheme::menuBackground, juce::Colours::black);
    getCurrentColourScheme().setUIColour(ColourScheme::outline, juce::Colours::white);
    getCurrentColourScheme().setUIColour(ColourScheme::defaultText, juce::Colours::white);
    getCurrentColourScheme().setUIColour(ColourScheme::defaultFill, juce::Colours::black);
    getCurrentColourScheme().setUIColour(ColourScheme::highlightedText, juce::Colours::lightblue);
    getCurrentColourScheme().setUIColour(ColourScheme::highlightedFill, juce::Colours::lightblue);
    getCurrentColourScheme().setUIColour(ColourScheme::menuText, juce::Colours::white);
    SetColours();
}

juce::Font DarkTheme::getComboBoxFont(juce::ComboBox& comboBox)
{
    return juce::Font("Segoe UI Variable", 20.0f, juce::Font::italic);
}

LightTheme::LightTheme()
{
    setColourScheme(getLightColourScheme());
    getCurrentColourScheme().setUIColour(ColourScheme::windowBackground, juce::Colours::white);
    getCurrentColourScheme().setUIColour(ColourScheme::widgetBackground, juce::Colours::white);
    getCurrentColourScheme().setUIColour(ColourScheme::menuBackground, juce::Colours::white);
    getCurrentColourScheme().setUIColour(ColourScheme::outline, juce::Colours::black);
    getCurrentColourScheme().setUIColour(ColourScheme::defaultText, juce::Colours::black);
    getCurrentColourScheme().setUIColour(ColourScheme::defaultFill, juce::Colours::white);
    getCurrentColourScheme().setUIColour(ColourScheme::highlightedText, juce::Colours::lightblue);
    getCurrentColourScheme().setUIColour(ColourScheme::highlightedFill, juce::Colours::lightblue);
    getCurrentColourScheme().setUIColour(ColourScheme::menuText, juce::Colours::black);
    SetColours();
}

juce::Font LightTheme::getComboBoxFont(juce::ComboBox& comboBox)
{
    return juce::Font("Segoe UI Variable", 20.0f, juce::Font::italic);
}
