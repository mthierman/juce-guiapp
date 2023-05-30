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

// void MainComponent::resized()
// {
//     themeSwitcher.setBounds(5, 5, 100, 20);
//     tab1.setBounds(110, 5, 100, 20);
//     tab2.setBounds(215, 5, 100, 20);
//     webView1.setBounds(0, 30, (getWidth() / 2) - 1, getHeight() - 25);
//     webView2.setBounds((getWidth() / 2) + 1, 30, (getWidth() / 2) - 1,
//                        getBounds().getHeight() - 25);
// }

void MainComponent::resized()
{
    auto height = 30;
    themeSwitcher.setBounds(0, 0, getWidth(), height);

    tab1.setBounds(0, height, (getWidth() / 2), height);

    tab2.setBounds((getWidth() / 2), height, (getWidth() / 2), height);

    webView1.setBounds(0, (height * 2), (getWidth() / 2), getHeight() - (height * 2));

    webView2.setBounds((getWidth() / 2), (height * 2), (getWidth() / 2),
                       getHeight() - (height * 2));
}

void MainComponent::lookAndFeelChanged() { repaint(); }
