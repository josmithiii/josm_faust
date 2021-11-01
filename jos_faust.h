// JOS Faust modules - started 2021-10-28

/*******************************************************************************
 The block below describes the properties of this module, and is read by
 the Projucer to automatically generate project code that uses it.
 For details about the syntax and how to create or use a module, see the
 JUCE Module Format.md file.
*******************************************************************************/

#pragma once

#if 0

 BEGIN_JUCE_MODULE_DECLARATION

  ID:                 jos_faust
  vendor:             jos
  version:            0.0.1
  name:               JOS Faust Modules for JUCE
  description:        C++ module for use with the JUCE Framework, based on jos functions from the Faust Libraries
  website:            https://ccrma.stanford.edu/~jos/jos_faust/
  license:            MIT unless otherwise specified (also have LGPL and BSD modules)
  minimumCppStandard: 14
  dependencies:       juce_audio_utils
  OSXFrameworks:      Accelerate
  iOSFrameworks:      Accelerate

 END_JUCE_MODULE_DECLARATION

#endif

/*******************************************************************************/

#include <juce_audio_utils/juce_audio_utils.h>

//==============================================================================

/** Config: JOS_FAUST_PARAM_LOG

    When this flag is enabled, every setting of a Faust DSP parameter will
    be logged in the console.
*/
#ifndef JOS_FAUST_PARAM_LOG
#define JOS_FAUST_PARAM_LOG 1
#endif

#include <complex>

namespace jos
{
  static const float PI = atanf(1.0f) * 4.0f;
  static const float PI2 = atanf(1.0f) * 8.0f;
#undef Complex
  template <typename Type>
    using Complex = std::complex<Type>;
};

//==============================================================================
#include "shared/jos_shared.h"
#include "oscillators/jos_oscillators.h"
#include "filters/jos_filters.h"
#include "effects/jos_effects.h"
