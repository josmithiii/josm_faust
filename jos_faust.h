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

  ID:                 jos_faust
  vendor:             jos
  version:            0.0.1
  name:               JOS Faust Modules for JUCE
  description:        C++ module for use with the JUCE Framework, based on jos functions from the Faust Libraries
  website:            https://ccrma.stanford.edu/~jos/jos_modules/
  license:            MIT unless otherwise specified (also have LGPL and BSD Faust functions)
  minimumCppStandard: 14
  dependencies:       juce_audio_utils
  OSXFrameworks:      Accelerate
  iOSFrameworks:      Accelerate

 END_JUCE_MODULE_DECLARATION

*******************************************************************************/

/*! \file jos_faust.h
    Includes everything in the jos_faust module
    @tags{jos_faust}
*/

#pragma once
#define JOS_FAUST_H_INCLUDED

#include <juce_audio_utils/juce_audio_utils.h> // dependencies

//==============================================================================

/** Config: JOS_FAUST_PARAM_LOG

    When this flag is enabled, every setting of a Faust DSP parameter will
    be logged in the console.
*/
#ifndef JOS_FAUST_PARAM_LOG
#define JOS_FAUST_PARAM_LOG 1
#endif

//==============================================================================

//needed? #include <complex>

#include "shared/jos_shared.h"
#include "oscillators/jos_oscillators.h"
#include "filters/jos_filters.h"
#include "effects/jos_effects.h"
//#include "effects/jos_freeverb.h"
//#include "effects/jos_zitarev.h"

namespace jos
{
  static const float PI = atanf(1.0f) * 4.0f;
  static const float PI2 = atanf(1.0f) * 8.0f;
  //#undef Complex // done by juce_audio_basics.h
  template <typename Type>
  using Complex = std::complex<Type>;
}

