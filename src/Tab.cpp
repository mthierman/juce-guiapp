#include "Tab.hpp"

Tab::Tab() {}

Tab::~Tab() { setLookAndFeel(nullptr); }

void Tab::paint(juce::Graphics& g)
{
    if (somethingIsBeingDragged)
    {
        g.fillAll(juce::Colours::lightpink);
        g.setColour(juce::Colours::black);
        g.drawRect(getLocalBounds());
        g.drawText("Dragging!", getLocalBounds(), juce::Justification::centred);
    }
    if (!somethingIsBeingDragged)
    {
        g.fillAll(juce::Colours::lightcoral);
        g.setColour(juce::Colours::black);
        g.drawRect(getLocalBounds());
        g.drawText("Not Dragging.", getLocalBounds(), juce::Justification::centred);
    }
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
    if (!somethingIsBeingDragged && mouseEvent.getDistanceFromDragStart() > 1.5f)
    {
        if (auto* container = juce::DragAndDropContainer::findParentDragContainerFor(this))
        {
            container->startDragging("Tab", this);
            somethingIsBeingDragged = true;
        }
    }
}
