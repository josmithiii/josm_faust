/*
 * jos_freeverb.h - freeverb from the faustlibraries distribution (in reverbs.lib)
 * Julius Smith
 * October 2021
 * MIT License with LGPL component
 */

//#ifndef __FREEVERB_H__
//#define __FREEVERB_H__

#include "../shared/jos_faust_module.h"

namespace jos
{

//==============================================================================
/**
    Freeverb is a well known free open-source reverb.
    Reference: https://ccrma.stanford.edu/~jos/pasp/Freeverb.html

    \ingroup effects

    @see jos::Zitarev

    @tags{Effects}

*/
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
    Freeverb(int numInChans, int numOutChans) // xtor
      : mNumInputs(numInChans), mNumOutputs(numOutChans)
    {
      if ( mNumInputs < 1 ) {
        std::cerr << "*** Freeverb.h: must have at least one input audio channels\n";
        mNumInputs = 1;
      }
      if ( mNumInputs > 2 ) {
        std::cerr << "*** Freeverb.h: limiting number of audio output channels to 2\n";
        mNumInputs = 2;
      }
#if 1
      std::cout << "Freeverb: constructed for "
                << mNumInputs << " input channels and "
                << mNumOutputs << " output channels with reverb level = "
                << mReverbLevel << "\n";
#endif

      freeverbP = new freeverb; // stereo input and output
      freeverbUIP = new APIUI; // #included in *dsp.h
      freeverbP->buildUserInterface(freeverbUIP);
    }

    /** Destructor. */
    virtual ~Freeverb() {
      delete freeverbP;
      delete freeverbUIP;
    }

    ///@{
    int getNumInputs() override { return(mNumInputs); }
    int getNumOutputs() override { return(mNumOutputs); }
    ///@}

    void prepareToPlay(double samplingRateHz, int maxSamplesPerBlock) override {
      DBG("Freeverb: prepareToPlay(" << samplingRateHz << ")");
      jassert(samplingRateHz>0);
      FaustModule::prepareToPlay(samplingRateHz, maxSamplesPerBlock); // common initialization, e.g., sampleRate = samplingRateHz;
      FAUSTFLOAT fs = FAUSTFLOAT(samplingRateHz); // Faust typically uses floats, but may be double or quad

      freeverbP->init(fs); // compression filter parameters depend on sampling rate
      jassert(freeverbP->getNumOutputs() == mNumOutputs);
      int ndx = freeverbUIP->getParamIndex("Wet");
      freeverbUIP->setParamValue(ndx, mReverbLevel);
    }

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

   \ingroup effects
*/

//==============================================================================

//#endif // __FREEVERB_H__
