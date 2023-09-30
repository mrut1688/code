//
// File: strcmp.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 23-Aug-2023 11:38:45
//

// Include Files
#include "strcmp.h"
#include "data_pspm_data.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : const char a_data[]
//                const int a_size[2]
//                boolean_T b_bool[3]
// Return Type  : void
//
namespace coder {
namespace internal {
void b_strcmp(const char a_data[], const int a_size[2], boolean_T b_bool[3])
{
  int exitg1;
  int kstr;
  b_bool[0] = false;
  b_bool[1] = false;
  if (a_size[1] == 11) {
    kstr = 0;
    do {
      exitg1 = 0;
      if (kstr < 11) {
        if (a_data[kstr] != cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool[1] = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  b_bool[2] = false;
  if (a_size[1] == 11) {
    kstr = 0;
    do {
      exitg1 = 0;
      if (kstr < 11) {
        if (a_data[kstr] != cv1[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool[2] = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
}

//
// Arguments    : const char a_data[]
//                const int a_size[2]
//                boolean_T b_bool[2]
// Return Type  : void
//
void c_strcmp(const char a_data[], const int a_size[2], boolean_T b_bool[2])
{
  int exitg1;
  int kstr;
  b_bool[0] = false;
  if (a_size[1] == 11) {
    kstr = 0;
    do {
      exitg1 = 0;
      if (kstr < 11) {
        if (a_data[kstr] != cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool[0] = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  b_bool[1] = false;
  if (a_size[1] == 11) {
    kstr = 0;
    do {
      exitg1 = 0;
      if (kstr < 11) {
        if (a_data[kstr] != cv1[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool[1] = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for strcmp.cpp
//
// [EOF]
//
