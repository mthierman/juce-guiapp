#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>

class ThemeSwitcher : public juce::Component
{
  public:
    ThemeSwitcher()
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

    void modeChange()
    {
        auto dark = juce::Desktop::getInstance().isDarkModeActive();
        switch (mode.getSelectedId())
        {
        case Dark:
            setDarkTheme();
            break;
        case Light:
            setLightTheme();
            break;
        case Grey:
            setGreyTheme();
            break;
        case Midnight:
            setMidnightTheme();
            break;
        case System:
            if (dark)
            {
                setDarkTheme();
            }
            if (!dark)
            {
                setLightTheme();
            }
            break;
        default:
            break;
        }
        repaint();
    }

    void setDarkTheme() { juce::Desktop::getInstance().setDefaultLookAndFeel(&darkTheme); }

    void setLightTheme() { juce::Desktop::getInstance().setDefaultLookAndFeel(&lightTheme); }

    void setGreyTheme() { juce::Desktop::getInstance().setDefaultLookAndFeel(&greyTheme); }

    void setMidnightTheme() { juce::Desktop::getInstance().setDefaultLookAndFeel(&midnightTheme); }

  private:
    juce::ComboBox mode;
    enum Mode
    {
        Dark = 1,
        Light,
        Grey,
        Midnight,
        System
    };
    juce::LookAndFeel_V4 darkTheme = juce::LookAndFeel_V4::getDarkColourScheme();
    juce::LookAndFeel_V4 lightTheme = juce::LookAndFeel_V4::getLightColourScheme();
    juce::LookAndFeel_V4 greyTheme = juce::LookAndFeel_V4::getGreyColourScheme();
    juce::LookAndFeel_V4 midnightTheme = juce::LookAndFeel_V4::getMidnightColourScheme();
};
