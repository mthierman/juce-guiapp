#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>

#include "WebView.hpp"
#include "Theme.hpp"

class Content : public juce::Component
{
  public:
    Content()
    {
        addAndMakeVisible(themeSwitcher);
        addAndMakeVisible(webView);
    }

    ~Content() override { setLookAndFeel(nullptr); }

    void resized() override
    {
        themeSwitcher.setBounds(5, 5, 100, 30);
        webView.setBounds(0, 40, getWidth(), getHeight() - 40);
    }

    void lookAndFeelChanged() override { repaint(); }

  private:
    WebView webView;
    ThemeSwitcher themeSwitcher;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Content)
};
