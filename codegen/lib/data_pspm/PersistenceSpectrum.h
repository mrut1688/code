//
// File: PersistenceSpectrum.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 23-Aug-2023 11:38:45
//

#ifndef PERSISTENCESPECTRUM_H
#define PERSISTENCESPECTRUM_H

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
class PersistenceSpectrum {
public:
  unsigned int NFreqBin;
  double magMax;
  double magMin;
  array<double, 1U> spectrum;
  array<unsigned int, 1U> temp;

private:
  double f1;
  double f2;
  unsigned int NMagBin;
};

} // namespace pspectrum
} // namespace codegenable
} // namespace internal
} // namespace signal
} // namespace coder

#endif
//
// File trailer for PersistenceSpectrum.h
//
// [EOF]
//
