
#pragma once

/*
This is where we will implement the audio processing functions.

This way, we don't fill up our processBlock function with a ton of calculations.

Also, we can reuse this for future projects (or people on GitHub can use this too!).


*/

#define _USE_MATH_DEFINES
#include <math.h>
#include <JuceHeader.h>
namespace Processing
{
    //Pan to the left or right (we should change this to take in both channel's data pointers rather than call it twice in the process block. will do later.)
	void pan(int channel, float * channelData, int sample, float amount)
	{
        
        if (channel == 0)
            channelData[sample] = (amount > 0 ? channelData[sample] - (channelData[sample] * amount) : channelData[sample]);
        else
            channelData[sample] = (amount < 0 ? channelData[sample] - (channelData[sample] * -amount) : channelData[sample]);
        
	}

    //Widen the sound.
    //thanks musicdsp.org
    void widen(float* leftChannel, float* rightChannel, int sample, float amount)
    {
        float scale = amount * 0.5f;
        
        float m = (leftChannel[sample] + rightChannel[sample]) * 0.5f;
        float s = (-leftChannel[sample] + rightChannel[sample]) * scale;

        leftChannel[sample] = m - s;
        rightChannel[sample] = m + s;
        
    }

    //Increases the volume of the mid audio
    void midBoost(float* leftChannel, float* rightChannel, int sample, float amount)
    {
        float scale = amount * 0.5f;
        
        float m = (leftChannel[sample] + rightChannel[sample]) * scale;
        float s = (-leftChannel[sample] + rightChannel[sample]) * 0.5f;

        leftChannel[sample] = m - s;
        rightChannel[sample] = m + s;
        
    }

    //Increases or decreases volume
    void gain(float* channelData, float amount, int sample)
    {
        
        channelData[sample] *= amount;
        
    }

    //Prevents data from going above a specified value
    void clip(float* channelData, int sample, float amount)
    {
        if (amount < 1.0f)
        {
            channelData[sample] = channelData[sample] > amount ? amount : channelData[sample];
            channelData[sample] = channelData[sample] < -amount ? -amount : channelData[sample];
        }
        
    }

    //Prevents the audio signal from going below a specified value
    void revClip(float* channelData, int sample, float amount)
    {
        channelData[sample] = (channelData[sample] < amount && channelData[sample] > 0) ? amount : channelData[sample];
        channelData[sample] = (channelData[sample] > -amount && channelData[sample] < 0) ? -amount : channelData[sample];

    }

    //Rotates the signal around
    void rotate(float* leftChannel, float* rightChannel, int sample, float amount)
    {
        float amountInRad = amount;
        float right = rightChannel[sample];
        float left = leftChannel[sample];
        leftChannel[sample] = right * sin(amountInRad) + left * cos(amountInRad);
        rightChannel[sample] = right * cos(amountInRad) - left * sin(amountInRad);

    }

    //Distorts the audio signal using a simple soft clip distortion algorithm combined with a certain amount of the original signal
    void distort(float* channelData, int sample, float amount)
    {
        channelData[sample] = channelData[sample] / (1 + amount) + atan(channelData[sample] * (amount * 10) /( 2 * M_PI));

    }

    //Moves the signal around so that other algorithms can be applied assymetrically
    void translate(float* channelData, int sample, float amount)
    {
        channelData[sample] = channelData[sample] + amount;
    }
};