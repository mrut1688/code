//
// File: ZoomSpectrum.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 23-Aug-2023 11:38:45
//

// Include Files
#include "ZoomSpectrum.h"
#include "ZoomEstimator.h"
#include "data_pspm_data.h"
#include "data_pspm_rtwutil.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

// Function Definitions
//
// Arguments    : ZoomEstimator *iobj_0
// Return Type  : void
//
namespace coder {
namespace signal {
namespace internal {
namespace codegenable {
namespace pspectrum {
void ZoomSpectrum::configureCZT(ZoomEstimator *iobj_0)
{
  array<double, 2U> y;
  array<unsigned int, 2U> eidx;
  double poly[8];
  double b_beta;
  double result;
  double stride;
  double varargin_4;
  double varargin_6;
  int i;
  int k;
  int n;
  unsigned int pmax;
  unsigned int pmin;
  unsigned int qY;
  unsigned int varargin_8;
  boolean_T varargin_10;
  boolean_T varargin_11;
  b_beta = this->beta;
  if (b_beta <= 2.9) {
    memcpy(&poly[0], &dv[0], 8U * sizeof(double));
  } else if (b_beta <= 4.9) {
    memcpy(&poly[0], &dv2[0], 8U * sizeof(double));
  } else {
    memcpy(&poly[0], &dv1[0], 8U * sizeof(double));
  }
  result = 0.0;
  for (n = 0; n < 8; n++) {
    result = result * b_beta + poly[n];
  }
  b_beta = this->fs * result / this->targetRBW;
  b_beta = rt_roundd_snf(b_beta);
  if (b_beta < 4.294967296E+9) {
    if (b_beta >= 0.0) {
      pmax = static_cast<unsigned int>(b_beta);
    } else {
      pmax = 0U;
    }
  } else if (b_beta >= 4.294967296E+9) {
    pmax = MAX_uint32_T;
  } else {
    pmax = 0U;
  }
  this->nWindow = pmax;
  pmax = this->nWindow;
  pmin = this->nExpected;
  if (pmax < pmin) {
    pmin = pmax;
  }
  if (pmin == 0U) {
    this->nWindow = 1U;
  } else {
    this->nWindow = pmin;
  }
  stride = static_cast<double>(this->nWindow) / (2.0 * result - 1.0);
  if (!(stride > 1.0)) {
    stride = 1.0;
  }
  pmin = this->nExpected;
  qY = pmin - this->nWindow;
  if (qY > pmin) {
    qY = 0U;
  }
  pmax = static_cast<unsigned int>(ceil(static_cast<double>(qY) / stride));
  if (static_cast<double>(pmax) + 1.0 < 4.294967296E+9) {
    pmax++;
  } else {
    pmax = MAX_uint32_T;
  }
  this->nSegments = pmax;
  if ((this->nSegments > 1U) && (this->nWindow > 1U)) {
    pmin = this->nExpected;
    qY = pmin - this->nWindow;
    if (qY > pmin) {
      qY = 0U;
    }
    pmin = this->nSegments;
    pmax = pmin - 1U;
    if (pmin - 1U > pmin) {
      pmax = 0U;
    }
    stride = static_cast<double>(qY) / static_cast<double>(pmax);
    pmin = this->nWindow;
    qY = pmin - 1U;
    if (pmin - 1U > pmin) {
      qY = 0U;
    }
    b_beta = ceil(static_cast<double>(qY) / stride);
    if (b_beta < 4.294967296E+9) {
      pmax = static_cast<unsigned int>(b_beta);
    } else if (b_beta >= 4.294967296E+9) {
      pmax = MAX_uint32_T;
    } else {
      pmax = 0U;
    }
    this->nEstimators = pmax;
  } else {
    stride = this->nWindow;
    this->nEstimators = 1U;
  }
  varargin_11 = (this->nSegments != 1U);
  pmax = this->nWindow;
  b_beta = this->fs;
  result = this->f1;
  varargin_4 = this->f2;
  pmin = this->nPoints;
  varargin_6 = this->beta;
  varargin_8 = this->nEstimators;
  varargin_10 = this->reassigning;
  qY = varargin_8 - 1U;
  if (varargin_8 - 1U > varargin_8) {
    qY = 0U;
  }
  n = static_cast<int>(qY);
  eidx.set_size(1, static_cast<int>(qY) + 1);
  for (k = 0; k <= n; k++) {
    eidx[k] = static_cast<unsigned int>(k);
  }
  iobj_0->fstart = result;
  iobj_0->fstop = varargin_4;
  iobj_0->fs = b_beta;
  iobj_0->beta = varargin_6;
  iobj_0->nPoints = pmin;
  iobj_0->nWindow = pmax;
  if (pmin > 2147483647U) {
    pmin = MAX_uint32_T;
  } else {
    pmin <<= 1;
  }
  qY = pmin - 1U;
  if (pmin - 1U > pmin) {
    qY = 0U;
  }
  pmax = 32U;
  if (qY <= 1U) {
    pmax = 0U;
  } else {
    boolean_T exitg1;
    pmin = 0U;
    exitg1 = false;
    while ((!exitg1) && (pmax - pmin > 1U)) {
      unsigned int p;
      unsigned int pow2p;
      p = (pmin + pmax) >> 1U;
      pow2p = 1U << p;
      if (pow2p == qY) {
        pmax = p;
        exitg1 = true;
      } else if (pow2p > qY) {
        pmax = p;
      } else {
        pmin = p;
      }
    }
  }
  b_beta = rt_powd_snf(2.0, static_cast<double>(pmax));
  if (b_beta < 4.294967296E+9) {
    pmax = static_cast<unsigned int>(b_beta);
  } else {
    pmax = MAX_uint32_T;
  }
  iobj_0->nfft = pmax;
  iobj_0->eIdx.set_size(1, eidx.size(1));
  n = eidx.size(1);
  for (i = 0; i < n; i++) {
    iobj_0->eIdx[i] = eidx[i];
  }
  iobj_0->nEstimators = varargin_8;
  iobj_0->stride = stride;
  iobj_0->reassign = varargin_10;
  iobj_0->selfAssign = varargin_11;
  iobj_0->nSamplesProcessed.set_size(static_cast<int>(varargin_8));
  n = static_cast<int>(varargin_8);
  for (i = 0; i < n; i++) {
    iobj_0->nSamplesProcessed[i] = 0U;
  }
  y.set_size(1, eidx.size(1));
  n = eidx.size(1);
  for (i = 0; i < n; i++) {
    y[i] = static_cast<double>(eidx[i]) * stride;
  }
  n = y.size(1);
  for (k = 0; k < n; k++) {
    y[k] = rt_roundd_snf(y[k]);
  }
  iobj_0->nSkip.set_size(1, y.size(1));
  n = y.size(1);
  for (i = 0; i < n; i++) {
    b_beta = rt_roundd_snf(y[i]);
    if (b_beta < 2.147483648E+9) {
      k = static_cast<int>(b_beta);
    } else if (b_beta >= 2.147483648E+9) {
      k = MAX_int32_T;
    } else {
      k = 0;
    }
    iobj_0->nSkip[i] = k;
  }
  k = static_cast<int>(iobj_0->nfft);
  n = static_cast<int>(iobj_0->nEstimators);
  iobj_0->aa.set_size(k, n);
  n *= k;
  for (i = 0; i < n; i++) {
    iobj_0->aa[i].re = 0.0;
    iobj_0->aa[i].im = 0.0;
  }
  k = static_cast<int>(iobj_0->nfft);
  n = static_cast<int>(iobj_0->nEstimators);
  iobj_0->bb.set_size(k, n);
  n *= k;
  for (i = 0; i < n; i++) {
    iobj_0->bb[i].re = 0.0;
    iobj_0->bb[i].im = 0.0;
  }
  k = static_cast<int>(iobj_0->nfft);
  n = static_cast<int>(iobj_0->nEstimators);
  iobj_0->AA.set_size(k, n);
  n *= k;
  for (i = 0; i < n; i++) {
    iobj_0->AA[i].re = 0.0;
    iobj_0->AA[i].im = 0.0;
  }
  k = static_cast<int>(iobj_0->nfft);
  n = static_cast<int>(iobj_0->nEstimators);
  iobj_0->BB.set_size(k, n);
  n *= k;
  for (i = 0; i < n; i++) {
    iobj_0->BB[i].re = 0.0;
    iobj_0->BB[i].im = 0.0;
  }
  k = static_cast<int>(iobj_0->nfft);
  n = static_cast<int>(iobj_0->nEstimators);
  iobj_0->UR.set_size(k, n);
  n *= k;
  for (i = 0; i < n; i++) {
    iobj_0->UR[i].re = 0.0;
    iobj_0->UR[i].im = 0.0;
  }
  k = static_cast<int>(iobj_0->nfft);
  n = static_cast<int>(iobj_0->nEstimators);
  iobj_0->LL.set_size(k, n);
  n *= k;
  for (i = 0; i < n; i++) {
    iobj_0->LL[i].re = 0.0;
    iobj_0->LL[i].im = 0.0;
  }
  k = static_cast<int>(iobj_0->nfft);
  n = static_cast<int>(iobj_0->nEstimators);
  iobj_0->ur.set_size(k, n);
  n *= k;
  for (i = 0; i < n; i++) {
    iobj_0->ur[i].re = 0.0;
    iobj_0->ur[i].im = 0.0;
  }
  k = static_cast<int>(iobj_0->nfft);
  n = static_cast<int>(iobj_0->nEstimators);
  iobj_0->ll.set_size(k, n);
  n *= k;
  for (i = 0; i < n; i++) {
    iobj_0->ll[i].re = 0.0;
    iobj_0->ll[i].im = 0.0;
  }
  k = static_cast<int>(iobj_0->nfft);
  n = static_cast<int>(iobj_0->nEstimators);
  iobj_0->bbf.set_size(k, n);
  n *= k;
  for (i = 0; i < n; i++) {
    iobj_0->bbf[i].re = 0.0;
    iobj_0->bbf[i].im = 0.0;
  }
  k = static_cast<int>(iobj_0->nfft);
  n = static_cast<int>(iobj_0->nEstimators);
  iobj_0->BBF.set_size(k, n);
  n *= k;
  for (i = 0; i < n; i++) {
    iobj_0->BBF[i].re = 0.0;
    iobj_0->BBF[i].im = 0.0;
  }
  k = static_cast<int>(iobj_0->nfft);
  n = static_cast<int>(iobj_0->nEstimators);
  iobj_0->URF.set_size(k, n);
  n *= k;
  for (i = 0; i < n; i++) {
    iobj_0->URF[i].re = 0.0;
    iobj_0->URF[i].im = 0.0;
  }
  k = static_cast<int>(iobj_0->nfft);
  n = static_cast<int>(iobj_0->nEstimators);
  iobj_0->LLF.set_size(k, n);
  n *= k;
  for (i = 0; i < n; i++) {
    iobj_0->LLF[i].re = 0.0;
    iobj_0->LLF[i].im = 0.0;
  }
  k = static_cast<int>(iobj_0->nfft);
  n = static_cast<int>(iobj_0->nEstimators);
  iobj_0->urf.set_size(k, n);
  n *= k;
  for (i = 0; i < n; i++) {
    iobj_0->urf[i].re = 0.0;
    iobj_0->urf[i].im = 0.0;
  }
  k = static_cast<int>(iobj_0->nfft);
  n = static_cast<int>(iobj_0->nEstimators);
  iobj_0->llf.set_size(k, n);
  n *= k;
  for (i = 0; i < n; i++) {
    iobj_0->llf[i].re = 0.0;
    iobj_0->llf[i].im = 0.0;
  }
  k = static_cast<int>(iobj_0->nfft);
  n = static_cast<int>(iobj_0->nEstimators);
  iobj_0->bbt.set_size(k, n);
  n *= k;
  for (i = 0; i < n; i++) {
    iobj_0->bbt[i].re = 0.0;
    iobj_0->bbt[i].im = 0.0;
  }
  k = static_cast<int>(iobj_0->nfft);
  n = static_cast<int>(iobj_0->nEstimators);
  iobj_0->BBT.set_size(k, n);
  n *= k;
  for (i = 0; i < n; i++) {
    iobj_0->BBT[i].re = 0.0;
    iobj_0->BBT[i].im = 0.0;
  }
  k = static_cast<int>(iobj_0->nfft);
  n = static_cast<int>(iobj_0->nEstimators);
  iobj_0->URT.set_size(k, n);
  n *= k;
  for (i = 0; i < n; i++) {
    iobj_0->URT[i].re = 0.0;
    iobj_0->URT[i].im = 0.0;
  }
  k = static_cast<int>(iobj_0->nfft);
  n = static_cast<int>(iobj_0->nEstimators);
  iobj_0->LLT.set_size(k, n);
  n *= k;
  for (i = 0; i < n; i++) {
    iobj_0->LLT[i].re = 0.0;
    iobj_0->LLT[i].im = 0.0;
  }
  k = static_cast<int>(iobj_0->nfft);
  n = static_cast<int>(iobj_0->nEstimators);
  iobj_0->urt.set_size(k, n);
  n *= k;
  for (i = 0; i < n; i++) {
    iobj_0->urt[i].re = 0.0;
    iobj_0->urt[i].im = 0.0;
  }
  k = static_cast<int>(iobj_0->nfft);
  n = static_cast<int>(iobj_0->nEstimators);
  iobj_0->llt.set_size(k, n);
  n *= k;
  for (i = 0; i < n; i++) {
    iobj_0->llt[i].re = 0.0;
    iobj_0->llt[i].im = 0.0;
  }
  k = static_cast<int>(iobj_0->nEstimators);
  iobj_0->bpos.set_size(k);
  for (i = 0; i < k; i++) {
    iobj_0->bpos[i] = 0.0;
  }
  k = static_cast<int>(iobj_0->nEstimators);
  iobj_0->bvel.set_size(k);
  for (i = 0; i < k; i++) {
    iobj_0->bvel[i] = 0.0;
  }
  k = static_cast<int>(iobj_0->nEstimators);
  iobj_0->bacc.set_size(k);
  for (i = 0; i < k; i++) {
    iobj_0->bacc[i] = 0.0;
  }
  k = static_cast<int>(iobj_0->nEstimators);
  iobj_0->Wxpos.set_size(k);
  for (i = 0; i < k; i++) {
    iobj_0->Wxpos[i].re = 0.0;
    iobj_0->Wxpos[i].im = 0.0;
  }
  k = static_cast<int>(iobj_0->nEstimators);
  iobj_0->Wxvel.set_size(k);
  for (i = 0; i < k; i++) {
    iobj_0->Wxvel[i].re = 0.0;
    iobj_0->Wxvel[i].im = 0.0;
  }
  k = static_cast<int>(iobj_0->nEstimators);
  iobj_0->Wxacc.set_size(k);
  for (i = 0; i < k; i++) {
    iobj_0->Wxacc[i].re = 0.0;
    iobj_0->Wxacc[i].im = 0.0;
  }
  k = static_cast<int>(iobj_0->nEstimators);
  iobj_0->Wwpos.set_size(k);
  for (i = 0; i < k; i++) {
    iobj_0->Wwpos[i].re = 0.0;
    iobj_0->Wwpos[i].im = 0.0;
  }
  k = static_cast<int>(iobj_0->nEstimators);
  iobj_0->Wwvel.set_size(k);
  for (i = 0; i < k; i++) {
    iobj_0->Wwvel[i].re = 0.0;
    iobj_0->Wwvel[i].im = 0.0;
  }
  k = static_cast<int>(iobj_0->nEstimators);
  iobj_0->Wwacc.set_size(k);
  for (i = 0; i < k; i++) {
    iobj_0->Wwacc[i].re = 0.0;
    iobj_0->Wwacc[i].im = 0.0;
  }
  k = static_cast<int>(iobj_0->nEstimators);
  iobj_0->ibuf.set_size(k);
  for (i = 0; i < k; i++) {
    iobj_0->ibuf[i] = 0.0;
  }
  k = static_cast<int>(iobj_0->nEstimators);
  iobj_0->nSamplesProcessed.set_size(k);
  for (i = 0; i < k; i++) {
    iobj_0->nSamplesProcessed[i] = 0U;
  }
  k = static_cast<int>(iobj_0->nEstimators);
  iobj_0->ksum.set_size(k);
  for (i = 0; i < k; i++) {
    iobj_0->ksum[i] = 0.0;
  }
  k = static_cast<int>(iobj_0->nEstimators);
  iobj_0->ksumsq.set_size(k);
  for (i = 0; i < k; i++) {
    iobj_0->ksumsq[i] = 0.0;
  }
  k = static_cast<int>(iobj_0->nEstimators);
  iobj_0->dtpos.set_size(k);
  for (i = 0; i < k; i++) {
    iobj_0->dtpos[i] = 0.0;
  }
  k = static_cast<int>(iobj_0->nEstimators);
  iobj_0->dtvel.set_size(k);
  for (i = 0; i < k; i++) {
    iobj_0->dtvel[i] = 0.0;
  }
  k = static_cast<int>(iobj_0->nEstimators);
  iobj_0->dfpos.set_size(k);
  for (i = 0; i < k; i++) {
    iobj_0->dfpos[i] = 0.0;
  }
  k = static_cast<int>(iobj_0->nEstimators);
  iobj_0->dfvel.set_size(k);
  for (i = 0; i < k; i++) {
    iobj_0->dfvel[i] = 0.0;
  }
  this->Estimators = iobj_0;
}

//
// Arguments    : boolean_T convertToDB
//                double gain
//                ::coder::array<double, 1U> &dstSpectrum
// Return Type  : void
//
void ZoomSpectrum::fetchSpectrum(boolean_T convertToDB, double gain,
                                 ::coder::array<double, 1U> &dstSpectrum) const
{
  int i;
  int obj_idx_0;
  if (static_cast<double>(dstSpectrum.size(0)) < this->nPoints) {
    obj_idx_0 = static_cast<int>(this->nPoints);
    dstSpectrum.set_size(obj_idx_0);
    for (i = 0; i < obj_idx_0; i++) {
      dstSpectrum[i] = 0.0;
    }
  }
  if (convertToDB) {
    double dBgain;
    dBgain = 10.0 * log10(gain);
    i = static_cast<int>(this->nPoints);
    for (obj_idx_0 = 0; obj_idx_0 < i; obj_idx_0++) {
      dstSpectrum[obj_idx_0] = 10.0 * log10(this->Pxx[obj_idx_0]) - dBgain;
    }
  } else {
    i = static_cast<int>(this->nPoints);
    for (obj_idx_0 = 0; obj_idx_0 < i; obj_idx_0++) {
      dstSpectrum[obj_idx_0] = this->Pxx[obj_idx_0] / gain;
    }
  }
}

//
// Arguments    : void
// Return Type  : double
//
double ZoomSpectrum::finalizeSpectrum()
{
  ZoomEstimator *obj;
  double gain;
  double pwrScaling;
  int idx;
  unsigned int nSamples;
  unsigned int u1;
  pwrScaling = 0.0;
  u1 = this->nEstimators;
  idx = 0;
  while ((idx <= static_cast<int>(u1) - 1) && (!(pwrScaling != 0.0))) {
    obj = this->Estimators;
    nSamples = obj->nSamplesProcessed[idx];
    if (nSamples == 0U) {
      pwrScaling = this->Estimators->getPowerScaling(idx + 1U);
    }
    idx++;
  }
  if (this->nRemaining != 0U) {
    int i;
    unsigned int maxNumSamplesProcessed;
    maxNumSamplesProcessed = 0U;
    u1 = this->nEstimators;
    i = static_cast<int>(u1);
    for (idx = 0; idx < i; idx++) {
      obj = this->Estimators;
      u1 = obj->nSamplesProcessed[idx];
      if (maxNumSamplesProcessed <= u1) {
        maxNumSamplesProcessed = u1;
      }
    }
    if (maxNumSamplesProcessed > 0U) {
      boolean_T exitg1;
      u1 = this->nEstimators;
      idx = 0;
      exitg1 = false;
      while ((!exitg1) && (idx <= static_cast<int>(u1) - 1)) {
        obj = this->Estimators;
        nSamples = obj->nSamplesProcessed[idx];
        if (maxNumSamplesProcessed == nSamples) {
          obj = this->Estimators;
          if (obj->nSamplesProcessed[idx] != 0U) {
            while (obj->ibuf[idx] < obj->nPoints) {
              obj->bb[(static_cast<int>(obj->ibuf[idx] + 1.0) +
                       obj->bb.size(0) * idx) -
                      1]
                  .re = 0.0;
              obj->bb[(static_cast<int>(obj->ibuf[idx] + 1.0) +
                       obj->bb.size(0) * idx) -
                      1]
                  .im = 0.0;
              if (obj->reassign) {
                obj->bbf[(static_cast<int>(obj->ibuf[idx] + 1.0) +
                          obj->bbf.size(0) * idx) -
                         1]
                    .re = 0.0;
                obj->bbf[(static_cast<int>(obj->ibuf[idx] + 1.0) +
                          obj->bbf.size(0) * idx) -
                         1]
                    .im = 0.0;
                if (!obj->selfAssign) {
                  obj->bbt[(static_cast<int>(obj->ibuf[idx] + 1.0) +
                            obj->bbt.size(0) * idx) -
                           1]
                      .re = 0.0;
                  obj->bbt[(static_cast<int>(obj->ibuf[idx] + 1.0) +
                            obj->bbt.size(0) * idx) -
                           1]
                      .im = 0.0;
                }
              }
              obj->ibuf[idx] = obj->ibuf[idx] + 1.0;
            }
            obj->processBlock(idx + 1U);
            obj->ibuf[idx] = 0.0;
            obj->accumulateResult(idx + 1U, this);
          }
          if (pwrScaling == 0.0) {
            pwrScaling = this->Estimators->getPowerScaling(idx + 1U);
          }
          exitg1 = true;
        } else {
          idx++;
        }
      }
    }
  }
  gain = rtNaN;
  if (this->nEstimators > 0U) {
    gain = pwrScaling * this->nAvg;
  }
  if ((this->nProcessed > 1.0) && (this->nExpected > 1U) &&
      (this->nProcessed < this->nExpected)) {
    gain *= this->nProcessed / static_cast<double>(this->nExpected);
  }
  return gain;
}

//
// Arguments    : void
// Return Type  : ZoomSpectrum *
//
ZoomSpectrum *ZoomSpectrum::init()
{
  ZoomSpectrum *obj;
  array<cuint8_T, 1U> r;
  int i;
  int loop_ub;
  obj = this;
  obj->nSkip = 0U;
  obj->_pobj0.nSkip.set_size(1, 1);
  obj->_pobj0.nSkip[0] = 0;
  obj->_pobj0.nSamplesProcessed.set_size(1);
  obj->_pobj0.nSamplesProcessed[0] = 0U;
  obj->_pobj0.nfft = 0U;
  obj->_pobj0.reassign = false;
  obj->_pobj0.selfAssign = false;
  obj->_pobj0.nWindow = 0U;
  obj->_pobj0.beta = 0.0;
  obj->_pobj0.fstart = 0.0;
  obj->_pobj0.fstop = 0.0;
  obj->_pobj0.fs = 0.0;
  obj->_pobj0.nPoints = 0U;
  obj->_pobj0.bpos.set_size(1);
  obj->_pobj0.bpos[0] = 0.0;
  obj->_pobj0.bvel.set_size(1);
  obj->_pobj0.bvel[0] = 0.0;
  obj->_pobj0.bacc.set_size(1);
  obj->_pobj0.bacc[0] = 0.0;
  obj->_pobj0.ksum.set_size(1);
  obj->_pobj0.ksum[0] = 0.0;
  obj->_pobj0.ksumsq.set_size(1);
  obj->_pobj0.ksumsq[0] = 0.0;
  obj->_pobj0.Wxpos.set_size(1);
  obj->_pobj0.Wxpos[0].re = 0.0;
  obj->_pobj0.Wxpos[0].im = 0.0;
  obj->_pobj0.Wxvel.set_size(1);
  obj->_pobj0.Wxvel[0].re = 0.0;
  obj->_pobj0.Wxvel[0].im = 0.0;
  obj->_pobj0.Wxacc.set_size(1);
  obj->_pobj0.Wxacc[0].re = 0.0;
  obj->_pobj0.Wxacc[0].im = 0.0;
  obj->_pobj0.Wwpos.set_size(1);
  obj->_pobj0.Wwpos[0].re = 0.0;
  obj->_pobj0.Wwpos[0].im = 0.0;
  obj->_pobj0.Wwvel.set_size(1);
  obj->_pobj0.Wwvel[0].re = 0.0;
  obj->_pobj0.Wwvel[0].im = 0.0;
  obj->_pobj0.Wwacc.set_size(1);
  obj->_pobj0.Wwacc[0].re = 0.0;
  obj->_pobj0.Wwacc[0].im = 0.0;
  obj->_pobj0.ibuf.set_size(1);
  obj->_pobj0.ibuf[0] = 0.0;
  obj->_pobj0.dtpos.set_size(1);
  obj->_pobj0.dtpos[0] = 0.0;
  obj->_pobj0.dtvel.set_size(1);
  obj->_pobj0.dtvel[0] = 0.0;
  obj->_pobj0.dfpos.set_size(1);
  obj->_pobj0.dfpos[0] = 0.0;
  obj->_pobj0.dfvel.set_size(1);
  obj->_pobj0.dfvel[0] = 0.0;
  obj->_pobj0.stride = 0.0;
  obj->_pobj0.eIdx.set_size(1, 1);
  obj->_pobj0.eIdx[0] = 0U;
  obj->_pobj0.nEstimators = 0U;
  r.set_size(static_cast<int>(obj->_pobj0.nfft));
  loop_ub = static_cast<int>(obj->_pobj0.nfft);
  for (i = 0; i < loop_ub; i++) {
    r[i].re = 0U;
    r[i].im = 0U;
  }
  obj->_pobj0.bbf.set_size(r.size(0), 1);
  loop_ub = r.size(0);
  for (i = 0; i < loop_ub; i++) {
    obj->_pobj0.bbf[i].re = 0.0;
    obj->_pobj0.bbf[i].im = static_cast<signed char>(r[i].im);
  }
  r.set_size(static_cast<int>(obj->_pobj0.nfft));
  loop_ub = static_cast<int>(obj->_pobj0.nfft);
  for (i = 0; i < loop_ub; i++) {
    r[i].re = 0U;
    r[i].im = 0U;
  }
  obj->_pobj0.BBF.set_size(r.size(0), 1);
  loop_ub = r.size(0);
  for (i = 0; i < loop_ub; i++) {
    obj->_pobj0.BBF[i].re = 0.0;
    obj->_pobj0.BBF[i].im = static_cast<signed char>(r[i].im);
  }
  r.set_size(static_cast<int>(obj->_pobj0.nfft));
  loop_ub = static_cast<int>(obj->_pobj0.nfft);
  for (i = 0; i < loop_ub; i++) {
    r[i].re = 0U;
    r[i].im = 0U;
  }
  obj->_pobj0.URF.set_size(r.size(0), 1);
  loop_ub = r.size(0);
  for (i = 0; i < loop_ub; i++) {
    obj->_pobj0.URF[i].re = 0.0;
    obj->_pobj0.URF[i].im = static_cast<signed char>(r[i].im);
  }
  r.set_size(static_cast<int>(obj->_pobj0.nfft));
  loop_ub = static_cast<int>(obj->_pobj0.nfft);
  for (i = 0; i < loop_ub; i++) {
    r[i].re = 0U;
    r[i].im = 0U;
  }
  obj->_pobj0.LLF.set_size(r.size(0), 1);
  loop_ub = r.size(0);
  for (i = 0; i < loop_ub; i++) {
    obj->_pobj0.LLF[i].re = 0.0;
    obj->_pobj0.LLF[i].im = static_cast<signed char>(r[i].im);
  }
  r.set_size(static_cast<int>(obj->_pobj0.nfft));
  loop_ub = static_cast<int>(obj->_pobj0.nfft);
  for (i = 0; i < loop_ub; i++) {
    r[i].re = 0U;
    r[i].im = 0U;
  }
  obj->_pobj0.urf.set_size(r.size(0), 1);
  loop_ub = r.size(0);
  for (i = 0; i < loop_ub; i++) {
    obj->_pobj0.urf[i].re = 0.0;
    obj->_pobj0.urf[i].im = static_cast<signed char>(r[i].im);
  }
  r.set_size(static_cast<int>(obj->_pobj0.nfft));
  loop_ub = static_cast<int>(obj->_pobj0.nfft);
  for (i = 0; i < loop_ub; i++) {
    r[i].re = 0U;
    r[i].im = 0U;
  }
  obj->_pobj0.llf.set_size(r.size(0), 1);
  loop_ub = r.size(0);
  for (i = 0; i < loop_ub; i++) {
    obj->_pobj0.llf[i].re = 0.0;
    obj->_pobj0.llf[i].im = static_cast<signed char>(r[i].im);
  }
  r.set_size(static_cast<int>(obj->_pobj0.nfft));
  loop_ub = static_cast<int>(obj->_pobj0.nfft);
  for (i = 0; i < loop_ub; i++) {
    r[i].re = 0U;
    r[i].im = 0U;
  }
  obj->_pobj0.bbt.set_size(r.size(0), 1);
  loop_ub = r.size(0);
  for (i = 0; i < loop_ub; i++) {
    obj->_pobj0.bbt[i].re = 0.0;
    obj->_pobj0.bbt[i].im = static_cast<signed char>(r[i].im);
  }
  r.set_size(static_cast<int>(obj->_pobj0.nfft));
  loop_ub = static_cast<int>(obj->_pobj0.nfft);
  for (i = 0; i < loop_ub; i++) {
    r[i].re = 0U;
    r[i].im = 0U;
  }
  obj->_pobj0.BBT.set_size(r.size(0), 1);
  loop_ub = r.size(0);
  for (i = 0; i < loop_ub; i++) {
    obj->_pobj0.BBT[i].re = 0.0;
    obj->_pobj0.BBT[i].im = static_cast<signed char>(r[i].im);
  }
  r.set_size(static_cast<int>(obj->_pobj0.nfft));
  loop_ub = static_cast<int>(obj->_pobj0.nfft);
  for (i = 0; i < loop_ub; i++) {
    r[i].re = 0U;
    r[i].im = 0U;
  }
  obj->_pobj0.URT.set_size(r.size(0), 1);
  loop_ub = r.size(0);
  for (i = 0; i < loop_ub; i++) {
    obj->_pobj0.URT[i].re = 0.0;
    obj->_pobj0.URT[i].im = static_cast<signed char>(r[i].im);
  }
  r.set_size(static_cast<int>(obj->_pobj0.nfft));
  loop_ub = static_cast<int>(obj->_pobj0.nfft);
  for (i = 0; i < loop_ub; i++) {
    r[i].re = 0U;
    r[i].im = 0U;
  }
  obj->_pobj0.LLT.set_size(r.size(0), 1);
  loop_ub = r.size(0);
  for (i = 0; i < loop_ub; i++) {
    obj->_pobj0.LLT[i].re = 0.0;
    obj->_pobj0.LLT[i].im = static_cast<signed char>(r[i].im);
  }
  r.set_size(static_cast<int>(obj->_pobj0.nfft));
  loop_ub = static_cast<int>(obj->_pobj0.nfft);
  for (i = 0; i < loop_ub; i++) {
    r[i].re = 0U;
    r[i].im = 0U;
  }
  obj->_pobj0.urt.set_size(r.size(0), 1);
  loop_ub = r.size(0);
  for (i = 0; i < loop_ub; i++) {
    obj->_pobj0.urt[i].re = 0.0;
    obj->_pobj0.urt[i].im = static_cast<signed char>(r[i].im);
  }
  r.set_size(static_cast<int>(obj->_pobj0.nfft));
  loop_ub = static_cast<int>(obj->_pobj0.nfft);
  for (i = 0; i < loop_ub; i++) {
    r[i].re = 0U;
    r[i].im = 0U;
  }
  obj->_pobj0.llt.set_size(r.size(0), 1);
  loop_ub = r.size(0);
  for (i = 0; i < loop_ub; i++) {
    obj->_pobj0.llt[i].re = 0.0;
    obj->_pobj0.llt[i].im = static_cast<signed char>(r[i].im);
  }
  r.set_size(static_cast<int>(obj->_pobj0.nfft));
  loop_ub = static_cast<int>(obj->_pobj0.nfft);
  for (i = 0; i < loop_ub; i++) {
    r[i].re = 0U;
    r[i].im = 0U;
  }
  obj->_pobj0.UR.set_size(r.size(0), 1);
  loop_ub = r.size(0);
  for (i = 0; i < loop_ub; i++) {
    obj->_pobj0.UR[i].re = 0.0;
    obj->_pobj0.UR[i].im = static_cast<signed char>(r[i].im);
  }
  r.set_size(static_cast<int>(obj->_pobj0.nfft));
  loop_ub = static_cast<int>(obj->_pobj0.nfft);
  for (i = 0; i < loop_ub; i++) {
    r[i].re = 0U;
    r[i].im = 0U;
  }
  obj->_pobj0.LL.set_size(r.size(0), 1);
  loop_ub = r.size(0);
  for (i = 0; i < loop_ub; i++) {
    obj->_pobj0.LL[i].re = 0.0;
    obj->_pobj0.LL[i].im = static_cast<signed char>(r[i].im);
  }
  r.set_size(static_cast<int>(obj->_pobj0.nfft));
  loop_ub = static_cast<int>(obj->_pobj0.nfft);
  for (i = 0; i < loop_ub; i++) {
    r[i].re = 0U;
    r[i].im = 0U;
  }
  obj->_pobj0.ur.set_size(r.size(0), 1);
  loop_ub = r.size(0);
  for (i = 0; i < loop_ub; i++) {
    obj->_pobj0.ur[i].re = 0.0;
    obj->_pobj0.ur[i].im = static_cast<signed char>(r[i].im);
  }
  r.set_size(static_cast<int>(obj->_pobj0.nfft));
  loop_ub = static_cast<int>(obj->_pobj0.nfft);
  for (i = 0; i < loop_ub; i++) {
    r[i].re = 0U;
    r[i].im = 0U;
  }
  obj->_pobj0.ll.set_size(r.size(0), 1);
  loop_ub = r.size(0);
  for (i = 0; i < loop_ub; i++) {
    obj->_pobj0.ll[i].re = 0.0;
    obj->_pobj0.ll[i].im = static_cast<signed char>(r[i].im);
  }
  r.set_size(static_cast<int>(obj->_pobj0.nfft));
  loop_ub = static_cast<int>(obj->_pobj0.nfft);
  for (i = 0; i < loop_ub; i++) {
    r[i].re = 0U;
    r[i].im = 0U;
  }
  obj->_pobj0.aa.set_size(r.size(0), 1);
  loop_ub = r.size(0);
  for (i = 0; i < loop_ub; i++) {
    obj->_pobj0.aa[i].re = 0.0;
    obj->_pobj0.aa[i].im = static_cast<signed char>(r[i].im);
  }
  r.set_size(static_cast<int>(obj->_pobj0.nfft));
  loop_ub = static_cast<int>(obj->_pobj0.nfft);
  for (i = 0; i < loop_ub; i++) {
    r[i].re = 0U;
    r[i].im = 0U;
  }
  obj->_pobj0.bb.set_size(r.size(0), 1);
  loop_ub = r.size(0);
  for (i = 0; i < loop_ub; i++) {
    obj->_pobj0.bb[i].re = 0.0;
    obj->_pobj0.bb[i].im = static_cast<signed char>(r[i].im);
  }
  r.set_size(static_cast<int>(obj->_pobj0.nfft));
  loop_ub = static_cast<int>(obj->_pobj0.nfft);
  for (i = 0; i < loop_ub; i++) {
    r[i].re = 0U;
    r[i].im = 0U;
  }
  obj->_pobj0.AA.set_size(r.size(0), 1);
  loop_ub = r.size(0);
  for (i = 0; i < loop_ub; i++) {
    obj->_pobj0.AA[i].re = 0.0;
    obj->_pobj0.AA[i].im = static_cast<signed char>(r[i].im);
  }
  r.set_size(static_cast<int>(obj->_pobj0.nfft));
  loop_ub = static_cast<int>(obj->_pobj0.nfft);
  for (i = 0; i < loop_ub; i++) {
    r[i].re = 0U;
    r[i].im = 0U;
  }
  obj->_pobj0.BB.set_size(r.size(0), 1);
  loop_ub = r.size(0);
  for (i = 0; i < loop_ub; i++) {
    obj->_pobj0.BB[i].re = 0.0;
    obj->_pobj0.BB[i].im = static_cast<signed char>(r[i].im);
  }
  obj->Estimators = &obj->_pobj0;
  return obj;
}

//
// Arguments    : double x
// Return Type  : void
//
void ZoomSpectrum::processSample(double x)
{
  ZoomEstimator *obj;
  int i;
  unsigned int q0;
  q0 = this->nEstimators;
  i = static_cast<int>(q0);
  for (int idx = 0; idx < i; idx++) {
    obj = this->Estimators;
    if (obj->nSkip[idx] != 0) {
      int b_q0;
      b_q0 = obj->nSkip[idx];
      if (b_q0 < -2147483647) {
        b_q0 = MIN_int32_T;
      } else {
        b_q0--;
      }
      obj->nSkip[idx] = b_q0;
    } else {
      double bess;
      double y_im;
      double y_re;
      unsigned int qY;
      if (obj->nSamplesProcessed[idx] == 0U) {
        obj->reset(idx + 1U);
      }
      bess = 1.0;
      if (obj->beta != 0.0) {
        bess = ZoomEstimator::besseli0of2sqrt(obj->bpos[idx]);
      }
      obj->ksum[idx] = obj->ksum[idx] + bess;
      obj->ksumsq[idx] = obj->ksumsq[idx] + bess * bess;
      y_re = obj->Wxpos[idx].re;
      y_im = obj->Wxpos[idx].im;
      y_re *= x;
      y_im *= x;
      obj->bb[(static_cast<int>(obj->ibuf[idx] + 1.0) + obj->bb.size(0) * idx) -
              1]
          .re = bess * y_re;
      obj->bb[(static_cast<int>(obj->ibuf[idx] + 1.0) + obj->bb.size(0) * idx) -
              1]
          .im = bess * y_im;
      if (obj->reassign) {
        double a;
        a = 0.0;
        if (obj->beta != 0.0) {
          a = obj->dtpos[idx] * ZoomEstimator::dbesseli0of2sqrt(obj->bpos[idx]);
        }
        obj->bbf[(static_cast<int>(obj->ibuf[idx] + 1.0) +
                  obj->bbf.size(0) * idx) -
                 1]
            .re = a * y_re;
        obj->bbf[(static_cast<int>(obj->ibuf[idx] + 1.0) +
                  obj->bbf.size(0) * idx) -
                 1]
            .im = a * y_im;
        obj->dtpos[idx] = obj->dtpos[idx] + obj->dtvel[idx];
        if (!obj->selfAssign) {
          a = obj->dfpos[idx] * bess;
          obj->bbt[(static_cast<int>(obj->ibuf[idx] + 1.0) +
                    obj->bbt.size(0) * idx) -
                   1]
              .re = a * y_re;
          obj->bbt[(static_cast<int>(obj->ibuf[idx] + 1.0) +
                    obj->bbt.size(0) * idx) -
                   1]
              .im = a * y_im;
          obj->dfpos[idx] = obj->dfpos[idx] + obj->dfvel[idx];
        }
      }
      obj->bpos[idx] = obj->bpos[idx] + obj->bvel[idx];
      obj->bvel[idx] = obj->bvel[idx] + obj->bacc[idx];
      bess = obj->Wxpos[idx].re * obj->Wxvel[idx].re -
             obj->Wxpos[idx].im * obj->Wxvel[idx].im;
      y_re = obj->Wxpos[idx].re * obj->Wxvel[idx].im +
             obj->Wxpos[idx].im * obj->Wxvel[idx].re;
      obj->Wxpos[idx].re = bess;
      obj->Wxpos[idx].im = y_re;
      bess = obj->Wxvel[idx].re * obj->Wxacc[idx].re -
             obj->Wxvel[idx].im * obj->Wxacc[idx].im;
      y_re = obj->Wxvel[idx].re * obj->Wxacc[idx].im +
             obj->Wxvel[idx].im * obj->Wxacc[idx].re;
      obj->Wxvel[idx].re = bess;
      obj->Wxvel[idx].im = y_re;
      obj->ibuf[idx] = obj->ibuf[idx] + 1.0;
      if (obj->ibuf[idx] == obj->nPoints) {
        obj->processBlock(idx + 1U);
        obj->ibuf[idx] = 0.0;
      }
      q0 = obj->nSamplesProcessed[idx];
      qY = q0 + 1U;
      if (q0 + 1U < q0) {
        qY = MAX_uint32_T;
      }
      obj->nSamplesProcessed[idx] = qY;
      if (obj->nSamplesProcessed[idx] == obj->nWindow) {
        int b_q0;
        if (obj->ibuf[idx] > 1.0) {
          while (obj->ibuf[idx] < obj->nPoints) {
            obj->bb[(static_cast<int>(obj->ibuf[idx] + 1.0) +
                     obj->bb.size(0) * idx) -
                    1]
                .re = 0.0;
            obj->bb[(static_cast<int>(obj->ibuf[idx] + 1.0) +
                     obj->bb.size(0) * idx) -
                    1]
                .im = 0.0;
            if (obj->reassign) {
              obj->bbf[(static_cast<int>(obj->ibuf[idx] + 1.0) +
                        obj->bbf.size(0) * idx) -
                       1]
                  .re = 0.0;
              obj->bbf[(static_cast<int>(obj->ibuf[idx] + 1.0) +
                        obj->bbf.size(0) * idx) -
                       1]
                  .im = 0.0;
              if (!obj->selfAssign) {
                obj->bbt[(static_cast<int>(obj->ibuf[idx] + 1.0) +
                          obj->bbt.size(0) * idx) -
                         1]
                    .re = 0.0;
                obj->bbt[(static_cast<int>(obj->ibuf[idx] + 1.0) +
                          obj->bbt.size(0) * idx) -
                         1]
                    .im = 0.0;
              }
            }
            obj->ibuf[idx] = obj->ibuf[idx] + 1.0;
          }
          obj->processBlock(idx + 1U);
          obj->ibuf[idx] = 0.0;
        }
        obj->accumulateResult(idx + 1U, this);
        obj->nSamplesProcessed[idx] = 0U;
        bess = obj->stride * static_cast<double>(obj->eIdx[idx]);
        bess = rt_roundd_snf(bess);
        q0 = obj->eIdx[idx];
        qY = q0 + obj->nEstimators;
        if (qY < q0) {
          qY = MAX_uint32_T;
        }
        y_re = obj->stride * static_cast<double>(qY);
        y_re = rt_roundd_snf(y_re);
        q0 = obj->eIdx[idx];
        qY = q0 + obj->nEstimators;
        if (qY < q0) {
          qY = MAX_uint32_T;
        }
        obj->eIdx[idx] = qY;
        if (y_re < 4.294967296E+9) {
          if (y_re >= 0.0) {
            q0 = static_cast<unsigned int>(y_re);
          } else {
            q0 = 0U;
          }
        } else if (y_re >= 4.294967296E+9) {
          q0 = MAX_uint32_T;
        } else {
          q0 = 0U;
        }
        if (q0 > 2147483647U) {
          q0 = 2147483647U;
        }
        if (bess < 4.294967296E+9) {
          if (bess >= 0.0) {
            qY = static_cast<unsigned int>(bess);
          } else {
            qY = 0U;
          }
        } else if (bess >= 4.294967296E+9) {
          qY = MAX_uint32_T;
        } else {
          qY = 0U;
        }
        if (qY > 2147483647U) {
          qY = 2147483647U;
        }
        b_q0 = static_cast<int>(q0) - static_cast<int>(qY);
        q0 = obj->nWindow;
        if (q0 > 2147483647U) {
          q0 = 2147483647U;
        }
        if ((b_q0 >= 0) && (static_cast<int>(q0) < b_q0 - MAX_int32_T)) {
          b_q0 = MAX_int32_T;
        } else if ((b_q0 < 0) && (static_cast<int>(q0) > b_q0 - MIN_int32_T)) {
          b_q0 = MIN_int32_T;
        } else {
          b_q0 -= static_cast<int>(q0);
        }
        obj->nSkip[idx] = b_q0;
      }
    }
  }
}

//
// Arguments    : const ::coder::array<creal_T, 2U> &x
// Return Type  : boolean_T
//
boolean_T ZoomSpectrum::processSegment(const ::coder::array<creal_T, 2U> &x)
{
  ZoomEstimator *obj;
  unsigned int idx;
  unsigned int q0;
  unsigned int qY;
  int u0;
  int u1;
  if ((x.size(0) == 0) || (x.size(1) == 0)) {
    u1 = 0;
  } else {
    u0 = x.size(0);
    u1 = x.size(1);
    if (u0 > u1) {
      u1 = u0;
    }
  }
  idx = 0U;
  while ((idx < static_cast<unsigned int>(u1)) && (this->nSkip != 0U)) {
    idx++;
    q0 = this->nSkip;
    qY = q0 - 1U;
    if (q0 - 1U > q0) {
      qY = 0U;
    }
    this->nSkip = qY;
  }
  while ((idx < static_cast<unsigned int>(u1)) && (this->nRemaining != 0U)) {
    int i;
    q0 = this->nEstimators;
    i = static_cast<int>(q0);
    for (int b_idx = 0; b_idx < i; b_idx++) {
      obj = this->Estimators;
      if (obj->nSkip[b_idx] != 0) {
        u0 = obj->nSkip[b_idx];
        if (u0 < -2147483647) {
          u0 = MIN_int32_T;
        } else {
          u0--;
        }
        obj->nSkip[b_idx] = u0;
      } else {
        double bess;
        double y_im;
        double y_re;
        if (obj->nSamplesProcessed[b_idx] == 0U) {
          obj->reset(b_idx + 1U);
        }
        bess = 1.0;
        if (obj->beta != 0.0) {
          bess = ZoomEstimator::besseli0of2sqrt(obj->bpos[b_idx]);
        }
        obj->ksum[b_idx] = obj->ksum[b_idx] + bess;
        obj->ksumsq[b_idx] = obj->ksumsq[b_idx] + bess * bess;
        y_re = x[static_cast<int>(idx)].re * obj->Wxpos[b_idx].re -
               x[static_cast<int>(idx)].im * obj->Wxpos[b_idx].im;
        y_im = x[static_cast<int>(idx)].re * obj->Wxpos[b_idx].im +
               x[static_cast<int>(idx)].im * obj->Wxpos[b_idx].re;
        obj->bb[(static_cast<int>(obj->ibuf[b_idx] + 1.0) +
                 obj->bb.size(0) * b_idx) -
                1]
            .re = bess * y_re;
        obj->bb[(static_cast<int>(obj->ibuf[b_idx] + 1.0) +
                 obj->bb.size(0) * b_idx) -
                1]
            .im = bess * y_im;
        if (obj->reassign) {
          double a;
          a = 0.0;
          if (obj->beta != 0.0) {
            a = obj->dtpos[b_idx] *
                ZoomEstimator::dbesseli0of2sqrt(obj->bpos[b_idx]);
          }
          obj->bbf[(static_cast<int>(obj->ibuf[b_idx] + 1.0) +
                    obj->bbf.size(0) * b_idx) -
                   1]
              .re = a * y_re;
          obj->bbf[(static_cast<int>(obj->ibuf[b_idx] + 1.0) +
                    obj->bbf.size(0) * b_idx) -
                   1]
              .im = a * y_im;
          obj->dtpos[b_idx] = obj->dtpos[b_idx] + obj->dtvel[b_idx];
          if (!obj->selfAssign) {
            a = obj->dfpos[b_idx] * bess;
            obj->bbt[(static_cast<int>(obj->ibuf[b_idx] + 1.0) +
                      obj->bbt.size(0) * b_idx) -
                     1]
                .re = a * y_re;
            obj->bbt[(static_cast<int>(obj->ibuf[b_idx] + 1.0) +
                      obj->bbt.size(0) * b_idx) -
                     1]
                .im = a * y_im;
            obj->dfpos[b_idx] = obj->dfpos[b_idx] + obj->dfvel[b_idx];
          }
        }
        obj->bpos[b_idx] = obj->bpos[b_idx] + obj->bvel[b_idx];
        obj->bvel[b_idx] = obj->bvel[b_idx] + obj->bacc[b_idx];
        bess = obj->Wxpos[b_idx].re * obj->Wxvel[b_idx].re -
               obj->Wxpos[b_idx].im * obj->Wxvel[b_idx].im;
        y_re = obj->Wxpos[b_idx].re * obj->Wxvel[b_idx].im +
               obj->Wxpos[b_idx].im * obj->Wxvel[b_idx].re;
        obj->Wxpos[b_idx].re = bess;
        obj->Wxpos[b_idx].im = y_re;
        bess = obj->Wxvel[b_idx].re * obj->Wxacc[b_idx].re -
               obj->Wxvel[b_idx].im * obj->Wxacc[b_idx].im;
        y_re = obj->Wxvel[b_idx].re * obj->Wxacc[b_idx].im +
               obj->Wxvel[b_idx].im * obj->Wxacc[b_idx].re;
        obj->Wxvel[b_idx].re = bess;
        obj->Wxvel[b_idx].im = y_re;
        obj->ibuf[b_idx] = obj->ibuf[b_idx] + 1.0;
        if (obj->ibuf[b_idx] == obj->nPoints) {
          obj->processBlock(b_idx + 1U);
          obj->ibuf[b_idx] = 0.0;
        }
        q0 = obj->nSamplesProcessed[b_idx];
        qY = q0 + 1U;
        if (q0 + 1U < q0) {
          qY = MAX_uint32_T;
        }
        obj->nSamplesProcessed[b_idx] = qY;
        if (obj->nSamplesProcessed[b_idx] == obj->nWindow) {
          if (obj->ibuf[b_idx] > 1.0) {
            while (obj->ibuf[b_idx] < obj->nPoints) {
              obj->bb[(static_cast<int>(obj->ibuf[b_idx] + 1.0) +
                       obj->bb.size(0) * b_idx) -
                      1]
                  .re = 0.0;
              obj->bb[(static_cast<int>(obj->ibuf[b_idx] + 1.0) +
                       obj->bb.size(0) * b_idx) -
                      1]
                  .im = 0.0;
              if (obj->reassign) {
                obj->bbf[(static_cast<int>(obj->ibuf[b_idx] + 1.0) +
                          obj->bbf.size(0) * b_idx) -
                         1]
                    .re = 0.0;
                obj->bbf[(static_cast<int>(obj->ibuf[b_idx] + 1.0) +
                          obj->bbf.size(0) * b_idx) -
                         1]
                    .im = 0.0;
                if (!obj->selfAssign) {
                  obj->bbt[(static_cast<int>(obj->ibuf[b_idx] + 1.0) +
                            obj->bbt.size(0) * b_idx) -
                           1]
                      .re = 0.0;
                  obj->bbt[(static_cast<int>(obj->ibuf[b_idx] + 1.0) +
                            obj->bbt.size(0) * b_idx) -
                           1]
                      .im = 0.0;
                }
              }
              obj->ibuf[b_idx] = obj->ibuf[b_idx] + 1.0;
            }
            obj->processBlock(b_idx + 1U);
            obj->ibuf[b_idx] = 0.0;
          }
          obj->accumulateResult(b_idx + 1U, this);
          obj->nSamplesProcessed[b_idx] = 0U;
          bess = obj->stride * static_cast<double>(obj->eIdx[b_idx]);
          bess = rt_roundd_snf(bess);
          q0 = obj->eIdx[b_idx];
          qY = q0 + obj->nEstimators;
          if (qY < q0) {
            qY = MAX_uint32_T;
          }
          y_re = obj->stride * static_cast<double>(qY);
          y_re = rt_roundd_snf(y_re);
          q0 = obj->eIdx[b_idx];
          qY = q0 + obj->nEstimators;
          if (qY < q0) {
            qY = MAX_uint32_T;
          }
          obj->eIdx[b_idx] = qY;
          if (y_re < 4.294967296E+9) {
            if (y_re >= 0.0) {
              q0 = static_cast<unsigned int>(y_re);
            } else {
              q0 = 0U;
            }
          } else if (y_re >= 4.294967296E+9) {
            q0 = MAX_uint32_T;
          } else {
            q0 = 0U;
          }
          if (q0 > 2147483647U) {
            q0 = 2147483647U;
          }
          if (bess < 4.294967296E+9) {
            if (bess >= 0.0) {
              qY = static_cast<unsigned int>(bess);
            } else {
              qY = 0U;
            }
          } else if (bess >= 4.294967296E+9) {
            qY = MAX_uint32_T;
          } else {
            qY = 0U;
          }
          if (qY > 2147483647U) {
            qY = 2147483647U;
          }
          u0 = static_cast<int>(q0) - static_cast<int>(qY);
          q0 = obj->nWindow;
          if (q0 > 2147483647U) {
            q0 = 2147483647U;
          }
          if ((u0 >= 0) && (static_cast<int>(q0) < u0 - MAX_int32_T)) {
            u0 = MAX_int32_T;
          } else if ((u0 < 0) && (static_cast<int>(q0) > u0 - MIN_int32_T)) {
            u0 = MIN_int32_T;
          } else {
            u0 -= static_cast<int>(q0);
          }
          obj->nSkip[b_idx] = u0;
        }
      }
    }
    idx++;
    q0 = this->nRemaining;
    qY = q0 - 1U;
    if (q0 - 1U > q0) {
      qY = 0U;
    }
    this->nRemaining = qY;
    this->nProcessed++;
  }
  return this->nRemaining != 0U;
}

//
// Arguments    : double inT1
//                double inT2
//                double inF1
//                double inF2
//                double inBeta
//                unsigned int inNpoints
//                double inMaxFs
//                boolean_T autoZoomFFT
//                boolean_T varargin_1
// Return Type  : void
//
void ZoomSpectrum::setup(double inT1, double inT2, double inF1, double inF2,
                         double inBeta, unsigned int inNpoints, double inMaxFs,
                         boolean_T autoZoomFFT, boolean_T varargin_1)
{
  double poly[8];
  double b_beta;
  double result;
  unsigned int q0;
  unsigned int qY;
  this->t1 = inT1;
  this->t2 = inT2;
  this->f1 = inF1;
  this->f2 = inF2;
  this->maxFs = inMaxFs;
  if (inBeta > 40.0) {
    this->beta = 40.0;
  } else if (inBeta >= 0.0) {
    this->beta = inBeta;
  } else {
    this->beta = 0.0;
  }
  this->nPoints = inNpoints;
  this->autoZoom = autoZoomFFT;
  this->reassigning = varargin_1;
  b_beta = this->beta;
  if (b_beta <= 2.9) {
    memcpy(&poly[0], &dv[0], 8U * sizeof(double));
  } else if (b_beta <= 4.9) {
    memcpy(&poly[0], &dv2[0], 8U * sizeof(double));
  } else {
    memcpy(&poly[0], &dv1[0], 8U * sizeof(double));
  }
  result = 0.0;
  for (int idx = 0; idx < 8; idx++) {
    result = result * b_beta + poly[idx];
  }
  b_beta = result / (fabs(this->t2 - this->t1) + 2.2204460492503131E-16);
  q0 = this->nPoints;
  qY = q0 - 1U;
  if (q0 - 1U > q0) {
    qY = 0U;
  }
  if (this->autoZoom) {
    result = fabs(this->f2 - this->f1);
  } else {
    result = this->maxFs;
  }
  result /= static_cast<double>(qY);
  if ((b_beta > result) || rtIsNaN(result)) {
    this->targetRBW = b_beta;
  } else {
    this->targetRBW = result;
  }
}

} // namespace pspectrum
} // namespace codegenable
} // namespace internal
} // namespace signal
} // namespace coder

//
// File trailer for ZoomSpectrum.cpp
//
// [EOF]
//
