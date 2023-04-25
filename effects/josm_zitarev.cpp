/*
 * josm_zitarev.cpp
 * Julius Smith
 * October 2021
 * BSD License with LGPL component that is easily rewritten if need be
 */

#include "josm_zitarev.h"

namespace josm {

#include "../faust-src/faustheadersdir/zitarev.h" // stereo in and out

  Zitarev::Zitarev(int numInChans, int numOutChans) // xtor
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
  }

  Zitarev::~Zitarev() { }

  void Zitarev::prepareToPlay(double samplingRateHz, int maxSamplesPerBlock) {
    DBG("Zitarev: prepareToPlay(" << samplingRateHz << ")");
    jassert(samplingRateHz>0);
    FaustModule::prepareToPlay(samplingRateHz, maxSamplesPerBlock); // common initialization, e.g., sampleRate = samplingRateHz;
    FAUSTFLOAT fs = FAUSTFLOAT(samplingRateHz); // Faust typically uses floats, but may be double or quad

    zitarevP.reset(new zitarev); // stereo input and output
    zitarevUIP.reset(new APIUI); // #included in *dsp.h
    zitarevP->buildUserInterface(zitarevUIP.get());
    zitarevP->init(fs); // compression filter parameters depend on sampling rate
    jassert(zitarevP->getNumOutputs() == mNumOutputs);
    int ndx = zitarevUIP->getParamIndex("Wet");
    zitarevUIP->setParamValue(ndx, mReverbLevel);
  }

  void Zitarev::releaseResources() {
  }

  void Zitarev::processBlock (juce::AudioBuffer<float>& audioBuffer, juce::MidiBuffer& midi)
  {
    if (not inited) { return; }
    int numSamples = audioBuffer.getNumSamples();
    int numChans = audioBuffer.getNumChannels();
    jassert(getNumInputs() <= numChans);
    jassert(getNumOutputs() <= numChans);
    auto bufPointersFaust = josm::getBufferPointersFaust<float>(audioBuffer);
    compute(numSamples, bufPointersFaust.get(), bufPointersFaust.get());
  }

  void Zitarev::compute(int nframes, float** inputs, float** outputs)
  {
    jassert(inited);
    if (mReverbLevel > 0.0f) {
      zitarevP->compute(nframes, inputs, outputs);
    } // else in-place processing means we're done
  }
} // namespace josm
