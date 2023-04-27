// Functions based on Faust's filters.lib
// Started 2021-10-28

#pragma once
#define JOSM_FILTERS_H_INCLUDED

/* \defgroup filters Filters
 *  @{
 */
//#include "jos_biquad.h"
//#include "jos_filterbank.h"
/* @}*/

namespace josm {

/**
 * @struct Biquad
 * @brief Struct to represent a second-order section (biquad) of a digital filter.
 */
struct Biquad {
    double b0, b1, b2; ///< Numerator coefficients
    double a1, a2;     ///< Denominator coefficients (a0 is assumed to be 1)
};

/**
 * @brief Designs a Butterworth digital filter implemented as biquads.
 *
 * The function calculates the biquad coefficients for a Butterworth digital filter,
 * given the filter order, the desired cutoff frequency in Hz, and the sampling rate in Hz.
 *
 * @param order The order of the Butterworth filter.
 * @param cutoffFrequency The desired cutoff frequency in Hz.
 * @param samplingRate The sampling rate of the digital signal in Hz.
 * @return A vector of Biquad structs, each containing the coefficients for a second-order section of the filter.
 *
 * Example usage:
 * @code
 * int order = 4;
 * double cutoffFrequency = 1000.0;
 * double samplingRate = 44100.0;
 * std::vector<Biquad> biquads = designButterworthBiquads(order, cutoffFrequency, samplingRate);
 * @endcode
 */
std::vector<Biquad> designButterworthBiquads(int order, double cutoffFrequency, double samplingRate);

} // namespace josm

/* @}*/
