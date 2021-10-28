#pragma once

#include <JuceHeader.h>

//namespace jos {

  class FaustModule {
    // Contains any common code shared by all Faust modules.

    double sampleRate = 0;
    int blockSize = 0;

  protected:

    bool inited = false;

  public:

    FaustModule() {}
    virtual ~FaustModule() {}

    // standard API:

    virtual int getNumInputs() = 0;
    virtual int getNumOutputs() = 0;
    virtual void prepareToPlay(double samplingRateHz, int maxSamplesPerBlock) { sampleRate = samplingRateHz; blockSize = maxSamplesPerBlock; inited = true; }
    virtual void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) = 0;
    virtual void releaseResources() { inited = false; }

  };

//};
