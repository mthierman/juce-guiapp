#include "Theme.hpp"

ThemeSwitcher::ThemeSwitcher()
{
    addAndMakeVisible(mode);
    mode.addSectionHeading("Mode");
    mode.addItem("Dark", 1);
    mode.addItem("Light", 2);
    mode.addItem("Grey", 3);
    mode.addItem("Midnight", 4);
    mode.addItem("System", 5);
    mode.onChange = [this] { modeChange(); };
    mode.setSelectedId(System);
}

void ThemeSwitcher::resized() { mode.setBounds(0, 0, getWidth(), getHeight()); }

void ThemeSwitcher::modeChange()
{
    auto dark = juce::Desktop::getInstance().isDarkModeActive();
    switch (mode.getSelectedId())
    {
    case Dark:
        juce::Desktop::getInstance().setDefaultLookAndFeel(&darkTheme);
        break;
    case Light:
        juce::Desktop::getInstance().setDefaultLookAndFeel(&lightTheme);
        break;
    case Grey:
        juce::Desktop::getInstance().setDefaultLookAndFeel(&greyTheme);
        break;
    case Midnight:
        juce::Desktop::getInstance().setDefaultLookAndFeel(&midnightTheme);
        break;
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
    default:
        break;
    }
    repaint();
}
