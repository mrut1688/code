//
// File: data_pspm.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 23-Aug-2023 11:38:45
//

// Include Files
#include "data_pspm.h"
#include "PersistenceSpectrum.h"
#include "Spectrogram.h"
#include "data_pspm_data.h"
#include "data_pspm_initialize.h"
#include "data_pspm_internal_types.h"
#include "data_pspm_rtwutil.h"
#include "mrdivide_helper.h"
#include "pspectrum.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "coder_bounded_array.h"
#include <math.h>
#include <string.h>

// Function Definitions
//
// Arguments    : const coder::array<double, 2U> &dat
//                unsigned int fs
//                coder::array<double, 2U> &pdata
//                coder::array<double, 2U> &fdata
//                coder::array<double, 2U> &tdata
// Return Type  : void
//
void data_pspm(const coder::array<double, 2U> &dat, unsigned int fs,
               coder::array<double, 2U> &pdata, coder::array<double, 2U> &fdata,
               coder::array<double, 2U> &tdata)
{
  coder::signal::internal::codegenable::pspectrum::PersistenceSpectrum
      persistenceObj;
  coder::signal::internal::codegenable::pspectrum::Spectrogram spectrogramObj;
  coder::array<double, 2U> b_expl_temp;
  coder::array<double, 2U> c_expl_temp;
  coder::array<double, 2U> d_expl_temp;
  coder::array<double, 2U> e_expl_temp;
  coder::array<double, 2U> r;
  coder::array<double, 2U> timeResolution;
  coder::array<double, 1U> F;
  coder::array<double, 1U> TORPWR;
  coder::array<double, 1U> b;
  coder::array<int, 1U> r2;
  coder::array<boolean_T, 2U> r1;
  struct_T expl_temp;
  double poly[8];
  double timeResolution_data[2];
  double opts_MinThreshold;
  int exitg1;
  int i;
  int nx;
  boolean_T timeResolutionAuto;
  if (!isInitialized_data_pspm) {
    data_pspm_initialize();
  }
  timeResolution_data[0] = 0.0;
  timeResolution_data[1] = 30.0;
  coder::parseAndValidateInputs(dat, fs, timeResolution_data, &expl_temp);
  opts_MinThreshold = expl_temp.MinThreshold;
  timeResolutionAuto = false;
  if (expl_temp.Type.size[1] == 11) {
    nx = 0;
    do {
      exitg1 = 0;
      if (nx < 11) {
        if (expl_temp.Type.data[nx] != cv[nx]) {
          exitg1 = 1;
        } else {
          nx++;
        }
      } else {
        timeResolutionAuto = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  if (timeResolutionAuto) {
    double dF;
    double kbeta;
    double timeFactor;
    unsigned int Npoints_data;
    int idx;
    int timeResolution_size_idx_0;
    int timeResolution_size_idx_1;
    boolean_T convertToDB;
    if (expl_temp.IsNormalizedFreq) {
      timeFactor = 0.5;
    } else {
      timeFactor = 1.0;
    }
    kbeta = 40.0 * (1.0 - expl_temp.Leakage);
    Npoints_data = 1024U;
    timeResolutionAuto = false;
    timeResolution_size_idx_0 = 1;
    timeResolution_size_idx_1 = 1;
    timeResolution_data[0] = -1.0;
    if (((expl_temp.FrequencyResolution.size[0] == 0) ||
         (expl_temp.FrequencyResolution.size[1] == 0)) &&
        ((expl_temp.TimeResolution.size[0] == 0) ||
         (expl_temp.TimeResolution.size[1] == 0))) {
      timeResolutionAuto = true;
    } else if ((expl_temp.FrequencyResolution.size[0] != 0) &&
               (expl_temp.FrequencyResolution.size[1] != 0)) {
      if (kbeta <= 2.9) {
        memcpy(&poly[0], &dv[0], 8U * sizeof(double));
      } else if (kbeta <= 4.9) {
        memcpy(&poly[0], &dv2[0], 8U * sizeof(double));
      } else {
        memcpy(&poly[0], &dv1[0], 8U * sizeof(double));
      }
      dF = 0.0;
      for (idx = 0; idx < 8; idx++) {
        dF = dF * kbeta + poly[idx];
      }
      c_expl_temp.set(&expl_temp.FrequencyResolution.data[0],
                      expl_temp.FrequencyResolution.size[0],
                      expl_temp.FrequencyResolution.size[1]);
      coder::internal::mrdiv(dF, c_expl_temp, r);
      timeResolution_size_idx_1 = r.size(1);
      nx = r.size(1);
      for (i = 0; i < nx; i++) {
        timeResolution_data[i] = r[i] / timeFactor;
      }
      e_expl_temp.set(&expl_temp.FrequencyResolution.data[0],
                      expl_temp.FrequencyResolution.size[0],
                      expl_temp.FrequencyResolution.size[1]);
      coder::internal::mrdiv(4.0 * expl_temp.EffectiveFs, e_expl_temp, r);
      nx = r.size(1);
      for (i = 0; i < nx; i++) {
        double d;
        d = rt_roundd_snf(r[i] + 1.0);
        if (d < 4.294967296E+9) {
          if (d >= 0.0) {
            Npoints_data = static_cast<unsigned int>(d);
          } else {
            Npoints_data = 0U;
          }
        } else if (d >= 4.294967296E+9) {
          Npoints_data = MAX_uint32_T;
        } else {
          Npoints_data = 0U;
        }
      }
    } else if ((expl_temp.TimeResolution.size[0] != 0) &&
               (expl_temp.TimeResolution.size[1] != 0)) {
      timeResolution_size_idx_0 = expl_temp.TimeResolution.size[0];
      timeResolution_size_idx_1 = expl_temp.TimeResolution.size[1];
      nx = expl_temp.TimeResolution.size[0] * expl_temp.TimeResolution.size[1];
      if (0 <= nx - 1) {
        memcpy(&timeResolution_data[0], &expl_temp.TimeResolution.data[0],
               nx * sizeof(double));
      }
    }
    spectrogramObj.spectrogramDataLen = 0U;
    spectrogramObj.tgtRBW = rtInf;
    spectrogramObj.zMin = rtInf;
    spectrogramObj.zMax = rtMinusInf;
    convertToDB = false;
    if (expl_temp.Type.size[1] == 11) {
      nx = 0;
      do {
        exitg1 = 0;
        if (nx < 11) {
          if (expl_temp.Type.data[nx] != cv1[nx]) {
            exitg1 = 1;
          } else {
            nx++;
          }
        } else {
          convertToDB = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
    timeResolution.set_size(timeResolution_size_idx_0,
                            timeResolution_size_idx_1);
    nx = timeResolution_size_idx_0 * timeResolution_size_idx_1 - 1;
    for (i = 0; i <= nx; i++) {
      timeResolution[i] = timeResolution_data[i];
    }
    spectrogramObj.setup(
        timeResolutionAuto, timeResolution, expl_temp.OverlapPercent,
        expl_temp.DataLength, expl_temp.DataLength, timeFactor,
        expl_temp.EffectiveFs, expl_temp.t2, expl_temp.t2,
        expl_temp.FrequencyLimits[0], expl_temp.FrequencyLimits[1], kbeta,
        (unsigned int *)&Npoints_data, 4.0 * expl_temp.EffectiveFs, false,
        convertToDB);
    spectrogramObj.computeSpectrogram(expl_temp.Data, expl_temp.TimeVector);
    spectrogramObj.getSpectrogramMatrix(pdata);
    F.set_size(static_cast<int>(spectrogramObj.nPoints));
    nx = static_cast<int>(spectrogramObj.nPoints);
    for (i = 0; i < nx; i++) {
      F[i] = 0.0;
    }
    Npoints_data = spectrogramObj.nPoints - 1U;
    if (spectrogramObj.nPoints - 1U > spectrogramObj.nPoints) {
      Npoints_data = 0U;
    }
    dF = (spectrogramObj.f2 - spectrogramObj.f1) /
         static_cast<double>(Npoints_data);
    i = static_cast<int>(spectrogramObj.nPoints);
    for (idx = 0; idx < i; idx++) {
      F[idx] =
          spectrogramObj.f1 + ((static_cast<double>(idx) + 1.0) - 1.0) * dF;
    }
    if (1U > spectrogramObj.totalWindows) {
      nx = 0;
    } else {
      nx = static_cast<int>(spectrogramObj.totalWindows);
    }
    TORPWR.set_size(nx);
    for (i = 0; i < nx; i++) {
      TORPWR[i] = spectrogramObj.timeVector[i] / timeFactor;
    }
    if (expl_temp.MinThreshold > 0.0) {
      r1.set_size(pdata.size(0), pdata.size(1));
      nx = pdata.size(0) * pdata.size(1);
      for (i = 0; i < nx; i++) {
        r1[i] = (pdata[i] < opts_MinThreshold);
      }
      timeResolution_size_idx_1 = r1.size(0) * r1.size(1) - 1;
      nx = 0;
      for (timeResolution_size_idx_0 = 0;
           timeResolution_size_idx_0 <= timeResolution_size_idx_1;
           timeResolution_size_idx_0++) {
        if (r1[timeResolution_size_idx_0]) {
          nx++;
        }
      }
      r2.set_size(nx);
      nx = 0;
      for (timeResolution_size_idx_0 = 0;
           timeResolution_size_idx_0 <= timeResolution_size_idx_1;
           timeResolution_size_idx_0++) {
        if (r1[timeResolution_size_idx_0]) {
          r2[nx] = timeResolution_size_idx_0 + 1;
          nx++;
        }
      }
      nx = r2.size(0) - 1;
      for (i = 0; i <= nx; i++) {
        pdata[r2[i] - 1] = 0.0;
      }
    }
    fdata.set_size(F.size(0), 1);
    nx = F.size(0);
    for (i = 0; i < nx; i++) {
      fdata[i] = F[i];
    }
    tdata.set_size(TORPWR.size(0), 1);
    nx = TORPWR.size(0);
    for (i = 0; i < nx; i++) {
      tdata[i] = TORPWR[i];
    }
  } else {
    double d;
    double dF;
    double kbeta;
    double timeFactor;
    unsigned long long u1;
    unsigned int Npoints_data;
    int idx;
    int timeResolution_size_idx_0;
    int timeResolution_size_idx_1;
    unsigned int u;
    unsigned int u2;
    boolean_T convertToDB;
    if (expl_temp.IsNormalizedFreq) {
      timeFactor = 0.5;
    } else {
      timeFactor = 1.0;
    }
    kbeta = 40.0 * (1.0 - expl_temp.Leakage);
    Npoints_data = 1024U;
    timeResolutionAuto = false;
    timeResolution_size_idx_0 = 1;
    timeResolution_size_idx_1 = 1;
    timeResolution_data[0] = -1.0;
    if (((expl_temp.FrequencyResolution.size[0] == 0) ||
         (expl_temp.FrequencyResolution.size[1] == 0)) &&
        ((expl_temp.TimeResolution.size[0] == 0) ||
         (expl_temp.TimeResolution.size[1] == 0))) {
      timeResolutionAuto = true;
    } else if ((expl_temp.FrequencyResolution.size[0] != 0) &&
               (expl_temp.FrequencyResolution.size[1] != 0)) {
      if (kbeta <= 2.9) {
        memcpy(&poly[0], &dv[0], 8U * sizeof(double));
      } else if (kbeta <= 4.9) {
        memcpy(&poly[0], &dv2[0], 8U * sizeof(double));
      } else {
        memcpy(&poly[0], &dv1[0], 8U * sizeof(double));
      }
      dF = 0.0;
      for (idx = 0; idx < 8; idx++) {
        dF = dF * kbeta + poly[idx];
      }
      b_expl_temp.set(&expl_temp.FrequencyResolution.data[0],
                      expl_temp.FrequencyResolution.size[0],
                      expl_temp.FrequencyResolution.size[1]);
      coder::internal::mrdiv(dF, b_expl_temp, r);
      timeResolution_size_idx_1 = r.size(1);
      nx = r.size(1);
      for (i = 0; i < nx; i++) {
        timeResolution_data[i] = r[i] / timeFactor;
      }
      d_expl_temp.set(&expl_temp.FrequencyResolution.data[0],
                      expl_temp.FrequencyResolution.size[0],
                      expl_temp.FrequencyResolution.size[1]);
      coder::internal::mrdiv(4.0 * expl_temp.EffectiveFs, d_expl_temp, r);
      nx = r.size(1);
      for (i = 0; i < nx; i++) {
        d = rt_roundd_snf(r[i] + 1.0);
        if (d < 4.294967296E+9) {
          if (d >= 0.0) {
            Npoints_data = static_cast<unsigned int>(d);
          } else {
            Npoints_data = 0U;
          }
        } else if (d >= 4.294967296E+9) {
          Npoints_data = MAX_uint32_T;
        } else {
          Npoints_data = 0U;
        }
      }
    } else if ((expl_temp.TimeResolution.size[0] != 0) &&
               (expl_temp.TimeResolution.size[1] != 0)) {
      timeResolution_size_idx_0 = expl_temp.TimeResolution.size[0];
      timeResolution_size_idx_1 = expl_temp.TimeResolution.size[1];
      nx = expl_temp.TimeResolution.size[0] * expl_temp.TimeResolution.size[1];
      if (0 <= nx - 1) {
        memcpy(&timeResolution_data[0], &expl_temp.TimeResolution.data[0],
               nx * sizeof(double));
      }
    }
    spectrogramObj.spectrogramDataLen = 0U;
    spectrogramObj.tgtRBW = rtInf;
    spectrogramObj.zMin = rtInf;
    spectrogramObj.zMax = rtMinusInf;
    convertToDB = false;
    if (expl_temp.Type.size[1] == 11) {
      nx = 0;
      do {
        exitg1 = 0;
        if (nx < 11) {
          if (expl_temp.Type.data[nx] != cv1[nx]) {
            exitg1 = 1;
          } else {
            nx++;
          }
        } else {
          convertToDB = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
    timeResolution.set_size(timeResolution_size_idx_0,
                            timeResolution_size_idx_1);
    nx = timeResolution_size_idx_0 * timeResolution_size_idx_1 - 1;
    for (i = 0; i <= nx; i++) {
      timeResolution[i] = timeResolution_data[i];
    }
    spectrogramObj.setup(
        timeResolutionAuto, timeResolution, expl_temp.OverlapPercent,
        expl_temp.DataLength, expl_temp.DataLength, timeFactor,
        expl_temp.EffectiveFs, expl_temp.t2, expl_temp.t2,
        expl_temp.FrequencyLimits[0], expl_temp.FrequencyLimits[1], kbeta,
        (unsigned int *)&Npoints_data, 4.0 * expl_temp.EffectiveFs, true,
        convertToDB);
    spectrogramObj.computeSpectrogram(expl_temp.Data, expl_temp.TimeVector);
    spectrogramObj.getSpectrogramMatrix(timeResolution);
    F.set_size(static_cast<int>(spectrogramObj.nPoints));
    nx = static_cast<int>(spectrogramObj.nPoints);
    for (i = 0; i < nx; i++) {
      F[i] = 0.0;
    }
    Npoints_data = spectrogramObj.nPoints - 1U;
    if (spectrogramObj.nPoints - 1U > spectrogramObj.nPoints) {
      Npoints_data = 0U;
    }
    dF = (spectrogramObj.f2 - spectrogramObj.f1) /
         static_cast<double>(Npoints_data);
    i = static_cast<int>(spectrogramObj.nPoints);
    for (idx = 0; idx < i; idx++) {
      F[idx] =
          spectrogramObj.f1 + ((static_cast<double>(idx) + 1.0) - 1.0) * dF;
    }
    dF = 0.05 * fabs(spectrogramObj.zMax - spectrogramObj.zMin);
    persistenceObj.NFreqBin = static_cast<unsigned int>(F.size(0));
    persistenceObj.magMin = spectrogramObj.zMin - dF;
    persistenceObj.magMax = spectrogramObj.zMax + dF;
    d = rt_roundd_snf(expl_temp.NumPowerBins);
    if (d < 4.294967296E+9) {
      if (d >= 0.0) {
        u = static_cast<unsigned int>(d);
      } else {
        u = 0U;
      }
    } else if (d >= 4.294967296E+9) {
      u = MAX_uint32_T;
    } else {
      u = 0U;
    }
    u1 = static_cast<unsigned long long>(static_cast<unsigned int>(F.size(0))) *
         u;
    if (u1 > 4294967295ULL) {
      u1 = 4294967295ULL;
    }
    persistenceObj.spectrum.set_size(static_cast<int>(u1));
    u1 = static_cast<unsigned long long>(static_cast<unsigned int>(F.size(0))) *
         u;
    if (u1 > 4294967295ULL) {
      u1 = 4294967295ULL;
    }
    nx = static_cast<int>(u1);
    for (i = 0; i < nx; i++) {
      persistenceObj.spectrum[i] = 0.0;
    }
    u1 = static_cast<unsigned long long>(static_cast<unsigned int>(F.size(0))) *
         u;
    if (u1 > 4294967295ULL) {
      u1 = 4294967295ULL;
    }
    persistenceObj.temp.set_size(static_cast<int>(u1));
    u1 = static_cast<unsigned long long>(static_cast<unsigned int>(F.size(0))) *
         u;
    if (u1 > 4294967295ULL) {
      u1 = 4294967295ULL;
    }
    nx = static_cast<int>(u1);
    for (i = 0; i < nx; i++) {
      persistenceObj.temp[i] = 0U;
    }
    dF = (persistenceObj.magMax - persistenceObj.magMin) /
         static_cast<double>(u);
    d = rt_roundd_snf(
        static_cast<double>(timeResolution.size(0) * timeResolution.size(1)) /
        static_cast<double>(static_cast<unsigned int>(F.size(0))));
    if (d < 4.294967296E+9) {
      if (d >= 0.0) {
        u2 = static_cast<unsigned int>(d);
      } else {
        u2 = 0U;
      }
    } else if (d >= 4.294967296E+9) {
      u2 = MAX_uint32_T;
    } else {
      u2 = 0U;
    }
    i = F.size(0);
    for (idx = 0; idx < i; idx++) {
      u1 = static_cast<unsigned long long>(idx) * u;
      if (u1 > 4294967295ULL) {
        u1 = 4294967295ULL;
      }
      nx = static_cast<int>(u2);
      for (int jdx = 0; jdx < nx; jdx++) {
        unsigned long long u3;
        boolean_T exitg2;
        u3 = static_cast<unsigned long long>(jdx) * persistenceObj.NFreqBin;
        if (u3 > 4294967295ULL) {
          u3 = 4294967295ULL;
        }
        Npoints_data = idx + static_cast<unsigned int>(u3);
        if (Npoints_data < static_cast<unsigned int>(idx)) {
          Npoints_data = MAX_uint32_T;
        }
        timeResolution_size_idx_1 = 0;
        exitg2 = false;
        while ((!exitg2) &&
               (timeResolution_size_idx_1 <= static_cast<int>(u) - 1)) {
          unsigned int qY;
          qY = static_cast<unsigned int>(timeResolution_size_idx_1);
          if (static_cast<unsigned int>(timeResolution_size_idx_1) >
              timeResolution_size_idx_1 + 1U) {
            qY = 0U;
          }
          if ((timeResolution[static_cast<int>(Npoints_data)] >=
               persistenceObj.magMin + static_cast<double>(qY) * dF) &&
              (timeResolution[static_cast<int>(Npoints_data)] <=
               persistenceObj.magMin +
                   static_cast<double>(timeResolution_size_idx_1 + 1U) * dF)) {
            unsigned int q0;
            timeResolution_size_idx_0 = static_cast<int>(u1);
            if (static_cast<int>(u1) < 0) {
              timeResolution_size_idx_0 = 0;
            }
            Npoints_data =
                (static_cast<unsigned int>(timeResolution_size_idx_0) +
                 timeResolution_size_idx_1) +
                1U;
            if (Npoints_data <
                static_cast<unsigned int>(timeResolution_size_idx_0)) {
              Npoints_data = MAX_uint32_T;
            }
            timeResolution_size_idx_0 = static_cast<int>(u1);
            if (static_cast<int>(u1) < 0) {
              timeResolution_size_idx_0 = 0;
            }
            qY = (static_cast<unsigned int>(timeResolution_size_idx_0) +
                  timeResolution_size_idx_1) +
                 1U;
            if (qY < static_cast<unsigned int>(timeResolution_size_idx_0)) {
              qY = MAX_uint32_T;
            }
            q0 = persistenceObj.temp[static_cast<int>(qY) - 1];
            qY = q0 + 1U;
            if (q0 + 1U < q0) {
              qY = MAX_uint32_T;
            }
            persistenceObj.temp[static_cast<int>(Npoints_data) - 1] = qY;
            exitg2 = true;
          } else {
            timeResolution_size_idx_1++;
          }
        }
      }
    }
    i = persistenceObj.temp.size(0);
    for (idx = 0; idx < i; idx++) {
      persistenceObj.spectrum[idx] = persistenceObj.temp[idx];
      persistenceObj.temp[idx] = 0U;
    }
    pdata.set_size(static_cast<int>(u), F.size(0));
    nx = static_cast<int>(u) * F.size(0);
    for (i = 0; i < nx; i++) {
      pdata[i] = 100.0 * (persistenceObj.spectrum[i] /
                          static_cast<double>(timeResolution.size(1)));
    }
    F.set_size(static_cast<int>(persistenceObj.NFreqBin));
    nx = static_cast<int>(persistenceObj.NFreqBin);
    for (i = 0; i < nx; i++) {
      F[i] = 0.0;
    }
    Npoints_data = persistenceObj.NFreqBin - 1U;
    if (persistenceObj.NFreqBin - 1U > persistenceObj.NFreqBin) {
      Npoints_data = 0U;
    }
    dF = (expl_temp.FrequencyLimits[1] - expl_temp.FrequencyLimits[0]) /
         static_cast<double>(Npoints_data);
    i = static_cast<int>(persistenceObj.NFreqBin);
    for (idx = 0; idx < i; idx++) {
      F[idx] = expl_temp.FrequencyLimits[0] +
               ((static_cast<double>(idx) + 1.0) - 1.0) * dF;
    }
    TORPWR.set_size(static_cast<int>(u));
    nx = static_cast<int>(u);
    for (i = 0; i < nx; i++) {
      TORPWR[i] = 0.0;
    }
    dF = (persistenceObj.magMax - persistenceObj.magMin) /
         static_cast<double>(u);
    kbeta = persistenceObj.magMin + dF / 2.0;
    i = static_cast<int>(u);
    for (idx = 0; idx < i; idx++) {
      TORPWR[idx] = kbeta + ((static_cast<double>(idx) + 1.0) - 1.0) * dF;
    }
    if (expl_temp.MinThreshold > 0.0) {
      timeResolution_size_idx_1 = pdata.size(0) * pdata.size(1) - 1;
      nx = 0;
      for (timeResolution_size_idx_0 = 0;
           timeResolution_size_idx_0 <= timeResolution_size_idx_1;
           timeResolution_size_idx_0++) {
        if (pdata[timeResolution_size_idx_0] < opts_MinThreshold) {
          nx++;
        }
      }
      r2.set_size(nx);
      nx = 0;
      for (timeResolution_size_idx_0 = 0;
           timeResolution_size_idx_0 <= timeResolution_size_idx_1;
           timeResolution_size_idx_0++) {
        if (pdata[timeResolution_size_idx_0] < opts_MinThreshold) {
          r2[nx] = timeResolution_size_idx_0 + 1;
          nx++;
        }
      }
      nx = r2.size(0) - 1;
      for (i = 0; i <= nx; i++) {
        pdata[r2[i] - 1] = 0.0;
      }
    }
    b.set_size(TORPWR.size(0));
    nx = TORPWR.size(0);
    for (i = 0; i < nx; i++) {
      b[i] = TORPWR[i] / 10.0;
    }
    TORPWR.set_size(b.size(0));
    nx = b.size(0);
    for (timeResolution_size_idx_1 = 0; timeResolution_size_idx_1 < nx;
         timeResolution_size_idx_1++) {
      TORPWR[timeResolution_size_idx_1] =
          rt_powd_snf(10.0, b[timeResolution_size_idx_1]);
    }
    fdata.set_size(F.size(0), 1);
    nx = F.size(0);
    for (i = 0; i < nx; i++) {
      fdata[i] = F[i];
    }
    tdata.set_size(TORPWR.size(0), 1);
    nx = TORPWR.size(0);
    for (i = 0; i < nx; i++) {
      tdata[i] = TORPWR[i];
    }
  }
  if (expl_temp.IsNormalizedFreq) {
    fdata.set_size(fdata.size(0), 1);
    nx = fdata.size(0) - 1;
    for (i = 0; i <= nx; i++) {
      fdata[i] = fdata[i] * 3.1415926535897931;
    }
  }
}

//
// File trailer for data_pspm.cpp
//
// [EOF]
//
