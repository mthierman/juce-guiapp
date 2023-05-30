#include "WebView.hpp"

WebView::WebView(Options options, juce::TextEditor& addressBox)
    : juce::WebBrowserComponent(options), addressBar(addressBox)
{
    juce::Font inter = juce::Font("Segoe UI Variable", 20.0f, juce::Font::plain);
    addressBar.setFont(inter);
    addressBar.setJustification(juce::Justification::centred);
}

void WebView::paint(juce::Graphics& g) { g.fillAll(juce::Colours::transparentBlack); }

bool WebView::pageAboutToLoad(const juce::String& newURL)
{
    addressBar.setText(newURL, false);
    return true;
}

void WebView::newWindowAttemptingToLoad(const juce::String& newURL) { goToURL(newURL); }

WebViewComponent::WebViewComponent()
{
    dataLocation =
        juce::File::getSpecialLocation(juce::File::SpecialLocationType::windowsLocalAppData)
            .getChildFile("Test");
    dllLocation =
        juce::File::getSpecialLocation(juce::File::SpecialLocationType::windowsLocalAppData)
            .getChildFile("Test")
            .getChildFile("WebView2Loader.dll");
    webView.reset(
        new WebView(options.withBackend(WebView::Options::Backend::webview2)
                        .withWinWebView2Options(optionsWebView2.withDLLLocation(dllLocation)
                                                    .withUserDataFolder(dataLocation)
                                                    .withBackgroundColour(juce::Colours::black)),
                    addressBar));
    addAndMakeVisible(webView.get());
    addAndMakeVisible(addressBar);
    addressBar.onReturnKey = [this] { navigate(addressBar.getText()); };
    webView->goToURL("https://docs.juce.com/develop/index.html");
}

WebViewComponent::~WebViewComponent() { setLookAndFeel(nullptr); }

void WebViewComponent::paint(juce::Graphics& g) { g.fillAll(juce::Colours::transparentBlack); }

void WebViewComponent::resized()
{
    webView->setBounds(0, 0, getWidth(), getHeight() - 100);
    addressBar.setBounds(0, getHeight() - 100, getWidth(), 100);
}

void WebViewComponent::lookAndFeelChanged()
{
    addressBar.applyColourToAllText(findColour(juce::TextEditor::textColourId));
    repaint();
}

void WebViewComponent::urlChange()
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

void WebViewComponent::navigate(juce::String checkUrl) { webView->goToURL(checkUrl); }
