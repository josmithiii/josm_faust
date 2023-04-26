// Anything needing separate compilation (such as static initialization) goes here

#include "josm_filters.h"

#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

namespace josm {

std::vector<Biquad> designButterworthBiquads(int order, double cutoffFrequency, double samplingRate) {
    // Step 1: Calculate the analog Butterworth filter prototype coefficients (poles and zeros)
    std::vector<std::complex<double>> poles;
    for (int i = 0; i < order; i++) {
        double theta = (2.0 * i + 1.0) * M_PI / (2.0 * order);
        poles.push_back(std::polar(1.0, theta));
    }

    // Step 2: Perform the bilinear transform on the analog coefficients to obtain the digital coefficients
    double preWarpFrequency = 2.0 * samplingRate * std::tan(M_PI * cutoffFrequency / samplingRate);
    std::vector<std::complex<double>> digitalPoles;
    for (const auto& pole : poles) {
        digitalPoles.push_back((2.0 * samplingRate + pole * preWarpFrequency) / (2.0 * samplingRate - pole * preWarpFrequency));
    }

    // Step 3: Convert the digital coefficients into second-order sections (biquads)
    std::vector<Biquad> biquads;
    for (int i = 0; i < order / 2; i++) {
        Biquad bq;
        bq.b0 = 1.0;
        bq.b1 = 0.0;
        bq.b2 = 0.0;
        bq.a1 = -2.0 * digitalPoles[2 * i].real();
        bq.a2 = std::norm(digitalPoles[2 * i]);
        biquads.push_back(bq);
    }

    if (order % 2 == 1) {
        Biquad bq;
        bq.b0 = 1.0;
        bq.b1 = 1.0;
        bq.b2 = 0.0;
        bq.a1 = -digitalPoles.back().real();
        bq.a2 = 0.0;
        biquads.push_back(bq);
    }

    return biquads;
}

/*
  This test function designs a Butterworth digital filter implemented
  as biquads, given the filter order, the desired cutoff frequency in
  Hz, and the sampling rate in Hz. The function returns a vector of
  `Biquad` structs, each containing the coefficients b0, b1, b2, a1,
  and a2 for a second-order section (biquad) of the filter. The main
  function demonstrates how to call the `designButterworthBiquads`
  function and print the resulting biquad coefficients.
*/

#if 0
int main() {
  int order = 4;
  double cutoffFrequency = 1000.0;
  double samplingRate = 44100.0;

  std::vector<Biquad> biquads = designButterworthBiquads(order, cutoffFrequency, samplingRate);

  std::cout << "Butterworth Biquad Coefficients:" << std::endl;
  for (size_t i = 0; i < biquads.size(); i++) {
    std::cout << "Biquad " << i + 1 << ":" << std::endl;
    std::cout << "b0: " << biquads[i].b0 << ", b1: " << biquads[i].b1 << ", b2: " << biquads[i].b2 << std::endl;
    std::cout << "a1: " << biquads[i].a1 << ", a2: " << biquads[i].a2 << std::endl;
  }
  return 0;
}
#endif

  //==============================================================================
  //                                  UNIT TESTS                                ||
  //==============================================================================

//#if JOS_UNIT_TESTS
#if JUCE_UNIT_TESTS

// #include <JuceHeader.h>
// #include "ButterworthBiquads.h" // Make sure to include the header file containing the `designButterworthBiquads` function

class ButterworthBiquadsTest : public UnitTest {
public:
    ButterworthBiquadsTest() : UnitTest("Butterworth Biquads Test") {}

    void runTest() override {
        beginTest("Design Butterworth Biquads");

        int order = 4;
        double cutoffFrequency = 1000.0;
        double samplingRate = 44100.0;

        std::vector<Biquad> biquads = designButterworthBiquads(order, cutoffFrequency, samplingRate);

        // Test the number of biquads created
        expect(biquads.size() == (order + 1) / 2, "Incorrect number of biquads");

        // Test if the calculated coefficients are within an acceptable range (you may need to adjust the tolerance)
        double tolerance = 1e-6;
        for (const auto& biquad : biquads) {
            expect(std::abs(biquad.b0) <= 1.0 + tolerance, "b0 coefficient out of range");
            expect(std::abs(biquad.b1) <= 1.0 + tolerance, "b1 coefficient out of range");
            expect(std::abs(biquad.b2) <= 1.0 + tolerance, "b2 coefficient out of range");
            expect(std::abs(biquad.a1) <= 2.0 + tolerance, "a1 coefficient out of range");
            expect(std::abs(biquad.a2) <= 1.0 + tolerance, "a2 coefficient out of range");
        }
    }
};

static ButterworthBiquadsTest butterworthBiquadsTest;

#endif // JUCE_UNIT_TESTS

} // namespace josm
