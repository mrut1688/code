//
// File: computeOverlapSamples.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 23-Aug-2023 11:38:45
//

#ifndef COMPUTEOVERLAPSAMPLES_H
#define COMPUTEOVERLAPSAMPLES_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace signal {
namespace internal {
namespace pspectrum {
void computeOverlapSamples(
    double perOverlap,
    const ::coder::array<unsigned int, 2U> &timeResolutionSamples,
    ::coder::array<double, 2U> &overlapSamples,
    ::coder::array<double, 2U> &b_perOverlap);

}
} // namespace internal
} // namespace signal
} // namespace coder

#endif
//
// File trailer for computeOverlapSamples.h
//
// [EOF]
//
