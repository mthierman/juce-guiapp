#include "WebView.hpp"

Browser::Browser(Options options, juce::TextEditor& addressBox)
    : juce::WebBrowserComponent(options), addressBar(addressBox)
{
    juce::Font inter = juce::Font("Segoe UI Variable", 20.0f, juce::Font::plain);
    addressBar.setFont(inter);
    addressBar.setJustification(juce::Justification::centred);
}

void Browser::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::transparentBlack);
    // if (somethingIsBeingDragged)
    // {
    //     g.setColour(juce::Colours::red);
    //     g.drawRect(getLocalBounds());
    // }
}

bool Browser::pageAboutToLoad(const juce::String& newURL)
{
    addressBar.setText(newURL, false);
    return true;
}

void Browser::newWindowAttemptingToLoad(const juce::String& newURL) { goToURL(newURL); }

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
    addAndMakeVisible(addressBar);
    addressBar.onReturnKey = [this] { navigate(addressBar.getText()); };
    webView->goToURL("https://docs.juce.com/develop/index.html");
}

WebView::~WebView() { setLookAndFeel(nullptr); }

void WebView::paint(juce::Graphics& g) { g.fillAll(juce::Colours::transparentBlack); }

void WebView::resized()
{
    webView->setBounds(0, 0, getWidth(), getHeight() - 30);
    addressBar.setBounds(0, getBounds().getHeight() - 30, getWidth(), 30);
}

void WebView::lookAndFeelChanged()
{
    addressBar.applyColourToAllText(findColour(juce::TextEditor::textColourId));
    repaint();
}

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

void WebView::navigate(juce::String checkUrl) { webView->goToURL(checkUrl); }

// bool WebView::isInterestedInDragSource(const SourceDetails& dragSourceDetails) { return true; }

// void WebView::itemDragEnter(const SourceDetails& dragSourceDetails)
// {
//     somethingIsBeingDragged = true;
//     repaint();
// }

// void WebView::itemDragMove(const SourceDetails& dragSourceDetails) { repaint(); }

// void WebView::itemDragExit(const SourceDetails& dragSourceDetails)
// {
//     somethingIsBeingDragged = false;
//     repaint();
// }

// void WebView::itemDropped(const SourceDetails& dragSourceDetails)
// {
//     somethingIsBeingDragged = false;
//     repaint();
// }

// void WebView::mouseDrag(const juce::MouseEvent& mouseEvent)
// {
//     if (!somethingIsBeingDragged && mouseEvent.getDistanceFromDragStart() > 1.5f)
//     {
//         if (auto* container = juce::DragAndDropContainer::findParentDragContainerFor(this))
//         {
//             container->startDragging("Browser", this);
//             somethingIsBeingDragged = true;
//         }
//     }
// }
