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

    

    juce::Slider rotaterSlider;
    std::unique_ptr<SliderAttachment> rotateAttachment;
    juce::Slider postRotaterSlider;
    std::unique_ptr<SliderAttachment> postRotateAttachment;

    juce::Slider preWidthSlider;
    juce::Slider postWidthSlider;
    std::unique_ptr<SliderAttachment> preWidthAttachment;
    std::unique_ptr<SliderAttachment> postWidthAttachment;
    
    juce::Slider preMidSlider;
    juce::Slider postMidSlider;
    std::unique_ptr<SliderAttachment> preMidAttachment;
    std::unique_ptr<SliderAttachment> postMidAttachment;

    juce::Slider lClipSlider;
    std::unique_ptr<SliderAttachment> lClipAttachment;
    
    juce::Slider rClipSlider;
    std::unique_ptr<SliderAttachment> rClipAttachment;
    

    juce::Slider lRevClipSlider;
    std::unique_ptr<SliderAttachment> lRevClipAttachment;

    juce::Slider rRevClipSlider;
    std::unique_ptr<SliderAttachment> rRevClipAttachment;

    OpenGLComponent openGLComponent;
    juce::Slider lMoveSlider;
    std::unique_ptr<SliderAttachment> lMoveAttachment;

    juce::Slider rMoveSlider;
    std::unique_ptr<SliderAttachment> rMoveAttachment;

    juce::Slider lDistortSlider;
    std::unique_ptr<SliderAttachment> lDistortAttachment;

    juce::Slider rDistortSlider;
    std::unique_ptr<SliderAttachment> rDistortAttachment;

    juce::Label prePanLabel;
    juce::Label postPanLabel;
    juce::Label preMidLabel;
    juce::Label postMidLabel;
    juce::Label preWidthLabel;
    juce::Label postWidthLabel;
    juce::Label lClipLabel;
    juce::Label rClipLabel;
    juce::Label lDistortLabel;
    juce::Label rDistortLabel;
    juce::Label lTranslateLabel;
    juce::Label rTranslateLabel;
    juce::Label lReverseClipLabel;
    juce::Label rReverseClipLabel;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LissajousVSTAudioProcessorEditor)
};
