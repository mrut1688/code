//
// File: Spectrogram.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 23-Aug-2023 11:38:45
//

// Include Files
#include "Spectrogram.h"
#include "WindowDataBuffer.h"
#include "ZoomEstimator.h"
#include "ZoomSpectrum.h"
#include "computeOverlapSamples.h"
#include "data_pspm_data.h"
#include "data_pspm_rtwutil.h"
#include "ifft.h"
#include "mrdivide_helper.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <math.h>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &dataRe
//                const ::coder::array<double, 2U> &dataIm
//                double dataBeginTime
//                unsigned int numOfWin
// Return Type  : void
//
namespace coder {
namespace signal {
namespace internal {
namespace codegenable {
namespace pspectrum {
void Spectrogram::computeSpectrogramCore(
    const ::coder::array<double, 2U> &dataRe,
    const ::coder::array<double, 2U> &dataIm, double dataBeginTime,
    unsigned int numOfWin)
{
  ZoomEstimator lobj_1;
  ZoomEstimator *obj;
  ZoomSpectrum lZoomSpectrum;
  array<creal_T, 2U> b_dataRe;
  array<creal_T, 1U> a;
  array<creal_T, 1U> b_obj;
  array<double, 1U> df;
  array<double, 1U> dstSpectrum;
  array<int, 1U> r;
  if ((this->winStartIndex < this->totalWindows) &&
      (this->LastWindowTEnd < this->signalEndTime + 1.0 / this->fs)) {
    unsigned int q0;
    unsigned int qY;
    unsigned int u;
    dataBeginTime *= this->timeFactor;
    u = this->winStartIndex;
    q0 = this->winStartIndex;
    qY = q0 + numOfWin;
    if (qY < q0) {
      qY = MAX_uint32_T;
    }
    for (unsigned int idx = u; idx <= qY; idx++) {
      double X_re;
      double gain;
      double t1Seg;
      double t2Seg;
      double tEnd;
      double tStart;
      double ts;
      unsigned int b_qY;
      int loop_ub;
      int u1;
      boolean_T guard1 = false;
      boolean_T isConvertToDBFlag;
      b_qY = idx - this->winStartIndex;
      if (b_qY > idx) {
        b_qY = 0U;
      }
      tStart = dataBeginTime + static_cast<double>(b_qY) *
                                   (this->timeResolution - this->overlap);
      tEnd = tStart + this->timeResolution;
      b_qY = idx + 1U;
      if (idx + 1U < idx) {
        b_qY = MAX_uint32_T;
      }
      this->timeVector[static_cast<int>(b_qY) - 1] =
          tStart + (tEnd - tStart) / 2.0;
      lZoomSpectrum.init();
      lZoomSpectrum.setup(tStart, tEnd, this->f1, this->f2, this->beta,
                          this->nPoints, this->maxFs, this->useZoomFFT,
                          this->useReassignement);
      gain = this->signalBeginTime;
      t2Seg = this->signalEndTime;
      lZoomSpectrum.t0 = dataBeginTime;
      lZoomSpectrum.fs = this->fs;
      ts = 1.0 / lZoomSpectrum.fs;
      X_re = lZoomSpectrum.t1;
      if ((gain > X_re) || rtIsNaN(X_re)) {
        t1Seg = gain;
      } else {
        t1Seg = X_re;
      }
      X_re = lZoomSpectrum.t2;
      if ((!(t2Seg < X_re)) && (!rtIsNaN(X_re))) {
        t2Seg = X_re;
      }
      gain = (t2Seg - t1Seg) * lZoomSpectrum.fs;
      X_re = floor(fabs(gain));
      if (X_re < 4.294967296E+9) {
        b_qY = static_cast<unsigned int>(X_re);
      } else if (X_re >= 4.294967296E+9) {
        b_qY = MAX_uint32_T;
      } else {
        b_qY = 0U;
      }
      if (b_qY == 0U) {
        lZoomSpectrum.nExpected = 1U;
      } else {
        lZoomSpectrum.nExpected = b_qY;
      }
      lZoomSpectrum.nRemaining = lZoomSpectrum.nExpected;
      lZoomSpectrum.nProcessed = 0.0;
      lZoomSpectrum.nSkip = 0U;
      if (lZoomSpectrum.t0 < t1Seg) {
        gain = (t1Seg - lZoomSpectrum.t0) * lZoomSpectrum.fs;
        gain = floor(gain);
        if (gain < 4.294967296E+9) {
          if (gain >= 0.0) {
            b_qY = static_cast<unsigned int>(gain);
          } else {
            b_qY = 0U;
          }
        } else if (gain >= 4.294967296E+9) {
          b_qY = MAX_uint32_T;
        } else {
          b_qY = 0U;
        }
        lZoomSpectrum.nSkip = b_qY;
      } else if (lZoomSpectrum.t0 - t1Seg > ts) {
        gain = lZoomSpectrum.fs * (lZoomSpectrum.t0 - t1Seg);
        gain = floor(gain);
        q0 = lZoomSpectrum.nRemaining;
        if (gain < 4.294967296E+9) {
          if (gain >= 0.0) {
            b_qY = static_cast<unsigned int>(gain);
          } else {
            b_qY = 0U;
          }
        } else if (gain >= 4.294967296E+9) {
          b_qY = MAX_uint32_T;
        } else {
          b_qY = 0U;
        }
        b_qY = q0 - b_qY;
        if (b_qY > q0) {
          b_qY = 0U;
        }
        lZoomSpectrum.nRemaining = b_qY;
      }
      if (lZoomSpectrum.t0 > t2Seg) {
        lZoomSpectrum.nRemaining = 1U;
      }
      lZoomSpectrum.configureCZT(&lobj_1);
      lZoomSpectrum.Pxx.set_size(static_cast<int>(lZoomSpectrum.nPoints));
      loop_ub = static_cast<int>(lZoomSpectrum.nPoints);
      for (u1 = 0; u1 < loop_ub; u1++) {
        lZoomSpectrum.Pxx[u1] = 0.0;
      }
      lZoomSpectrum.nAvg = 0.0;
      if (this->bIsTwoSided) {
        b_dataRe.set_size(dataRe.size(0), dataRe.size(1));
        loop_ub = dataRe.size(0) * dataRe.size(1);
        for (u1 = 0; u1 < loop_ub; u1++) {
          b_dataRe[u1].re = dataRe[u1];
          b_dataRe[u1].im = dataIm[u1];
        }
        lZoomSpectrum.processSegment(b_dataRe);
      } else {
        unsigned int b_idx;
        if ((dataRe.size(0) == 0) || (dataRe.size(1) == 0)) {
          u1 = 0;
        } else {
          loop_ub = dataRe.size(0);
          u1 = dataRe.size(1);
          if (loop_ub > u1) {
            u1 = loop_ub;
          }
        }
        b_idx = 0U;
        while ((b_idx < static_cast<unsigned int>(u1)) &&
               (lZoomSpectrum.nSkip != 0U)) {
          b_idx++;
          q0 = lZoomSpectrum.nSkip;
          b_qY = q0 - 1U;
          if (q0 - 1U > q0) {
            b_qY = 0U;
          }
          lZoomSpectrum.nSkip = b_qY;
        }
        while ((b_idx < static_cast<unsigned int>(u1)) &&
               (lZoomSpectrum.nRemaining != 0U)) {
          lZoomSpectrum.processSample(dataRe[static_cast<int>(b_idx)]);
          b_idx++;
          q0 = lZoomSpectrum.nRemaining;
          b_qY = q0 - 1U;
          if (q0 - 1U > q0) {
            b_qY = 0U;
          }
          lZoomSpectrum.nRemaining = b_qY;
          lZoomSpectrum.nProcessed++;
        }
      }
      if ((!this->useReassignement) && this->bIsConvertToDB) {
        isConvertToDBFlag = true;
      } else {
        isConvertToDBFlag = false;
      }
      if (this->bIsTwoSided) {
        gain = lZoomSpectrum.finalizeSpectrum();
        dstSpectrum.set_size(static_cast<int>(lZoomSpectrum.nPoints));
        loop_ub = static_cast<int>(lZoomSpectrum.nPoints);
        for (u1 = 0; u1 < loop_ub; u1++) {
          dstSpectrum[u1] = 0.0;
        }
        lZoomSpectrum.fetchSpectrum(isConvertToDBFlag, gain, dstSpectrum);
      } else {
        gain = lZoomSpectrum.finalizeSpectrum() / 2.0;
        dstSpectrum.set_size(static_cast<int>(lZoomSpectrum.nPoints));
        loop_ub = static_cast<int>(lZoomSpectrum.nPoints);
        for (u1 = 0; u1 < loop_ub; u1++) {
          dstSpectrum[u1] = 0.0;
        }
        lZoomSpectrum.fetchSpectrum(isConvertToDBFlag, gain, dstSpectrum);
      }
      if (rtIsInf(this->tgtRBW)) {
        this->tgtRBW = lZoomSpectrum.targetRBW;
      }
      guard1 = false;
      if (this->bComputeZLimits && (!this->useReassignement)) {
        X_re = this->t1 * this->timeFactor;
        if ((tStart < X_re) && (tEnd < X_re)) {
          guard1 = true;
        } else {
          X_re = this->t2 * this->timeFactor;
          if ((tStart > X_re) && (tEnd > X_re)) {
            guard1 = true;
          } else {
            X_re = this->zMin;
            gain = this->zMax;
            u1 = dstSpectrum.size(0);
            for (loop_ub = 0; loop_ub < u1; loop_ub++) {
              if ((!rtIsInf(dstSpectrum[loop_ub])) &&
                  (!rtIsNaN(dstSpectrum[loop_ub]))) {
                if (dstSpectrum[loop_ub] < X_re) {
                  X_re = dstSpectrum[loop_ub];
                }
                if (dstSpectrum[loop_ub] > gain) {
                  gain = dstSpectrum[loop_ub];
                }
              }
            }
            this->zMin = X_re;
            this->zMax = gain;
          }
        }
      } else {
        guard1 = true;
      }
      if (guard1 && (this->bComputeZLimits && this->useReassignement)) {
        X_re = this->t1 * this->timeFactor;
        if ((!(tStart < X_re)) || (!(tEnd < X_re))) {
          X_re = this->t2 * this->timeFactor;
          if ((!(tStart > X_re)) || (!(tEnd > X_re))) {
            b_qY = idx + 1U;
            if (idx + 1U < idx) {
              b_qY = MAX_uint32_T;
            }
            this->bIncludeInZlimitsCalculation[static_cast<int>(b_qY) - 1] =
                this->bComputeZLimits;
          }
        }
      }
      b_qY = idx + 1U;
      if (idx + 1U < idx) {
        b_qY = MAX_uint32_T;
      }
      loop_ub = this->mStftMatrix.size(1);
      r.set_size(loop_ub);
      for (u1 = 0; u1 < loop_ub; u1++) {
        r[u1] = u1;
      }
      loop_ub = r.size(0);
      for (u1 = 0; u1 < loop_ub; u1++) {
        this->mStftMatrix[(static_cast<int>(b_qY) +
                           this->mStftMatrix.size(0) * r[u1]) -
                          1] = dstSpectrum[u1];
      }
      if (this->useReassignement) {
        dstSpectrum.set_size(static_cast<int>(lZoomSpectrum.nPoints));
        loop_ub = static_cast<int>(lZoomSpectrum.nPoints);
        for (u1 = 0; u1 < loop_ub; u1++) {
          dstSpectrum[u1] = 0.0;
        }
        if (lZoomSpectrum.nEstimators == 1U) {
          obj = lZoomSpectrum.Estimators;
          dstSpectrum.set_size(static_cast<int>(obj->nPoints));
          loop_ub = static_cast<int>(obj->nPoints);
          for (u1 = 0; u1 < loop_ub; u1++) {
            dstSpectrum[u1] = 0.0;
          }
          if (obj->reassign && (!obj->selfAssign)) {
            loop_ub = obj->urt.size(0);
            r.set_size(loop_ub);
            for (u1 = 0; u1 < loop_ub; u1++) {
              r[u1] = u1;
            }
            loop_ub = obj->URT.size(0);
            b_obj.set_size(loop_ub);
            for (u1 = 0; u1 < loop_ub; u1++) {
              b_obj[u1] = obj->URT[u1];
            }
            ifft(b_obj, a);
            b_qY = obj->nfft;
            loop_ub = a.size(0);
            for (u1 = 0; u1 < loop_ub; u1++) {
              obj->urt[r[u1]].re = static_cast<double>(b_qY) * a[u1].re;
              obj->urt[r[u1]].im = static_cast<double>(b_qY) * a[u1].im;
            }
            loop_ub = obj->llt.size(0);
            r.set_size(loop_ub);
            for (u1 = 0; u1 < loop_ub; u1++) {
              r[u1] = u1;
            }
            loop_ub = obj->LLT.size(0);
            b_obj.set_size(loop_ub);
            for (u1 = 0; u1 < loop_ub; u1++) {
              b_obj[u1] = obj->LLT[u1];
            }
            ifft(b_obj, a);
            b_qY = obj->nfft;
            loop_ub = a.size(0);
            for (u1 = 0; u1 < loop_ub; u1++) {
              obj->llt[r[u1]].re = static_cast<double>(b_qY) * a[u1].re;
              obj->llt[r[u1]].im = static_cast<double>(b_qY) * a[u1].im;
            }
            b_qY = obj->nPoints;
            u1 = static_cast<int>(b_qY);
            for (loop_ub = 0; loop_ub < u1; loop_ub++) {
              b_qY = (loop_ub + obj->nPoints) + 1U;
              if (b_qY < loop_ub + 1U) {
                b_qY = MAX_uint32_T;
              }
              X_re =
                  obj->ur[loop_ub].re + obj->ll[static_cast<int>(b_qY) - 1].re;
              b_qY = (loop_ub + obj->nPoints) + 1U;
              if (b_qY < loop_ub + 1U) {
                b_qY = MAX_uint32_T;
              }
              t1Seg =
                  obj->ur[loop_ub].im + obj->ll[static_cast<int>(b_qY) - 1].im;
              b_qY = (loop_ub + obj->nPoints) + 1U;
              if (b_qY < loop_ub + 1U) {
                b_qY = MAX_uint32_T;
              }
              ts = obj->urt[loop_ub].re +
                   obj->llt[static_cast<int>(b_qY) - 1].re;
              b_qY = (loop_ub + obj->nPoints) + 1U;
              if (b_qY < loop_ub + 1U) {
                b_qY = MAX_uint32_T;
              }
              tStart = obj->urt[loop_ub].im +
                       obj->llt[static_cast<int>(b_qY) - 1].im;
              if (t1Seg == 0.0) {
                if (tStart == 0.0) {
                  ts /= X_re;
                } else if (ts == 0.0) {
                  ts = 0.0;
                } else {
                  ts /= X_re;
                }
              } else if (X_re == 0.0) {
                if (ts == 0.0) {
                  ts = tStart / t1Seg;
                } else if (tStart == 0.0) {
                  ts = 0.0;
                } else {
                  ts = tStart / t1Seg;
                }
              } else {
                gain = fabs(X_re);
                t2Seg = fabs(t1Seg);
                if (gain > t2Seg) {
                  gain = t1Seg / X_re;
                  ts = (ts + gain * tStart) / (X_re + gain * t1Seg);
                } else if (t2Seg == gain) {
                  if (X_re > 0.0) {
                    X_re = 0.5;
                  } else {
                    X_re = -0.5;
                  }
                  if (t1Seg > 0.0) {
                    t1Seg = 0.5;
                  } else {
                    t1Seg = -0.5;
                  }
                  ts = (ts * X_re + tStart * t1Seg) / gain;
                } else {
                  gain = X_re / t1Seg;
                  ts = (gain * ts + tStart) / (t1Seg + gain * X_re);
                }
              }
              dstSpectrum[loop_ub] = ts;
            }
          }
        }
        df.set_size(static_cast<int>(lZoomSpectrum.nPoints));
        loop_ub = static_cast<int>(lZoomSpectrum.nPoints);
        for (u1 = 0; u1 < loop_ub; u1++) {
          df[u1] = 0.0;
        }
        if (lZoomSpectrum.nEstimators == 1U) {
          obj = lZoomSpectrum.Estimators;
          df.set_size(static_cast<int>(obj->nPoints));
          loop_ub = static_cast<int>(obj->nPoints);
          for (u1 = 0; u1 < loop_ub; u1++) {
            df[u1] = 0.0;
          }
          if (obj->reassign && (!obj->selfAssign)) {
            loop_ub = obj->urf.size(0);
            r.set_size(loop_ub);
            for (u1 = 0; u1 < loop_ub; u1++) {
              r[u1] = u1;
            }
            loop_ub = obj->URF.size(0);
            b_obj.set_size(loop_ub);
            for (u1 = 0; u1 < loop_ub; u1++) {
              b_obj[u1] = obj->URF[u1];
            }
            ifft(b_obj, a);
            b_qY = obj->nfft;
            loop_ub = a.size(0);
            for (u1 = 0; u1 < loop_ub; u1++) {
              obj->urf[r[u1]].re = static_cast<double>(b_qY) * a[u1].re;
              obj->urf[r[u1]].im = static_cast<double>(b_qY) * a[u1].im;
            }
            loop_ub = obj->llf.size(0);
            r.set_size(loop_ub);
            for (u1 = 0; u1 < loop_ub; u1++) {
              r[u1] = u1;
            }
            loop_ub = obj->LLF.size(0);
            b_obj.set_size(loop_ub);
            for (u1 = 0; u1 < loop_ub; u1++) {
              b_obj[u1] = obj->LLF[u1];
            }
            ifft(b_obj, a);
            b_qY = obj->nfft;
            loop_ub = a.size(0);
            for (u1 = 0; u1 < loop_ub; u1++) {
              obj->llf[r[u1]].re = static_cast<double>(b_qY) * a[u1].re;
              obj->llf[r[u1]].im = static_cast<double>(b_qY) * a[u1].im;
            }
            b_qY = obj->nPoints;
            u1 = static_cast<int>(b_qY);
            for (loop_ub = 0; loop_ub < u1; loop_ub++) {
              b_qY = (loop_ub + obj->nPoints) + 1U;
              if (b_qY < loop_ub + 1U) {
                b_qY = MAX_uint32_T;
              }
              X_re =
                  obj->ur[loop_ub].re + obj->ll[static_cast<int>(b_qY) - 1].re;
              b_qY = (loop_ub + obj->nPoints) + 1U;
              if (b_qY < loop_ub + 1U) {
                b_qY = MAX_uint32_T;
              }
              t1Seg =
                  obj->ur[loop_ub].im + obj->ll[static_cast<int>(b_qY) - 1].im;
              b_qY = (loop_ub + obj->nPoints) + 1U;
              if (b_qY < loop_ub + 1U) {
                b_qY = MAX_uint32_T;
              }
              ts = obj->urf[loop_ub].re +
                   obj->llf[static_cast<int>(b_qY) - 1].re;
              b_qY = (loop_ub + obj->nPoints) + 1U;
              if (b_qY < loop_ub + 1U) {
                b_qY = MAX_uint32_T;
              }
              tStart = obj->urf[loop_ub].im +
                       obj->llf[static_cast<int>(b_qY) - 1].im;
              if (t1Seg == 0.0) {
                if (tStart == 0.0) {
                  tStart = 0.0;
                } else {
                  tStart /= X_re;
                }
              } else if (X_re == 0.0) {
                if (ts == 0.0) {
                  tStart = 0.0;
                } else {
                  tStart = -(ts / t1Seg);
                }
              } else {
                gain = fabs(X_re);
                t2Seg = fabs(t1Seg);
                if (gain > t2Seg) {
                  gain = t1Seg / X_re;
                  tStart = (tStart - gain * ts) / (X_re + gain * t1Seg);
                } else if (t2Seg == gain) {
                  if (X_re > 0.0) {
                    X_re = 0.5;
                  } else {
                    X_re = -0.5;
                  }
                  if (t1Seg > 0.0) {
                    t1Seg = 0.5;
                  } else {
                    t1Seg = -0.5;
                  }
                  tStart = (tStart * X_re - ts * t1Seg) / gain;
                } else {
                  gain = X_re / t1Seg;
                  tStart = (gain * tStart - ts) / (t1Seg + gain * X_re);
                }
              }
              df[loop_ub] = -tStart * obj->fs / 6.2831853071795862;
            }
          }
        }
        b_qY = idx + 1U;
        if (idx + 1U < idx) {
          b_qY = MAX_uint32_T;
        }
        loop_ub = this->mStftTimeCorrections.size(1);
        r.set_size(loop_ub);
        for (u1 = 0; u1 < loop_ub; u1++) {
          r[u1] = u1;
        }
        loop_ub = r.size(0);
        for (u1 = 0; u1 < loop_ub; u1++) {
          this->mStftTimeCorrections[(static_cast<int>(b_qY) +
                                      this->mStftTimeCorrections.size(0) *
                                          r[u1]) -
                                     1] = dstSpectrum[u1];
        }
        b_qY = idx + 1U;
        if (idx + 1U < idx) {
          b_qY = MAX_uint32_T;
        }
        loop_ub = this->mStftFreqCorrections.size(1);
        r.set_size(loop_ub);
        for (u1 = 0; u1 < loop_ub; u1++) {
          r[u1] = u1;
        }
        loop_ub = r.size(0);
        for (u1 = 0; u1 < loop_ub; u1++) {
          this->mStftFreqCorrections[(static_cast<int>(b_qY) +
                                      this->mStftFreqCorrections.size(0) *
                                          r[u1]) -
                                     1] = df[u1];
        }
      }
    }
    qY = numOfWin - 1U;
    if (numOfWin - 1U > numOfWin) {
      qY = 0U;
    }
    this->LastWindowTEnd =
        (dataBeginTime +
         static_cast<double>(qY) * (this->timeResolution * this->overlap)) +
        this->timeResolution;
    q0 = this->winStartIndex;
    qY = q0 + numOfWin;
    if (qY < q0) {
      qY = MAX_uint32_T;
    }
    this->winStartIndex = qY;
  }
  this->createSpectrogramData();
}

//
// Arguments    : void
// Return Type  : void
//
void Spectrogram::createSpectrogramData()
{
  int i;
  this->totalWindows = this->winStartIndex;
  if (this->useReassignement) {
    double dataMax;
    double dataMin;
    unsigned long long u;
    int obj_idx_0;
    u = static_cast<unsigned long long>(this->totalWindows) * this->nPoints;
    if (u > 4294967295ULL) {
      u = 4294967295ULL;
    }
    obj_idx_0 = static_cast<int>(u);
    this->spectrogramData.set_size(static_cast<int>(u));
    for (i = 0; i < obj_idx_0; i++) {
      this->spectrogramData[i] = 0.0;
    }
    i = this->spectrogramData.size(0);
    if (i < 0) {
      i = 0;
    }
    this->spectrogramDataLen = static_cast<unsigned int>(i);
    this->performReassignment();
    dataMin = rtInf;
    dataMax = rtMinusInf;
    i = this->spectrogramData.size(0);
    for (int b_i = 0; b_i < i; b_i++) {
      double x;
      if (this->bIsConvertToDB) {
        this->spectrogramData[b_i] = 10.0 * log10(this->spectrogramData[b_i]);
      }
      x = this->spectrogramData[b_i];
      if ((!rtIsInf(x)) && (!rtIsNaN(x)) &&
          this->bIncludeInZlimitsCalculation[static_cast<int>(
              ((static_cast<double>(b_i) + 1.0) - 1.0) /
              static_cast<double>(this->nPoints))]) {
        x = this->spectrogramData[b_i];
        if ((!(dataMin < x)) && (!rtIsNaN(x))) {
          dataMin = x;
        }
        x = this->spectrogramData[b_i];
        if ((!(dataMax > x)) && (!rtIsNaN(x))) {
          dataMax = x;
        }
      }
    }
    if (this->bComputeZLimits) {
      this->zMax = dataMax;
      this->zMin = dataMin;
    }
  } else {
    unsigned long long u;
    int obj_idx_0;
    unsigned int spectrogramDataPos;
    u = static_cast<unsigned long long>(this->totalWindows) * this->nPoints;
    if (u > 4294967295ULL) {
      u = 4294967295ULL;
    }
    obj_idx_0 = static_cast<int>(u);
    this->spectrogramData.set_size(static_cast<int>(u));
    for (i = 0; i < obj_idx_0; i++) {
      this->spectrogramData[i] = 0.0;
    }
    spectrogramDataPos = 0U;
    i = static_cast<int>(this->totalWindows);
    for (int b_i = 0; b_i < i; b_i++) {
      obj_idx_0 = static_cast<int>(this->nPoints);
      for (int j = 0; j < obj_idx_0; j++) {
        this->spectrogramData[static_cast<int>(spectrogramDataPos + j)] =
            this->mStftMatrix[b_i + this->mStftMatrix.size(0) * j];
      }
      spectrogramDataPos += obj_idx_0;
    }
  }
  i = this->spectrogramData.size(0);
  if (i < 0) {
    i = 0;
  }
  this->spectrogramDataLen = static_cast<unsigned int>(i);
  if (rtIsInf(this->zMin)) {
    this->zMin = -379.29779453595978;
  }
  if (rtIsInf(this->zMax)) {
    this->zMax = 385.3183941905445;
  }
  if (this->zMin == this->zMax) {
    this->zMin -= 0.01 * fabs(this->zMin);
    this->zMax += 0.01 * fabs(this->zMax);
  }
}

//
// Arguments    : void
// Return Type  : void
//
void Spectrogram::performReassignment()
{
  int srcDataHeight;
  int srcDataWidth;
  srcDataWidth = static_cast<int>(this->totalWindows);
  srcDataHeight = static_cast<int>(this->nPoints);
  for (int i = 0; i < srcDataWidth; i++) {
    for (int j = 0; j < srcDataHeight; j++) {
      double iTime;
      double jFreq;
      iTime = rt_roundd_snf(
          (static_cast<double>(i + 1) - 1.0) +
          this->mStftTimeCorrections[i +
                                     this->mStftTimeCorrections.size(0) * j] *
              static_cast<double>(srcDataWidth - 1) / (this->t2 - this->t1));
      jFreq = rt_roundd_snf(
          (static_cast<double>(j + 1) - 1.0) +
          this->mStftFreqCorrections[i +
                                     this->mStftFreqCorrections.size(0) * j] *
              static_cast<double>(srcDataHeight - 1) / (this->f2 - this->f1));
      if ((iTime >= 0.0) && (iTime < srcDataWidth) && (jFreq >= 0.0) &&
          (jFreq < srcDataHeight)) {
        int b_i;
        b_i = static_cast<int>(iTime) * srcDataHeight + static_cast<int>(jFreq);
        this->spectrogramData[b_i] =
            this->spectrogramData[b_i] +
            this->mStftMatrix[i + this->mStftMatrix.size(0) * j];
      }
    }
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &data
//                const ::coder::array<double, 2U> &b_timeVector
// Return Type  : void
//
void Spectrogram::computeSpectrogram(
    const ::coder::array<double, 2U> &data,
    const ::coder::array<double, 2U> &b_timeVector)
{
  WindowDataBuffer *obj;
  array<double, 2U> dataIm;
  array<double, 2U> outputDataIm;
  array<double, 2U> outputTime;
  array<unsigned int, 2U> windowSamplesIn;
  int loop_ub;
  unsigned int overlapSamplesIn;
  int unnamed_idx_1;
  boolean_T b;
  boolean_T b1;
  dataIm.set_size(data.size(0), data.size(1));
  loop_ub = data.size(0) * data.size(1);
  for (unnamed_idx_1 = 0; unnamed_idx_1 < loop_ub; unnamed_idx_1++) {
    dataIm[unnamed_idx_1] = 0.0;
  }
  windowSamplesIn.set_size(this->timeResolutionSamples.size(0),
                           this->timeResolutionSamples.size(1));
  loop_ub =
      this->timeResolutionSamples.size(0) * this->timeResolutionSamples.size(1);
  for (unnamed_idx_1 = 0; unnamed_idx_1 < loop_ub; unnamed_idx_1++) {
    windowSamplesIn[unnamed_idx_1] = this->timeResolutionSamples[unnamed_idx_1];
  }
  overlapSamplesIn = this->overlapSamples;
  this->dataTimeBuffer.windowSampleLength = windowSamplesIn[0];
  this->dataTimeBuffer.overlapSampleLength = overlapSamplesIn;
  if ((dataIm.size(0) != 0) && (dataIm.size(1) != 0)) {
    this->dataTimeBuffer.dataIm.set_size(dataIm.size(0), dataIm.size(1));
    loop_ub = dataIm.size(0) * dataIm.size(1);
    for (unnamed_idx_1 = 0; unnamed_idx_1 < loop_ub; unnamed_idx_1++) {
      this->dataTimeBuffer.dataIm[unnamed_idx_1] = 0.0;
    }
  } else {
    this->dataTimeBuffer.dataIm.set_size(data.size(0), data.size(1));
    loop_ub = data.size(0) * data.size(1);
    for (unnamed_idx_1 = 0; unnamed_idx_1 < loop_ub; unnamed_idx_1++) {
      this->dataTimeBuffer.dataIm[unnamed_idx_1] = 0.0;
    }
  }
  this->dataTimeBuffer.dataRe.set_size(data.size(0), data.size(1));
  loop_ub = data.size(0) * data.size(1);
  for (unnamed_idx_1 = 0; unnamed_idx_1 < loop_ub; unnamed_idx_1++) {
    this->dataTimeBuffer.dataRe[unnamed_idx_1] = data[unnamed_idx_1];
  }
  this->dataTimeBuffer.time.set_size(b_timeVector.size(0),
                                     b_timeVector.size(1));
  loop_ub = b_timeVector.size(0) * b_timeVector.size(1);
  for (unnamed_idx_1 = 0; unnamed_idx_1 < loop_ub; unnamed_idx_1++) {
    this->dataTimeBuffer.time[unnamed_idx_1] = b_timeVector[unnamed_idx_1];
  }
  obj = &this->dataTimeBuffer;
  b = (this->dataTimeBuffer.dataRe.size(0) == 0);
  b1 = (this->dataTimeBuffer.dataRe.size(1) == 0);
  if (b || b1) {
    dataIm.set_size(0, 0);
    outputDataIm.set_size(0, 0);
    outputTime.set_size(0, 0);
    overlapSamplesIn = 0U;
  } else {
    unsigned int qY;
    overlapSamplesIn = this->dataTimeBuffer.windowSampleLength;
    qY = overlapSamplesIn - this->dataTimeBuffer.overlapSampleLength;
    if (qY > overlapSamplesIn) {
      qY = 0U;
    }
    if (qY > 2147483647U) {
      qY = 2147483647U;
    }
    if (this->dataTimeBuffer.dataRe.size(0) *
            this->dataTimeBuffer.dataRe.size(1) >
        static_cast<int>(qY)) {
      unsigned int windowEndIdx;
      overlapSamplesIn = 1U;
      windowEndIdx = this->dataTimeBuffer.windowSampleLength;
      while (static_cast<double>(windowEndIdx) <
             obj->dataRe.size(0) * obj->dataRe.size(1)) {
        qY = windowEndIdx + obj->windowSampleLength;
        if (qY < windowEndIdx) {
          qY = MAX_uint32_T;
        }
        windowEndIdx = qY - obj->overlapSampleLength;
        if (windowEndIdx > qY) {
          windowEndIdx = 0U;
        }
        qY = overlapSamplesIn + 1U;
        if (overlapSamplesIn + 1U < overlapSamplesIn) {
          qY = MAX_uint32_T;
        }
        overlapSamplesIn = qY;
      }
    } else {
      overlapSamplesIn = 1U;
    }
    dataIm.set_size(this->dataTimeBuffer.dataRe.size(0),
                    this->dataTimeBuffer.dataRe.size(1));
    loop_ub = this->dataTimeBuffer.dataRe.size(0) *
              this->dataTimeBuffer.dataRe.size(1);
    for (unnamed_idx_1 = 0; unnamed_idx_1 < loop_ub; unnamed_idx_1++) {
      dataIm[unnamed_idx_1] = this->dataTimeBuffer.dataRe[unnamed_idx_1];
    }
    b = (this->dataTimeBuffer.dataIm.size(0) == 0);
    b1 = (this->dataTimeBuffer.dataIm.size(1) == 0);
    if ((!b) && (!b1)) {
      outputDataIm.set_size(this->dataTimeBuffer.dataIm.size(0),
                            this->dataTimeBuffer.dataIm.size(1));
      loop_ub = this->dataTimeBuffer.dataIm.size(0) *
                this->dataTimeBuffer.dataIm.size(1);
      for (unnamed_idx_1 = 0; unnamed_idx_1 < loop_ub; unnamed_idx_1++) {
        outputDataIm[unnamed_idx_1] =
            this->dataTimeBuffer.dataIm[unnamed_idx_1];
      }
    } else {
      loop_ub = this->dataTimeBuffer.dataRe.size(0);
      unnamed_idx_1 = this->dataTimeBuffer.dataRe.size(1);
      outputDataIm.set_size(loop_ub, unnamed_idx_1);
      loop_ub *= unnamed_idx_1;
      for (unnamed_idx_1 = 0; unnamed_idx_1 < loop_ub; unnamed_idx_1++) {
        outputDataIm[unnamed_idx_1] = 0.0;
      }
    }
    outputTime.set_size(this->dataTimeBuffer.time.size(0),
                        this->dataTimeBuffer.time.size(1));
    loop_ub =
        this->dataTimeBuffer.time.size(0) * this->dataTimeBuffer.time.size(1);
    for (unnamed_idx_1 = 0; unnamed_idx_1 < loop_ub; unnamed_idx_1++) {
      outputTime[unnamed_idx_1] = this->dataTimeBuffer.time[unnamed_idx_1];
    }
    this->dataTimeBuffer.dataIm.set_size(0, 0);
    this->dataTimeBuffer.dataRe.set_size(0, 0);
    this->dataTimeBuffer.time.set_size(0, 0);
  }
  this->computeSpectrogramCore(dataIm, outputDataIm, outputTime[0],
                               overlapSamplesIn);
}

//
// Arguments    : ::coder::array<double, 2U> &spectMatrix
// Return Type  : void
//
void Spectrogram::getSpectrogramMatrix(::coder::array<double, 2U> &spectMatrix)
{
  int i;
  int obj_idx_0;
  if (this->spectrogramDataLen == 0U) {
    this->totalWindows = this->winStartIndex;
    if (this->useReassignement) {
      double dataMax;
      double dataMin;
      unsigned long long u;
      u = static_cast<unsigned long long>(this->totalWindows) * this->nPoints;
      if (u > 4294967295ULL) {
        u = 4294967295ULL;
      }
      obj_idx_0 = static_cast<int>(u);
      this->spectrogramData.set_size(static_cast<int>(u));
      for (i = 0; i < obj_idx_0; i++) {
        this->spectrogramData[i] = 0.0;
      }
      i = this->spectrogramData.size(0);
      if (i < 0) {
        i = 0;
      }
      this->spectrogramDataLen = static_cast<unsigned int>(i);
      this->performReassignment();
      dataMin = rtInf;
      dataMax = rtMinusInf;
      i = this->spectrogramData.size(0);
      for (int b_i = 0; b_i < i; b_i++) {
        double x;
        this->spectrogramData[b_i] =
            this->spectrogramData[b_i] + 2.2204460492503131E-16;
        if (this->bIsConvertToDB) {
          this->spectrogramData[b_i] = 10.0 * log10(this->spectrogramData[b_i]);
        }
        x = this->spectrogramData[b_i];
        if ((!rtIsInf(x)) && (!rtIsNaN(x)) &&
            this->bIncludeInZlimitsCalculation[static_cast<int>(
                ((static_cast<double>(b_i) + 1.0) - 1.0) /
                static_cast<double>(this->nPoints))]) {
          x = this->spectrogramData[b_i];
          if ((!(dataMin < x)) && (!rtIsNaN(x))) {
            dataMin = x;
          }
          x = this->spectrogramData[b_i];
          if ((!(dataMax > x)) && (!rtIsNaN(x))) {
            dataMax = x;
          }
        }
      }
      if (this->bComputeZLimits) {
        this->zMax = dataMax;
        this->zMin = dataMin;
      }
    } else {
      unsigned long long u;
      unsigned int spectrogramDataPos;
      boolean_T bZMaxSet;
      boolean_T bZMinSet;
      boolean_T isConvertToDBFlag;
      isConvertToDBFlag = this->bIsConvertToDB;
      bZMinSet = false;
      bZMaxSet = false;
      u = static_cast<unsigned long long>(this->totalWindows) * this->nPoints;
      if (u > 4294967295ULL) {
        u = 4294967295ULL;
      }
      obj_idx_0 = static_cast<int>(u);
      this->spectrogramData.set_size(static_cast<int>(u));
      for (i = 0; i < obj_idx_0; i++) {
        this->spectrogramData[i] = 0.0;
      }
      spectrogramDataPos = 0U;
      i = static_cast<int>(this->totalWindows);
      for (int b_i = 0; b_i < i; b_i++) {
        obj_idx_0 = static_cast<int>(this->nPoints);
        for (int j = 0; j < obj_idx_0; j++) {
          if (isConvertToDBFlag) {
            double x;
            x = this->zMax;
            if ((!rtIsInf(x)) && (!rtIsNaN(x)) && (!bZMaxSet)) {
              this->zMax = 10.0 * log10(rt_powd_snf(10.0, this->zMax / 10.0) +
                                        2.2204460492503131E-16);
              bZMaxSet = true;
            } else if (!bZMaxSet) {
              this->zMax = -156.53559774527022;
              bZMaxSet = true;
            }
            x = this->zMin;
            if ((!rtIsInf(x)) && (!rtIsNaN(x)) && (!bZMinSet)) {
              this->zMin = 10.0 * log10(rt_powd_snf(10.0, this->zMin / 10.0) +
                                        2.2204460492503131E-16);
              bZMinSet = true;
            } else if (!bZMinSet) {
              this->zMin = -156.53559774527022;
              bZMinSet = true;
            }
            this->spectrogramData[static_cast<int>(spectrogramDataPos + j)] =
                10.0 *
                log10(rt_powd_snf(
                    10.0,
                    this->mStftMatrix[b_i + this->mStftMatrix.size(0) * j] /
                            10.0 +
                        2.2204460492503131E-16));
          } else {
            if (!bZMaxSet) {
              this->zMax += 2.2204460492503131E-16;
              bZMaxSet = true;
            }
            if (!bZMinSet) {
              this->zMin += 2.2204460492503131E-16;
              bZMinSet = true;
            }
            this->spectrogramData[static_cast<int>(spectrogramDataPos + j)] =
                this->mStftMatrix[b_i + this->mStftMatrix.size(0) * j] +
                2.2204460492503131E-16;
          }
        }
        spectrogramDataPos += obj_idx_0;
      }
    }
    i = this->spectrogramData.size(0);
    if (i < 0) {
      i = 0;
    }
    this->spectrogramDataLen = static_cast<unsigned int>(i);
    if (rtIsInf(this->zMin)) {
      this->zMin = -379.29779453595978;
    }
    if (rtIsInf(this->zMax)) {
      this->zMax = 385.3183941905445;
    }
    if (this->zMin == this->zMax) {
      this->zMin -= 0.01 * fabs(this->zMin);
      this->zMax += 0.01 * fabs(this->zMax);
    }
  }
  spectMatrix.set_size(static_cast<int>(this->nPoints),
                       static_cast<int>(this->totalWindows));
  obj_idx_0 =
      static_cast<int>(this->nPoints) * static_cast<int>(this->totalWindows);
  for (i = 0; i < obj_idx_0; i++) {
    spectMatrix[i] = this->spectrogramData[i];
  }
}

//
// Arguments    : boolean_T bComputeTimeResolution
//                ::coder::array<double, 2U> &timeResolutionIn
//                double OverlapPercentIn
//                double totalSignalSamplesIn
//                double totalInputSignalSamplesIn
//                double timeFactorIn
//                double fsIn
//                double signalEndTimeIn
//                double t2In
//                double f1In
//                double f2In
//                double betaIn
//                const unsigned int nPointsIn_data[]
//                double maxFsIn
//                boolean_T bComputeZLimitsIn
//                boolean_T isConvertToDBIn
// Return Type  : void
//
void Spectrogram::setup(boolean_T bComputeTimeResolution,
                        ::coder::array<double, 2U> &timeResolutionIn,
                        double OverlapPercentIn, double totalSignalSamplesIn,
                        double totalInputSignalSamplesIn, double timeFactorIn,
                        double fsIn, double signalEndTimeIn, double t2In,
                        double f1In, double f2In, double betaIn,
                        const unsigned int nPointsIn_data[], double maxFsIn,
                        boolean_T bComputeZLimitsIn, boolean_T isConvertToDBIn)
{
  array<double, 2U> Y;
  array<double, 2U> b_OverlapPercentIn;
  array<double, 2U> c_ovlpSamples;
  array<double, 2U> ovlpSamples;
  array<unsigned int, 2U> b_ovlpSamples;
  array<unsigned int, 2U> totalWins;
  array<boolean_T, 2U> x;
  double d;
  unsigned int b_overlapSamples;
  int i;
  int loop_ub;
  unsigned int numberOfSignalSamples;
  int nx;
  int y_size_idx_1;
  boolean_T exitg1;
  boolean_T y;
  if (bComputeTimeResolution) {
    d = rt_roundd_snf(totalSignalSamplesIn);
    if (d < 4.294967296E+9) {
      if (d >= 0.0) {
        numberOfSignalSamples = static_cast<unsigned int>(d);
      } else {
        numberOfSignalSamples = 0U;
      }
    } else if (d >= 4.294967296E+9) {
      numberOfSignalSamples = MAX_uint32_T;
    } else {
      numberOfSignalSamples = 0U;
    }
    if (numberOfSignalSamples >= 16384U) {
      nx = static_cast<int>(
          ceil(static_cast<double>(numberOfSignalSamples) / 128.0));
    } else if (static_cast<int>(numberOfSignalSamples) >= 8192) {
      nx = static_cast<int>(
          ceil(static_cast<double>(numberOfSignalSamples) / 64.0));
    } else if (static_cast<int>(numberOfSignalSamples) >= 4096) {
      nx = static_cast<int>(
          ceil(static_cast<double>(numberOfSignalSamples) / 32.0));
    } else if (static_cast<int>(numberOfSignalSamples) >= 2048) {
      nx = static_cast<int>(
          ceil(static_cast<double>(numberOfSignalSamples) / 16.0));
    } else if (static_cast<int>(numberOfSignalSamples) >= 64) {
      nx = static_cast<int>(
          ceil(static_cast<double>(numberOfSignalSamples) / 8.0));
    } else {
      nx = static_cast<int>(
          ceil(static_cast<double>(numberOfSignalSamples) / 2.0));
    }
    this->timeResolutionSamples.set_size(1, 1);
    this->timeResolutionSamples[0] = static_cast<unsigned int>(nx);
  } else if (timeFactorIn != 1.0) {
    nx = timeResolutionIn.size(0) * timeResolutionIn.size(1);
    for (y_size_idx_1 = 0; y_size_idx_1 < nx; y_size_idx_1++) {
      timeResolutionIn[y_size_idx_1] = floor(timeResolutionIn[y_size_idx_1]);
    }
    this->timeResolutionSamples.set_size(timeResolutionIn.size(0),
                                         timeResolutionIn.size(1));
    loop_ub = timeResolutionIn.size(0) * timeResolutionIn.size(1);
    for (i = 0; i < loop_ub; i++) {
      d = rt_roundd_snf(timeResolutionIn[i]);
      if (d < 4.294967296E+9) {
        if (d >= 0.0) {
          numberOfSignalSamples = static_cast<unsigned int>(d);
        } else {
          numberOfSignalSamples = 0U;
        }
      } else if (d >= 4.294967296E+9) {
        numberOfSignalSamples = MAX_uint32_T;
      } else {
        numberOfSignalSamples = 0U;
      }
      this->timeResolutionSamples[i] = numberOfSignalSamples;
    }
  } else {
    nx = timeResolutionIn.size(0);
    y_size_idx_1 = timeResolutionIn.size(1);
    loop_ub = timeResolutionIn.size(0) * timeResolutionIn.size(1);
    for (i = 0; i < loop_ub; i++) {
      timeResolutionIn[i] = timeResolutionIn[i] * fsIn;
    }
    nx *= y_size_idx_1;
    for (y_size_idx_1 = 0; y_size_idx_1 < nx; y_size_idx_1++) {
      timeResolutionIn[y_size_idx_1] = floor(timeResolutionIn[y_size_idx_1]);
    }
    this->timeResolutionSamples.set_size(timeResolutionIn.size(0),
                                         timeResolutionIn.size(1));
    loop_ub = timeResolutionIn.size(0) * timeResolutionIn.size(1);
    for (i = 0; i < loop_ub; i++) {
      d = rt_roundd_snf(timeResolutionIn[i]);
      if (d < 4.294967296E+9) {
        if (d >= 0.0) {
          numberOfSignalSamples = static_cast<unsigned int>(d);
        } else {
          numberOfSignalSamples = 0U;
        }
      } else if (d >= 4.294967296E+9) {
        numberOfSignalSamples = MAX_uint32_T;
      } else {
        numberOfSignalSamples = 0U;
      }
      this->timeResolutionSamples[i] = numberOfSignalSamples;
    }
  }
  x.set_size(this->timeResolutionSamples.size(0),
             this->timeResolutionSamples.size(1));
  loop_ub =
      this->timeResolutionSamples.size(0) * this->timeResolutionSamples.size(1);
  for (i = 0; i < loop_ub; i++) {
    x[i] = (this->timeResolutionSamples[i] == 0U);
  }
  y = ((x.size(0) != 0) && (x.size(1) != 0));
  if (y) {
    i = x.size(0) * x.size(1);
    y_size_idx_1 = 0;
    exitg1 = false;
    while ((!exitg1) && (y_size_idx_1 <= i - 1)) {
      if (!x[y_size_idx_1]) {
        y = false;
        exitg1 = true;
      } else {
        y_size_idx_1++;
      }
    }
  }
  if (y) {
    this->timeResolutionSamples.set_size(1, 1);
    this->timeResolutionSamples[0] = 1U;
  }
  timeResolutionIn.set_size(this->timeResolutionSamples.size(0),
                            this->timeResolutionSamples.size(1));
  loop_ub =
      this->timeResolutionSamples.size(0) * this->timeResolutionSamples.size(1);
  for (i = 0; i < loop_ub; i++) {
    timeResolutionIn[i] =
        static_cast<double>(this->timeResolutionSamples[i]) / fsIn;
  }
  ::coder::signal::internal::pspectrum::computeOverlapSamples(
      OverlapPercentIn, this->timeResolutionSamples, ovlpSamples,
      b_OverlapPercentIn);
  b_ovlpSamples.set_size(ovlpSamples.size(0), ovlpSamples.size(1));
  loop_ub = ovlpSamples.size(0) * ovlpSamples.size(1);
  for (i = 0; i < loop_ub; i++) {
    d = rt_roundd_snf(ovlpSamples[i]);
    if (d < 4.294967296E+9) {
      if (d >= 0.0) {
        numberOfSignalSamples = static_cast<unsigned int>(d);
      } else {
        numberOfSignalSamples = 0U;
      }
    } else if (d >= 4.294967296E+9) {
      numberOfSignalSamples = MAX_uint32_T;
    } else {
      numberOfSignalSamples = 0U;
    }
    b_ovlpSamples[i] = numberOfSignalSamples;
  }
  this->overlapSamples = b_ovlpSamples[0];
  this->timeResolution = timeResolutionIn[0];
  this->overlap = static_cast<double>(this->overlapSamples) / fsIn;
  d = rt_roundd_snf(totalInputSignalSamplesIn);
  if (d < 4.294967296E+9) {
    if (d >= 0.0) {
      numberOfSignalSamples = static_cast<unsigned int>(d);
    } else {
      numberOfSignalSamples = 0U;
    }
  } else if (d >= 4.294967296E+9) {
    numberOfSignalSamples = MAX_uint32_T;
  } else {
    numberOfSignalSamples = 0U;
  }
  this->totalInputSignalSamples = numberOfSignalSamples;
  this->timeFactor = timeFactorIn;
  this->fs = fsIn;
  this->signalBeginTime = 0.0 * this->timeFactor;
  this->signalEndTime = signalEndTimeIn * this->timeFactor;
  this->t1 = 0.0;
  this->t2 = t2In;
  this->f1 = f1In;
  this->f2 = f2In;
  this->beta = betaIn;
  this->nPoints = nPointsIn_data[0];
  this->maxFs = maxFsIn;
  this->bComputeZLimits = bComputeZLimitsIn;
  this->zMin = rtInf;
  this->zMax = rtMinusInf;
  this->useZoomFFT = false;
  this->useReassignement = false;
  numberOfSignalSamples = this->totalInputSignalSamples;
  b_ovlpSamples.set_size(this->timeResolutionSamples.size(0),
                         this->timeResolutionSamples.size(1));
  loop_ub =
      this->timeResolutionSamples.size(0) * this->timeResolutionSamples.size(1);
  for (i = 0; i < loop_ub; i++) {
    b_ovlpSamples[i] = this->timeResolutionSamples[i];
  }
  b_overlapSamples = this->overlapSamples;
  x.set_size(b_ovlpSamples.size(0), b_ovlpSamples.size(1));
  loop_ub = b_ovlpSamples.size(0) * b_ovlpSamples.size(1);
  for (i = 0; i < loop_ub; i++) {
    x[i] = (numberOfSignalSamples < b_ovlpSamples[i]);
  }
  y = ((x.size(0) != 0) && (x.size(1) != 0));
  if (y) {
    i = x.size(0) * x.size(1);
    y_size_idx_1 = 0;
    exitg1 = false;
    while ((!exitg1) && (y_size_idx_1 <= i - 1)) {
      if (!x[y_size_idx_1]) {
        y = false;
        exitg1 = true;
      } else {
        y_size_idx_1++;
      }
    }
  }
  if (y) {
    totalWins.set_size(1, 1);
    totalWins[0] = 1U;
  } else {
    unsigned int q0;
    unsigned int qY;
    c_ovlpSamples.set_size(b_ovlpSamples.size(0), b_ovlpSamples.size(1));
    loop_ub = b_ovlpSamples.size(0) * b_ovlpSamples.size(1);
    for (i = 0; i < loop_ub; i++) {
      q0 = b_ovlpSamples[i];
      qY = q0 - b_overlapSamples;
      if (qY > q0) {
        qY = 0U;
      }
      c_ovlpSamples[i] = qY;
    }
    qY = numberOfSignalSamples - b_overlapSamples;
    if (qY > numberOfSignalSamples) {
      qY = 0U;
    }
    ::coder::internal::mrdiv(static_cast<double>(qY), c_ovlpSamples, Y);
    nx = Y.size(1);
    for (y_size_idx_1 = 0; y_size_idx_1 < nx; y_size_idx_1++) {
      Y[y_size_idx_1] = ceil(Y[y_size_idx_1]);
    }
    totalWins.set_size(1, Y.size(1));
    loop_ub = Y.size(1);
    for (i = 0; i < loop_ub; i++) {
      d = rt_roundd_snf(Y[i]);
      if (d < 4.294967296E+9) {
        if (d >= 0.0) {
          q0 = static_cast<unsigned int>(d);
        } else {
          q0 = 0U;
        }
      } else if (d >= 4.294967296E+9) {
        q0 = MAX_uint32_T;
      } else {
        q0 = 0U;
      }
      qY = q0 + 1U;
      if (q0 + 1U < q0) {
        qY = MAX_uint32_T;
      }
      totalWins[i] = qY;
    }
  }
  this->totalWindows = totalWins[0];
  this->winStartIndex = 0U;
  this->LastWindowTEnd = this->signalBeginTime;
  nx = static_cast<int>(this->totalWindows);
  y_size_idx_1 = static_cast<int>(this->nPoints);
  this->mStftMatrix.set_size(nx, y_size_idx_1);
  loop_ub = nx * y_size_idx_1;
  for (i = 0; i < loop_ub; i++) {
    this->mStftMatrix[i] = 0.0;
  }
  nx = static_cast<int>(this->totalWindows);
  y_size_idx_1 = static_cast<int>(this->nPoints);
  this->mStftTimeCorrections.set_size(nx, y_size_idx_1);
  loop_ub = nx * y_size_idx_1;
  for (i = 0; i < loop_ub; i++) {
    this->mStftTimeCorrections[i] = 0.0;
  }
  nx = static_cast<int>(this->totalWindows);
  y_size_idx_1 = static_cast<int>(this->nPoints);
  this->mStftFreqCorrections.set_size(nx, y_size_idx_1);
  loop_ub = nx * y_size_idx_1;
  for (i = 0; i < loop_ub; i++) {
    this->mStftFreqCorrections[i] = 0.0;
  }
  nx = static_cast<int>(this->totalWindows);
  this->timeVector.set_size(nx);
  for (i = 0; i < nx; i++) {
    this->timeVector[i] = 0.0;
  }
  this->bIsTwoSided = false;
  this->bIsConvertToDB = isConvertToDBIn;
  nx = static_cast<int>(this->totalWindows);
  this->bIncludeInZlimitsCalculation.set_size(nx);
  for (i = 0; i < nx; i++) {
    this->bIncludeInZlimitsCalculation[i] = false;
  }
}

} // namespace pspectrum
} // namespace codegenable
} // namespace internal
} // namespace signal
} // namespace coder

//
// File trailer for Spectrogram.cpp
//
// [EOF]
//
