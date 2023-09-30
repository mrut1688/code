//
// File: ZoomSpectrum.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 23-Aug-2023 11:38:45
//

#ifndef ZOOMSPECTRUM_H
#define ZOOMSPECTRUM_H

// Include Files
#include "ZoomEstimator.h"
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
class ZoomSpectrum {
public:
  ZoomSpectrum *init();
  void setup(double inT1, double inT2, double inF1, double inF2, double inBeta,
             unsigned int inNpoints, double inMaxFs, boolean_T autoZoomFFT,
             boolean_T varargin_1);
  void configureCZT(ZoomEstimator *iobj_0);
  void processSample(double x);
  double finalizeSpectrum();
  boolean_T processSegment(const ::coder::array<creal_T, 2U> &x);
  void fetchSpectrum(boolean_T convertToDB, double gain,
                     ::coder::array<double, 1U> &dstSpectrum) const;
  double t1;
  double t2;
  double f1;
  double f2;
  double beta;
  unsigned int nPoints;
  double t0;
  double fs;
  double maxFs;
  double targetRBW;
  boolean_T autoZoom;
  boolean_T reassigning;
  double nAvg;
  array<double, 1U> Pxx;
  ZoomEstimator *Estimators;
  unsigned int nExpected;
  unsigned int nSkip;
  unsigned int nRemaining;
  unsigned int nWindow;
  unsigned int nEstimators;
  double nProcessed;
  unsigned int nSegments;
  ZoomEstimator _pobj0;
};

} // namespace pspectrum
} // namespace codegenable
} // namespace internal
} // namespace signal
} // namespace coder

#endif
//
// File trailer for ZoomSpectrum.h
//
// [EOF]
//
