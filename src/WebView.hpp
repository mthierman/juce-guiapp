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

        addAndMakeVisible(url);
        url.addSectionHeading("URL");
        url.addItem("about:blank", 1);
        url.addItem("example.com", 2);
        url.addItem("dotpiano.com", 3);
        url.addItem("synth.ameo.dev", 4);
        url.setSelectedId(Blank);
        url.onChange = [this] { urlChange(); };
    }

    ~WebView() override { setLookAndFeel(nullptr); }

    void resized() override
    {
        webView->setBounds(0, 0, getWidth(), getHeight() - 40);
        url.setBounds(5, getBounds().getHeight() - 35, 200, 30);
    }

    void lookAndFeelChanged() override { repaint(); }

    void urlChange()
    {
        switch (url.getSelectedId())
        {
        case Blank:
            webView->goToURL("about:blank");
            break;
        case Example:
            webView->goToURL("https://example.com/");
            break;
        case Dotpiano:
            webView->goToURL("https://dotpiano.com/");
            break;
        case Ameo:
            webView->goToURL("https://synth.ameo.dev/");
            break;
        default:
            break;
        }
    }

  private:
    std::unique_ptr<juce::WebBrowserComponent> webView;
    juce::File dataLocation;
    juce::File dllLocation;
    juce::WebBrowserComponent::Options options;
    juce::WebBrowserComponent::Options::WinWebView2 optionsWebView2;
    juce::ComboBox url;
    enum Page
    {
        Blank = 1,
        Example,
        Dotpiano,
        Ameo,
    };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WebView)
};
