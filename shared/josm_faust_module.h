/**
   \file jos_faust_module.h

   Abstract superclass shared by all Faust modules

   @tags{Shared}
*/

#pragma once

// We are in a module now: #include <JuceHeader.h>

namespace josm {

  /** Abstract class for Faust modules, taking care of common functions such as standard Faust API */

  class FaustModule {

    double sampleRate = 0;
    int blockSize = 0;

  protected:

    bool inited = false;

  public:

    FaustModule() {}
    virtual ~FaustModule() {}

    // standard API:

    //==============================================================================
    /** Returns the number of input (output) channels of audio data that this instance supports (set in constructor). */
    virtual int getNumInputs() = 0;
    virtual int getNumOutputs() = 0;

    //==============================================================================
    /** Tell the module to prepare for playing.

        The prepareToPlay(samplingRateHz) method must be called before
        useful output can be obtained from processBlock().

        When playback has finished, releaseResources() is called to
        release any persistent resources allocated by prepareToPlay().

        @param samplingRateHz           the audio sample rate expected for all audio buffers processed.
                                        Filter coefficients depend on the sampling rate, for example.
        @param maxSamplesPerBlock       the maximum number of samples in each AudioBuffer passed to
                                        processBlock(). Smaller buffer sizes are fine, but not larger,
                                        when it is used. (Some modules allocate persistent arrays of this 
                                        size to achieve best performance.)

        @see releaseResources, processBlock
    */
    virtual void prepareToPlay(double samplingRateHz, int maxSamplesPerBlock) { sampleRate = samplingRateHz; blockSize = maxSamplesPerBlock; inited = true; }

    /** Called for each successive block of audio data.

        After calling prepareToPlay(), this function is called (in the
        audio thread) each time the audio destination (such as audio
        playback hardware) requests another block of audio data.

        @see prepareToPlay, releaseResources
    */
    virtual void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) = 0;

    /** Release anything allocated by prepareToPlay() after all calls to processBlock() are complete.
        @see prepareToPlay
     */
    virtual void releaseResources() { inited = false; }

  }; // class FaustModule

} // namespace josm
