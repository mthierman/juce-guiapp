#pragma once

// #include <juce_audio_basics/juce_audio_basics.h>
// #include <juce_audio_devices/juce_audio_devices.h>
// #include <juce_audio_formats/juce_audio_formats.h>
// #include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>
// #include <juce_core/juce_core.h>
// #include <juce_data_structures/juce_data_structures.h>
// #include <juce_events/juce_events.h>
// #include <juce_graphics/juce_graphics.h>
// #include <juce_gui_basics/juce_gui_basics.h>
// #include <juce_gui_extra/juce_gui_extra.h>
// #include <juce_dsp/juce_dsp.h>

class MyComponent : public juce::AudioAppComponent
{
  public:
    MyComponent()
    {
        setSize(600, 400);
        setAudioChannels(0, 2);
    }

    ~MyComponent() override { shutdownAudio(); }

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override
    {
        juce::String message;
        message << "Preparing to play audio...\n";
        message << " samplesPerBlockExpected = " << samplesPerBlockExpected << "\n";
        message << " sampleRate = " << sampleRate;
        juce::Logger::getCurrentLogger()->writeToLog(message);
    }

    void releaseResources() override
    {
        juce::Logger::getCurrentLogger()->writeToLog("Releasing audio resources");
    }

    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override
    {
        for (auto channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
        {
            // Get a pointer to the start sample in the buffer for this audio output channel
            auto *buffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);

            // Fill the required number of samples with noise between -0.125 and +0.125
            for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
                buffer[sample] = random.nextFloat() * 0.25f - 0.125f;
        }
    }

  private:
    juce::Random random;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MyComponent)
};
