#include "MainComponent.hpp"

MainComponent::MainComponent()
{
    addAndMakeVisible(themeSwitcher);
    addAndMakeVisible(tab1);
    addAndMakeVisible(tab2);
    addAndMakeVisible(webView1);
    addAndMakeVisible(webView2);
}

MainComponent::~MainComponent() { setLookAndFeel(nullptr); }

void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(findColour(juce::ComboBox::backgroundColourId));
}

void MainComponent::resized()
{
    themeSwitcher.setBounds(5, 5, 100, 25);
    tab1.setBounds(104, 2, 100, 20);
    tab2.setBounds(208, 2, 100, 20);
    webView1.setBounds(0, 35, (getWidth() / 2) - 1, getHeight());
    webView2.setBounds((getWidth() / 2) + 1, 35, (getWidth() / 2) - 1, getBounds().getHeight());
}

void MainComponent::lookAndFeelChanged() { repaint(); }
