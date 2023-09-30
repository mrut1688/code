//
// File: ZoomEstimator.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 23-Aug-2023 11:38:45
//

#ifndef ZOOMESTIMATOR_H
#define ZOOMESTIMATOR_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder {
namespace signal {
namespace internal {
namespace codegenable {
namespace pspectrum {
class ZoomSpectrum;

}
} // namespace codegenable
} // namespace internal
} // namespace signal
} // namespace coder

// Type Definitions
namespace coder {
namespace signal {
namespace internal {
namespace codegenable {
namespace pspectrum {
class ZoomEstimator {
public:
  void reset(unsigned int idx);
  static double besseli0of2sqrt(double x);
  static double dbesseli0of2sqrt(double x);
  void processBlock(unsigned int nEst);
  void accumulateResult(unsigned int nEst, ZoomSpectrum *spectObj);
  double getPowerScaling(unsigned int nEst);
  double fstart;
  double fstop;
  double fs;
  double beta;
  unsigned int nPoints;
  unsigned int nWindow;
  unsigned int nfft;
  array<unsigned int, 2U> eIdx;
  unsigned int nEstimators;
  double stride;
  boolean_T reassign;
  boolean_T selfAssign;
  array<double, 1U> bpos;
  array<double, 1U> bvel;
  array<double, 1U> bacc;
  array<creal_T, 1U> Wxpos;
  array<creal_T, 1U> Wxvel;
  array<creal_T, 1U> Wxacc;
  array<creal_T, 1U> Wwpos;
  array<creal_T, 1U> Wwvel;
  array<creal_T, 1U> Wwacc;
  array<double, 1U> ibuf;
  array<unsigned int, 1U> nSamplesProcessed;
  array<int, 2U> nSkip;
  array<double, 1U> ksum;
  array<double, 1U> ksumsq;
  array<double, 1U> dtpos;
  array<double, 1U> dtvel;
  array<double, 1U> dfpos;
  array<double, 1U> dfvel;
  array<creal_T, 2U> aa;
  array<creal_T, 2U> bb;
  array<creal_T, 2U> bbt;
  array<creal_T, 2U> bbf;
  array<creal_T, 2U> AA;
  array<creal_T, 2U> BB;
  array<creal_T, 2U> BBT;
  array<creal_T, 2U> BBF;
  array<creal_T, 2U> UR;
  array<creal_T, 2U> LL;
  array<creal_T, 2U> URT;
  array<creal_T, 2U> LLT;
  array<creal_T, 2U> URF;
  array<creal_T, 2U> LLF;
  array<creal_T, 2U> ur;
  array<creal_T, 2U> ll;
  array<creal_T, 2U> urt;
  array<creal_T, 2U> llt;
  array<creal_T, 2U> urf;
  array<creal_T, 2U> llf;
};

} // namespace pspectrum
} // namespace codegenable
} // namespace internal
} // namespace signal
} // namespace coder

#endif
//
// File trailer for ZoomEstimator.h
//
// [EOF]
//
