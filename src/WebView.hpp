#include <juce_gui_extra/juce_gui_extra.h>

class Browser : public juce::WebBrowserComponent
{
  public:
    Browser(Options options, juce::TextEditor& addressBox);
    void paint(juce::Graphics&) override;
    bool pageAboutToLoad(const juce::String& newURL) override;
    void newWindowAttemptingToLoad(const juce::String& newURL) override;

  private:
    juce::TextEditor& addressBar;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Browser)
};

// class WebView : public juce::Component,
//                 public juce::DragAndDropTarget
class WebView : public juce::Component
{
  public:
    WebView();
    ~WebView() override;
    void paint(juce::Graphics&) override;
    void resized() override;
    void lookAndFeelChanged() override;
    void urlChange();
    void navigate(juce::String checkUrl);
    // bool isInterestedInDragSource(const SourceDetails& dragSourceDetails) override;
    // void itemDragEnter(const SourceDetails& dragSourceDetails) override;
    // void itemDragMove(const SourceDetails& dragSourceDetails) override;
    // void itemDragExit(const SourceDetails& dragSourceDetails) override;
    // void itemDropped(const SourceDetails& dragSourceDetails) override;
    // void mouseDrag(const juce::MouseEvent& mouseEvent) override;

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
    // bool somethingIsBeingDragged = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WebView)
};
