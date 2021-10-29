/**
 * jos_freeverb.h
 * Julius Smith
 * October 2021
 * MIT License
 */

/** Freeverb from the faustlibraries distribution (in reverbs.lib)
 *
 */
#ifndef __FREEVERB_H__
#define __FREEVERB_H__

namespace jos {

  //#define SINE_TEST

#include "../FaustModule.h"
#include "../faust-src/faustheadersdir/freeverb.h" // stereo in and out
#if 0
#include "../faust-src/faustheadersdir/zitarev.h" // stereo in and out
#endif

//==============================================================================
/**
    An echo-based delay effect ("artificial reverberation"), providing a virtual acoustic listening space.

    @tags{Effects}
*/

  class Freeverb : public jos::FaustModule
  {
    int mNumInputs;
    int mNumOutputs;

    float mReverbLevel;

    freeverb* freeverbP;
    APIUI* freeverbUIP;

#if 0
    zitarev* zitarevP;
    APIUI* zitarevUIP;
#endif

    void compute(int nframes, float** inputs, float** outputs);

  public:
    //==============================================================================
    /** Creates an instance of Freeverb with the specified number of input and output channels. */
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
      // std::cout << "Using freeverb\n";

#if 0
      zitarevP = new zitarev; // stereo input and output
      zitarevUIP = new APIUI;
      zitarevP->buildUserInterface(zitarevUIP);
      // std::cout << "Using zitarev\n";
#endif

    }

    /** Destructor.

        This will free any memory allocated by Freeverb.
    */
    virtual ~Freeverb() {
      delete freeverbP;
      delete freeverbUIP;
#if 0
      delete zitarevP;
      delete zitarevUIP;
#endif
    }

    int getNumInputs() override { return(mNumInputs); }
    int getNumOutputs() override { return(mNumOutputs); }

    void prepareToPlay(double samplingRateHz, int maxSamplesPerBlock) override {
      DBG("Freeverb: prepareToPlay(" << samplingRateHz << ")");
      jassert(samplingRateHz>0);
      FaustModule::prepareToPlay(samplingRateHz, maxSamplesPerBlock); // common initialization, e.g., sampleRate = samplingRateHz;
      FAUSTFLOAT fs = FAUSTFLOAT(samplingRateHz); // Faust typically uses floats, but may be double or quad

      freeverbP->init(fs); // compression filter parameters depend on sampling rate
      jassert(freeverbP->getNumOutputs() == mNumOutputs);
      int ndx = freeverbUIP->getParamIndex("Wet");
      freeverbUIP->setParamValue(ndx, mReverbLevel);
#if 0
      zitarevP->init(fs); // compression filter parameters depend on sampling rate
      jassert(zitarevP->getNumOutputs() == mNumOutputs);
      int ndx = zitarevUIP->getParamIndex("Wet");
      float zitaLevel = mReverbLevel-1.0f; // range within zitarev is 0 to 1 (our version only)
      zitarevUIP->setParamValue(ndx, zitaLevel);
#endif
    }

    //==============================================================================
    /** Set the reverberation level between 0 (no reverb) to 1 (maximally "wet" reverb) */
    void setReverbLevel(float level) {
      mReverbLevel = level;
    }

    virtual void processBlock (juce::AudioBuffer<float>& audio, juce::MidiBuffer& midi) override;

  }; // Class Freeverb

}; // namespace jos

#endif // __FREEVERB_H__
