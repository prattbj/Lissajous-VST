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
TwoDimensionCompressionAudioProcessorEditor::TwoDimensionCompressionAudioProcessorEditor (TwoDimensionCompressionAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    addAndMakeVisible(openGLComponent);

    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (WIDTH, HEIGHT);
}

TwoDimensionCompressionAudioProcessorEditor::~TwoDimensionCompressionAudioProcessorEditor()
{
}

//==============================================================================
void TwoDimensionCompressionAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    
}

void TwoDimensionCompressionAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    openGLComponent.setBounds(0, 0, WIDTH, HEIGHT);
}
