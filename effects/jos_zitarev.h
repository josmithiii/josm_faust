/*
 * jos_zitarev.h - zitarev from the faustlibraries distribution (in reverbs.lib)
 * Julius Smith
 * October 2021
 * BSD License with LGPL component
 */

#pragma once

namespace jos
{

//==============================================================================

  /** Forward declarations of classes provided by the Faust distribution. */
  class zitarev;
  class APIUI;

  /** Zitarev is a Schroeder reverb by Jezar at Dreampoint used extensively in free software.
      Reference: https://ccrma.stanford.edu/~jos/pasp/Zitarev.html
      @see Freeverb
      @tags{Effects}

      Source:
       - [jos_zitarev.h](https://github.com/josmithiii/jos_faust/blob/ebad3340273c1739d9ce383d54ccaee3aee476a0/effects/jos_zitarev.h)
       - [jos_zitarev.cpp](https://github.com/josmithiii/jos_faust/blob/ebad3340273c1739d9ce383d54ccaee3aee476a0/effects/jos_zitarev.cpp)
       - [zitarev.dsp](https://github.com/josmithiii/jos_faust/blob/main/faust-src/zitarev.dsp)
    */
  class JUCE_API Zitarev : public FaustModule
  {
    /** Number of input signals. */
    int mNumInputs;

    /** Number of output signals. */
    int mNumOutputs;

    /** Amount of reverb desired from 0 (none) to 1 (maximally wet). */
    float mReverbLevel;

    /** Faust signal processing module (derived class of dsp) implementing Zitarev. */
    std::unique_ptr<zitarev> zitarevP;

    /** Faust user interface (derived class of UI) controlling Zitarev. */
    std::unique_ptr<APIUI> zitarevUIP;

    /** process nframes samples of audio from inputs to outputs. */
    void compute(int nframes, float** inputs, float** outputs);

  public:
    /** Constructor.

        Creates an instance of Zitarev with the specified number of input and output channels.

        @param numInChans number of input channels
        @param numOutChans number of output channels

        @see Freeverb

        @tags{effects}
    */
    Zitarev(int numInChans, int numOutChans); // xtor

    /** Destructor. */
    virtual ~Zitarev();

    /** Ask the Faust signal-processing module how many inputs it has. */
    int getNumInputs() override { return(mNumInputs); }

    /** Ask the Faust signal-processing module how many outputs it has. */
    int getNumOutputs() override { return(mNumOutputs); }

    /** Tell the Faust signal-processing module what the sampling rate is. */
    void prepareToPlay(double samplingRateHz, int maxSamplesPerBlock) override;

    /** Release any resources allocated in prepareToPlay(). */
    void releaseResources() override;

    /** Set the reverberation level between 0 (no reverb) to 1 (maximally "wet" reverb). */
    void setReverbLevel(float level) {
      mReverbLevel = level;
    }

    /** Process the audio buffer along with any MIDI controls. */
    virtual void processBlock (juce::AudioBuffer<float>& audio, juce::MidiBuffer& midi) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Zitarev)

  }; // Class Zitarev

} // namespace jos
