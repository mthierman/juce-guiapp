#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>

class WebView2 : public juce::Component
{
  public:
    WebView2()
    {
        addAndMakeVisible(url);
        url.addSectionHeading("URL");
        url.addItem("blank", 1);
        url.addItem("example", 2);
        url.addItem("dotpiano", 3);
        url.addItem("ameo", 4);
        url.setSelectedId(Blank);
        url.onChange = [this] { urlChange(); };

        addAndMakeVisible(mode);
        mode.addSectionHeading("Mode");
        mode.addItem("Dark", 1);
        mode.addItem("Light", 2);
        mode.addItem("System", 3);
        mode.onChange = [this] { modeChange(); };
        mode.setSelectedId(System);

        dataLocation =
            juce::File::getSpecialLocation(juce::File::SpecialLocationType::windowsLocalAppData)
                .getChildFile("Test");
        dllLocation =
            juce::File::getSpecialLocation(juce::File::SpecialLocationType::windowsLocalAppData)
                .getChildFile("Test")
                .getChildFile("WebView2Loader.dll");
        webView.reset(new juce::WebBrowserComponent(
            options.withBackend(juce::WebBrowserComponent::Options::Backend::webview2)
                .withWinWebView2Options(optionsWebView2.withDLLLocation(dllLocation)
                                            .withUserDataFolder(dataLocation))));
        addAndMakeVisible(webView.get());
    }

    ~WebView2() override { setLookAndFeel(nullptr); }

    void resized() override
    {
        url.setBounds(5, 5, 400, 30);
        mode.setBounds(450, 5, 400, 30);
        webView->setBounds(0, 40, getWidth(), getHeight() - 40);
    }

    void urlChange()
    {
        switch (url.getSelectedId())
        {
        case Blank:
            webView->goToURL("about:blank");
            break;
        case Example:
            webView->goToURL("https://example.com/");
            break;
        case Dotpiano:
            webView->goToURL("https://dotpiano.com/");
            break;
        case Ameo:
            webView->goToURL("https://synth.ameo.dev/");
            break;
        default:
            break;
        }
        repaint();
    }

    void modeChange()
    {
        auto dark = juce::Desktop::getInstance().isDarkModeActive();
        switch (mode.getSelectedId())
        {
        case Dark:
            // setLookAndFeel(&darkTheme);
            // setColour(juce::ResizableWindow::backgroundColourId, juce::Colours::black);
            juce::Desktop::getInstance().setDefaultLookAndFeel(&darkTheme);
            break;
        case Light:
            // setLookAndFeel(&lightTheme);
            // setColour(juce::ResizableWindow::backgroundColourId, juce::Colours::white);
            juce::Desktop::getInstance().setDefaultLookAndFeel(&lightTheme);
            break;
        case System:
            if (dark)
            {
                // setLookAndFeel(&darkTheme);
                // setColour(juce::ResizableWindow::backgroundColourId, juce::Colours::black);
                juce::Desktop::getInstance().setDefaultLookAndFeel(&darkTheme);
            }
            if (!dark)
            {
                // setLookAndFeel(&lightTheme);
                // setColour(juce::ResizableWindow::backgroundColourId, juce::Colours::white);
                juce::Desktop::getInstance().setDefaultLookAndFeel(&lightTheme);
            }
            break;
        default:
            break;
        }
        repaint();
    }

  private:
    enum URL
    {
        Blank = 1,
        Example,
        Dotpiano,
        Ameo,

    };
    enum Mode
    {
        Dark = 1,
        Light,
        System
    };

    std::unique_ptr<juce::WebBrowserComponent> webView;
    juce::LookAndFeel_V4 lightTheme = juce::LookAndFeel_V4::getLightColourScheme();
    juce::LookAndFeel_V4 darkTheme = juce::LookAndFeel_V4::getGreyColourScheme();
    juce::File dataLocation;
    juce::File dllLocation;
    juce::WebBrowserComponent::Options options;
    juce::WebBrowserComponent::Options::WinWebView2 optionsWebView2;
    juce::ComboBox url;
    juce::ComboBox mode;
};
