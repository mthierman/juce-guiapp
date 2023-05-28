#include <juce_gui_basics/juce_gui_basics.h>

class LookAndFeel : public juce::LookAndFeel_V4
{
  public:
    LookAndFeel();
    void SetColours();

  private:
};

class CustomTheme : public LookAndFeel
{
  public:
    CustomTheme();
    juce::Font getComboBoxFont(juce::ComboBox&) override;

  private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomTheme)
};

class DarkTheme : public LookAndFeel
{
  public:
    DarkTheme();

  private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DarkTheme)
};

class LightTheme : public LookAndFeel
{
  public:
    LightTheme();

  private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LightTheme)
};
