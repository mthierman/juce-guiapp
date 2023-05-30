#include <juce_gui_basics/juce_gui_basics.h>

class Tab : public juce::Component,
            public juce::DragAndDropTarget
{
  public:
    Tab(juce::String);
    ~Tab() override;
    void paint(juce::Graphics&) override;
    void resized() override;
    void lookAndFeelChanged() override;
    bool isInterestedInDragSource(const SourceDetails& dragSourceDetails) override;
    void itemDragEnter(const SourceDetails& dragSourceDetails) override;
    void itemDragMove(const SourceDetails& dragSourceDetails) override;
    void itemDragExit(const SourceDetails& dragSourceDetails) override;
    void itemDropped(const SourceDetails& dragSourceDetails) override;
    void mouseDrag(const juce::MouseEvent& mouseEvent) override;
    void mouseUp(const juce::MouseEvent& mouseEvent) override;

  private:
    bool somethingIsBeingDragged = false;
    juce::String tabTitle;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Tab)
};
