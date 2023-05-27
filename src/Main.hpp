#include <juce_gui_basics/juce_gui_basics.h>

class App : public juce::JUCEApplication
{
  public:
    App();
    const juce::String getApplicationName() override;
    const juce::String getApplicationVersion() override;
    bool moreThanOneInstanceAllowed() override;
    void initialise(const juce::String &commandLine) override;
    void shutdown() override;
    void systemRequestedQuit() override;
    void anotherInstanceStarted(const juce::String &commandLine) override;

    class Window : public juce::DocumentWindow
    {
      public:
        explicit Window(juce::String name);
        ~Window() override;
        void closeButtonPressed() override;
        void lookAndFeelChanged() override;

      private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Window)
    };

  private:
    std::unique_ptr<Window> mainWindow;
};
