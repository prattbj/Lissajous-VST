#pragma once
#include "JuceHeader.h"
#include <memory>

using namespace juce;
/*
circular buffer for 2 channel audio

used to communicate between the processor and the openGL component

*/
template <class T>
class CircularBuffer
{
public:
	CircularBuffer(int size)
	{
		bufferSize = size;
		audioBuffer = new AudioBuffer<T>(2, bufferSize);
		writePosition = 0;
	}

	void pushSamples(AudioBuffer<T>& newData)
	{
		for (int i = 0; i < 2; i++)
		{
			const int currentPos = writePosition.get();
			if ((currentPos + newData.getNumSamples()) > bufferSize - 1)
			{
				int numToEdge = bufferSize - currentPos;

				audioBuffer->copyFrom(i, currentPos, newData, i, 0, numToEdge);
				audioBuffer->copyFrom(i, 0, newData, i, 0 + numToEdge, newData.getNumSamples() - numToEdge);
			}
			else
			{
				audioBuffer->copyFrom(i, currentPos, newData, i, 0, newData.getNumSamples());
			}
		}

		writePosition += newData.getNumSamples();
		writePosition = writePosition.get() % bufferSize;
	}

	AudioBuffer<T> getSamples()
	{
		return *audioBuffer;
	}
private:
	int bufferSize;
	 
	AudioBuffer<T> *audioBuffer;
	Atomic<int> writePosition;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CircularBuffer)
};