#include "LookAndFeel.hpp"

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
        System = 1,
        Dark,
        Light,
        Custom
    };
    DarkLookAndFeel darkTheme;
    LightLookAndFeel lightTheme;
    CustomLookAndFeel customTheme;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ThemeSwitcher)
};
