/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/
#define WIDTH 720
#define HEIGHT 480
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LissajousVSTAudioProcessorEditor::LissajousVSTAudioProcessorEditor(LissajousVSTAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor(&p), audioProcessor(p), openGLComponent(&audioProcessor), valueTreeState(vts)
{
    addAndMakeVisible(openGLComponent);

    addAndMakeVisible(prePanSlider);
    prePanSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    prePanSlider.setRange(-1.0f, 1.0f);
    prePanAttachment.reset(new SliderAttachment(vts, "prePanSlider", prePanSlider));
    prePanSlider.setValue(*vts.getRawParameterValue("prePanSlider"));
    prePanSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

    //addAndMakeVisible(panLabel);
    //panLabel.setText("Pan", NotificationType::dontSendNotification);
    
    addAndMakeVisible(postPanSlider);
    postPanSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    postPanSlider.setRange(-1.0f, 1.0f);
    postPanAttachment.reset(new SliderAttachment(vts, "postPanSlider", postPanSlider));
    postPanSlider.setValue(*vts.getRawParameterValue("postPanSlider"));
    postPanSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    
    addAndMakeVisible(preWidthSlider);
    preWidthSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    preWidthSlider.setRange(0.0f, 2.0f);
    preWidthAttachment.reset(new SliderAttachment(vts, "preWidthSlider", preWidthSlider));
    preWidthSlider.setValue(*vts.getRawParameterValue("preWidthSlider"));
    preWidthSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

    addAndMakeVisible(postWidthSlider);
    postWidthSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    postWidthSlider.setRange(0.0f, 2.0f);
    postWidthAttachment.reset(new SliderAttachment(vts, "postWidthSlider", postWidthSlider));
    postWidthSlider.setValue(*vts.getRawParameterValue("postWidthSlider"));
    postWidthSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

    addAndMakeVisible(preMidSlider);
    preMidSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    preMidSlider.setRange(0.0f, 2.0f);
    preMidAttachment.reset(new SliderAttachment(vts, "preMidSlider", preMidSlider));
    preMidSlider.setValue(*vts.getRawParameterValue("preMidSlider"));
    preMidSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

    addAndMakeVisible(postMidSlider);
    postMidSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    postMidSlider.setRange(0.0f, 2.0f);
    postMidAttachment.reset(new SliderAttachment(vts, "postMidSlider", postMidSlider));
    postMidSlider.setValue(*vts.getRawParameterValue("postMidSlider"));
    postMidSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

    //addAndMakeVisible(widthLabel);
    //widthLabel.setText("Width", NotificationType::dontSendNotification);
    addAndMakeVisible(lClipSlider);
    lClipSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    lClipSlider.setRange(0.0f, 1.0f);
    lClipAttachment.reset(new SliderAttachment(vts, "lClipSlider", lClipSlider));
    lClipSlider.setValue(*vts.getRawParameterValue("lClipSlider"));
    lClipSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

    addAndMakeVisible(rClipSlider);
    rClipSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    rClipSlider.setRange(0.0f, 1.0f);
    rClipAttachment.reset(new SliderAttachment(vts, "rClipSlider", rClipSlider));
    rClipSlider.setValue(*vts.getRawParameterValue("rClipSlider"));
    rClipSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);


    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(WIDTH, HEIGHT);
}

LissajousVSTAudioProcessorEditor::~LissajousVSTAudioProcessorEditor()
{
}

//==============================================================================
void LissajousVSTAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    
}

void LissajousVSTAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    openGLComponent.setBounds(WIDTH * 1 / 3, HEIGHT / 4, WIDTH * 1 / 3, HEIGHT / 2);

    
    //Top sliders
    prePanSlider.setBounds(WIDTH / 2 - 40, HEIGHT * 1 / 20, 80, 80);
    preMidSlider.setBounds(WIDTH / 2 - 120, HEIGHT * 1 / 20, 80, 80);
    preWidthSlider.setBounds(WIDTH / 2 + 40, HEIGHT * 1 / 20, 80, 80);

    //Side sliders
    lClipSlider.setBounds(WIDTH / 6, HEIGHT / 5, 20, HEIGHT / 2);
    rClipSlider.setBounds(WIDTH * 5 / 6, HEIGHT / 5, 20, HEIGHT / 2);

    //Bottom sliders
    postPanSlider.setBounds(WIDTH / 2 - 40, HEIGHT * 4 / 5, 80, 80);
    postMidSlider.setBounds(WIDTH / 2 - 120, HEIGHT * 4 / 5, 80, 80);
    postWidthSlider.setBounds(WIDTH / 2 + 40, HEIGHT * 4 / 5, 80, 80);
}

