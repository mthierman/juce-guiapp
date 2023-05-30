#include "Theme.hpp"
#include "WebView.hpp"
#include "Tab.hpp"

class MainComponent : public juce::Component,
                      public juce::DragAndDropContainer
{
  public:
    MainComponent();
    ~MainComponent() override;
    void paint(juce::Graphics&) override;
    void resized() override;
    void lookAndFeelChanged() override;

  private:
    ThemeSwitcher themeSwitcher;
    Tab tab1;
    Tab tab2;
    WebView webView1;
    WebView webView2;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
