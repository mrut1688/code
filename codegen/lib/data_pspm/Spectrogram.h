//
// File: Spectrogram.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 23-Aug-2023 11:38:45
//

#ifndef SPECTROGRAM_H
#define SPECTROGRAM_H

// Include Files
#include "WindowDataBuffer.h"
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
class Spectrogram {
public:
  void setup(boolean_T bComputeTimeResolution,
             ::coder::array<double, 2U> &timeResolutionIn,
             double OverlapPercentIn, double totalSignalSamplesIn,
             double totalInputSignalSamplesIn, double timeFactorIn, double fsIn,
             double signalEndTimeIn, double t2In, double f1In, double f2In,
             double betaIn, const unsigned int nPointsIn_data[], double maxFsIn,
             boolean_T bComputeZLimitsIn, boolean_T isConvertToDBIn);
  void computeSpectrogram(const ::coder::array<double, 2U> &data,
                          const ::coder::array<double, 2U> &b_timeVector);
  void computeSpectrogramCore(const ::coder::array<double, 2U> &dataRe,
                              const ::coder::array<double, 2U> &dataIm,
                              double dataBeginTime, unsigned int numOfWin);
  void getSpectrogramMatrix(::coder::array<double, 2U> &spectMatrix);

private:
  void createSpectrogramData();
  void performReassignment();

public:
  unsigned int spectrogramDataLen;
  array<double, 1U> timeVector;
  unsigned int totalWindows;
  double f1;
  double f2;
  unsigned int nPoints;
  double zMin;
  double zMax;
  double tgtRBW;

private:
  array<boolean_T, 1U> bIncludeInZlimitsCalculation;
  array<double, 1U> spectrogramData;
  array<double, 2U> mStftMatrix;
  array<double, 2U> mStftTimeCorrections;
  array<double, 2U> mStftFreqCorrections;
  WindowDataBuffer dataTimeBuffer;
  unsigned int winStartIndex;
  double timeResolution;
  array<unsigned int, 2U> timeResolutionSamples;
  double overlap;
  unsigned int overlapSamples;
  unsigned int totalInputSignalSamples;
  double timeFactor;
  double fs;
  double signalBeginTime;
  double signalEndTime;
  double t1;
  double t2;
  double beta;
  double maxFs;
  boolean_T bComputeZLimits;
  boolean_T useZoomFFT;
  boolean_T useReassignement;
  boolean_T bIsTwoSided;
  boolean_T bIsConvertToDB;
  double LastWindowTEnd;
};

} // namespace pspectrum
} // namespace codegenable
} // namespace internal
} // namespace signal
} // namespace coder

#endif
//
// File trailer for Spectrogram.h
//
// [EOF]
//
