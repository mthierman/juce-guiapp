#include "MainComponent.hpp"

MainComponent::MainComponent()
{
    addAndMakeVisible(themeSwitcher);
    addAndMakeVisible(webView);
}

MainComponent::~MainComponent() { setLookAndFeel(nullptr); }

void MainComponent::resized()
{
    themeSwitcher.setBounds(5, 5, 100, 30);
    webView.setBounds(0, 40, getWidth(), getHeight() - 40);
}

void MainComponent::lookAndFeelChanged() { repaint(); }
