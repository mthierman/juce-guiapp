#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() { setSize(800, 800); }

//==============================================================================
void MainComponent::paint(juce::Graphics &g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    juce::Font mainComponentFont("Inter", 20.0f, 0);
    g.setFont(mainComponentFont);
    g.setColour(juce::Colours::white);
    g.drawText(currentSizeAsString, getWidth() - 100, getHeight() - 25, 100, 25,
               juce::Justification::topLeft, true);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    currentSizeAsString = juce::String(getWidth()) + " x " + juce::String(getHeight());
}
