#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>

class Browser : public juce::WebBrowserComponent
{
  public:
    using WebBrowserComponent::WebBrowserComponent;

  private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Browser)
};
