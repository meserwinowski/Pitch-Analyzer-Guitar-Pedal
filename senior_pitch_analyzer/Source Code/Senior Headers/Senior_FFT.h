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
#define RFFT_STAGES             10                 // RFFT = 1024
#define RFFT_SIZE               (1 << RFFT_STAGES) // 2 ^ STAGES
#define CIRC_BUFF_SIZE          2 * RFFT_SIZE
#define CIRC_MASK               CIRC_BUFF_SIZE - 1
#define OVERLAP                 4                  // Phase Vocoder FFT Overlap
#define MAG_THRESHOLD           750000.0f
#define FREQ_NAN                1.0f

typedef struct stringData {
    uint16_t str;
    uint16_t* cBuff;       // Pointer to Circular Buffer
    float32 phaseOld;      // Previous Phase Calculation
    float32 phaseNew;      // New Phase Calculation
    uint16_t xDMA;         // DMA to Circular Buffer Index
    bool_t done;           // DMA Done Flag
    float32 fo_est;
} STRING_DATA;

#define INIT_STRINGDATA(X, num, cb) STRING_DATA X = {.str = num, .cBuff = cb, .phaseOld = 0, .phaseNew = 0, .xDMA = 0, .done = 0};

// Function Prototypes
void initFFT(RFFT_F32_STRUCT_Handle handler_rfft);

#pragma CODE_SECTION(vocodeAnalysis, ".TI.ramfunc");
//float32 vocodeAnalysis(volatile float32* phase1,
//                       volatile float32* phase2,
//                       RFFT_F32_STRUCT_Handle handler_rfft);
float32 vocodeAnalysis(STRING_DATA* string, RFFT_F32_STRUCT_Handle handler_rfft);

/* ------------------------------------------------------------------------------ */

#endif /* _SENIOR_FFT_H_ */
