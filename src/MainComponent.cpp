#include "MainComponent.hpp"

MainComponent::MainComponent()
{
    addAndMakeVisible(themeSwitcher);
    addAndMakeVisible(webView);
    addAndMakeVisible(webView2);
}

MainComponent::~MainComponent() { setLookAndFeel(nullptr); }

void MainComponent::paint(juce::Graphics &g)
{
    g.fillAll(findColour(juce::ComboBox::backgroundColourId));
}

void MainComponent::resized()
{
    themeSwitcher.setBounds(2, 2, 100, 20);
    webView.setBounds(0, 24, (getWidth() / 2) - 1, getHeight() - 24);
    webView2.setBounds((getWidth() / 2) + 1, 24, (getWidth() / 2) - 1, getHeight() - 24);
}

void MainComponent::lookAndFeelChanged() { repaint(); }
