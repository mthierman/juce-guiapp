#include "Content.hpp"

class App : public juce::JUCEApplication
{
  public:
    App() {}

    const juce::String getApplicationName() override { return JUCE_APPLICATION_NAME_STRING; }

    const juce::String getApplicationVersion() override { return JUCE_APPLICATION_VERSION_STRING; }

    bool moreThanOneInstanceAllowed() override { return true; }

    void initialise(const juce::String &commandLine) override
    {
        juce::ignoreUnused(commandLine);
        mainWindow.reset(new Window(getApplicationName()));
    }

    void shutdown() override { mainWindow = nullptr; }

    void systemRequestedQuit() override { quit(); }

    void anotherInstanceStarted(const juce::String &commandLine) override
    {
        juce::ignoreUnused(commandLine);
    }

    class Window : public juce::DocumentWindow
    {
      public:
        explicit Window(juce::String name)
            : DocumentWindow(name,
                             juce::Desktop::getInstance().getDefaultLookAndFeel().findColour(
                                 ResizableWindow::backgroundColourId),
                             DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar(false);
            setContentOwned(new Content(), false);
            setResizeLimits(640, 480, 800, 600);
            setResizable(true, false);
            centreWithSize(getWidth(), getHeight());
            setVisible(true);
        }

        ~Window() override { setLookAndFeel(nullptr); }

        void closeButtonPressed() override
        {
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

        void lookAndFeelChanged() override
        {
            setBackgroundColour(juce::Desktop::getInstance().getDefaultLookAndFeel().findColour(
                ResizableWindow::backgroundColourId));
            repaint();
        }

      private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Window)
    };

  private:
    std::unique_ptr<Window> mainWindow;
};
