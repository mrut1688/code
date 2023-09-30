//
// File: mrdivide_helper.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 23-Aug-2023 11:38:45
//

// Include Files
#include "mrdivide_helper.h"
#include "qrsolve.h"
#include "rt_nonfinite.h"
#include "xgeqp3.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : double A
//                const ::coder::array<double, 2U> &B
//                ::coder::array<double, 2U> &Y
// Return Type  : void
//
namespace coder {
namespace internal {
void mrdiv(double A, const ::coder::array<double, 2U> &B,
           ::coder::array<double, 2U> &Y)
{
  array<double, 2U> b_A;
  array<double, 1U> b_Y;
  array<double, 1U> tau;
  array<int, 2U> jpvt;
  if (B.size(0) == 0) {
    Y.set_size(1, 0);
  } else if (B.size(0) == 1) {
    Y.set_size(1, 1);
    Y[0] = A / B[0];
  } else {
    double b_B;
    int j;
    int loop_ub;
    int m;
    int mn;
    int rankA;
    b_B = A;
    b_A.set_size(1, B.size(0));
    loop_ub = B.size(0);
    for (m = 0; m < loop_ub; m++) {
      b_A[b_A.size(0) * m] = B[m];
    }
    lapack::xgeqp3(b_A, tau, jpvt);
    rankA = rankFromQR(b_A);
    b_Y.set_size(b_A.size(1));
    loop_ub = b_A.size(1);
    for (m = 0; m < loop_ub; m++) {
      b_Y[m] = 0.0;
    }
    m = b_A.size(0);
    loop_ub = b_A.size(0);
    mn = b_A.size(1);
    if (loop_ub < mn) {
      mn = loop_ub;
    }
    for (j = 0; j < mn; j++) {
      if (tau[j] != 0.0) {
        double wj;
        wj = b_B;
        for (loop_ub = 2; loop_ub <= m; loop_ub++) {
          wj += b_A[loop_ub - 1] * b_B;
        }
        wj *= tau[j];
        if (wj != 0.0) {
          b_B -= wj;
          for (loop_ub = 2; loop_ub <= m; loop_ub++) {
            b_B -= b_A[loop_ub - 1] * wj;
          }
        }
      }
    }
    if (0 <= rankA - 1) {
      b_Y[jpvt[0] - 1] = b_B;
    }
    for (j = rankA; j >= 1; j--) {
      m = jpvt[j - 1];
      b_Y[m - 1] = b_Y[m - 1] / b_A[(j + b_A.size(0) * (j - 1)) - 1];
      for (loop_ub = 0; loop_ub <= j - 2; loop_ub++) {
        b_Y[jpvt[loop_ub] - 1] =
            b_Y[jpvt[loop_ub] - 1] -
            b_Y[jpvt[j - 1] - 1] * b_A[loop_ub + b_A.size(0) * (j - 1)];
      }
    }
    Y.set_size(1, b_Y.size(0));
    loop_ub = b_Y.size(0);
    for (m = 0; m < loop_ub; m++) {
      Y[m] = b_Y[m];
    }
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for mrdivide_helper.cpp
//
// [EOF]
//
