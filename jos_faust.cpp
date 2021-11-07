#ifdef JOS_FAUST_H_INCLUDED
 /* When you add this cpp file to your project, you mustn't include it in a file where you've
    already included any other headers - just put it inside a file on its own, possibly with your config
    flags preceding it, but don't include anything else. That also includes avoiding any automatic prefix
    header files that the compiler may be using.
 */
 #error "Incorrect use of JUCE-style module jos_faust"
#endif

#include "jos_faust.h"

#include "shared/jos_shared.cpp"
#include "oscillators/jos_oscillators.cpp"
#include "filters/jos_filters.cpp"
#include "effects/jos_effects.cpp"
//#include "effects/jos_freeverb.cpp"
//#include "effects/jos_zitarev.cpp"
