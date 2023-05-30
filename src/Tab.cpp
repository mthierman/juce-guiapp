#include "Tab.hpp"

Tab::Tab() {}

Tab::~Tab() { setLookAndFeel(nullptr); }

void Tab::paint(juce::Graphics& g) { g.fillAll(juce::Colours::red); }

void Tab::resized() {}

void Tab::lookAndFeelChanged() { repaint(); }

bool Tab::isInterestedInDragSource(const SourceDetails& dragSourceDetails) { return true; }

void Tab::itemDragEnter(const SourceDetails& dragSourceDetails) { repaint(); }
void Tab::itemDragMove(const SourceDetails& dragSourceDetails) { repaint(); }
void Tab::itemDragExit(const SourceDetails& dragSourceDetails) { repaint(); }
void Tab::itemDropped(const SourceDetails& dragSourceDetails) { repaint(); }
