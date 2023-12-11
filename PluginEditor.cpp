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

    //Make the plugin look good
    getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::blue);

    addAndMakeVisible(prePanSlider);
    prePanSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    prePanSlider.setRange(-1.0f, 1.0f);
    prePanAttachment.reset(new SliderAttachment(vts, "prePanSlider", prePanSlider));
    prePanSlider.setValue(*vts.getRawParameterValue("prePanSlider"));
    prePanSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

    
    
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

    addAndMakeVisible(lRevClipSlider);
    lRevClipSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    lRevClipSlider.setRange(0.0f, 1.0f);
    lRevClipAttachment.reset(new SliderAttachment(vts, "lRevClipSlider", lRevClipSlider));
    lRevClipSlider.setValue(*vts.getRawParameterValue("lRevClipSlider"));
    lRevClipSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

    addAndMakeVisible(rRevClipSlider);
    rRevClipSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    rRevClipSlider.setRange(0.0f, 1.0f);
    rRevClipAttachment.reset(new SliderAttachment(vts, "rRevClipSlider", rRevClipSlider));
    rRevClipSlider.setValue(*vts.getRawParameterValue("rRevClipSlider"));
    rRevClipSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

    addAndMakeVisible(lMoveSlider);
    lMoveSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    lMoveSlider.setRange(-1.0f, 1.0f);
    lMoveAttachment.reset(new SliderAttachment(vts, "lMoveSlider", lMoveSlider));
    lMoveSlider.setValue(*vts.getRawParameterValue("lMoveSlider"));
    lMoveSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

    addAndMakeVisible(rMoveSlider);
    rMoveSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    rMoveSlider.setRange(-1.0f, 1.0f);
    rMoveAttachment.reset(new SliderAttachment(vts, "rMoveSlider", rMoveSlider));
    rMoveSlider.setValue(*vts.getRawParameterValue("rMoveSlider"));
    rMoveSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

    addAndMakeVisible(lDistortSlider);
    lDistortSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    lDistortSlider.setRange(-1.0f, 1.0f);
    lDistortAttachment.reset(new SliderAttachment(vts, "lDistortSlider", lDistortSlider));
    lDistortSlider.setValue(*vts.getRawParameterValue("lDistortSlider"));
    lDistortSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

    addAndMakeVisible(rDistortSlider);
    rDistortSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    rDistortSlider.setRange(-1.0f, 1.0f);
    rDistortAttachment.reset(new SliderAttachment(vts, "rDistortSlider", rDistortSlider));
    rDistortSlider.setValue(*vts.getRawParameterValue("rDistortSlider"));
    rDistortSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

    addAndMakeVisible(rotaterSlider);
    rotaterSlider.setRange(-180.0f, 180.0f);
    rotateAttachment.reset(new SliderAttachment(vts, "rotaterSlider", rotaterSlider));
    rotaterSlider.setValue(*vts.getRawParameterValue("rotaterSlider"));
    rotaterSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

    addAndMakeVisible(postRotaterSlider);
    postRotaterSlider.setRange(-180.0f, 180.0f);
    postRotateAttachment.reset(new SliderAttachment(vts, "postRotaterSlider", postRotaterSlider));
    postRotaterSlider.setValue(*vts.getRawParameterValue("postRotaterSlider"));
    postRotaterSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    
    //Labels
    
    addAndMakeVisible(prePanLabel);
    prePanLabel.setText("Pan", NotificationType::dontSendNotification);
    prePanLabel.setFont(juce::Font(16.0f));
    prePanLabel.setColour(juce::Label::textColourId, juce::Colours::aqua);
    prePanLabel.setJustificationType(juce::Justification::centred);
    prePanLabel.attachToComponent(&prePanSlider, false);

    addAndMakeVisible(preMidLabel);
    preMidLabel.setText("Mid", NotificationType::dontSendNotification);
    preMidLabel.setFont(juce::Font(16.0f));
    preMidLabel.setColour(juce::Label::textColourId, juce::Colours::aqua);
    preMidLabel.setJustificationType(juce::Justification::centred);
    preMidLabel.attachToComponent(&preMidSlider, false);

    addAndMakeVisible(preWidthLabel);
    preWidthLabel.setText("Width", NotificationType::dontSendNotification);
    preWidthLabel.setFont(juce::Font(16.0f));
    preWidthLabel.setColour(juce::Label::textColourId, juce::Colours::aqua);
    preWidthLabel.setJustificationType(juce::Justification::centred);
    preWidthLabel.attachToComponent(&preWidthSlider, false);

    addAndMakeVisible(lDistortLabel);
    lDistortLabel.setText("Distort", NotificationType::dontSendNotification);
    lDistortLabel.setFont(juce::Font(16.0f));
    lDistortLabel.setColour(juce::Label::textColourId, juce::Colours::aqua);
    lDistortLabel.setJustificationType(juce::Justification::centred);
    
    addAndMakeVisible(rDistortLabel);
    rDistortLabel.setText("Distort", NotificationType::dontSendNotification);
    rDistortLabel.setFont(juce::Font(16.0f));
    rDistortLabel.setColour(juce::Label::textColourId, juce::Colours::aqua);
    rDistortLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(rTranslateLabel);
    rTranslateLabel.setText("Translate", NotificationType::dontSendNotification);
    rTranslateLabel.setFont(juce::Font(16.0f));
    rTranslateLabel.setColour(juce::Label::textColourId, juce::Colours::aqua);
    rTranslateLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(lTranslateLabel);
    lTranslateLabel.setText("Translate", NotificationType::dontSendNotification);
    lTranslateLabel.setFont(juce::Font(16.0f));
    lTranslateLabel.setColour(juce::Label::textColourId, juce::Colours::aqua);
    lTranslateLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(lReverseClipLabel);
    lReverseClipLabel.setText("Expand", NotificationType::dontSendNotification);
    lReverseClipLabel.setFont(juce::Font(16.0f));
    lReverseClipLabel.setColour(juce::Label::textColourId, juce::Colours::aqua);
    lReverseClipLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(rReverseClipLabel);
    rReverseClipLabel.setText("Expand", NotificationType::dontSendNotification);
    rReverseClipLabel.setFont(juce::Font(16.0f));
    rReverseClipLabel.setColour(juce::Label::textColourId, juce::Colours::aqua);
    rReverseClipLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(rClipLabel);
    rClipLabel.setText("Clip", NotificationType::dontSendNotification);
    rClipLabel.setFont(juce::Font(16.0f));
    rClipLabel.setColour(juce::Label::textColourId, juce::Colours::aqua);
    rClipLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(lClipLabel);
    lClipLabel.setText("Clip", NotificationType::dontSendNotification);
    lClipLabel.setFont(juce::Font(16.0f));
    lClipLabel.setColour(juce::Label::textColourId, juce::Colours::aqua);
    lClipLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(postPanLabel);
    postPanLabel.setText("Pan", NotificationType::dontSendNotification);
    postPanLabel.setFont(juce::Font(16.0f));
    postPanLabel.setColour(juce::Label::textColourId, juce::Colours::aqua);
    postPanLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(postMidLabel);
    postMidLabel.setText("Mid", NotificationType::dontSendNotification);
    postMidLabel.setFont(juce::Font(16.0f));
    postMidLabel.setColour(juce::Label::textColourId, juce::Colours::aqua);
    postMidLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(postWidthLabel);
    postWidthLabel.setText("Width", NotificationType::dontSendNotification);
    postWidthLabel.setFont(juce::Font(16.0f));
    postWidthLabel.setColour(juce::Label::textColourId, juce::Colours::aqua);
    postWidthLabel.setJustificationType(juce::Justification::centred);

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
    g.fillAll(Colours::black);
    g.drawImageAt(ImageCache::getFromMemory(BinaryData::bckgrnd_png, BinaryData::bckgrnd_pngSize), 0, 0);

   
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

    rotaterSlider.setBounds(WIDTH * 1 / 3, HEIGHT / 5, WIDTH * 1 / 3, 20);

    //Side sliders
    lClipSlider.setBounds(WIDTH * 4 / 18 - 10, HEIGHT / 4, 20, HEIGHT / 2);
    lClipLabel.setBounds(WIDTH * 4 / 18 - 40, HEIGHT / 5, 80, 20);

    rClipSlider.setBounds(WIDTH * 14 / 18 - 10, HEIGHT / 4, 20, HEIGHT / 2);
    rClipLabel.setBounds(WIDTH * 14 / 18 - 40, HEIGHT / 5, 80, 20);

    lRevClipSlider.setBounds(WIDTH * 3 / 18 - 10, HEIGHT / 4, 20, HEIGHT / 2);
    lReverseClipLabel.setBounds(WIDTH * 3 / 18 - 40, HEIGHT * 3 / 4, 80, 20);

    rRevClipSlider.setBounds(WIDTH * 15 / 18 - 10, HEIGHT / 4, 20, HEIGHT / 2);
    rReverseClipLabel.setBounds(WIDTH * 15 / 18 - 40, HEIGHT * 3/ 4, 80, 20);

    lMoveSlider.setBounds(WIDTH * 1/ 18 - 10, HEIGHT / 4, 20, HEIGHT / 2);
    lTranslateLabel.setBounds(WIDTH * 1 / 18 - 40, HEIGHT * 3 / 4, 80, 20);

    rMoveSlider.setBounds(WIDTH * 17 / 18 - 10, HEIGHT / 4, 20, HEIGHT / 2);
    rTranslateLabel.setBounds(WIDTH * 17 / 18 - 40, HEIGHT * 3 / 4, 80, 20);

    lDistortSlider.setBounds(WIDTH * 2 / 18 - 10, HEIGHT / 4, 20, HEIGHT / 2);
    lDistortLabel.setBounds(WIDTH * 2 / 18 - 40, HEIGHT / 5, 80, 20);

    rDistortSlider.setBounds(WIDTH * 16 / 18 - 10, HEIGHT / 4, 20, HEIGHT / 2);
    rDistortLabel.setBounds(WIDTH * 16 / 18 - 40, HEIGHT / 5, 80, 20);
    //Bottom sliders
    postPanSlider.setBounds(WIDTH / 2 - 40, HEIGHT * 4 / 5, 80, 80);
    postMidSlider.setBounds(WIDTH / 2 - 120, HEIGHT * 4 / 5, 80, 80);
    postWidthSlider.setBounds(WIDTH / 2 + 40, HEIGHT * 4 / 5, 80, 80);

    postPanLabel.setBounds(WIDTH / 2 - 40, HEIGHT * 17 / 18, 80, 20);

    postMidLabel.setBounds(WIDTH / 2 - 120, HEIGHT * 17 / 18, 80, 20);

    postWidthLabel.setBounds(WIDTH / 2 + 40, HEIGHT * 17 / 18, 80, 20);


    postRotaterSlider.setBounds(WIDTH * 1 / 3, HEIGHT * 4 / 5 -20, WIDTH * 1 / 3, 20);
}
