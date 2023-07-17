/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

#include "OpenGLComponent.h"
typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
//==============================================================================
/**
*/
class LissajousVSTAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    LissajousVSTAudioProcessorEditor (LissajousVSTAudioProcessor&, juce::AudioProcessorValueTreeState&);
    ~LissajousVSTAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    //void sliderValueChanged(juce::Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    LissajousVSTAudioProcessor& audioProcessor;
    juce::AudioProcessorValueTreeState& valueTreeState;

    juce::Slider prePanSlider;
    juce::Slider postPanSlider;
    std::unique_ptr<SliderAttachment> prePanAttachment;
    std::unique_ptr<SliderAttachment> postPanAttachment;
    //juce::Label panLabel;

    juce::Slider preWidthSlider;
    juce::Slider postWidthSlider;
    std::unique_ptr<SliderAttachment> preWidthAttachment;
    std::unique_ptr<SliderAttachment> postWidthAttachment;
    //juce::Label widthLabel;
    juce::Slider preMidSlider;
    juce::Slider postMidSlider;
    std::unique_ptr<SliderAttachment> preMidAttachment;
    std::unique_ptr<SliderAttachment> postMidAttachment;

    juce::Slider lClipSlider;
    std::unique_ptr<SliderAttachment> lClipAttachment;

    juce::Slider rClipSlider;
    std::unique_ptr<SliderAttachment> rClipAttachment;
    OpenGLComponent openGLComponent;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LissajousVSTAudioProcessorEditor)
};
