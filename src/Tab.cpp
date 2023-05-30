#include "Tab.hpp"

Tab::Tab(juce::String title) { tabTitle = title; }

Tab::~Tab() { setLookAndFeel(nullptr); }

void Tab::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::lightblue);
    g.setColour(juce::Colours::black);
    g.drawText(tabTitle, getLocalBounds(), juce::Justification::centred);
}

void Tab::resized() {}

void Tab::lookAndFeelChanged() { repaint(); }

bool Tab::isInterestedInDragSource(const SourceDetails& dragSourceDetails) { return true; }

void Tab::itemDragEnter(const SourceDetails& dragSourceDetails)
{
    somethingIsBeingDragged = true;
    repaint();
}

void Tab::itemDragMove(const SourceDetails& dragSourceDetails) { repaint(); }

void Tab::itemDragExit(const SourceDetails& dragSourceDetails)
{
    somethingIsBeingDragged = false;
    repaint();
}

void Tab::itemDropped(const SourceDetails& dragSourceDetails)
{
    somethingIsBeingDragged = false;
    repaint();
}

void Tab::mouseDrag(const juce::MouseEvent& mouseEvent)
{
    if (!somethingIsBeingDragged)
    {
        if (auto* container = juce::DragAndDropContainer::findParentDragContainerFor(this))
        {
            container->startDragging("Tab", this);
            somethingIsBeingDragged = true;
        }
    }
    repaint();
}

void Tab::mouseUp(const juce::MouseEvent& mouseEvent)
{
    somethingIsBeingDragged = false;
    repaint();
}
