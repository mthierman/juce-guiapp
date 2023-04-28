#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_core/juce_core.h>
#include <juce_data_structures/juce_data_structures.h>
#include <juce_events/juce_events.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MyComponent : public juce::AudioAppComponent, public juce::ChangeListener
{
  public:
    MyComponent() : state(Stopped)
    {
        addAndMakeVisible(&openButton);
        openButton.setButtonText("Open...");
        openButton.onClick = [this] { openButtonClicked(); };

        addAndMakeVisible(&playButton);
        playButton.setButtonText("Play");
        playButton.onClick = [this] { playButtonClicked(); };
        playButton.setColour(juce::TextButton::buttonColourId, juce::Colours::green);
        playButton.setEnabled(false);

        addAndMakeVisible(&stopButton);
        stopButton.setButtonText("Stop");
        stopButton.onClick = [this] { stopButtonClicked(); };
        stopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
        stopButton.setEnabled(false);

        setSize(300, 200);

        formatManager.registerBasicFormats();    // [1]
        transportSource.addChangeListener(this); // [2]

        setAudioChannels(0, 2);
    }

    ~MyComponent() override { shutdownAudio(); }

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override
    {
        transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    }

    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override
    {
        if (readerSource.get() == nullptr)
        {
            bufferToFill.clearActiveBufferRegion();
            return;
        }

        transportSource.getNextAudioBlock(bufferToFill);
    }

    void releaseResources() override { transportSource.releaseResources(); }

    void resized() override
    {
        openButton.setBounds(10, 10, getWidth() - 20, 20);
        playButton.setBounds(10, 40, getWidth() - 20, 20);
        stopButton.setBounds(10, 70, getWidth() - 20, 20);
    }

    void changeListenerCallback(juce::ChangeBroadcaster *source) override
    {
        if (source == &transportSource)
        {
            if (transportSource.isPlaying())
                changeState(Playing);
            else
                changeState(Stopped);
        }
    }

  private:
    enum TransportState
    {
        Stopped,
        Starting,
        Playing,
        Stopping
    };

    void changeState(TransportState newState)
    {
        if (state != newState)
        {
            state = newState;

            switch (state)
            {
            case Stopped: // [3]
                stopButton.setEnabled(false);
                playButton.setEnabled(true);
                transportSource.setPosition(0.0);
                break;

            case Starting: // [4]
                playButton.setEnabled(false);
                transportSource.start();
                break;

            case Playing: // [5]
                stopButton.setEnabled(true);
                break;

            case Stopping: // [6]
                transportSource.stop();
                break;
            }
        }
    }

    void openButtonClicked()
    {
        chooser = std::make_unique<juce::FileChooser>("Select a Wave file to play...", juce::File{},
                                                      "*.wav"); // [7]
        auto chooserFlags =
            juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles;

        chooser->launchAsync(chooserFlags, [this](const juce::FileChooser &fc) // [8]
                             {
                                 auto file = fc.getResult();

                                 if (file != juce::File{}) // [9]
                                 {
                                     auto *reader = formatManager.createReaderFor(file); // [10]

                                     if (reader != nullptr)
                                     {
                                         auto newSource =
                                             std::make_unique<juce::AudioFormatReaderSource>(
                                                 reader, true); // [11]
                                         transportSource.setSource(newSource.get(), 0, nullptr,
                                                                   reader->sampleRate); // [12]
                                         playButton.setEnabled(true);                   // [13]
                                         readerSource.reset(newSource.release());       // [14]
                                     }
                                 }
                             });
    }

    void playButtonClicked() { changeState(Starting); }

    void stopButtonClicked() { changeState(Stopping); }

    //==========================================================================
    juce::TextButton openButton;
    juce::TextButton playButton;
    juce::TextButton stopButton;

    std::unique_ptr<juce::FileChooser> chooser;

    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
    TransportState state;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MyComponent)
};
