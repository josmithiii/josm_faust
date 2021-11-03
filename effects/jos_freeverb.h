/*
 * jos_freeverb.h - freeverb from the faustlibraries distribution (in reverbs.lib)
 * Julius Smith
 * October 2021
 * MIT License with LGPL component
 */

//#ifndef __FREEVERB_H__
//#define __FREEVERB_H__

//#include "../shared/jos_faust_module.h"

namespace jos
{

//==============================================================================
/**
    Freeverb is a well known free open-source reverb.
    Reference: https://ccrma.stanford.edu/~jos/pasp/Freeverb.html

    @see jos::Zitarev

    @tags{Effects}

*/class freeverb;
  class APIUI;

  class JUCE_API Freeverb : public jos::FaustModule
  {
    int mNumInputs;
    int mNumOutputs;

    float mReverbLevel;

    freeverb* freeverbP;
    APIUI* freeverbUIP;

    void compute(int nframes, float** inputs, float** outputs);

  public:
    //==============================================================================
    /** 
        Creates an instance of Freeverb with the specified number of input and output channels. 

        @param numInChans number of input channels
        @param numOutChans number of output channels

        @see Zitarev

        @tags{effects}
     */
    Freeverb(int numInChans, int numOutChans); // xtor

    /** Destructor. */
    virtual ~Freeverb();

    ///@{
    int getNumInputs() override { return(mNumInputs); }
    int getNumOutputs() override { return(mNumOutputs); }
    ///@}

    void prepareToPlay(double samplingRateHz, int maxSamplesPerBlock) override;

    //==============================================================================
    /** Set the reverberation level between 0 (no reverb) to 1 (maximally "wet" reverb) */
    void setReverbLevel(float level) {
      mReverbLevel = level;
    }

    virtual void processBlock (juce::AudioBuffer<float>& audio, juce::MidiBuffer& midi) override;

  }; // Class Freeverb

} // namespace jos

/**
   \file jos_freeverb.h

   C++ wrapper for re.freeverb in the faustlibraries distribution (reverbs.lib).

*/

//==============================================================================

//#endif // __FREEVERB_H__
