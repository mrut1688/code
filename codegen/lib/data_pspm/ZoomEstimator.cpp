//
// File: ZoomEstimator.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 23-Aug-2023 11:38:45
//

// Include Files
#include "ZoomEstimator.h"
#include "ZoomSpectrum.h"
#include "data_pspm_data.h"
#include "data_pspm_rtwutil.h"
#include "fft.h"
#include "ifft.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <math.h>

// Function Definitions
//
// Arguments    : unsigned int nEst
//                ZoomSpectrum *spectObj
// Return Type  : void
//
namespace coder {
namespace signal {
namespace internal {
namespace codegenable {
namespace pspectrum {
void ZoomEstimator::accumulateResult(unsigned int nEst, ZoomSpectrum *spectObj)
{
  array<creal_T, 1U> a;
  array<creal_T, 1U> obj;
  array<int, 1U> r;
  unsigned int b;
  int i;
  int loop_ub;
  loop_ub = this->ur.size(0);
  r.set_size(loop_ub);
  for (i = 0; i < loop_ub; i++) {
    r[i] = i;
  }
  loop_ub = this->UR.size(0);
  obj.set_size(loop_ub);
  for (i = 0; i < loop_ub; i++) {
    obj[i] = this->UR[i + this->UR.size(0) * (static_cast<int>(nEst) - 1)];
  }
  ifft(obj, a);
  b = this->nfft;
  loop_ub = a.size(0);
  for (i = 0; i < loop_ub; i++) {
    this->ur[r[i] + this->ur.size(0) * (static_cast<int>(nEst) - 1)].re =
        static_cast<double>(b) * a[i].re;
    this->ur[r[i] + this->ur.size(0) * (static_cast<int>(nEst) - 1)].im =
        static_cast<double>(b) * a[i].im;
  }
  loop_ub = this->ll.size(0);
  r.set_size(loop_ub);
  for (i = 0; i < loop_ub; i++) {
    r[i] = i;
  }
  loop_ub = this->LL.size(0);
  obj.set_size(loop_ub);
  for (i = 0; i < loop_ub; i++) {
    obj[i] = this->LL[i + this->LL.size(0) * (static_cast<int>(nEst) - 1)];
  }
  ifft(obj, a);
  b = this->nfft;
  loop_ub = a.size(0);
  for (i = 0; i < loop_ub; i++) {
    this->ll[r[i] + this->ll.size(0) * (static_cast<int>(nEst) - 1)].re =
        static_cast<double>(b) * a[i].re;
    this->ll[r[i] + this->ll.size(0) * (static_cast<int>(nEst) - 1)].im =
        static_cast<double>(b) * a[i].im;
  }
  if (this->reassign && this->selfAssign) {
    double binWidth;
    unsigned int q0;
    loop_ub = this->urf.size(0);
    r.set_size(loop_ub);
    for (i = 0; i < loop_ub; i++) {
      r[i] = i;
    }
    loop_ub = this->URF.size(0);
    obj.set_size(loop_ub);
    for (i = 0; i < loop_ub; i++) {
      obj[i] = this->URF[i + this->URF.size(0) * (static_cast<int>(nEst) - 1)];
    }
    ifft(obj, a);
    b = this->nfft;
    loop_ub = a.size(0);
    for (i = 0; i < loop_ub; i++) {
      this->urf[r[i] + this->urf.size(0) * (static_cast<int>(nEst) - 1)].re =
          static_cast<double>(b) * a[i].re;
      this->urf[r[i] + this->urf.size(0) * (static_cast<int>(nEst) - 1)].im =
          static_cast<double>(b) * a[i].im;
    }
    loop_ub = this->llf.size(0);
    r.set_size(loop_ub);
    for (i = 0; i < loop_ub; i++) {
      r[i] = i;
    }
    loop_ub = this->LLF.size(0);
    obj.set_size(loop_ub);
    for (i = 0; i < loop_ub; i++) {
      obj[i] = this->LLF[i + this->LLF.size(0) * (static_cast<int>(nEst) - 1)];
    }
    ifft(obj, a);
    b = this->nfft;
    loop_ub = a.size(0);
    for (i = 0; i < loop_ub; i++) {
      this->llf[r[i] + this->llf.size(0) * (static_cast<int>(nEst) - 1)].re =
          static_cast<double>(b) * a[i].re;
      this->llf[r[i] + this->llf.size(0) * (static_cast<int>(nEst) - 1)].im =
          static_cast<double>(b) * a[i].im;
    }
    q0 = this->nPoints;
    b = q0 - 1U;
    if (q0 - 1U > q0) {
      b = 0U;
    }
    binWidth = (this->fstop - this->fstart) / static_cast<double>(b);
    b = this->nPoints;
    i = static_cast<int>(b);
    for (loop_ub = 0; loop_ub < i; loop_ub++) {
      double XF_im;
      double XF_re;
      double X_im;
      double X_re;
      double deltaF;
      b = (loop_ub + this->nPoints) + 1U;
      if (b < loop_ub + 1U) {
        b = MAX_uint32_T;
      }
      X_re = this->ur[loop_ub + this->ur.size(0) * (static_cast<int>(nEst) - 1)]
                 .re +
             this->ll[(static_cast<int>(b) +
                       this->ll.size(0) * (static_cast<int>(nEst) - 1)) -
                      1]
                 .re;
      b = (loop_ub + this->nPoints) + 1U;
      if (b < loop_ub + 1U) {
        b = MAX_uint32_T;
      }
      X_im = this->ur[loop_ub + this->ur.size(0) * (static_cast<int>(nEst) - 1)]
                 .im +
             this->ll[(static_cast<int>(b) +
                       this->ll.size(0) * (static_cast<int>(nEst) - 1)) -
                      1]
                 .im;
      b = (loop_ub + this->nPoints) + 1U;
      if (b < loop_ub + 1U) {
        b = MAX_uint32_T;
      }
      XF_re =
          this->urf[loop_ub + this->urf.size(0) * (static_cast<int>(nEst) - 1)]
              .re +
          this->llf[(static_cast<int>(b) +
                     this->llf.size(0) * (static_cast<int>(nEst) - 1)) -
                    1]
              .re;
      b = (loop_ub + this->nPoints) + 1U;
      if (b < loop_ub + 1U) {
        b = MAX_uint32_T;
      }
      XF_im =
          this->urf[loop_ub + this->urf.size(0) * (static_cast<int>(nEst) - 1)]
              .im +
          this->llf[(static_cast<int>(b) +
                     this->llf.size(0) * (static_cast<int>(nEst) - 1)) -
                    1]
              .im;
      if (X_im == 0.0) {
        if (XF_im == 0.0) {
          XF_im = 0.0;
        } else {
          XF_im /= X_re;
        }
      } else if (X_re == 0.0) {
        if (XF_re == 0.0) {
          XF_im = 0.0;
        } else {
          XF_im = -(XF_re / X_im);
        }
      } else {
        double bim;
        deltaF = fabs(X_re);
        bim = fabs(X_im);
        if (deltaF > bim) {
          deltaF = X_im / X_re;
          XF_im = (XF_im - deltaF * XF_re) / (X_re + deltaF * X_im);
        } else if (bim == deltaF) {
          double b_X_im;
          if (X_re > 0.0) {
            bim = 0.5;
          } else {
            bim = -0.5;
          }
          if (X_im > 0.0) {
            b_X_im = 0.5;
          } else {
            b_X_im = -0.5;
          }
          XF_im = (XF_im * bim - XF_re * b_X_im) / deltaF;
        } else {
          deltaF = X_re / X_im;
          XF_im = (deltaF * XF_im - XF_re) / (X_im + deltaF * X_re);
        }
      }
      deltaF = -XF_im * this->fs / 6.2831853071795862;
      deltaF = rt_roundd_snf(((static_cast<double>(loop_ub) + 1.0) - 1.0) +
                             deltaF / binWidth);
      if ((deltaF > 0.0) && (deltaF < this->nPoints)) {
        spectObj->Pxx[static_cast<int>(deltaF)] =
            spectObj->Pxx[static_cast<int>(deltaF)] +
            (X_re * X_re + X_im * X_im);
      }
    }
  } else {
    b = this->nPoints;
    i = static_cast<int>(b);
    for (loop_ub = 0; loop_ub < i; loop_ub++) {
      double X_im;
      double X_re;
      b = (loop_ub + this->nPoints) + 1U;
      if (b < loop_ub + 1U) {
        b = MAX_uint32_T;
      }
      X_re = this->ur[loop_ub + this->ur.size(0) * (static_cast<int>(nEst) - 1)]
                 .re +
             this->ll[(static_cast<int>(b) +
                       this->ll.size(0) * (static_cast<int>(nEst) - 1)) -
                      1]
                 .re;
      b = (loop_ub + this->nPoints) + 1U;
      if (b < loop_ub + 1U) {
        b = MAX_uint32_T;
      }
      X_im = this->ur[loop_ub + this->ur.size(0) * (static_cast<int>(nEst) - 1)]
                 .im +
             this->ll[(static_cast<int>(b) +
                       this->ll.size(0) * (static_cast<int>(nEst) - 1)) -
                      1]
                 .im;
      spectObj->Pxx[loop_ub] =
          spectObj->Pxx[loop_ub] + (X_re * X_re + X_im * X_im);
    }
  }
  spectObj->nAvg++;
}

//
// Arguments    : double x
// Return Type  : double
//
double ZoomEstimator::besseli0of2sqrt(double x)
{
  double bessSqrt;
  if (x < 3.0) {
    double rz8;
    double w;
    double z;
    int n;
    n = 0;
    z = 1.0;
    bessSqrt = 1.0;
    rz8 = 1.0;
    w = 0.0;
    while ((w < bessSqrt) && (n < 60)) {
      w = bessSqrt;
      n++;
      z /= static_cast<double>(n * n);
      rz8 *= x;
      bessSqrt += z * rz8;
    }
  } else {
    double p;
    double rz8;
    double w;
    double z;
    z = 2.0 * sqrt(x);
    rz8 = 1.0 / (8.0 * z);
    w = 1.0;
    p = 1.0;
    for (int n = 0; n < 9; n++) {
      int num;
      num = ((n + 1) << 1) - 1;
      p = p * rz8 *
          (static_cast<double>(num * num) / (static_cast<double>(n) + 1.0));
      w += p;
    }
    bessSqrt = w * exp(z) * sqrt(rz8) * 1.1283791670955126;
  }
  return bessSqrt;
}

//
// Arguments    : double x
// Return Type  : double
//
double ZoomEstimator::dbesseli0of2sqrt(double x)
{
  double dbessSqrt;
  if (x < 3.0) {
    double p;
    double rz8;
    double z;
    z = 0.0;
    dbessSqrt = 1.0;
    p = 1.0;
    rz8 = 0.0;
    while (rz8 < dbessSqrt) {
      rz8 = dbessSqrt;
      z++;
      p = p * x * (1.0 / (z + 1.0)) * (1.0 / (z + 2.0));
      dbessSqrt += p;
    }
  } else {
    double p;
    double rz8;
    double w;
    double z;
    z = 2.0 * sqrt(x);
    rz8 = 1.0 / (8.0 * z);
    w = 1.0;
    p = 1.0;
    for (int idx = 0; idx < 9; idx++) {
      int num;
      num = ((idx + 1) << 1) - 1;
      p = p * rz8 *
          (-(4.0 - static_cast<double>(num * num)) /
           (static_cast<double>(idx) + 1.0));
      w += p;
    }
    dbessSqrt = w * exp(z) * (sqrt(rz8) / z) * 2.2567583341910251;
  }
  return dbessSqrt;
}

//
// Arguments    : unsigned int nEst
// Return Type  : double
//
double ZoomEstimator::getPowerScaling(unsigned int nEst)
{
  double powScale;
  double windowGain;
  unsigned int ifftCorrect;
  if ((this->nSamplesProcessed[static_cast<int>(nEst) - 1] > 0U) ||
      (this->ksum[static_cast<int>(nEst) - 1] == 0.0)) {
    while (this->nSamplesProcessed[static_cast<int>(nEst) - 1] <
           this->nWindow) {
      unsigned int qY;
      windowGain = 1.0;
      if (this->beta != 0.0) {
        windowGain = ZoomEstimator::besseli0of2sqrt(
            this->bpos[static_cast<int>(nEst) - 1]);
      }
      this->ksum[static_cast<int>(nEst) - 1] =
          this->ksum[static_cast<int>(nEst) - 1] + windowGain;
      this->ksumsq[static_cast<int>(nEst) - 1] =
          this->ksumsq[static_cast<int>(nEst) - 1] + windowGain * windowGain;
      this->bpos[static_cast<int>(nEst) - 1] =
          this->bpos[static_cast<int>(nEst) - 1] +
          this->bvel[static_cast<int>(nEst) - 1];
      this->bvel[static_cast<int>(nEst) - 1] =
          this->bvel[static_cast<int>(nEst) - 1] +
          this->bacc[static_cast<int>(nEst) - 1];
      ifftCorrect = this->nSamplesProcessed[static_cast<int>(nEst) - 1];
      qY = ifftCorrect + 1U;
      if (ifftCorrect + 1U < ifftCorrect) {
        qY = MAX_uint32_T;
      }
      this->nSamplesProcessed[static_cast<int>(nEst) - 1] = qY;
    }
  }
  if (this->reassign) {
    ifftCorrect = this->nfft;
    powScale = this->ksumsq[static_cast<int>(nEst) - 1] *
               static_cast<double>(ifftCorrect) *
               static_cast<double>(ifftCorrect) *
               static_cast<double>(this->nPoints);
  } else {
    windowGain = this->ksum[static_cast<int>(nEst) - 1] *
                 static_cast<double>(this->nfft);
    powScale = windowGain * windowGain;
  }
  return powScale;
}

//
// Arguments    : unsigned int nEst
// Return Type  : void
//
void ZoomEstimator::processBlock(unsigned int nEst)
{
  array<creal_T, 1U> obj;
  array<creal_T, 1U> r;
  int i;
  int loop_ub;
  loop_ub = this->bb.size(0);
  obj.set_size(loop_ub);
  for (i = 0; i < loop_ub; i++) {
    obj[i] = this->bb[i + this->bb.size(0) * (static_cast<int>(nEst) - 1)];
  }
  fft(obj, r);
  loop_ub = r.size(0);
  for (i = 0; i < loop_ub; i++) {
    this->BB[i + this->BB.size(0) * (static_cast<int>(nEst) - 1)] = r[i];
  }
  loop_ub = this->UR.size(0) - 1;
  obj.set_size(loop_ub + 1);
  for (i = 0; i <= loop_ub; i++) {
    obj[i].re =
        this->UR[i + this->UR.size(0) * (static_cast<int>(nEst) - 1)].re +
        (this->AA[i + this->AA.size(0) * (static_cast<int>(nEst) - 1)].re *
             this->BB[i + this->BB.size(0) * (static_cast<int>(nEst) - 1)].re -
         this->AA[i + this->AA.size(0) * (static_cast<int>(nEst) - 1)].im *
             this->BB[i + this->BB.size(0) * (static_cast<int>(nEst) - 1)].im);
    obj[i].im =
        this->UR[i + this->UR.size(0) * (static_cast<int>(nEst) - 1)].im +
        (this->AA[i + this->AA.size(0) * (static_cast<int>(nEst) - 1)].re *
             this->BB[i + this->BB.size(0) * (static_cast<int>(nEst) - 1)].im +
         this->AA[i + this->AA.size(0) * (static_cast<int>(nEst) - 1)].im *
             this->BB[i + this->BB.size(0) * (static_cast<int>(nEst) - 1)].re);
  }
  loop_ub = obj.size(0);
  for (i = 0; i < loop_ub; i++) {
    this->UR[i + this->UR.size(0) * (static_cast<int>(nEst) - 1)] = obj[i];
  }
  if (this->reassign) {
    loop_ub = this->bbf.size(0);
    obj.set_size(loop_ub);
    for (i = 0; i < loop_ub; i++) {
      obj[i] = this->bbf[i + this->bbf.size(0) * (static_cast<int>(nEst) - 1)];
    }
    fft(obj, r);
    loop_ub = r.size(0);
    for (i = 0; i < loop_ub; i++) {
      this->BBF[i + this->BBF.size(0) * (static_cast<int>(nEst) - 1)] = r[i];
    }
    loop_ub = this->URF.size(0) - 1;
    obj.set_size(loop_ub + 1);
    for (i = 0; i <= loop_ub; i++) {
      obj[i].re =
          this->URF[i + this->URF.size(0) * (static_cast<int>(nEst) - 1)].re +
          (this->AA[i + this->AA.size(0) * (static_cast<int>(nEst) - 1)].re *
               this->BBF[i + this->BBF.size(0) * (static_cast<int>(nEst) - 1)]
                   .re -
           this->AA[i + this->AA.size(0) * (static_cast<int>(nEst) - 1)].im *
               this->BBF[i + this->BBF.size(0) * (static_cast<int>(nEst) - 1)]
                   .im);
      obj[i].im =
          this->URF[i + this->URF.size(0) * (static_cast<int>(nEst) - 1)].im +
          (this->AA[i + this->AA.size(0) * (static_cast<int>(nEst) - 1)].re *
               this->BBF[i + this->BBF.size(0) * (static_cast<int>(nEst) - 1)]
                   .im +
           this->AA[i + this->AA.size(0) * (static_cast<int>(nEst) - 1)].im *
               this->BBF[i + this->BBF.size(0) * (static_cast<int>(nEst) - 1)]
                   .re);
    }
    loop_ub = obj.size(0);
    for (i = 0; i < loop_ub; i++) {
      this->URF[i + this->URF.size(0) * (static_cast<int>(nEst) - 1)] = obj[i];
    }
    if (!this->selfAssign) {
      loop_ub = this->bbt.size(0);
      obj.set_size(loop_ub);
      for (i = 0; i < loop_ub; i++) {
        obj[i] =
            this->bbt[i + this->bbt.size(0) * (static_cast<int>(nEst) - 1)];
      }
      fft(obj, r);
      loop_ub = r.size(0);
      for (i = 0; i < loop_ub; i++) {
        this->BBT[i + this->BBT.size(0) * (static_cast<int>(nEst) - 1)] = r[i];
      }
      loop_ub = this->URT.size(0) - 1;
      obj.set_size(loop_ub + 1);
      for (i = 0; i <= loop_ub; i++) {
        obj[i].re =
            this->URT[i + this->URT.size(0) * (static_cast<int>(nEst) - 1)].re +
            (this->AA[i + this->AA.size(0) * (static_cast<int>(nEst) - 1)].re *
                 this->BBT[i + this->BBT.size(0) * (static_cast<int>(nEst) - 1)]
                     .re -
             this->AA[i + this->AA.size(0) * (static_cast<int>(nEst) - 1)].im *
                 this->BBT[i + this->BBT.size(0) * (static_cast<int>(nEst) - 1)]
                     .im);
        obj[i].im =
            this->URT[i + this->URT.size(0) * (static_cast<int>(nEst) - 1)].im +
            (this->AA[i + this->AA.size(0) * (static_cast<int>(nEst) - 1)].re *
                 this->BBT[i + this->BBT.size(0) * (static_cast<int>(nEst) - 1)]
                     .im +
             this->AA[i + this->AA.size(0) * (static_cast<int>(nEst) - 1)].im *
                 this->BBT[i + this->BBT.size(0) * (static_cast<int>(nEst) - 1)]
                     .re);
      }
      loop_ub = obj.size(0);
      for (i = 0; i < loop_ub; i++) {
        this->URT[i + this->URT.size(0) * (static_cast<int>(nEst) - 1)] =
            obj[i];
      }
    }
  }
  i = static_cast<int>(this->nPoints);
  for (loop_ub = 0; loop_ub < i; loop_ub++) {
    double im;
    unsigned int q0;
    unsigned int qY;
    q0 = this->nPoints;
    qY = (q0 - loop_ub) - 1U;
    if (qY > q0) {
      qY = 0U;
    }
    this->aa[static_cast<int>(qY) +
             this->aa.size(0) * (static_cast<int>(nEst) - 1)] =
        this->Wwpos[static_cast<int>(nEst) - 1];
    im = this->Wwpos[static_cast<int>(nEst) - 1].re *
             this->Wwvel[static_cast<int>(nEst) - 1].im +
         this->Wwpos[static_cast<int>(nEst) - 1].im *
             this->Wwvel[static_cast<int>(nEst) - 1].re;
    this->Wwpos[static_cast<int>(nEst) - 1].re =
        this->Wwpos[static_cast<int>(nEst) - 1].re *
            this->Wwvel[static_cast<int>(nEst) - 1].re -
        this->Wwpos[static_cast<int>(nEst) - 1].im *
            this->Wwvel[static_cast<int>(nEst) - 1].im;
    this->Wwpos[static_cast<int>(nEst) - 1].im = im;
    im = this->Wwvel[static_cast<int>(nEst) - 1].re *
             this->Wwacc[static_cast<int>(nEst) - 1].im +
         this->Wwvel[static_cast<int>(nEst) - 1].im *
             this->Wwacc[static_cast<int>(nEst) - 1].re;
    this->Wwvel[static_cast<int>(nEst) - 1].re =
        this->Wwvel[static_cast<int>(nEst) - 1].re *
            this->Wwacc[static_cast<int>(nEst) - 1].re -
        this->Wwvel[static_cast<int>(nEst) - 1].im *
            this->Wwacc[static_cast<int>(nEst) - 1].im;
    this->Wwvel[static_cast<int>(nEst) - 1].im = im;
  }
  loop_ub = this->aa.size(0);
  obj.set_size(loop_ub);
  for (i = 0; i < loop_ub; i++) {
    obj[i] = this->aa[i + this->aa.size(0) * (static_cast<int>(nEst) - 1)];
  }
  fft(obj, r);
  loop_ub = r.size(0);
  for (i = 0; i < loop_ub; i++) {
    this->AA[i + this->AA.size(0) * (static_cast<int>(nEst) - 1)] = r[i];
  }
  loop_ub = this->LL.size(0) - 1;
  obj.set_size(loop_ub + 1);
  for (i = 0; i <= loop_ub; i++) {
    obj[i].re =
        this->LL[i + this->LL.size(0) * (static_cast<int>(nEst) - 1)].re +
        (this->AA[i + this->AA.size(0) * (static_cast<int>(nEst) - 1)].re *
             this->BB[i + this->BB.size(0) * (static_cast<int>(nEst) - 1)].re -
         this->AA[i + this->AA.size(0) * (static_cast<int>(nEst) - 1)].im *
             this->BB[i + this->BB.size(0) * (static_cast<int>(nEst) - 1)].im);
    obj[i].im =
        this->LL[i + this->LL.size(0) * (static_cast<int>(nEst) - 1)].im +
        (this->AA[i + this->AA.size(0) * (static_cast<int>(nEst) - 1)].re *
             this->BB[i + this->BB.size(0) * (static_cast<int>(nEst) - 1)].im +
         this->AA[i + this->AA.size(0) * (static_cast<int>(nEst) - 1)].im *
             this->BB[i + this->BB.size(0) * (static_cast<int>(nEst) - 1)].re);
  }
  loop_ub = obj.size(0);
  for (i = 0; i < loop_ub; i++) {
    this->LL[i + this->LL.size(0) * (static_cast<int>(nEst) - 1)] = obj[i];
  }
  if (this->reassign) {
    loop_ub = this->LLF.size(0) - 1;
    obj.set_size(loop_ub + 1);
    for (i = 0; i <= loop_ub; i++) {
      obj[i].re =
          this->LLF[i + this->LLF.size(0) * (static_cast<int>(nEst) - 1)].re +
          (this->AA[i + this->AA.size(0) * (static_cast<int>(nEst) - 1)].re *
               this->BBF[i + this->BBF.size(0) * (static_cast<int>(nEst) - 1)]
                   .re -
           this->AA[i + this->AA.size(0) * (static_cast<int>(nEst) - 1)].im *
               this->BBF[i + this->BBF.size(0) * (static_cast<int>(nEst) - 1)]
                   .im);
      obj[i].im =
          this->LLF[i + this->LLF.size(0) * (static_cast<int>(nEst) - 1)].im +
          (this->AA[i + this->AA.size(0) * (static_cast<int>(nEst) - 1)].re *
               this->BBF[i + this->BBF.size(0) * (static_cast<int>(nEst) - 1)]
                   .im +
           this->AA[i + this->AA.size(0) * (static_cast<int>(nEst) - 1)].im *
               this->BBF[i + this->BBF.size(0) * (static_cast<int>(nEst) - 1)]
                   .re);
    }
    loop_ub = obj.size(0);
    for (i = 0; i < loop_ub; i++) {
      this->LLF[i + this->LLF.size(0) * (static_cast<int>(nEst) - 1)] = obj[i];
    }
    if (!this->selfAssign) {
      loop_ub = this->LLT.size(0) - 1;
      obj.set_size(loop_ub + 1);
      for (i = 0; i <= loop_ub; i++) {
        obj[i].re =
            this->LLT[i + this->LLT.size(0) * (static_cast<int>(nEst) - 1)].re +
            (this->AA[i + this->AA.size(0) * (static_cast<int>(nEst) - 1)].re *
                 this->BBT[i + this->BBT.size(0) * (static_cast<int>(nEst) - 1)]
                     .re -
             this->AA[i + this->AA.size(0) * (static_cast<int>(nEst) - 1)].im *
                 this->BBT[i + this->BBT.size(0) * (static_cast<int>(nEst) - 1)]
                     .im);
        obj[i].im =
            this->LLT[i + this->LLT.size(0) * (static_cast<int>(nEst) - 1)].im +
            (this->AA[i + this->AA.size(0) * (static_cast<int>(nEst) - 1)].re *
                 this->BBT[i + this->BBT.size(0) * (static_cast<int>(nEst) - 1)]
                     .im +
             this->AA[i + this->AA.size(0) * (static_cast<int>(nEst) - 1)].im *
                 this->BBT[i + this->BBT.size(0) * (static_cast<int>(nEst) - 1)]
                     .re);
      }
      loop_ub = obj.size(0);
      for (i = 0; i < loop_ub; i++) {
        this->LLT[i + this->LLT.size(0) * (static_cast<int>(nEst) - 1)] =
            obj[i];
      }
    }
  }
}

//
// Arguments    : unsigned int idx
// Return Type  : void
//
void ZoomEstimator::reset(unsigned int idx)
{
  array<creal_T, 1U> obj;
  array<creal_T, 1U> r;
  double b;
  double dk;
  double k0;
  double re_tmp;
  double y_im;
  double y_re;
  double y_re_tmp;
  unsigned int b_qY;
  unsigned int c_qY;
  unsigned int d_qY;
  int i;
  int loop_ub_tmp_tmp;
  unsigned int q0;
  unsigned int qY;
  loop_ub_tmp_tmp = static_cast<int>(this->nfft);
  for (i = 0; i < loop_ub_tmp_tmp; i++) {
    this->aa[i + this->aa.size(0) * (static_cast<int>(idx) - 1)].re = 0.0;
    this->aa[i + this->aa.size(0) * (static_cast<int>(idx) - 1)].im = 0.0;
  }
  loop_ub_tmp_tmp = static_cast<int>(this->nfft);
  for (i = 0; i < loop_ub_tmp_tmp; i++) {
    this->bb[i + this->bb.size(0) * (static_cast<int>(idx) - 1)].re = 0.0;
    this->bb[i + this->bb.size(0) * (static_cast<int>(idx) - 1)].im = 0.0;
  }
  loop_ub_tmp_tmp = static_cast<int>(this->nfft);
  for (i = 0; i < loop_ub_tmp_tmp; i++) {
    this->UR[i + this->UR.size(0) * (static_cast<int>(idx) - 1)].re = 0.0;
    this->UR[i + this->UR.size(0) * (static_cast<int>(idx) - 1)].im = 0.0;
  }
  loop_ub_tmp_tmp = static_cast<int>(this->nfft);
  for (i = 0; i < loop_ub_tmp_tmp; i++) {
    this->LL[i + this->LL.size(0) * (static_cast<int>(idx) - 1)].re = 0.0;
    this->LL[i + this->LL.size(0) * (static_cast<int>(idx) - 1)].im = 0.0;
  }
  if (this->reassign) {
    loop_ub_tmp_tmp = static_cast<int>(this->nfft);
    for (i = 0; i < loop_ub_tmp_tmp; i++) {
      this->bbf[i + this->bbf.size(0) * (static_cast<int>(idx) - 1)].re = 0.0;
      this->bbf[i + this->bbf.size(0) * (static_cast<int>(idx) - 1)].im = 0.0;
    }
    loop_ub_tmp_tmp = static_cast<int>(this->nfft);
    for (i = 0; i < loop_ub_tmp_tmp; i++) {
      this->URF[i + this->URF.size(0) * (static_cast<int>(idx) - 1)].re = 0.0;
      this->URF[i + this->URF.size(0) * (static_cast<int>(idx) - 1)].im = 0.0;
    }
    loop_ub_tmp_tmp = static_cast<int>(this->nfft);
    for (i = 0; i < loop_ub_tmp_tmp; i++) {
      this->LLF[i + this->LLF.size(0) * (static_cast<int>(idx) - 1)].re = 0.0;
      this->LLF[i + this->LLF.size(0) * (static_cast<int>(idx) - 1)].im = 0.0;
    }
    if (!this->selfAssign) {
      loop_ub_tmp_tmp = static_cast<int>(this->nfft);
      for (i = 0; i < loop_ub_tmp_tmp; i++) {
        this->bbt[i + this->bbt.size(0) * (static_cast<int>(idx) - 1)].re = 0.0;
        this->bbt[i + this->bbt.size(0) * (static_cast<int>(idx) - 1)].im = 0.0;
      }
      loop_ub_tmp_tmp = static_cast<int>(this->nfft);
      for (i = 0; i < loop_ub_tmp_tmp; i++) {
        this->URT[i + this->URT.size(0) * (static_cast<int>(idx) - 1)].re = 0.0;
        this->URT[i + this->URT.size(0) * (static_cast<int>(idx) - 1)].im = 0.0;
      }
      loop_ub_tmp_tmp = static_cast<int>(this->nfft);
      for (i = 0; i < loop_ub_tmp_tmp; i++) {
        this->LLT[i + this->LLT.size(0) * (static_cast<int>(idx) - 1)].re = 0.0;
        this->LLT[i + this->LLT.size(0) * (static_cast<int>(idx) - 1)].im = 0.0;
      }
    }
  }
  q0 = this->nWindow;
  qY = q0 - 1U;
  if (q0 - 1U > q0) {
    qY = 0U;
  }
  b = this->beta * this->beta /
      (static_cast<double>(qY) * static_cast<double>(qY));
  this->bpos[static_cast<int>(idx) - 1] = 0.0;
  this->bvel[static_cast<int>(idx) - 1] = b * (static_cast<double>(qY) - 1.0);
  this->bacc[static_cast<int>(idx) - 1] = -2.0 * b;
  k0 = this->fstart / this->fs;
  q0 = this->nPoints;
  b_qY = q0 - 1U;
  if (q0 - 1U > q0) {
    b_qY = 0U;
  }
  y_re = rt_roundd_snf(static_cast<double>(b_qY) * this->fs);
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
  dk = (this->fstart - this->fstop) / static_cast<double>(q0);
  this->Wxpos[static_cast<int>(idx) - 1].re = 1.0;
  this->Wxpos[static_cast<int>(idx) - 1].im = 0.0;
  y_re_tmp = dk - 2.0 * k0;
  y_re = y_re_tmp * 0.0;
  y_im = y_re_tmp * 3.1415926535897931;
  if (y_im == 0.0) {
    this->Wxvel[static_cast<int>(idx) - 1].re = exp(y_re);
    this->Wxvel[static_cast<int>(idx) - 1].im = 0.0;
  } else {
    k0 = exp(y_re / 2.0);
    this->Wxvel[static_cast<int>(idx) - 1].re = k0 * (k0 * cos(y_im));
    this->Wxvel[static_cast<int>(idx) - 1].im = k0 * (k0 * sin(y_im));
  }
  y_re_tmp = dk * 0.0;
  y_im = dk * 6.2831853071795862;
  if (y_im == 0.0) {
    this->Wxacc[static_cast<int>(idx) - 1].re = exp(y_re_tmp);
    this->Wxacc[static_cast<int>(idx) - 1].im = 0.0;
  } else {
    k0 = exp(y_re_tmp / 2.0);
    this->Wxacc[static_cast<int>(idx) - 1].re = k0 * (k0 * cos(y_im));
    this->Wxacc[static_cast<int>(idx) - 1].im = k0 * (k0 * sin(y_im));
  }
  re_tmp = dk * -0.0;
  q0 = this->nPoints;
  b_qY = q0 - 1U;
  if (q0 - 1U > q0) {
    b_qY = 0U;
  }
  q0 = this->nPoints;
  c_qY = q0 - 1U;
  if (q0 - 1U > q0) {
    c_qY = 0U;
  }
  q0 = this->nPoints;
  d_qY = q0 - 1U;
  if (q0 - 1U > q0) {
    d_qY = 0U;
  }
  y_re = static_cast<double>(d_qY) * (static_cast<double>(b_qY) * re_tmp);
  q0 = this->nPoints;
  b_qY = q0 - 1U;
  if (q0 - 1U > q0) {
    b_qY = 0U;
  }
  y_im = static_cast<double>(b_qY) *
         (static_cast<double>(c_qY) * (dk * -3.1415926535897931));
  if (y_im == 0.0) {
    this->Wwpos[static_cast<int>(idx) - 1].re = exp(y_re);
    this->Wwpos[static_cast<int>(idx) - 1].im = 0.0;
  } else {
    k0 = exp(y_re / 2.0);
    this->Wwpos[static_cast<int>(idx) - 1].re = k0 * (k0 * cos(y_im));
    this->Wwpos[static_cast<int>(idx) - 1].im = k0 * (k0 * sin(y_im));
  }
  q0 = this->nPoints;
  if (q0 > 2147483647U) {
    q0 = MAX_uint32_T;
  } else {
    q0 <<= 1;
  }
  b_qY = q0 - 3U;
  if (q0 - 3U > q0) {
    b_qY = 0U;
  }
  y_re = static_cast<double>(b_qY) * y_re_tmp;
  q0 = this->nPoints;
  if (q0 > 2147483647U) {
    q0 = MAX_uint32_T;
  } else {
    q0 <<= 1;
  }
  b_qY = q0 - 3U;
  if (q0 - 3U > q0) {
    b_qY = 0U;
  }
  y_im = static_cast<double>(b_qY) * (dk * 3.1415926535897931);
  if (y_im == 0.0) {
    this->Wwvel[static_cast<int>(idx) - 1].re = exp(y_re);
    this->Wwvel[static_cast<int>(idx) - 1].im = 0.0;
  } else {
    k0 = exp(y_re / 2.0);
    this->Wwvel[static_cast<int>(idx) - 1].re = k0 * (k0 * cos(y_im));
    this->Wwvel[static_cast<int>(idx) - 1].im = k0 * (k0 * sin(y_im));
  }
  y_im = dk * -6.2831853071795862;
  if (y_im == 0.0) {
    this->Wwacc[static_cast<int>(idx) - 1].re = exp(re_tmp);
    this->Wwacc[static_cast<int>(idx) - 1].im = 0.0;
  } else {
    k0 = exp(re_tmp / 2.0);
    this->Wwacc[static_cast<int>(idx) - 1].re = k0 * (k0 * cos(y_im));
    this->Wwacc[static_cast<int>(idx) - 1].im = k0 * (k0 * sin(y_im));
  }
  this->ibuf[static_cast<int>(idx) - 1] = 0.0;
  this->nSamplesProcessed[static_cast<int>(idx) - 1] = 0U;
  this->ksum[static_cast<int>(idx) - 1] = 0.0;
  this->ksumsq[static_cast<int>(idx) - 1] = 0.0;
  this->dtpos[static_cast<int>(idx) - 1] = static_cast<double>(qY) * b;
  this->dtvel[static_cast<int>(idx) - 1] = -2.0 * b;
  this->dfpos[static_cast<int>(idx) - 1] = 0.0;
  if (this->fs > 0.0) {
    this->dfpos[static_cast<int>(idx) - 1] =
        -static_cast<double>(qY) / (2.0 * this->fs);
  }
  this->dfvel[static_cast<int>(idx) - 1] = 0.0;
  if (this->fs > 0.0) {
    this->dfvel[static_cast<int>(idx) - 1] = 1.0 / this->fs;
  }
  i = static_cast<int>(this->nPoints);
  for (loop_ub_tmp_tmp = 0; loop_ub_tmp_tmp < i; loop_ub_tmp_tmp++) {
    q0 = this->nPoints;
    qY = (q0 - loop_ub_tmp_tmp) - 1U;
    if (qY > q0) {
      qY = 0U;
    }
    this->aa[static_cast<int>(qY) +
             this->aa.size(0) * (static_cast<int>(idx) - 1)] =
        this->Wwpos[static_cast<int>(idx) - 1];
    y_re = this->Wwpos[static_cast<int>(idx) - 1].re *
               this->Wwvel[static_cast<int>(idx) - 1].im +
           this->Wwpos[static_cast<int>(idx) - 1].im *
               this->Wwvel[static_cast<int>(idx) - 1].re;
    this->Wwpos[static_cast<int>(idx) - 1].re =
        this->Wwpos[static_cast<int>(idx) - 1].re *
            this->Wwvel[static_cast<int>(idx) - 1].re -
        this->Wwpos[static_cast<int>(idx) - 1].im *
            this->Wwvel[static_cast<int>(idx) - 1].im;
    this->Wwpos[static_cast<int>(idx) - 1].im = y_re;
    y_re = this->Wwvel[static_cast<int>(idx) - 1].re *
               this->Wwacc[static_cast<int>(idx) - 1].im +
           this->Wwvel[static_cast<int>(idx) - 1].im *
               this->Wwacc[static_cast<int>(idx) - 1].re;
    this->Wwvel[static_cast<int>(idx) - 1].re =
        this->Wwvel[static_cast<int>(idx) - 1].re *
            this->Wwacc[static_cast<int>(idx) - 1].re -
        this->Wwvel[static_cast<int>(idx) - 1].im *
            this->Wwacc[static_cast<int>(idx) - 1].im;
    this->Wwvel[static_cast<int>(idx) - 1].im = y_re;
  }
  loop_ub_tmp_tmp = this->aa.size(0);
  obj.set_size(loop_ub_tmp_tmp);
  for (i = 0; i < loop_ub_tmp_tmp; i++) {
    obj[i] = this->aa[i + this->aa.size(0) * (static_cast<int>(idx) - 1)];
  }
  fft(obj, r);
  loop_ub_tmp_tmp = r.size(0);
  for (i = 0; i < loop_ub_tmp_tmp; i++) {
    this->AA[i + this->AA.size(0) * (static_cast<int>(idx) - 1)] = r[i];
  }
}

} // namespace pspectrum
} // namespace codegenable
} // namespace internal
} // namespace signal
} // namespace coder

//
// File trailer for ZoomEstimator.cpp
//
// [EOF]
//
