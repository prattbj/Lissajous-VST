/*
  ==============================================================================

    OpenGLComponent.cpp
    Created: 05/18/2023
    Author:  prattbj

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OpenGLComponent.h"

//==============================================================================
OpenGLComponent::OpenGLComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setOpaque(true);

    openGLContext.setRenderer(this);

    openGLContext.setContinuousRepainting(true);

    openGLContext.attachTo(*this);
}

OpenGLComponent::~OpenGLComponent()
{
    openGLContext.detach();
}

void OpenGLComponent::paint (juce::Graphics& g)
{
    
}

void OpenGLComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void OpenGLComponent::newOpenGLContextCreated() 
{

}
void OpenGLComponent::renderOpenGL() 
{

}
void OpenGLComponent::openGLContextClosing()
{

}