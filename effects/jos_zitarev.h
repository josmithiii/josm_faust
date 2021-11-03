/*
 * jos_zitarev.h - zitarev from the faustlibraries distribution (in reverbs.lib)
 * Julius Smith
 * October 2021
 * MIT License with LGPL component
 */

#ifndef __ZITAREV_H__
#define __ZITAREV_H__

namespace jos {

#include "../shared/jos_faust_module.h"
#include "../faust-src/faustheadersdir/zitarev.h" // stereo in and out

//==============================================================================
/**
    Zitarev is a rich artificial reverberator developed by Fons Adriaensen for pipe organ

    Reference: https://ccrma.stanford.edu/~jos/pasp/Zita_Rev1.html

    @see jos::Freeverb

    @tags{Effects}
 */

  class JUCE_API Zitarev : public jos::FaustModule
  {
    int mNumInputs;
    int mNumOutputs;

    float mReverbLevel;

    zitarev* zitarevP;
    APIUI* zitarevUIP;

    void compute(int nframes, float** inputs, float** outputs);

  public:
    //==============================================================================
    /** Constructor: Creates an instance of Zitarev with the specified number of input and output channels. */
    Zitarev(int numInChans, int numOutChans) // xtor
      : mNumInputs(numInChans), mNumOutputs(numOutChans)
    {
      if ( mNumInputs < 1 ) {
        std::cerr << "*** Zitarev.h: must have at least one input audio channels\n";
        mNumInputs = 1;
      }
      if ( mNumInputs > 2 ) {
        std::cerr << "*** Zitarev.h: limiting number of audio output channels to 2\n";
        mNumInputs = 2;
      }
#if 1
      std::cout << "Zitarev: constructed for "
                << mNumInputs << " input channels and "
                << mNumOutputs << " output channels with reverb level = "
                << mReverbLevel << "\n";
#endif

      zitarevP = new zitarev; // stereo input and output
      zitarevUIP = new APIUI; // #included in *dsp.h
      zitarevP->buildUserInterface(zitarevUIP);
    }

    /** Destructor. */
    virtual ~Zitarev() {
      delete zitarevP;
      delete zitarevUIP;
    }

    int getNumInputs() override { return(mNumInputs); }
    int getNumOutputs() override { return(mNumOutputs); }

    void prepareToPlay(double samplingRateHz, int maxSamplesPerBlock) override {
      DBG("Zitarev: prepareToPlay(" << samplingRateHz << ")");
      jassert(samplingRateHz>0);
      FaustModule::prepareToPlay(samplingRateHz, maxSamplesPerBlock); // common initialization, e.g., sampleRate = samplingRateHz;
      FAUSTFLOAT fs = FAUSTFLOAT(samplingRateHz); // Faust typically uses floats, but may be double or quad

      zitarevP->init(fs); // compression filter parameters depend on sampling rate
      jassert(zitarevP->getNumOutputs() == mNumOutputs);
      int ndx = zitarevUIP->getParamIndex("Wet");
      zitarevUIP->setParamValue(ndx, mReverbLevel);
    }

    //==============================================================================
    /** Set the reverberation level between 0 (no reverb) to 1 (maximally "wet" reverb) */
    void setReverbLevel(float level) {
      mReverbLevel = level;
    }

    virtual void processBlock (juce::AudioBuffer<float>& audio, juce::MidiBuffer& midi) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Zitarev)

  }; // Class Zitarev

} // namespace jos

/**
   \file jos_zitarev.h

   C++ wrapper for re.zita_rev1 in the faustlibraries distribution (reverbs.lib).

*/

#endif // __ZITAREV_H__
