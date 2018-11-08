/*
 * Senior_FFT.c
 *
 *  Created on: Oct 20, 2018
 *      Author: meser
 */

#include "F28379D_Senior_Design.h"

// Defines
#define binRange                (SAMP_FREQ / RFFT_SIZE) * 0.5

// Variables
volatile float32 res = 0;       // FFT Bin Conversion Result
volatile float32 freq_est = 0;  // Local Frequency Estimation from Phase Vocoder
float32 testN = 0.0;        // Phase Vocoder Estimation Iteration
volatile float32 magMax = 0.0;  // FFT Magnitude Maximum Value
volatile uint16_t magIndex = 0; // FFT Magnitude Maximum Index
volatile float32 upper = 0;     // Upper FFT Max Bin Range
volatile float32 lower = 0;     // Lower FFT Max Bin Range
float32 delta_t = 0.0128;       // Time between FFTs - (RFFT_SIZE / OVERLAP) * SAMPLING_PERIOD
float32 vpi = 6.2831853;

float32 best;
float32 pd;
float32 nRes;
float32 dRes;
float32 test_est;
float32 absRes;

// Align RFFT Buffers to 2 * FFT_SIZE in Linker File
#pragma DATA_SECTION(RFFTinBuff, "RFFTdata1"); // Define Input Buffer Data Section
float32 RFFTinBuff[RFFT_SIZE];
#pragma DATA_SECTION(RFFToutBuff, "RFFTdata2"); // Define Output Buffer Data Section
float32 RFFToutBuff[RFFT_SIZE];
#pragma DATA_SECTION(RFFTmagBuff, "RFFTdata3"); // Define Magnitude Buffer Data Section
float32 RFFTmagBuff[RFFT_SIZE/2 + 1];
#pragma DATA_SECTION(RFFTF32Coef, "RFFTdata4"); // Define Coefficient Buffer Data Section
float32 RFFTF32Coef[RFFT_SIZE];
#pragma DATA_SECTION(RFFTphaseBuff, "RFFTdata5"); // Define Phase Buffer Data Section
float32 RFFTphaseBuff[RFFT_SIZE/2];

// Initialize and Define Windowing Filter
float32 RFFTwindow[RFFT_SIZE/2] = HANN1024;

// Instantiate RFFT Struct
RFFT_F32_STRUCT rfft;
RFFT_F32_STRUCT_Handle handler_rfft = &rfft; // Pointer to struct (required by library)

// Initialize FFTs
void initFFT(RFFT_F32_STRUCT_Handle handler_rfft) {
    // Define buffers in the RFFT Structure through it's handler
    handler_rfft->FFTSize = RFFT_SIZE;
    handler_rfft->FFTStages = RFFT_STAGES;
    handler_rfft->InBuf = &RFFTinBuff[0];
    handler_rfft->OutBuf = &RFFToutBuff[0];
    handler_rfft->MagBuf = &RFFTmagBuff[0];
    handler_rfft->PhaseBuf = &RFFTphaseBuff[0];

    // Fill Cos Sin Table with Twiddle Factors (?)
#ifdef USE_TABLES
    handler_rfft->CosSinBuf = RFFT_f32_twiddleFactors;
#else
    handler_rfft->CosSinBuf = &RFFTF32Coef[0];
    RFFT_f32_sincostable(handler_rfft);
#endif

}

/*** Phase Vocoder Analysis Function ***/
// Takes in two phase values by reference
// Returns a fundamental frequency estimation
float32 vocodeAnalysis(float32* phase1, float32* phase2) {
    // Window Input Data
    RFFT_f32_win(&RFFTinBuff[0],  (float *)&RFFTwindow, RFFT_SIZE);

    // Run RFFT
    RFFT_f32(handler_rfft);

    // Calculate Magnitude and Phase
    RFFT_f32_mag_TMU0(handler_rfft);
    RFFT_f32_phase_TMU0(handler_rfft);

    // Find index of Magnitude Peak
    magMax = 0;
    magIndex = 0;
    for (int i = 0; i < (RFFT_SIZE / 2); i++) {
        if (handler_rfft->MagBuf[i] > magMax) {
            magMax = handler_rfft->MagBuf[i];
            magIndex = i;
        }
    }

    // Calculate frequency normally for comparison later
    res = (((float32) magIndex) / RFFT_SIZE) * NYQT_FREQ;

    // Save phase value at the same index as maximum magnitude
    *phase2 = handler_rfft->PhaseBuf[magIndex];

    // Run Phase Vocoder Analysis Routine
    upper = res + binRange;
    lower = res - binRange;
    testN = 0;
    nRes = 0;
    best = 1000;
    uint16_t nbest = 0;
    pd = *phase2 - *phase1;
    dRes = vpi * delta_t;
    while (testN < 50) {

        // Loop until frequency estimation is within a certain range
        nRes += 6.2831853;

        test_est = (pd + nRes) / dRes;
//        freq_est = ((*phase2 - *phase1) + (6.2831853 * n)) / (6.2831853 * delta_t);
        absRes = fabsf(res - freq_est);
        if (fabsf(res - freq_est) < best) {
            best = fabsf(res - freq_est);
            nbest = testN;
        }

        testN++;
    }

    // Save phase for next iteration and return F0 estimation
    freq_est = ((*phase2 - *phase1) + (M_2_PI * nbest)) / (M_2_PI * delta_t);
    *phase1 = *phase2;
    return freq_est;
}


