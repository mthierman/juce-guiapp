#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

class Browser : public juce::WebBrowserComponent
{
  public:
    Browser(Options options, juce::TextEditor &addressBox);
    bool pageAboutToLoad(const juce::String &newURL) override;
    void newWindowAttemptingToLoad(const juce::String &newURL) override;

  private:
    juce::TextEditor &addressBar;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Browser)
};

class WebView : public juce::Component
{
  public:
    WebView();
    ~WebView() override;
    void resized() override;
    void lookAndFeelChanged() override;
    void urlChange();
    void navigate(juce::String checkUrl);

  private:
    std::unique_ptr<Browser> webView;
    juce::File dataLocation;
    juce::File dllLocation;
    Browser::Options options;
    Browser::Options::WinWebView2 optionsWebView2;
    juce::ComboBox url;
    enum Page
    {
        Blank = 1,
        Example,
        Dotpiano,
        Ameo,
    };
    juce::TextEditor addressBar;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WebView)
};
