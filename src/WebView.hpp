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

        // addAndMakeVisible(mode);
        // mode.addSectionHeading("Mode");
        // mode.addItem("Dark", 1);
        // mode.addItem("Light", 2);
        // mode.addItem("System", 3);
        // mode.onChange = [this] { modeChange(); };
        // mode.setSelectedId(System);

        // auto dark = juce::Desktop::getInstance().isDarkModeActive();
        // if (dark)
        // {
        //     setDarkTheme();
        // }
        // if (!dark)
        // {
        //     setLightTheme();
        // }

        dataLocation =
            juce::File::getSpecialLocation(juce::File::SpecialLocationType::windowsLocalAppData)
                .getChildFile("Test");
        dllLocation =
            juce::File::getSpecialLocation(juce::File::SpecialLocationType::windowsLocalAppData)
                .getChildFile("Test")
                .getChildFile("WebView2Loader.dll");
        // webView.reset(new juce::WebBrowserComponent(
        //     options.withBackend(juce::WebBrowserComponent::Options::Backend::webview2)
        //         .withWinWebView2Options(
        //             optionsWebView2.withDLLLocation(dllLocation)
        //                 .withUserDataFolder(dataLocation)
        //                 .withBackgroundColour(
        //                     juce::Desktop::getInstance().getDefaultLookAndFeel().findColour(
        //                         juce::ResizableWindow::backgroundColourId)))));
        webView.reset(new juce::WebBrowserComponent(
            options.withBackend(juce::WebBrowserComponent::Options::Backend::webview2)
                .withWinWebView2Options(
                    optionsWebView2.withDLLLocation(dllLocation)
                        .withUserDataFolder(dataLocation)
                        .withBackgroundColour(
                            juce::Desktop::getInstance().getDefaultLookAndFeel().findColour(
                                juce::ResizableWindow::backgroundColourId)))));
        addAndMakeVisible(webView.get());
    }

    ~WebView2() override { setLookAndFeel(nullptr); }

    void resized() override
    {
        url.setBounds(5, 5, 400, 30);
        // mode.setBounds(450, 5, 400, 30);
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

    // void modeChange()
    // {
    //     auto dark = juce::Desktop::getInstance().isDarkModeActive();
    //     switch (mode.getSelectedId())
    //     {
    //     case Dark:
    //         setDarkTheme();
    //         break;
    //     case Light:
    //         setLightTheme();
    //         break;
    //     case System:
    //         if (dark)
    //         {
    //             setDarkTheme();
    //         }
    //         if (!dark)
    //         {
    //             setLightTheme();
    //         }
    //         break;
    //     default:
    //         break;
    //     }
    //     repaint();
    // }

    // void setDarkTheme() { juce::Desktop::getInstance().setDefaultLookAndFeel(&darkTheme); }

    // void setLightTheme() { juce::Desktop::getInstance().setDefaultLookAndFeel(&lightTheme); }

  private:
    std::unique_ptr<juce::WebBrowserComponent> webView;
    juce::File dataLocation;
    juce::File dllLocation;
    juce::WebBrowserComponent::Options options;
    juce::WebBrowserComponent::Options::WinWebView2 optionsWebView2;

    juce::ComboBox url;
    enum URL
    {
        Blank = 1,
        Example,
        Dotpiano,
        Ameo,

    };

    // juce::ComboBox mode;
    // enum Mode
    // {
    //     Dark = 1,
    //     Light,
    //     System
    // };
    // juce::LookAndFeel_V4 lightTheme = juce::LookAndFeel_V4::getLightColourScheme();
    // juce::LookAndFeel_V4 darkTheme = juce::LookAndFeel_V4::getGreyColourScheme();
};
