//
// File: computeOverlapSamples.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 23-Aug-2023 11:38:45
//

// Include Files
#include "computeOverlapSamples.h"
#include "qrsolve.h"
#include "rt_nonfinite.h"
#include "xgeqp3.h"
#include "coder_array.h"
#include <math.h>

// Function Definitions
//
// Arguments    : double perOverlap
//                const ::coder::array<unsigned int, 2U> &timeResolutionSamples
//                ::coder::array<double, 2U> &overlapSamples
//                ::coder::array<double, 2U> &b_perOverlap
// Return Type  : void
//
namespace coder {
namespace signal {
namespace internal {
namespace pspectrum {
void computeOverlapSamples(
    double perOverlap,
    const ::coder::array<unsigned int, 2U> &timeResolutionSamples,
    ::coder::array<double, 2U> &overlapSamples,
    ::coder::array<double, 2U> &b_perOverlap)
{
  array<double, 2U> A;
  array<double, 2U> B;
  array<double, 2U> b_tmp;
  array<double, 1U> tau;
  array<int, 2U> jpvt;
  double wj;
  int i;
  int k;
  int m;
  int nx;
  wj = perOverlap / 100.0;
  b_tmp.set_size(timeResolutionSamples.size(0), timeResolutionSamples.size(1));
  m = timeResolutionSamples.size(0) * timeResolutionSamples.size(1);
  for (i = 0; i < m; i++) {
    b_tmp[i] = timeResolutionSamples[i];
  }
  overlapSamples.set_size(b_tmp.size(0), b_tmp.size(1));
  m = b_tmp.size(0) * b_tmp.size(1);
  for (i = 0; i < m; i++) {
    overlapSamples[i] = wj * b_tmp[i];
  }
  nx = overlapSamples.size(0) * overlapSamples.size(1);
  for (k = 0; k < nx; k++) {
    overlapSamples[k] = floor(overlapSamples[k]);
  }
  b_perOverlap.set_size(overlapSamples.size(0), overlapSamples.size(1));
  m = overlapSamples.size(0) * overlapSamples.size(1);
  for (i = 0; i < m; i++) {
    b_perOverlap[i] = 100.0 * overlapSamples[i];
  }
  A.set_size(b_tmp.size(0), b_tmp.size(1));
  m = b_tmp.size(0) * b_tmp.size(1);
  for (i = 0; i < m; i++) {
    A[i] = b_tmp[i];
  }
  if ((b_perOverlap.size(0) == 0) || (b_perOverlap.size(1) == 0) ||
      ((b_tmp.size(0) == 0) || (b_tmp.size(1) == 0))) {
    unsigned int unnamed_idx_0;
    unnamed_idx_0 = static_cast<unsigned int>(b_perOverlap.size(0));
    b_perOverlap.set_size(static_cast<int>(unnamed_idx_0), b_tmp.size(0));
    m = static_cast<int>(unnamed_idx_0) * b_tmp.size(0);
    for (i = 0; i < m; i++) {
      b_perOverlap[i] = 0.0;
    }
  } else if (b_tmp.size(0) == b_tmp.size(1)) {
    int b_i;
    int b_nb;
    int j;
    int jp1j;
    int ldap1;
    int mn;
    int n;
    int nb;
    int u1;
    n = b_tmp.size(1);
    nx = b_tmp.size(1);
    jpvt.set_size(1, b_tmp.size(1));
    jpvt[0] = 1;
    m = 1;
    for (k = 2; k <= nx; k++) {
      m++;
      jpvt[k - 1] = m;
    }
    ldap1 = b_tmp.size(1);
    nx = b_tmp.size(1) - 1;
    u1 = b_tmp.size(1);
    if (nx < u1) {
      u1 = nx;
    }
    for (j = 0; j < u1; j++) {
      int jj;
      nb = n - j;
      mn = j * (n + 1);
      jj = j * (ldap1 + 1);
      jp1j = mn + 2;
      if (nb < 1) {
        nx = -1;
      } else {
        nx = 0;
        if (nb > 1) {
          wj = fabs(A[jj]);
          for (k = 2; k <= nb; k++) {
            double s;
            s = fabs(A[(mn + k) - 1]);
            if (s > wj) {
              nx = k - 1;
              wj = s;
            }
          }
        }
      }
      if (A[jj + nx] != 0.0) {
        if (nx != 0) {
          m = j + nx;
          jpvt[j] = m + 1;
          for (k = 0; k < n; k++) {
            nx = k * n;
            b_nb = j + nx;
            wj = A[b_nb];
            i = m + nx;
            A[b_nb] = A[i];
            A[i] = wj;
          }
        }
        i = jj + nb;
        for (b_i = jp1j; b_i <= i; b_i++) {
          A[b_i - 1] = A[b_i - 1] / A[jj];
        }
      }
      m = mn + n;
      b_nb = jj + ldap1;
      for (mn = 0; mn <= nb - 2; mn++) {
        nx = m + mn * n;
        wj = A[nx];
        if (A[nx] != 0.0) {
          i = b_nb + 2;
          jp1j = nb + b_nb;
          for (nx = i; nx <= jp1j; nx++) {
            A[nx - 1] = A[nx - 1] + A[((jj + nx) - b_nb) - 1] * -wj;
          }
        }
        b_nb += n;
      }
    }
    nb = b_perOverlap.size(0);
    for (j = 0; j < n; j++) {
      nx = nb * j - 1;
      m = n * j;
      for (k = 0; k < j; k++) {
        b_nb = nb * k;
        i = k + m;
        if (A[i] != 0.0) {
          for (b_i = 0; b_i < nb; b_i++) {
            jp1j = (b_i + nx) + 1;
            b_perOverlap[jp1j] =
                b_perOverlap[jp1j] - A[i] * b_perOverlap[b_i + b_nb];
          }
        }
      }
      wj = 1.0 / A[j + m];
      for (b_i = 0; b_i < nb; b_i++) {
        i = (b_i + nx) + 1;
        b_perOverlap[i] = wj * b_perOverlap[i];
      }
    }
    for (j = n; j >= 1; j--) {
      nx = nb * (j - 1) - 1;
      m = n * (j - 1) - 1;
      i = j + 1;
      for (k = i; k <= n; k++) {
        b_nb = nb * (k - 1);
        jp1j = k + m;
        if (A[jp1j] != 0.0) {
          for (b_i = 0; b_i < nb; b_i++) {
            mn = (b_i + nx) + 1;
            b_perOverlap[mn] =
                b_perOverlap[mn] - A[jp1j] * b_perOverlap[b_i + b_nb];
          }
        }
      }
    }
    i = b_tmp.size(1) - 1;
    for (j = i; j >= 1; j--) {
      jp1j = jpvt[j - 1];
      if (jp1j != j) {
        for (b_i = 0; b_i < nb; b_i++) {
          wj = b_perOverlap[b_i + b_perOverlap.size(0) * (j - 1)];
          b_perOverlap[b_i + b_perOverlap.size(0) * (j - 1)] =
              b_perOverlap[b_i + b_perOverlap.size(0) * (jp1j - 1)];
          b_perOverlap[b_i + b_perOverlap.size(0) * (jp1j - 1)] = wj;
        }
      }
    }
  } else {
    int b_i;
    int b_nb;
    int j;
    int jp1j;
    int mn;
    int nb;
    B.set_size(b_perOverlap.size(1), b_perOverlap.size(0));
    m = b_perOverlap.size(0);
    for (i = 0; i < m; i++) {
      nx = b_perOverlap.size(1);
      for (jp1j = 0; jp1j < nx; jp1j++) {
        B[jp1j + B.size(0) * i] = b_perOverlap[i + b_perOverlap.size(0) * jp1j];
      }
    }
    A.set_size(b_tmp.size(1), b_tmp.size(0));
    m = b_tmp.size(0);
    for (i = 0; i < m; i++) {
      nx = b_tmp.size(1);
      for (jp1j = 0; jp1j < nx; jp1j++) {
        A[jp1j + A.size(0) * i] = b_tmp[i + b_tmp.size(0) * jp1j];
      }
    }
    ::coder::internal::lapack::xgeqp3(A, tau, jpvt);
    jp1j = ::coder::internal::rankFromQR(A);
    nb = B.size(1);
    b_tmp.set_size(A.size(1), B.size(1));
    m = A.size(1) * B.size(1);
    for (i = 0; i < m; i++) {
      b_tmp[i] = 0.0;
    }
    m = A.size(0);
    b_nb = B.size(1);
    nx = A.size(0);
    mn = A.size(1);
    if (nx < mn) {
      mn = nx;
    }
    for (j = 0; j < mn; j++) {
      if (tau[j] != 0.0) {
        for (k = 0; k < b_nb; k++) {
          wj = B[j + B.size(0) * k];
          i = j + 2;
          for (b_i = i; b_i <= m; b_i++) {
            wj += A[(b_i + A.size(0) * j) - 1] * B[(b_i + B.size(0) * k) - 1];
          }
          wj *= tau[j];
          if (wj != 0.0) {
            B[j + B.size(0) * k] = B[j + B.size(0) * k] - wj;
            for (b_i = i; b_i <= m; b_i++) {
              B[(b_i + B.size(0) * k) - 1] = B[(b_i + B.size(0) * k) - 1] -
                                             A[(b_i + A.size(0) * j) - 1] * wj;
            }
          }
        }
      }
    }
    for (k = 0; k < nb; k++) {
      for (b_i = 0; b_i < jp1j; b_i++) {
        b_tmp[(jpvt[b_i] + b_tmp.size(0) * k) - 1] = B[b_i + B.size(0) * k];
      }
      for (j = jp1j; j >= 1; j--) {
        i = jpvt[j - 1];
        b_tmp[(i + b_tmp.size(0) * k) - 1] =
            b_tmp[(i + b_tmp.size(0) * k) - 1] /
            A[(j + A.size(0) * (j - 1)) - 1];
        for (b_i = 0; b_i <= j - 2; b_i++) {
          b_tmp[(jpvt[b_i] + b_tmp.size(0) * k) - 1] =
              b_tmp[(jpvt[b_i] + b_tmp.size(0) * k) - 1] -
              b_tmp[(jpvt[j - 1] + b_tmp.size(0) * k) - 1] *
                  A[b_i + A.size(0) * (j - 1)];
        }
      }
    }
    b_perOverlap.set_size(b_tmp.size(1), b_tmp.size(0));
    m = b_tmp.size(0);
    for (i = 0; i < m; i++) {
      nx = b_tmp.size(1);
      for (jp1j = 0; jp1j < nx; jp1j++) {
        b_perOverlap[jp1j + b_perOverlap.size(0) * i] =
            b_tmp[i + b_tmp.size(0) * jp1j];
      }
    }
  }
}

} // namespace pspectrum
} // namespace internal
} // namespace signal
} // namespace coder

//
// File trailer for computeOverlapSamples.cpp
//
// [EOF]
//
