//
// File: data_pspm_internal_types.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 23-Aug-2023 11:38:45
//

#ifndef DATA_PSPM_INTERNAL_TYPES_H
#define DATA_PSPM_INTERNAL_TYPES_H

// Include Files
#include "data_pspm_types.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include "coder_bounded_array.h"

// Type Definitions
struct struct_T {
  coder::array<double, 2U> Data;
  double DataLength;
  double NumChannels;
  boolean_T IsComplex;
  boolean_T IsSingle;
  coder::bounded_array<char, 7U, 2U> TimeMode;
  double EffectiveFs;
  boolean_T IsNormalizedFreq;
  boolean_T NonUniform;
  double t1;
  double t2;
  coder::array<double, 2U> TimeVector;
  double NyqustRange[2];
  double FrequencyLimits[2];
  coder::bounded_array<char, 15U, 2U> Type;
  double Leakage;
  double MinThreshold;
  coder::bounded_array<double, 2U, 2U> FrequencyResolution;
  boolean_T Reassign;
  coder::bounded_array<double, 2U, 2U> TimeResolution;
  double OverlapPercent;
  double NumPowerBins;
  boolean_T TwoSided;
};

#endif
//
// File trailer for data_pspm_internal_types.h
//
// [EOF]
//
