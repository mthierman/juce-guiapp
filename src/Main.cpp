#include "Main.hpp"
#include "MainComponent.hpp"
#include <choc_Platform.h>

#if CHOC_WINDOWS
#include "Windows.h"
#endif

App::App()
{
    SetEnvironmentVariableW(L"WEBVIEW2_DEFAULT_BACKGROUND_COLOR", L"0");
    SetEnvironmentVariableW(L"WEBVIEW2_ADDITIONAL_BROWSER_ARGUMENTS",
                            L"--enable-features=OverlayScrollbar,"
                            L"msOverlayScrollbarWinStyle:scrollbar_mode/"
                            L"full_mode,msOverlayScrollbarWinStyleAnimation,"
                            L"msWebView2BrowserHitTransparent"
                            L" --disable-features=msWebOOUI,msPdfOOUI");
}

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
    setUsingNativeTitleBar(false);
    setContentOwned(new MainComponent(), false);
    setResizeLimits(640, 480,
                    juce::Desktop::getInstance().getDisplays().getTotalBounds(true).getWidth(),
                    juce::Desktop::getInstance().getDisplays().getTotalBounds(true).getHeight());
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
