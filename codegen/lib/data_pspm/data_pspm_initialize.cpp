//
// File: data_pspm_initialize.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 23-Aug-2023 11:38:45
//

// Include Files
#include "data_pspm_initialize.h"
#include "data_pspm_data.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
void data_pspm_initialize()
{
  rt_InitInfAndNaN();
  isInitialized_data_pspm = true;
}

//
// File trailer for data_pspm_initialize.cpp
//
// [EOF]
//
