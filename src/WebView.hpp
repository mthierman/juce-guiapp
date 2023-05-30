#include <juce_gui_extra/juce_gui_extra.h>

class WebView : public juce::WebBrowserComponent
{
  public:
    // WebView(Options options, juce::TextEditor& addressBox);
    WebView(Options options);
    void paint(juce::Graphics&) override;
    bool pageAboutToLoad(const juce::String& newURL) override;
    void newWindowAttemptingToLoad(const juce::String& newURL) override;

  private:
    // juce::TextEditor& addressBar;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WebView)
};

class WebViewComponent : public juce::Component
{
  public:
    WebViewComponent();
    ~WebViewComponent() override;
    void paint(juce::Graphics&) override;
    void resized() override;
    void lookAndFeelChanged() override;
    // void navigate(juce::String checkUrl);

  private:
    std::unique_ptr<WebView> webView;
    juce::File dataLocation;
    juce::File dllLocation;
    WebView::Options options;
    WebView::Options::WinWebView2 optionsWebView2;
    // juce::TextEditor addressBar;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WebViewComponent)
};
