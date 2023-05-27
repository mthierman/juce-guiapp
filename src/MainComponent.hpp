#include "Theme.hpp"
#include "WebView.hpp"

class MainComponent : public juce::Component
{
  public:
    MainComponent();
    ~MainComponent() override;
    void resized() override;
    void lookAndFeelChanged() override;

  private:
    ThemeSwitcher themeSwitcher;
    WebView webView;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
