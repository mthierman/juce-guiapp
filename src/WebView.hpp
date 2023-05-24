#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>

class WebView : public juce::Component
{
  public:
    WebView()
    {
        dataLocation =
            juce::File::getSpecialLocation(juce::File::SpecialLocationType::windowsLocalAppData)
                .getChildFile("Test");
        dllLocation =
            juce::File::getSpecialLocation(juce::File::SpecialLocationType::windowsLocalAppData)
                .getChildFile("Test")
                .getChildFile("WebView2Loader.dll");
        webView.reset(new juce::WebBrowserComponent(
            options.withBackend(juce::WebBrowserComponent::Options::Backend::webview2)
                .withWinWebView2Options(optionsWebView2.withDLLLocation(dllLocation)
                                            .withUserDataFolder(dataLocation)
                                            .withBackgroundColour(juce::Colours::black))));
        addAndMakeVisible(webView.get());
    }

    ~WebView() override { setLookAndFeel(nullptr); }

    void resized() override { webView->setBounds(0, 0, getWidth(), getHeight()); }

    void lookAndFeelChanged() override { repaint(); }

  private:
    std::unique_ptr<juce::WebBrowserComponent> webView;
    juce::File dataLocation;
    juce::File dllLocation;
    juce::WebBrowserComponent::Options options;
    juce::WebBrowserComponent::Options::WinWebView2 optionsWebView2;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WebView)
};
