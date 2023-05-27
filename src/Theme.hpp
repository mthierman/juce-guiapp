#include "LookAndFeel.hpp"

class ThemeSwitcher : public juce::Component
{
  public:
    ThemeSwitcher();
    void paint(juce::Graphics &) override;
    void resized() override;
    void modeChange();

  private:
    juce::ComboBox mode;
    enum Mode
    {
        Custom = 1,
        System,
        Dark,
        Light
    };
    CustomTheme customTheme;
    DarkTheme darkTheme;
    LightTheme lightTheme;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ThemeSwitcher)
};
