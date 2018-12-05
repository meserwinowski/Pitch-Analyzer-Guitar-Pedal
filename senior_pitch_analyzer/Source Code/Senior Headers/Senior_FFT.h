/*
 * Senior_FFT.h
 *
 *  Created on: Oct 13, 2018
 *      Author: meser
 */

#ifndef _SENIOR_FFT_H_
#define _SENIOR_FFT_H_

#include "F28x_Project.h"
#include "fpu_rfft.h"
#include "fpu_fft_hann.h"

/*** Fast Fourier Transform (FFT) Library ***/
// Defines
#define RFFT_STAGES             10                 // RFFT = 1024
#define RFFT_SIZE               (1 << RFFT_STAGES) // 2 ^ STAGES
#define CIRC_BUFF_SIZE          2 * RFFT_SIZE
#define CIRC_MASK               CIRC_BUFF_SIZE - 1
#define OVERLAP                 4                  // Phase Vocoder FFT Overlap
#define PV_LOOP_COUNT           (30)      // Number of times the Phase Analysis routine will loop
#define DELTA_T                 (0.0256f) // Time between FFTs - (RFFT_SIZE / OVERLAP) * NYQUIST_PERIOD
#define DELTA_T_2_PI            (M_2_PI * DELTA_T)
#define FREQ_NAN                1.0f

// String Structure
typedef struct stringData {
    uint16_t str;
    uint16_t* cBuff;       // Pointer to Circular Buffer
//    int16_t* cBuff;       // Pointer to Circular Buffer
    float32 phaseOld;      // Previous Phase Calculation
    float32 phaseNew;      // New Phase Calculation
    uint16_t xDMA;         // DMA to Circular Buffer Index
    bool_t done;           // DMA Done Flag
    float32 magThresh;     // String Specific Magnitude Threshold
    float32 resFFT;        // Frequency Estimation from FFT
    float32  mBuff[8];     // Max Magnitude Buffer
    uint16_t mBCount;      // Max Magnitude Buffer Counter
    float32 fn_est;        // Phase Analysis Frequency Estimation
    float32 n_est;         // Converted Fret Estimation
} STRING_DATA;

// String Struct Initialization Macro
#define INIT_STRINGDATA(X, num, cb, mt) STRING_DATA X = {.str = num, .cBuff = cb, \
                                                         .phaseOld = 0, .phaseNew = 0, \
                                                         .xDMA = 0, .done = 0, \
                                                         .n_est = -1.0f, .magThresh = mt};

// Function Prototypes
void initFFT(RFFT_F32_STRUCT_Handle handler_rfft);

#pragma CODE_SECTION(vocodeAnalysis, ".TI.ramfunc");
void vocodeAnalysis(STRING_DATA* string, RFFT_F32_STRUCT_Handle handler_rfft);

/* ------------------------------------------------------------------------------ */

#endif /* _SENIOR_FFT_H_ */
