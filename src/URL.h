#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>

class URL : public juce::Component
{
  public:
    URL()
    {
        addAndMakeVisible(url);
        url.addSectionHeading("URL");
        url.addItem("about:blank", 1);
        url.addItem("example.com", 2);
        url.addItem("dotpiano.com", 3);
        url.addItem("synth.ameo.dev", 4);
        url.setSelectedId(Blank);
        url.onChange = [this] { urlChange(); };
    }

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
        repaint();
    }

  private:
    juce::ComboBox url;
    enum Page
    {
        Blank = 1,
        Example,
        Dotpiano,
        Ameo,
    };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(URL)
};
