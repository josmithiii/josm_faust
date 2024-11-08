#ifdef JOSM_FAUST_H_INCLUDED
 /* When you add this cpp file to your project, you mustn't include it in a file where you've
    already included any other headers - just put it inside a file on its own, possibly with your config
    flags preceding it, but don't include anything else. That also includes avoiding any automatic prefix
    header files that the compiler may be using.
 */
 #error "Incorrect use of JUCE-style module josm_faust"
#endif

//This would result in double includes, since each .cpp below does its own includes:
//#include "josm_faust.h"

#include "shared/josm_shared.cpp"
#include "oscillators/josm_oscillators.cpp"
// TEMP HACK: #include "filters/josm_filters.cpp"
#include "effects/josm_effects.cpp"
//#include "effects/josm_freeverb.cpp"
//#include "effects/josm_zitarev.cpp"
