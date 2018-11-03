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
#include "fpu_fft_hamming.h"

/*** Fast Fourier Transform (FFT) Library ***/
#define RFFT_STAGES             10                 // RFFT = 1024
#define RFFT_SIZE               (1 << RFFT_STAGES) // 2 ^ STAGES
#define CIRC_BUFF_SIZE          2 * RFFT_SIZE
#define CIRC_MASK               CIRC_BUFF_SIZE - 1
#define OVERLAP                 4                  // Phase Vocoder FFT Overlap
#define DELTA_t                 (RFFT_SIZE / OVERLAP) * SAMP_PER

void initFFT(RFFT_F32_STRUCT_Handle handler_rfft);
float32 vocodeAnalysis(float32* phase1, float32* phase2);

/* ------------------------------------------------------------------------------ */

#endif /* _SENIOR_FFT_H_ */
