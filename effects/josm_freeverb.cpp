/*
 * josm_freeverb.cpp
 * Julius Smith
 * October 2021
 * BSD License with LGPL component that is easily rewritten if need be
 */

#include "josm_freeverb.h"

namespace josm {

#include "../faust-src/faustheadersdir/freeverb.h" // stereo in and out

  Freeverb::Freeverb(int numInChans, int numOutChans) // xtor
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
  }

  Freeverb::~Freeverb() { }

  void Freeverb::prepareToPlay(double samplingRateHz, int maxSamplesPerBlock) {
    DBG("Freeverb: prepareToPlay(" << samplingRateHz << ")");
    jassert(samplingRateHz>0);
    FaustModule::prepareToPlay(samplingRateHz, maxSamplesPerBlock); // common initialization, e.g., sampleRate = samplingRateHz;
    FAUSTFLOAT fs = FAUSTFLOAT(samplingRateHz); // Faust typically uses floats, but may be double or quad

    freeverbP.reset(new freeverb); // stereo input and output
    freeverbUIP.reset(new APIUI); // #included in *dsp.h
    freeverbP->buildUserInterface(freeverbUIP.get());
    freeverbP->init(fs); // compression filter parameters depend on sampling rate
    jassert(freeverbP->getNumOutputs() == mNumOutputs);
    int ndx = freeverbUIP->getParamIndex("Wet");
    freeverbUIP->setParamValue(ndx, mReverbLevel);
  }

  void Freeverb::releaseResources() {
  }

  void Freeverb::processBlock (juce::AudioBuffer<float>& audioBuffer, juce::MidiBuffer& midi)
  {
    if (not inited) { return; }
    int numSamples = audioBuffer.getNumSamples();
    int numChans = audioBuffer.getNumChannels();
    jassert(getNumInputs() <= numChans);
    jassert(getNumOutputs() <= numChans);
    auto bufPointersFaust = josm::getBufferPointersFaust<float>(audioBuffer);
    compute(numSamples, bufPointersFaust.get(), bufPointersFaust.get());
  }

  void Freeverb::compute(int nframes, float** inputs, float** outputs)
  {
    jassert(inited);
    if (mReverbLevel > 0.0f) {
      freeverbP->compute(nframes, inputs, outputs);
    } // else in-place processing means we're done
  }
} // namespace josm
