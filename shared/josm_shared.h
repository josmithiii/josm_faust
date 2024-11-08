// Classes shared by multiple module categories
// Started 2021-10-30

/** \file
  jos_shared.h

  Includes classes shared among multiple modules.

  @see josm::FaustModule

  @tags{Shared}
*/

#pragma once
#define JOSM_SHARED_H_INCLUDED

/* \defgroup shared Shared
 *  @{
 */

#include <memory>
#include <juce_audio_basics/juce_audio_basics.h>

//? #include "josm_faust_module.h" // Abstract superclass shared by all Faust modules

namespace josm {

class TestClassShared {

  /** integer */
  int i;

  /** Constructor */
  TestClassShared() {}

  /** Destructor */
  ~TestClassShared() = default;
};

/**
 * @brief Get an array of write pointers from a JUCE AudioBuffer.
 *
 * This function returns a std::unique_ptr containing an array of write pointers
 * to the channels in a JUCE AudioBuffer. The unique_ptr manages the memory
 * for the array, so it is automatically deallocated when it goes out of scope.
 *
 * @tparam T The sample type of the AudioBuffer (e.g., float or double).
 * @param audioBuffer A reference to a JUCE AudioBuffer object.
 * @return A std::unique_ptr<T*[]> containing the array of write pointers.
 *
 * Usage example:
 * @code
 *   juce::AudioBuffer<float> buffer(2, 512);
 *   auto bufPtrsFaust = getBufferPointersFaust(buffer);
 *   faustModule.compute(buffer.getNumSamples(), bufPtrsFaust.get(), bufPtrsFaust.get());
 * @endcode
 *
 * Note that since JUCE uses in-place processing, all Faust modules should be compiled with
 * the -inpl (--in-place) option.
 */
template <typename T>
std::unique_ptr<T*[]> getBufferPointersFaust(juce::AudioBuffer<T>& audioBuffer) {
  T* const* writePointersJUCE = audioBuffer.getArrayOfWritePointers();
  int numChannels = audioBuffer.getNumChannels(); // we could pass this in
  std::unique_ptr<T*[]> bufferPointersFaust(new T*[numChannels]);
  for (int i = 0; i < numChannels; i++)
    bufferPointersFaust[i] = writePointersJUCE[i];
  return bufferPointersFaust;
}

  //==============================================================================
  //                                  UNIT TESTS                                ||
  //==============================================================================

//#if JOS_UNIT_TESTS
#if JUCE_UNIT_TESTS

  //  /l/mfjj/PGM/JUCE/modules/juce_core/unit_tests/juce_UnitTestCategories.h
  //  /l/jjm/unit_tests/jos_UnitTestCategories.h

#include <juce_core/juce_core.h>
#include <juce_audio_basics/juce_audio_basics.h>

  class GetBufferPointersFaustTest : public juce::UnitTest {
  public:
    GetBufferPointersFaustTest() : UnitTest("GetBufferPointersFaustTest", "JOSM-Shared") {}

    void runTest() override {
      beginTest("getBufferPointersFaust");

      // Create an AudioBuffer with 2 channels and 512 samples
      juce::AudioBuffer<float> buffer(2, 512);

      // Fill the buffer with some test data
      for (int channel = 0; channel < buffer.getNumChannels(); ++channel) {
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
          buffer.setSample(channel, sample, static_cast<float>(channel * sample));
        }
      }

      // Call the getBufferPointersFaust function
      std::unique_ptr<float*[]> bufPtrsFaust = getBufferPointersFaust(buffer);

      // Check if the returned pointers match the original buffer's pointers
      for (int channel = 0; channel < buffer.getNumChannels(); ++channel) {
        expectEquals<intptr_t>(reinterpret_cast<intptr_t>(bufPtrsFaust[unsigned(channel)]),
                               reinterpret_cast<intptr_t>(buffer.getWritePointer(channel)),
                               "Write pointer mismatch");
      }

      // Check if the values in the buffer match the test data
      for (int channel = 0; channel < buffer.getNumChannels(); ++channel) {
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
          expectEquals(buffer.getSample(channel, sample),
                       static_cast<float>(channel * sample),
                       "Buffer value mismatch");
        }
      }
    }
  };

  static GetBufferPointersFaustTest getBufferPointersFaustTest;

#endif // JUCE_UNIT_TESTS

} // namespace josm

/* @}*/
