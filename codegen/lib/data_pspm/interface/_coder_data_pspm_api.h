//
// File: _coder_data_pspm_api.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 23-Aug-2023 11:38:45
//

#ifndef _CODER_DATA_PSPM_API_H
#define _CODER_DATA_PSPM_API_H

// Include Files
#include "coder_array_mex.h"
#include "emlrt.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
void data_pspm(coder::array<real_T, 2U> *dat, uint32_T fs,
               coder::array<real_T, 2U> *pdata, coder::array<real_T, 2U> *fdata,
               coder::array<real_T, 2U> *tdata);

void data_pspm_api(const mxArray *const prhs[2], int32_T nlhs,
                   const mxArray *plhs[3]);

void data_pspm_atexit();

void data_pspm_initialize();

void data_pspm_terminate();

void data_pspm_xil_shutdown();

void data_pspm_xil_terminate();

#endif
//
// File trailer for _coder_data_pspm_api.h
//
// [EOF]
//
