/*
  ==============================================================================

    OpenGLComponent.cpp
    Created: 05/18/2023
    Author:  prattbj

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OpenGLComponent.h"

using namespace juce::gl;
//==============================================================================
OpenGLComponent::OpenGLComponent(LissajousVSTAudioProcessor* audioProcessor)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setOpaque(true);
    this->audioProcessor = audioProcessor;

    openGLContext.setRenderer(this);

    openGLContext.setContinuousRepainting(true);

    openGLContext.attachTo(*this);
    ibo = GLuint();
    vbo = GLuint();
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
    // Generate 1 buffer, using our vbo variable to store its ID.
    openGLContext.extensions.glGenBuffers(1, &vbo);

    // Generate 1 more buffer, this time using our IBO variable.
    openGLContext.extensions.glGenBuffers(1, &ibo);
}
void OpenGLComponent::renderOpenGL() 
{
    const float width = static_cast<float>(getWidth());
    const float height = static_cast<float>(getHeight());

    auto buffer = audioProcessor->getBuffer();
    juce::OpenGLHelpers::clear(juce::Colours::black);
    

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
    glOrtho(0, width, 0, height, -1, 1);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glLineWidth(2.0f);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor3f(.5f, .0f, .5f);

    glBegin(GL_LINE_STRIP);
    int numChannels = buffer.getNumChannels();
    int numSamples = buffer.getNumSamples();

    float* channelX = buffer.getWritePointer(0);
    float* channelY = buffer.getWritePointer(1);
    // Draw the audio data
    for (int sample = 0; sample < numSamples; ++sample)
    {
        
        float audioX = channelX[sample];
        float audioY = channelY[sample];
        // Multiply by .7071 = sin(45 deg) to scale since we rotate
        // Rotating cuts off the drawing if the x and y values are 
        // too high, so scaling down a little bit makes it so that 
        // the audio is only cut off if the values are greater than 1/-1
        // (at the same time)
        float xPos = audioX * width * 0.5f * 0.7071 + width * 0.5f;
        float yPos = audioY * height * 0.5f * 0.7071 + height * 0.5f;
        
        glVertex2f(xPos, yPos);
        
    }
    glEnd();

    glDisable(GL_BLEND);

    // Calculate the scaling factor
    float scaleFactor = 0.7071f;

    // Calculate the scaled width and height
    float scaledWidth = width * scaleFactor;
    float scaledHeight = height * scaleFactor;

    // Calculate the scaled center position
    float centerX = width * 0.5f;
    float centerY = height * 0.5f;
    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_TRIANGLES);
    //Draw 4 triangles to fill in the outside of the OpenGL context. That way,
    //audio signal doesn't escape the blue diamond
    glVertex2f(centerX - scaledWidth * 0.5f, centerY - scaledHeight * 0.5f);
    glVertex2f(centerX + scaledWidth * 0.5f, centerY - scaledHeight * 0.5f);
    glVertex2f(0, centerY - scaledHeight * 2.0f);

    glVertex2f(centerX + scaledWidth * 0.5f, centerY - scaledHeight * 0.5f);
    glVertex2f(centerX + scaledWidth * 0.5f, centerY + scaledHeight * 0.5f);
    glVertex2f(centerX + scaledWidth * 2.0f, 0);

    glVertex2f(centerX + scaledWidth * 0.5f, centerY + scaledHeight * 0.5f);
    glVertex2f(centerX - scaledWidth * 0.5f, centerY + scaledHeight * 0.5f);
    glVertex2f(0, centerY + scaledHeight * 2.0f);

    glVertex2f(centerX - scaledWidth * 0.5f, centerY + scaledHeight * 0.5f);
    glVertex2f(centerX - scaledWidth * 0.5f, centerY - scaledHeight * 0.5f);
    glVertex2f(centerX - scaledWidth * 2.0f, 0);
    glEnd();


    glColor3f(0.0f, 0.0f, 1.0f);

    // Blue diamond. Draw this after the 4 triangles so that it is on top of 
    // their edges.
    glBegin(GL_LINE_LOOP);
    glVertex2f(centerX - scaledWidth * 0.5f, centerY - scaledHeight * 0.5f);
    glVertex2f(centerX + scaledWidth * 0.5f, centerY - scaledHeight * 0.5f);
    glVertex2f(centerX + scaledWidth * 0.5f, centerY + scaledHeight * 0.5f);
    glVertex2f(centerX - scaledWidth * 0.5f, centerY + scaledHeight * 0.5f);
    glEnd();

   
}
void OpenGLComponent::openGLContextClosing()
{

}
