//
// File: allOrAny.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 23-Aug-2023 11:38:45
//

// Include Files
#include "allOrAny.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : const boolean_T x_data[]
//                const int x_size[2]
// Return Type  : boolean_T
//
namespace coder {
namespace internal {
boolean_T vectorAny(const boolean_T x_data[], const int x_size[2])
{
  int k;
  boolean_T exitg1;
  boolean_T y;
  y = false;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= x_size[1] - 1)) {
    if (!x_data[k]) {
      k++;
    } else {
      y = true;
      exitg1 = true;
    }
  }
  return y;
}

} // namespace internal
} // namespace coder

//
// File trailer for allOrAny.cpp
//
// [EOF]
//
