/*
  ==============================================================================

   This file is part of the JOS modules (JOSM), started 2021-10-28.
   Copyright (c) 2021 - Julius O. Smith III and others

   JOSM is an open source library subject to the various licenses
   chosen by contributing authors.

   JOSM IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES,
   WHETHER EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS
   FOR PURPOSE, ARE DISCLAIMED.

  ==============================================================================
*/

/* ******************************************************************************
 The block below describes the properties of this module, and is read by
 the Projucer to automatically generate project code that uses it.
 For details about the syntax and how to create or use a module, see the
 JUCE Module Format.md file.

 BEGIN_JUCE_MODULE_DECLARATION

  ID:                 josm_faust
  vendor:             jos
  version:            0.0.1
  name:               JOS Faust Modules for JUCE
  description:        C++ module for use with the JUCE Framework, based on jos functions and others from the Faust Libraries
  website:            https://ccrma.stanford.edu/~jos/jos_modules/
  source:             https://github.com/josmithiii/JOSModules
  license:            BSD unless otherwise specified (e.g., faust-src/freeverb.dsp is LGPL)
  minimumCppStandard: 14
  dependencies:       juce_audio_utils
  OSXFrameworks:      Accelerate
  iOSFrameworks:      Accelerate

 END_JUCE_MODULE_DECLARATION

*******************************************************************************/

/*! \file josm_faust.h
    Includes everything in the josm_faust module
    @tags{josm_faust}
*/

#pragma once
#define JOSM_FAUST_H_INCLUDED

#include <juce_audio_utils/juce_audio_utils.h> // dependencies

//==============================================================================

/** Config: JOSM_FAUST_PARAM_LOG

    When this flag is enabled, every setting of a Faust DSP parameter will
    be logged in the console.
*/
#ifndef JOSM_FAUST_PARAM_LOG
#define JOSM_FAUST_PARAM_LOG 1
#endif

//==============================================================================

//needed? #include <complex>

#include "shared/josm_shared.h"
#include "oscillators/josm_oscillators.h"
// TEMP HACK: #include "filters/josm_filters.h"
#include "effects/josm_effects.h"
//#include "effects/josm_freeverb.h"
//#include "effects/josm_zitarev.h"

namespace josm
{
  static const float PI = atanf(1.0f) * 4.0f;
  static const float PI2 = atanf(1.0f) * 8.0f;
  //#undef Complex // done by juce_audio_basics.h
  //template <typename Type>
  //using Complex = std::complex<Type>;
}
