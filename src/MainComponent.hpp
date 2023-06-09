#include "Theme.hpp"
#include "WebView.hpp"

class MainComponent : public juce::Component,
                      public juce::DragAndDropContainer
{
  public:
    MainComponent();
    ~MainComponent() override;
    void paint(juce::Graphics &) override;
    void resized() override;
    void lookAndFeelChanged() override;

  private:
    ThemeSwitcher themeSwitcher;
    WebView webView;
    WebView webView2;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
