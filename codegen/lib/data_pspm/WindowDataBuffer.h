//
// File: WindowDataBuffer.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 23-Aug-2023 11:38:45
//

#ifndef WINDOWDATABUFFER_H
#define WINDOWDATABUFFER_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
namespace signal {
namespace internal {
namespace codegenable {
namespace pspectrum {
class WindowDataBuffer {
public:
  array<double, 2U> dataRe;
  array<double, 2U> dataIm;
  array<double, 2U> time;
  unsigned int windowSampleLength;
  unsigned int overlapSampleLength;
};

} // namespace pspectrum
} // namespace codegenable
} // namespace internal
} // namespace signal
} // namespace coder

#endif
//
// File trailer for WindowDataBuffer.h
//
// [EOF]
//
