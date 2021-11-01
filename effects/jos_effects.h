// Effects based on Faust's effects.lib
// Started 2021-10-28

/**
   \file jos_effects.h

   Includes classes created from Faust modules in effects.lib in the faustlibraries distribution.
   Effects are essentially well known filters.
   Current effects include Freeverb and Zitarev.

   @see jos::Freeverb, jos::Zitarev

   @tags{Effects}
*/

#pragma once

#include "jos_freeverb.h"
#include "jos_zitarev.h"

namespace jos {

  /**
     Class for testing only
  */
  class TestClass {
  public:
    TestClass() {
      std::cout << "We have at least one class\n";
    }
  };

}
