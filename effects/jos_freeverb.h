/*
 * jos_freeverb.h - freeverb from the faustlibraries distribution (in reverbs.lib)
 * Julius Smith
 * October 2021
 * BSD License with LGPL component
 */

#pragma once

namespace jos
{

//==============================================================================

  /** Forward declarations of classes provided by the Faust distribution. */
  class freeverb;
  class APIUI;

  /** Freeverb is a Schroeder reverb by Jezar at Dreampoint used extensively in free software.
      Reference: https://ccrma.stanford.edu/~jos/pasp/Freeverb.html
      @see Zitarev
      @tags{Effects}

      Source:
       - [jos_freeverb.h](https://github.com/josmithiii/jos_faust/blob/ebad3340273c1739d9ce383d54ccaee3aee476a0/effects/jos_freeverb.h)
       - [jos_freeverb.cpp](https://github.com/josmithiii/jos_faust/blob/ebad3340273c1739d9ce383d54ccaee3aee476a0/effects/jos_freeverb.cpp)
       - [freeverb.dsp](https://github.com/josmithiii/jos_faust/blob/main/faust-src/freeverb.dsp)
    */
  class JUCE_API Freeverb : public FaustModule
  {
    /** Number of input signals. */
    int mNumInputs;

    /** Number of output signals. */
    int mNumOutputs;

    /** Amount of reverb desired from 0 (none) to 1 (maximally wet). */
    float mReverbLevel;

    /** Faust signal processing module (derived class of dsp) implementing Freeverb. */
    std::unique_ptr<freeverb> freeverbP;

    /** Faust user interface (derived class of UI) controlling Freeverb. */
    std::unique_ptr<APIUI> freeverbUIP;

    /** process nframes samples of audio from inputs to outputs. */
    void compute(int nframes, float** inputs, float** outputs);

  public:
    /** Constructor.

        Creates an instance of Freeverb with the specified number of input and output channels.

        @param numInChans number of input channels
        @param numOutChans number of output channels

        @see Zitarev

        @tags{effects}
    */
    Freeverb(int numInChans, int numOutChans); // xtor

    /** Destructor. */
    virtual ~Freeverb();

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

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Freeverb)

  }; // Class Freeverb

} // namespace jos
