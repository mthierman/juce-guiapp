#include <juce_gui_basics/juce_gui_basics.h>

class ThemeSwitcher : public juce::Component
{
  public:
    ThemeSwitcher();
    void resized() override;
    void modeChange();

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
    juce::LookAndFeel_V4 testTheme = juce::LookAndFeel_V4::getLightColourScheme();
};
