#include "Main.hpp"
#include "MainComponent.hpp"

App::App() {}

const juce::String App::getApplicationName() { return JUCE_APPLICATION_NAME_STRING; }

const juce::String App::getApplicationVersion() { return JUCE_APPLICATION_VERSION_STRING; }

bool App::moreThanOneInstanceAllowed() { return true; }

void App::initialise(const juce::String &commandLine)
{
    juce::ignoreUnused(commandLine);
    mainWindow.reset(new Window(getApplicationName()));
}

void App::shutdown() { mainWindow = nullptr; }

void App::systemRequestedQuit() { quit(); }

void App::anotherInstanceStarted(const juce::String &commandLine)
{
    juce::ignoreUnused(commandLine);
}

App::Window::Window(juce::String name)
    : DocumentWindow(name,
                     juce::Desktop::getInstance().getDefaultLookAndFeel().findColour(
                         ResizableWindow::backgroundColourId),
                     DocumentWindow::allButtons)
{
    setUsingNativeTitleBar(true);
    setContentOwned(new MainComponent(), false);
    setResizeLimits(640, 480, 800, 600);
    setResizable(true, false);
    centreWithSize(getWidth(), getHeight());
    setVisible(true);
}

App::Window::~Window() { setLookAndFeel(nullptr); }

void App::Window::closeButtonPressed() { JUCEApplication::getInstance()->systemRequestedQuit(); }

void App::Window::lookAndFeelChanged()
{
    setBackgroundColour(juce::Desktop::getInstance().getDefaultLookAndFeel().findColour(
        ResizableWindow::backgroundColourId));
    repaint();
}

START_JUCE_APPLICATION(App)
