/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ParameterProcessing.h"

//==============================================================================
LissajousVSTAudioProcessor::LissajousVSTAudioProcessor() :
    parameters(*this, nullptr, juce::Identifier("LissajousVST"),
        {
            std::make_unique<juce::AudioParameterFloat>("prePanSlider", "prePan", -1.0f, 1.0f, 0.0f),
            std::make_unique<juce::AudioParameterFloat>("postPanSlider", "postPan", -1.0f, 1.0f, 0.0f),
            std::make_unique<juce::AudioParameterFloat>("preWidthSlider", "preWidth", 0.0f, 2.0f, 1.0f),
            std::make_unique<juce::AudioParameterFloat>("postWidthSlider", "postWidth", 0.0f, 2.0f, 1.0f),
            std::make_unique<juce::AudioParameterFloat>("preMidSlider", "preMid", 0.0f, 2.0f, 1.0f),
            std::make_unique<juce::AudioParameterFloat>("postMidSlider", "postMid", 0.0f, 2.0f, 1.0f),
            std::make_unique<juce::AudioParameterFloat>("lClipSlider", "lClip", 0.0f, 1.0f, 1.0f),
            std::make_unique<juce::AudioParameterFloat>("rClipSlider", "rClip", 0.0f, 1.0f, 1.0f),
            std::make_unique<juce::AudioParameterFloat>("lRevClipSlider", "lRevClip", 0.0f, 1.0f, 0.0f),
            std::make_unique<juce::AudioParameterFloat>("rRevClipSlider", "rRevClip", 0.0f, 1.0f, 0.0f),
            std::make_unique<juce::AudioParameterFloat>("lDistortSlider", "lDistort", 0.0f, 1.0f, 0.0f),
            std::make_unique<juce::AudioParameterFloat>("rDistortSlider", "rDistort", 0.0f, 1.0f, 0.0f),
            std::make_unique<juce::AudioParameterFloat>("rotaterSlider", "rotate", -3.14f, 3.14f, 0.0f),
            std::make_unique<juce::AudioParameterFloat>("postRotaterSlider", "postRotate", -3.14f, 3.14f, 0.0f),
            std::make_unique<juce::AudioParameterFloat>("lMoveSlider", "translateL", -1.0f, 1.0f, 0.0f),
            std::make_unique<juce::AudioParameterFloat>("rMoveSlider", "translateR", -1.0f, 1.0f, 0.0f)
        }                                                                                   
        ),
    numSamples(256),
#ifndef JucePlugin_PreferredChannelConfigurations
      AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ) 
#endif
{
    buffer = std::make_unique<CircularBuffer<float>>(numSamples);
    
    //panAmount.set(*parameters.getRawParameterValue("panSlider"));
}

LissajousVSTAudioProcessor::~LissajousVSTAudioProcessor()
{
}

//==============================================================================
const juce::String LissajousVSTAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool LissajousVSTAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool LissajousVSTAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool LissajousVSTAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double LissajousVSTAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int LissajousVSTAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int LissajousVSTAudioProcessor::getCurrentProgram()
{
    return 0;
}

void LissajousVSTAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String LissajousVSTAudioProcessor::getProgramName (int index)
{
    return {};
}

void LissajousVSTAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void LissajousVSTAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    buffer = std::make_unique<CircularBuffer<float>>(samplesPerBlock * 2);
    numSamples = samplesPerBlock;

    prePan.reset(sampleRate, 0.05);
    postPan.reset(sampleRate, 0.05);
    preWidth.reset(sampleRate, 0.05);
    postWidth.reset(sampleRate, 0.05);
    preMid.reset(sampleRate, 0.05);
    postMid.reset(sampleRate, 0.05);
    lClip.reset(sampleRate, 0.05);
    rClip.reset(sampleRate, 0.05);
    lRevClip.reset(sampleRate, 0.05);
    rRevClip.reset(sampleRate, 0.05);
    lDistort.reset(sampleRate, 0.05);
    rDistort.reset(sampleRate, 0.05);
    rotate.reset(sampleRate, 0.05);
    postRotate.reset(sampleRate, 0.05);
    translateL.reset(sampleRate, 0.05);
    translateR.reset(sampleRate, 0.05);
}

void LissajousVSTAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool LissajousVSTAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void LissajousVSTAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.

    prePan.setTargetValue(*parameters.getRawParameterValue("prePanSlider"));
    postPan.setTargetValue(*parameters.getRawParameterValue("postPanSlider"));
    preWidth.setTargetValue(*parameters.getRawParameterValue("preWidthSlider"));
    postWidth.setTargetValue(*parameters.getRawParameterValue("postWidthSlider"));
    preMid.setTargetValue(*parameters.getRawParameterValue("preMidSlider"));
    postMid.setTargetValue(*parameters.getRawParameterValue("postMidSlider"));
    lClip.setTargetValue(*parameters.getRawParameterValue("lClipSlider"));
    rClip.setTargetValue(*parameters.getRawParameterValue("rClipSlider"));
    lRevClip.setTargetValue(*parameters.getRawParameterValue("lRevClipSlider"));
    rRevClip.setTargetValue(*parameters.getRawParameterValue("rRevClipSlider"));
    lDistort.setTargetValue(*parameters.getRawParameterValue("lDistortSlider"));
    rDistort.setTargetValue(*parameters.getRawParameterValue("rDistortSlider"));
    rotate.setTargetValue(*parameters.getRawParameterValue("rotaterSlider"));
    translateL.setTargetValue(*parameters.getRawParameterValue("lMoveSlider"));
    translateR.setTargetValue(*parameters.getRawParameterValue("rMoveSlider"));
    postRotate.setTargetValue(*parameters.getRawParameterValue("postRotaterSlider"));

    
    auto* lChannelData = buffer.getWritePointer(0);
    auto* rChannelData = buffer.getWritePointer(1);
    int numSamples = buffer.getNumSamples();

    for (int sample = 0; sample < numSamples; ++sample)
    {
        //Pre
        Processing::pan(0, lChannelData, sample, prePan.getNextValue());
        Processing::pan(1, rChannelData, sample, prePan.getCurrentValue());
        Processing::rotate(lChannelData, rChannelData, sample, rotate.getNextValue());
        Processing::widen(lChannelData, rChannelData, sample, preWidth.getNextValue());
        Processing::midBoost(lChannelData, rChannelData, sample, preMid.getNextValue());

        Processing::translate(lChannelData, sample, translateL.getNextValue());
        Processing::translate(rChannelData, sample, translateR.getNextValue());

        Processing::distort(lChannelData, sample, lDistort.getNextValue());
        Processing::distort(rChannelData, sample, rDistort.getNextValue());
        
        Processing::revClip(lChannelData, sample, lRevClip.getNextValue());
        Processing::revClip(rChannelData, sample, rRevClip.getNextValue());

        Processing::clip(lChannelData, sample, lClip.getNextValue());
        Processing::clip(rChannelData, sample, rClip.getNextValue());

        Processing::pan(0, lChannelData, sample, postPan.getNextValue());
        Processing::pan(1, rChannelData, sample, postPan.getCurrentValue());
        Processing::rotate(lChannelData, rChannelData, sample, postRotate.getNextValue());
        Processing::widen(lChannelData, rChannelData, sample, postWidth.getNextValue());
        Processing::midBoost(lChannelData, rChannelData, sample, postMid.getNextValue());

    }
    
    

    this->buffer->pushSamples(buffer);
}

//==============================================================================
bool LissajousVSTAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* LissajousVSTAudioProcessor::createEditor()
{
    return new LissajousVSTAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void LissajousVSTAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    if (auto xmlState = parameters.copyState().createXml())
    {
        copyXmlToBinary(*xmlState, destData);
    }
}

void LissajousVSTAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    if (auto xmlState = getXmlFromBinary(data, sizeInBytes))
    {
        parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LissajousVSTAudioProcessor();
}
