/**
 * \file Freeverb.cpp
 * \author Julius Smith
 * \date October 2021
 */

#include "Freeverb.h"

#include <iostream>

namespace jos {

  void Freeverb::processBlock (juce::AudioBuffer<float>& audioBuffer, juce::MidiBuffer& midi)
  {
    int numSamples = audioBuffer.getNumSamples();
    jassert(getNumInputs() <= audioBuffer.getNumChannels());
    jassert(getNumOutputs() <= audioBuffer.getNumChannels());
    float** writePointers = audioBuffer.getArrayOfWritePointers();
    float** readPointers { writePointers }; // we process in place - COMPILE FAUST WITH -inpl OPTION!
    compute(numSamples, readPointers, writePointers);
  }
  
  //*******************************************************************************
  void Freeverb::compute(int nframes, float** inputs, float** outputs)
  {
    jassert(inited);
    if (mReverbLevel > 0.0f) {
      freeverbP->compute(nframes, inputs, outputs);
    } // else in-place processing means we're done
#if 0
    if (mReverbLevel > 0.0f) {
      zitarevP->compute(nframes, inputs, outputs);
    } // else in-place processing means we're done
#endif
  }
};
