#include "Theme.hpp"

ThemeSwitcher::ThemeSwitcher()
{
    addAndMakeVisible(mode);
    mode.addSectionHeading("Mode");
    mode.addItem("Custom", 1);
    mode.addItem("System", 2);
    mode.addItem("Dark", 3);
    mode.addItem("Light", 4);
    mode.onChange = [this] { modeChange(); };
    mode.setSelectedId(System);
}

void ThemeSwitcher::paint(juce::Graphics &g)
{
    g.fillAll(findColour(juce::ComboBox::backgroundColourId));
}

void ThemeSwitcher::resized() { mode.setBounds(0, 0, getWidth(), getHeight()); }

void ThemeSwitcher::modeChange()
{
    auto dark = juce::Desktop::getInstance().isDarkModeActive();
    switch (mode.getSelectedId())
    {
    case Custom:
        juce::Desktop::getInstance().setDefaultLookAndFeel(&customTheme);
        break;
    case System:
        if (dark)
        {
            juce::Desktop::getInstance().setDefaultLookAndFeel(&lightTheme);
        }
        if (!dark)
        {
            juce::Desktop::getInstance().setDefaultLookAndFeel(&lightTheme);
        }
        break;
    case Dark:
        juce::Desktop::getInstance().setDefaultLookAndFeel(&darkTheme);
        break;
    case Light:
        juce::Desktop::getInstance().setDefaultLookAndFeel(&lightTheme);
        break;
    default:
        break;
    }
    repaint();
}
