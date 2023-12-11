/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CircularBuffer.h"
//==============================================================================
/**
*/
class LissajousVSTAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    LissajousVSTAudioProcessor();
    ~LissajousVSTAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    AudioBuffer<float> getBuffer()
    {
        return buffer->getSamples();
    }

    int getNumSamples()
    {
        return numSamples;
    }
    //Atomic<float> panAmount;
private:
    std::unique_ptr<CircularBuffer<float>>  buffer;
    int numSamples;
    juce::AudioProcessorValueTreeState parameters;
    
    juce::LinearSmoothedValue<float> prePan{ 0.0f };
    juce::LinearSmoothedValue<float> postPan{ 0.0f };
    juce::LinearSmoothedValue<float> preWidth{ 1.0f };
    juce::LinearSmoothedValue<float> postWidth{ 1.0f };
    juce::LinearSmoothedValue<float> preMid{ 1.0f };
    juce::LinearSmoothedValue<float> postMid{ 1.0f };
    juce::LinearSmoothedValue<float> lClip{ 1.0f };
    juce::LinearSmoothedValue<float> rClip{ 1.0f };
    juce::LinearSmoothedValue<float> lRevClip{ 0.0f };
    juce::LinearSmoothedValue<float> rRevClip{ 0.0f };
    juce::LinearSmoothedValue<float> lDistort{ 0.0f };
    juce::LinearSmoothedValue<float> rDistort{ 0.0f };
    juce::LinearSmoothedValue<float> rotate{ 0.0f };
    juce::LinearSmoothedValue<float> postRotate{ 0.0f };
    juce::LinearSmoothedValue<float> translateL{ 0.0f };
    juce::LinearSmoothedValue<float> translateR{ 0.0f };
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LissajousVSTAudioProcessor)
};
