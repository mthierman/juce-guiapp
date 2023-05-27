#include "WebView.hpp"

Browser::Browser(Options options, juce::TextEditor &addressBox)
    : juce::WebBrowserComponent(options), addressBar(addressBox)
{
}

bool Browser::pageAboutToLoad(const juce::String &newURL)
{
    addressBar.setText(newURL, false);
    return true;
}

void Browser::newWindowAttemptingToLoad(const juce::String &newURL) { goToURL(newURL); }

WebView::WebView()
{
    dataLocation =
        juce::File::getSpecialLocation(juce::File::SpecialLocationType::windowsLocalAppData)
            .getChildFile("Test");
    dllLocation =
        juce::File::getSpecialLocation(juce::File::SpecialLocationType::windowsLocalAppData)
            .getChildFile("Test")
            .getChildFile("WebView2Loader.dll");
    webView.reset(
        new Browser(options.withBackend(Browser::Options::Backend::webview2)
                        .withWinWebView2Options(optionsWebView2.withDLLLocation(dllLocation)
                                                    .withUserDataFolder(dataLocation)
                                                    .withBackgroundColour(juce::Colours::black)),
                    addressBar));
    addAndMakeVisible(webView.get());

    addAndMakeVisible(url);
    url.addSectionHeading("URL");
    url.addItem("about:blank", 1);
    url.addItem("example.com", 2);
    url.addItem("dotpiano.com", 3);
    url.addItem("synth.ameo.dev", 4);
    url.setSelectedId(Blank);
    url.onChange = [this] { urlChange(); };

    addAndMakeVisible(addressBar);
    addressBar.setJustification(juce::Justification::verticallyCentred);
    addressBar.onReturnKey = [this] { navigate(addressBar.getText()); };
}

WebView::~WebView() { setLookAndFeel(nullptr); }

void WebView::resized()
{
    webView->setBounds(0, 0, getWidth(), getHeight() - 40);
    url.setBounds(5, getBounds().getHeight() - 35, 200, 30);
    addressBar.setBounds(210, getBounds().getHeight() - 35, getWidth() - 215, 30);
}

void WebView::lookAndFeelChanged() { repaint(); }

void WebView::urlChange()
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

void WebView::navigate(juce::String checkUrl)
{
    if (checkUrl.contains("http://"))
    {
        webView->goToURL(checkUrl);
    };
    if (checkUrl.contains("https://"))
    {
        webView->goToURL(checkUrl);
    };
    if (!checkUrl.contains("http://") || !checkUrl.contains("https://"))
    {
        auto https = "https://" + checkUrl;
        webView->goToURL(https);
    };
}
