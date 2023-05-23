#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_core/juce_core.h>
#include <juce_data_structures/juce_data_structures.h>
#include <juce_events/juce_events.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>

class WebView2 : public juce::Component
{
  public:
    WebView2()
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
                                            .withUserDataFolder(dataLocation))));
        addAndMakeVisible(webView.get());
        addAndMakeVisible(url);
        url.addSectionHeading("URL");
        url.addItem("Example", 1);
        url.addItem("dotpiano", 2);
        url.addItem("ameo", 3);
        url.setSelectedId(Example);
        url.onChange = [this] { urlChange(); };
    }

    void resized() override
    {
        url.setBounds(0, getLocalBounds().getHeight() - 25, getWidth(), 25);
        webView->setBounds(0, 0, getWidth(), getHeight() - 25);
    }

    void urlChange()
    {
        switch (url.getSelectedId())
        {
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
        repaint();
    }

  private:
    enum URL
    {
        Example = 1,
        Dotpiano,
        Ameo
    };
    std::unique_ptr<juce::WebBrowserComponent> webView;
    juce::File dataLocation;
    juce::File dllLocation;
    juce::WebBrowserComponent::Options options;
    juce::WebBrowserComponent::Options::WinWebView2 optionsWebView2;
    juce::ComboBox url;
};
