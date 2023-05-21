/*
  ==============================================================================

    OpenGLComponent.h
    Created: 05/18/2023
    Author:  prattbj

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OpenGLComponent  : public juce::Component, public juce::OpenGLRenderer
{
public:
    OpenGLComponent();
    ~OpenGLComponent() override;

    void newOpenGLContextCreated() override;
    void renderOpenGL() override;
    void openGLContextClosing() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::OpenGLContext openGLContext;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OpenGLComponent)
};
