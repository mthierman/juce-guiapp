#include "Theme.hpp"

ThemeSwitcher::ThemeSwitcher()
{
    addAndMakeVisible(mode);
    mode.addSectionHeading("Mode");
    mode.addItem("System", 1);
    mode.addItem("Dark", 2);
    mode.addItem("Light", 3);
    mode.addItem("Custom", 4);
    mode.onChange = [this] { modeChange(); };
    mode.setSelectedId(System);
}

void ThemeSwitcher::resized() { mode.setBounds(0, 0, getWidth(), getHeight()); }

void ThemeSwitcher::modeChange()
{
    auto dark = juce::Desktop::getInstance().isDarkModeActive();
    switch (mode.getSelectedId())
    {
    case System:
        if (dark)
        {
            juce::Desktop::getInstance().setDefaultLookAndFeel(&darkTheme);
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
    case Custom:
        juce::Desktop::getInstance().setDefaultLookAndFeel(&customTheme);
        break;
    default:
        break;
    }
    repaint();
}
