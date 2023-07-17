
#pragma once

/*
This is where we will implement the audio processing functions.

This way, we don't fill up our processBlock function with a ton of calculations.

Also, we can reuse this for future projects (or people on GitHub can use this too!).


*/
namespace Processing
{
    //Pan to the left or right (we should change this to take in both channel's data pointers rather than call it twice in the process block. will do later.)
	void pan(int channel, float * channelData, int numSamples, float amount)
	{
        for (int sample = 0; sample < numSamples; ++sample)
        {
            if (channel == 0)
                channelData[sample] = (amount > 0 ? channelData[sample] - (channelData[sample] * amount) : channelData[sample]);
            else
                channelData[sample] = (amount < 0 ? channelData[sample] - (channelData[sample] * -amount) : channelData[sample]);
        }
	}

    //Widen the sound.
    //thanks musicdsp.org
    void widen(float* leftChannel, float* rightChannel, int numSamples, float amount)
    {
        float scale = amount * 0.5f;
        for (int sample = 0; sample < numSamples; ++sample)
        {
            float m = (leftChannel[sample] + rightChannel[sample]) * 0.5f;
            float s = (-leftChannel[sample] + rightChannel[sample]) * scale;

            leftChannel[sample] = m - s;
            rightChannel[sample] = m + s;
        }
    }

    //Increases the volume of the mid audio
    void midBoost(float* leftChannel, float* rightChannel, int numSamples, float amount)
    {
        float scale = amount * 0.5f;
        for (int sample = 0; sample < numSamples; ++sample)
        {
            float m = (leftChannel[sample] + rightChannel[sample]) * scale;
            float s = (-leftChannel[sample] + rightChannel[sample]) * 0.5f;

            leftChannel[sample] = m - s;
            rightChannel[sample] = m + s;
        }
    }

    //Increases or decreases volume
    void scale(float* channelData, float amount, int numSamples)
    {
        for (int sample = 0; sample < numSamples; ++sample)
        {
            channelData[sample] *= amount;
        }
    }

    //Prevents data from going above a specified value
    void clip(float* channelData, int numSamples, float amount)
    {
        for (int sample = 0; sample < numSamples; ++sample)
        {
            channelData[sample] = channelData[sample] > amount ? amount : channelData[sample];
            channelData[sample] = channelData[sample] < -amount ? -amount : channelData[sample];
        }
    }
};