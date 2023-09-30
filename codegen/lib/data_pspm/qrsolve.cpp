//
// File: qrsolve.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 23-Aug-2023 11:38:45
//

// Include Files
#include "qrsolve.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <math.h>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &A
// Return Type  : int
//
namespace coder {
namespace internal {
int rankFromQR(const ::coder::array<double, 2U> &A)
{
  int maxmn;
  int minmn;
  int r;
  r = 0;
  if (A.size(0) < A.size(1)) {
    minmn = A.size(0);
    maxmn = A.size(1);
  } else {
    minmn = A.size(1);
    maxmn = A.size(0);
  }
  if (minmn > 0) {
    double tol;
    tol = 2.2204460492503131E-15 * static_cast<double>(maxmn);
    if (1.4901161193847656E-8 < tol) {
      tol = 1.4901161193847656E-8;
    }
    tol *= fabs(A[0]);
    while ((r < minmn) && (!(fabs(A[r + A.size(0) * r]) <= tol))) {
      r++;
    }
  }
  return r;
}

} // namespace internal
} // namespace coder

//
// File trailer for qrsolve.cpp
//
// [EOF]
//
