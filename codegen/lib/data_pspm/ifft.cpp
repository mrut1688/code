//
// File: ifft.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 23-Aug-2023 11:38:45
//

// Include Files
#include "ifft.h"
#include "FFTImplementationCallback.h"
#include "data_pspm_data.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <math.h>

// Function Definitions
//
// Arguments    : const ::coder::array<creal_T, 1U> &x
//                ::coder::array<creal_T, 1U> &y
// Return Type  : void
//
namespace coder {
void ifft(const ::coder::array<creal_T, 1U> &x, ::coder::array<creal_T, 1U> &y)
{
  array<creal_T, 1U> b_fv;
  array<creal_T, 1U> fv;
  array<creal_T, 1U> wwc;
  array<double, 2U> costab;
  array<double, 2U> costab1q;
  array<double, 2U> sintab;
  array<double, 2U> sintabinv;
  int N2blue;
  int nd2;
  int nfft;
  nfft = x.size(0);
  if (x.size(0) == 0) {
    y.set_size(0);
  } else {
    double nt_im;
    int i;
    int k;
    int nInt2;
    int rt;
    boolean_T useRadix2;
    useRadix2 = ((x.size(0) & (x.size(0) - 1)) == 0);
    internal::FFTImplementationCallback::get_algo_sizes(x.size(0), useRadix2,
                                                        &N2blue, &nd2);
    nt_im = 6.2831853071795862 / static_cast<double>(nd2);
    nInt2 = nd2 / 2 / 2;
    costab1q.set_size(1, nInt2 + 1);
    costab1q[0] = 1.0;
    nd2 = nInt2 / 2 - 1;
    for (k = 0; k <= nd2; k++) {
      costab1q[k + 1] = cos(nt_im * (static_cast<double>(k) + 1.0));
    }
    i = nd2 + 2;
    rt = nInt2 - 1;
    for (k = i; k <= rt; k++) {
      costab1q[k] = sin(nt_im * static_cast<double>(nInt2 - k));
    }
    costab1q[nInt2] = 0.0;
    if (!useRadix2) {
      nInt2 = costab1q.size(1) - 1;
      nd2 = (costab1q.size(1) - 1) << 1;
      costab.set_size(1, nd2 + 1);
      sintab.set_size(1, nd2 + 1);
      costab[0] = 1.0;
      sintab[0] = 0.0;
      sintabinv.set_size(1, nd2 + 1);
      for (k = 0; k < nInt2; k++) {
        sintabinv[k + 1] = costab1q[(nInt2 - k) - 1];
      }
      i = costab1q.size(1);
      for (k = i; k <= nd2; k++) {
        sintabinv[k] = costab1q[k - nInt2];
      }
      for (k = 0; k < nInt2; k++) {
        costab[k + 1] = costab1q[k + 1];
        sintab[k + 1] = -costab1q[(nInt2 - k) - 1];
      }
      i = costab1q.size(1);
      for (k = i; k <= nd2; k++) {
        costab[k] = -costab1q[nd2 - k];
        sintab[k] = -costab1q[k - nInt2];
      }
    } else {
      nInt2 = costab1q.size(1) - 1;
      nd2 = (costab1q.size(1) - 1) << 1;
      costab.set_size(1, nd2 + 1);
      sintab.set_size(1, nd2 + 1);
      costab[0] = 1.0;
      sintab[0] = 0.0;
      for (k = 0; k < nInt2; k++) {
        costab[k + 1] = costab1q[k + 1];
        sintab[k + 1] = costab1q[(nInt2 - k) - 1];
      }
      i = costab1q.size(1);
      for (k = i; k <= nd2; k++) {
        costab[k] = -costab1q[nd2 - k];
        sintab[k] = costab1q[k - nInt2];
      }
      sintabinv.set_size(1, 0);
    }
    if (useRadix2) {
      internal::FFTImplementationCallback::r2br_r2dit_trig_impl(
          x, x.size(0), costab, sintab, y);
      if (y.size(0) > 1) {
        nt_im = 1.0 / static_cast<double>(y.size(0));
        nd2 = y.size(0);
        for (i = 0; i < nd2; i++) {
          y[i].re = nt_im * y[i].re;
          y[i].im = nt_im * y[i].im;
        }
      }
    } else {
      double nt_re;
      nd2 = (x.size(0) + x.size(0)) - 1;
      wwc.set_size(nd2);
      rt = 0;
      wwc[x.size(0) - 1].re = 1.0;
      wwc[x.size(0) - 1].im = 0.0;
      nInt2 = x.size(0) << 1;
      i = x.size(0);
      for (k = 0; k <= i - 2; k++) {
        int b_y;
        b_y = ((k + 1) << 1) - 1;
        if (nInt2 - rt <= b_y) {
          rt += b_y - nInt2;
        } else {
          rt += b_y;
        }
        nt_im = 3.1415926535897931 * static_cast<double>(rt) /
                static_cast<double>(nfft);
        if (nt_im == 0.0) {
          nt_re = 1.0;
          nt_im = 0.0;
        } else {
          nt_re = cos(nt_im);
          nt_im = sin(nt_im);
        }
        wwc[(x.size(0) - k) - 2].re = nt_re;
        wwc[(x.size(0) - k) - 2].im = -nt_im;
      }
      i = nd2 - 1;
      for (k = i; k >= nfft; k--) {
        wwc[k] = wwc[(nd2 - k) - 1];
      }
      y.set_size(x.size(0));
      nd2 = x.size(0);
      for (k = 0; k < nd2; k++) {
        nt_re = wwc[(nfft + k) - 1].re;
        nt_im = wwc[(nfft + k) - 1].im;
        y[k].re = nt_re * x[k].re + nt_im * x[k].im;
        y[k].im = nt_re * x[k].im - nt_im * x[k].re;
      }
      i = x.size(0) + 1;
      for (k = i; k <= nfft; k++) {
        y[k - 1].re = 0.0;
        y[k - 1].im = 0.0;
      }
      internal::FFTImplementationCallback::r2br_r2dit_trig_impl(
          y, N2blue, costab, sintab, fv);
      internal::FFTImplementationCallback::r2br_r2dit_trig_impl(
          wwc, N2blue, costab, sintab, b_fv);
      b_fv.set_size(fv.size(0));
      nd2 = fv.size(0);
      for (i = 0; i < nd2; i++) {
        nt_im = fv[i].re * b_fv[i].im + fv[i].im * b_fv[i].re;
        b_fv[i].re = fv[i].re * b_fv[i].re - fv[i].im * b_fv[i].im;
        b_fv[i].im = nt_im;
      }
      internal::FFTImplementationCallback::r2br_r2dit_trig_impl(
          b_fv, N2blue, costab, sintabinv, fv);
      if (fv.size(0) > 1) {
        nt_im = 1.0 / static_cast<double>(fv.size(0));
        nd2 = fv.size(0);
        for (i = 0; i < nd2; i++) {
          fv[i].re = nt_im * fv[i].re;
          fv[i].im = nt_im * fv[i].im;
        }
      }
      nt_re = x.size(0);
      i = x.size(0);
      rt = wwc.size(0);
      for (k = i; k <= rt; k++) {
        double ai;
        nt_im = wwc[k - 1].re * fv[k - 1].re + wwc[k - 1].im * fv[k - 1].im;
        ai = wwc[k - 1].re * fv[k - 1].im - wwc[k - 1].im * fv[k - 1].re;
        if (ai == 0.0) {
          nd2 = k - i;
          y[nd2].re = nt_im / nt_re;
          y[nd2].im = 0.0;
        } else if (nt_im == 0.0) {
          nd2 = k - i;
          y[nd2].re = 0.0;
          y[nd2].im = ai / nt_re;
        } else {
          nd2 = k - i;
          y[nd2].re = nt_im / nt_re;
          y[nd2].im = ai / nt_re;
        }
      }
    }
  }
}

} // namespace coder

//
// File trailer for ifft.cpp
//
// [EOF]
//
