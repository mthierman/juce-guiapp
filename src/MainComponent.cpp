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
    themeSwitcher.setBounds(5, 5, 100, 20);
    tab1.setBounds(110, 5, 100, 20);
    tab2.setBounds(215, 5, 100, 20);
    // webView1.setBounds(0, 35, (getWidth() / 2) - 1, getHeight());
    // webView2.setBounds((getWidth() / 2) + 1, 35, (getWidth() / 2) - 1, getBounds().getHeight());
    webView1.setBounds(0, 30, (getWidth() / 2) - 1, getHeight() - 25);
    webView2.setBounds((getWidth() / 2) + 1, 30, (getWidth() / 2) - 1,
                       getBounds().getHeight() - 25);
}

void MainComponent::lookAndFeelChanged() { repaint(); }
