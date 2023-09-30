//
// File: pspectrum.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 23-Aug-2023 11:38:45
//

// Include Files
#include "pspectrum.h"
#include "allOrAny.h"
#include "data_pspm_data.h"
#include "data_pspm_internal_types.h"
#include "data_pspm_rtwutil.h"
#include "rt_nonfinite.h"
#include "strcmp.h"
#include "coder_array.h"
#include "coder_bounded_array.h"
#include "rt_nonfinite.h"
#include <cstddef>
#include <math.h>
#include <stdio.h>
#include <string.h>

// Function Declarations
namespace coder {
static void extractTypeAndNameValuePairs(const double inputCell_f10[2],
                                         struct_T *opts);

}

// Function Definitions
//
// Arguments    : const double inputCell_f10[2]
//                struct_T *opts
// Return Type  : void
//
namespace coder {
static void extractTypeAndNameValuePairs(const double inputCell_f10[2],
                                         struct_T *opts)
{
  static const int iv[2] = {1, 3};
  static const char cv5[15] = {'F', 'r', 'e', 'q', 'u', 'e', 'n', 'c',
                               'y', 'L', 'i', 'm', 'i', 't', 's'};
  static const char cv6[15] = {'F', 'r', 'e', 'q', 'u', 'e', 'n', 'c',
                               'y', 'L', 'i', 'm', 'i', 't', 's'};
  static const char b_b[14] = {'O', 'v', 'e', 'r', 'l', 'a', 'p',
                               'P', 'e', 'r', 'c', 'e', 'n', 't'};
  static const char b_cv1[14] = {'T', 'i', 'm', 'e', 'R', 'e', 's',
                                 'o', 'l', 'u', 't', 'i', 'o', 'n'};
  static const char cv3[14] = {'T', 'i', 'm', 'e', 'R', 'e', 's',
                               'o', 'l', 'u', 't', 'i', 'o', 'n'};
  static const char cv4[14] = {'O', 'v', 'e', 'r', 'l', 'a', 'p',
                               'P', 'e', 'r', 'c', 'e', 'n', 't'};
  static const char b[12] = {'M', 'i', 'n', 'T', 'h', 'r',
                             'e', 's', 'h', 'o', 'l', 'd'};
  static const char b_cv[12] = {'M', 'i', 'n', 'T', 'h', 'r',
                                'e', 's', 'h', 'o', 'l', 'd'};
  static const char cv2[12] = {'N', 'u', 'm', 'P', 'o', 'w',
                               'e', 'r', 'B', 'i', 'n', 's'};
  int str_size[2];
  int exitg1;
  int kstr;
  char str_data[15];
  boolean_T bv[3];
  boolean_T b_bool;
  str_size[0] = 1;
  str_size[1] = 11;
  for (kstr = 0; kstr < 11; kstr++) {
    str_data[kstr] = cv[kstr];
  }
  internal::b_strcmp(str_data, str_size, bv);
  if (internal::vectorAny(bv, iv)) {
    opts->Type.size[0] = 1;
    opts->Type.size[1] = 11;
    for (kstr = 0; kstr < 11; kstr++) {
      opts->Type.data[kstr] = str_data[kstr];
    }
  }
  str_size[0] = 1;
  str_size[1] = 12;
  for (kstr = 0; kstr < 12; kstr++) {
    str_data[kstr] = b[kstr];
  }
  internal::b_strcmp(str_data, str_size, bv);
  if (internal::vectorAny(bv, iv)) {
    opts->Type.size[0] = 1;
    opts->Type.size[1] = 12;
    for (kstr = 0; kstr < 12; kstr++) {
      opts->Type.data[kstr] = str_data[kstr];
    }
  } else {
    b_bool = false;
    kstr = 0;
    do {
      exitg1 = 0;
      if (kstr < 12) {
        if (str_data[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
    if (b_bool) {
      opts->MinThreshold = -10.0;
    } else {
      b_bool = false;
      kstr = 0;
      do {
        exitg1 = 0;
        if (kstr < 12) {
          if (str_data[kstr] != cv2[kstr]) {
            exitg1 = 1;
          } else {
            kstr++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
      if (b_bool) {
        opts->NumPowerBins = -10.0;
      }
    }
  }
  str_size[0] = 1;
  str_size[1] = 14;
  for (kstr = 0; kstr < 14; kstr++) {
    str_data[kstr] = b_cv1[kstr];
  }
  internal::b_strcmp(str_data, str_size, bv);
  if (internal::vectorAny(bv, iv)) {
    opts->Type.size[0] = 1;
    opts->Type.size[1] = 14;
    for (kstr = 0; kstr < 14; kstr++) {
      opts->Type.data[kstr] = str_data[kstr];
    }
  } else {
    b_bool = false;
    kstr = 0;
    do {
      exitg1 = 0;
      if (kstr < 14) {
        if (str_data[kstr] != cv3[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
    if (b_bool) {
      opts->TimeResolution.size[0] = 1;
      opts->TimeResolution.size[1] = 1;
      opts->TimeResolution.data[0] = 1.0;
    } else {
      b_bool = false;
      kstr = 0;
      do {
        exitg1 = 0;
        if (kstr < 14) {
          if (str_data[kstr] != cv4[kstr]) {
            exitg1 = 1;
          } else {
            kstr++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
      if (b_bool) {
        opts->OverlapPercent = 1.0;
      }
    }
  }
  str_size[0] = 1;
  str_size[1] = 14;
  for (kstr = 0; kstr < 14; kstr++) {
    str_data[kstr] = b_b[kstr];
  }
  internal::b_strcmp(str_data, str_size, bv);
  if (internal::vectorAny(bv, iv)) {
    opts->Type.size[0] = 1;
    opts->Type.size[1] = 14;
    for (kstr = 0; kstr < 14; kstr++) {
      opts->Type.data[kstr] = str_data[kstr];
    }
  } else {
    b_bool = false;
    kstr = 0;
    do {
      exitg1 = 0;
      if (kstr < 14) {
        if (str_data[kstr] != cv3[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
    if (b_bool) {
      opts->TimeResolution.size[0] = 1;
      opts->TimeResolution.size[1] = 1;
      opts->TimeResolution.data[0] = 99.0;
    } else {
      b_bool = false;
      kstr = 0;
      do {
        exitg1 = 0;
        if (kstr < 14) {
          if (str_data[kstr] != cv4[kstr]) {
            exitg1 = 1;
          } else {
            kstr++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
      if (b_bool) {
        opts->OverlapPercent = 99.0;
      }
    }
  }
  str_size[0] = 1;
  str_size[1] = 15;
  for (kstr = 0; kstr < 15; kstr++) {
    str_data[kstr] = cv5[kstr];
  }
  internal::b_strcmp(str_data, str_size, bv);
  if (internal::vectorAny(bv, iv)) {
    opts->Type.size[0] = 1;
    opts->Type.size[1] = 15;
    for (kstr = 0; kstr < 15; kstr++) {
      opts->Type.data[kstr] = str_data[kstr];
    }
  } else {
    b_bool = false;
    kstr = 0;
    do {
      exitg1 = 0;
      if (kstr < 15) {
        if (str_data[kstr] != cv6[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
    if (b_bool) {
      opts->FrequencyLimits[0] = inputCell_f10[0];
      opts->FrequencyLimits[1] = inputCell_f10[1];
    }
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &x
//                unsigned int inputCell_f1
//                const double inputCell_f10[2]
//                struct_T *opts
// Return Type  : void
//
void parseAndValidateInputs(const ::coder::array<double, 2U> &x,
                            unsigned int inputCell_f1,
                            const double inputCell_f10[2], struct_T *opts)
{
  static const char b[7] = {'s', 'a', 'm', 'p', 'l', 'e', 's'};
  static const char b_cv[5] = {'p', 'o', 'w', 'e', 'r'};
  static const char b_cv1[2] = {'f', 's'};
  static const char cv2[2] = {'t', 's'};
  array<double, 2U> data;
  array<double, 1U> r;
  array<char, 2U> b_str;
  array<char, 2U> c_str;
  array<char, 2U> d_str;
  array<char, 2U> str;
  double poly[8];
  double Fs;
  double freqFactor;
  int exitg1;
  int i;
  int nbytes;
  boolean_T x_data[3];
  boolean_T bv[2];
  boolean_T b_bool;
  boolean_T exitg2;
  opts->Data.set_size(0, 0);
  opts->TimeMode.size[0] = 1;
  opts->TimeMode.size[1] = 7;
  for (i = 0; i < 7; i++) {
    opts->TimeMode.data[i] = b[i];
  }
  opts->EffectiveFs = 0.0;
  opts->IsNormalizedFreq = false;
  opts->NonUniform = false;
  opts->t1 = 0.0;
  opts->t2 = 0.0;
  opts->TimeVector.set_size(0, 0);
  opts->NyqustRange[0] = 0.0;
  opts->FrequencyLimits[0] = rtInf;
  opts->NyqustRange[1] = 0.0;
  opts->FrequencyLimits[1] = rtInf;
  opts->Type.size[0] = 1;
  opts->Type.size[1] = 5;
  for (i = 0; i < 5; i++) {
    opts->Type.data[i] = b_cv[i];
  }
  opts->Leakage = 0.5;
  opts->MinThreshold = rtMinusInf;
  opts->FrequencyResolution.size[0] = 0;
  opts->FrequencyResolution.size[1] = 0;
  opts->Reassign = false;
  opts->TimeResolution.size[0] = 0;
  opts->TimeResolution.size[1] = 0;
  opts->OverlapPercent = rtInf;
  opts->NumPowerBins = rtInf;
  if (x.size(0) == 1) {
    data.set_size(x.size(1), 1);
    nbytes = x.size(1);
    for (i = 0; i < nbytes; i++) {
      data[i] = x[i];
    }
  } else {
    data.set_size(x.size(0), x.size(1));
    nbytes = x.size(0) * x.size(1);
    for (i = 0; i < nbytes; i++) {
      data[i] = x[i];
    }
  }
  opts->IsSingle = false;
  opts->NumChannels = data.size(1);
  opts->DataLength = data.size(0);
  opts->IsComplex = false;
  opts->TwoSided = false;
  extractTypeAndNameValuePairs(inputCell_f10, opts);
  opts->TimeMode.size[0] = 1;
  opts->TimeMode.size[1] = 2;
  opts->TimeMode.data[0] = 'f';
  opts->TimeMode.data[1] = 's';
  b_bool = false;
  nbytes = 0;
  do {
    exitg1 = 0;
    if (nbytes < 2) {
      if (opts->TimeMode.data[nbytes] != b_cv1[nbytes]) {
        exitg1 = 1;
      } else {
        nbytes++;
      }
    } else {
      b_bool = true;
      exitg1 = 1;
    }
  } while (exitg1 == 0);
  if (b_bool) {
    nbytes = 1;
  } else {
    b_bool = false;
    nbytes = 0;
    do {
      exitg1 = 0;
      if (nbytes < 2) {
        if (opts->TimeMode.data[nbytes] != cv2[nbytes]) {
          exitg1 = 1;
        } else {
          nbytes++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
    if (b_bool) {
      nbytes = 2;
    } else {
      nbytes = -1;
    }
  }
  switch (nbytes) {
  case 0:
    break;
  case 1:
    opts->Data.set_size(data.size(0), data.size(1));
    nbytes = data.size(0) * data.size(1);
    for (i = 0; i < nbytes; i++) {
      opts->Data[i] = data[i];
    }
    opts->EffectiveFs = inputCell_f1;
    opts->t1 = 0.0;
    opts->t2 = (opts->DataLength - 1.0) / static_cast<double>(inputCell_f1);
    nbytes = static_cast<int>(floor(opts->DataLength - 1.0));
    r.set_size(nbytes + 1);
    for (i = 0; i <= nbytes; i++) {
      r[i] = static_cast<double>(i) / static_cast<double>(inputCell_f1);
    }
    opts->TimeVector.set_size(r.size(0), 1);
    nbytes = r.size(0);
    for (i = 0; i < nbytes; i++) {
      opts->TimeVector[i] = r[i];
    }
    break;
  case 2: {
    unsigned int u;
    unsigned int z_tmp;
    opts->Data.set_size(data.size(0), data.size(1));
    nbytes = data.size(0) * data.size(1);
    for (i = 0; i < nbytes; i++) {
      opts->Data[i] = data[i];
    }
    freqFactor = rt_roundd_snf(1.0 / static_cast<double>(inputCell_f1));
    if (freqFactor < 4.294967296E+9) {
      z_tmp = static_cast<unsigned int>(freqFactor);
      u = z_tmp;
    } else {
      z_tmp = MAX_uint32_T;
      u = MAX_uint32_T;
    }
    opts->EffectiveFs = u;
    opts->t1 = 0.0;
    opts->t2 = (opts->DataLength - 1.0) / static_cast<double>(z_tmp);
    nbytes = static_cast<int>(floor(opts->DataLength - 1.0));
    r.set_size(nbytes + 1);
    for (i = 0; i <= nbytes; i++) {
      r[i] = static_cast<double>(i) / static_cast<double>(z_tmp);
    }
    opts->TimeVector.set_size(r.size(0), 1);
    nbytes = r.size(0);
    for (i = 0; i < nbytes; i++) {
      opts->TimeVector[i] = r[i];
    }
  } break;
  }
  if (opts->IsNormalizedFreq) {
    freqFactor = 3.1415926535897931;
  } else {
    freqFactor = 1.0;
  }
  opts->NyqustRange[0] = 0.0;
  opts->NyqustRange[1] = opts->EffectiveFs / 2.0 * freqFactor;
  if ((opts->FrequencyLimits[0] != rtInf) &&
      (opts->FrequencyLimits[1] != rtInf)) {
    if ((opts->FrequencyLimits[1] <= 0.0) ||
        (opts->FrequencyLimits[0] >= opts->NyqustRange[1])) {
      nbytes = (int)snprintf(NULL, 0, "%f", 0.0) + 1;
      str.set_size(1, nbytes);
      snprintf(&str[0], (size_t)nbytes, "%f", 0.0);
      nbytes = (int)snprintf(NULL, 0, "%f", opts->NyqustRange[1]) + 1;
      b_str.set_size(1, nbytes);
      snprintf(&b_str[0], (size_t)nbytes, "%f", opts->NyqustRange[1]);
    }
    if (!(opts->FrequencyLimits[0] > 0.0)) {
      opts->FrequencyLimits[0] = 0.0;
    }
    if ((!(opts->FrequencyLimits[1] < opts->NyqustRange[1])) &&
        (!rtIsNaN(opts->NyqustRange[1]))) {
      opts->FrequencyLimits[1] = opts->NyqustRange[1];
    }
  } else {
    opts->FrequencyLimits[0] = 0.0;
    opts->FrequencyLimits[1] = opts->NyqustRange[1];
  }
  opts->FrequencyLimits[0] /= freqFactor;
  opts->FrequencyLimits[1] /= freqFactor;
  b_bool = false;
  if (opts->Type.size[1] == 11) {
    nbytes = 0;
    do {
      exitg1 = 0;
      if (nbytes < 11) {
        if (opts->Type.data[nbytes] != cv1[nbytes]) {
          exitg1 = 1;
        } else {
          nbytes++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  if (b_bool) {
    if (opts->MinThreshold == rtMinusInf) {
      opts->MinThreshold = 0.0;
    }
  } else {
    opts->MinThreshold = rt_powd_snf(10.0, opts->MinThreshold / 10.0);
  }
  if ((opts->FrequencyResolution.size[0] != 0) &&
      (opts->FrequencyResolution.size[1] != 0)) {
    nbytes =
        opts->FrequencyResolution.size[0] * opts->FrequencyResolution.size[1];
    for (i = 0; i < nbytes; i++) {
      opts->FrequencyResolution.data[i] /= freqFactor;
    }
  }
  internal::c_strcmp(opts->Type.data, opts->Type.size, bv);
  x_data[0] = bv[0];
  x_data[1] = bv[1];
  b_bool = false;
  nbytes = 0;
  exitg2 = false;
  while ((!exitg2) && (nbytes <= 1)) {
    if (!x_data[nbytes]) {
      nbytes++;
    } else {
      b_bool = true;
      exitg2 = true;
    }
  }
  if (b_bool && ((opts->TimeResolution.size[0] != 0) &&
                 (opts->TimeResolution.size[1] != 0))) {
    Fs = opts->EffectiveFs;
    if (opts->IsNormalizedFreq) {
      Fs = 1.0;
    }
    freqFactor = floor(opts->TimeResolution.data[0] * Fs);
    if ((freqFactor > opts->DataLength) || (freqFactor < 1.0)) {
      if (opts->IsNormalizedFreq) {
        nbytes = (int)snprintf(NULL, 0, "%f", opts->DataLength) + 1;
        c_str.set_size(1, nbytes);
        snprintf(&c_str[0], (size_t)nbytes, "%f", opts->DataLength);
      } else {
        freqFactor = opts->DataLength / Fs;
        nbytes = (int)snprintf(NULL, 0, "%f", freqFactor) + 1;
        c_str.set_size(1, nbytes);
        snprintf(&c_str[0], (size_t)nbytes, "%f", freqFactor);
        freqFactor = 1.0 / Fs;
        nbytes = (int)snprintf(NULL, 0, "%f", freqFactor) + 1;
        d_str.set_size(1, nbytes);
        snprintf(&d_str[0], (size_t)nbytes, "%f", freqFactor);
      }
    }
  }
  internal::c_strcmp(opts->Type.data, opts->Type.size, bv);
  x_data[0] = bv[0];
  x_data[1] = bv[1];
  b_bool = false;
  nbytes = 0;
  exitg2 = false;
  while ((!exitg2) && (nbytes <= 1)) {
    if (!x_data[nbytes]) {
      nbytes++;
    } else {
      b_bool = true;
      exitg2 = true;
    }
  }
  if (b_bool && (opts->OverlapPercent == rtInf)) {
    freqFactor = 40.0 * (1.0 - opts->Leakage);
    if (freqFactor <= 2.9) {
      memcpy(&poly[0], &dv[0], 8U * sizeof(double));
    } else if (freqFactor <= 4.9) {
      memcpy(&poly[0], &dv2[0], 8U * sizeof(double));
    } else {
      memcpy(&poly[0], &dv1[0], 8U * sizeof(double));
    }
    Fs = 0.0;
    for (nbytes = 0; nbytes < 8; nbytes++) {
      Fs = Fs * freqFactor + poly[nbytes];
    }
    opts->OverlapPercent = (1.0 - 1.0 / (2.0 * Fs - 1.0)) * 100.0;
  }
  b_bool = false;
  if (opts->Type.size[1] == 11) {
    nbytes = 0;
    do {
      exitg1 = 0;
      if (nbytes < 11) {
        if (opts->Type.data[nbytes] != cv1[nbytes]) {
          exitg1 = 1;
        } else {
          nbytes++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  if (b_bool && (opts->NumPowerBins == rtInf)) {
    opts->NumPowerBins = 256.0;
  }
}

} // namespace coder

//
// File trailer for pspectrum.cpp
//
// [EOF]
//
