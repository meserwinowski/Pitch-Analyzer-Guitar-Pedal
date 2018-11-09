/*
 * Senior_FFT.c
 *
 *  Created on: Oct 20, 2018
 *      Author: meser
 */

#include "F28379D_Senior_Design.h"

// Defines
#define PV_LOOP_COUNT           (25)     // Number of times the Phase Analysis routine will loop
#define DELTA_T                 (0.0256) // Time between FFTs - (RFFT_SIZE / OVERLAP) * NYQUIST_PERIOD
#define DELTA_T_2_PI            (M_2_PI * DELTA_T)

// Variables
volatile float32 resFFT = 0;             // FFT Bin Conversion Result
volatile float32 freq_est = 0;           // Local Frequency Estimation from Phase Vocoder
volatile float32 n = 0.0;                // Phase Vocoder Estimation Iteration
volatile float32 magMax = 0.0;           // FFT Magnitude Maximum Value
volatile uint16_t magIndex = 0;          // FFT Magnitude Maximum Index
volatile float32 phaseDifference = 0;    // Difference between the two given phase values
volatile float32 test_est = 0;           // Temporary variable to hold phase estimation
volatile float32 absDiff = 0;            // Absolute difference between FFT estimate and Phase estimate
volatile float32 smallest;               // Temporary Loop value to hold the smallest difference
volatile float32 nSmall = 0;             // Pi value of smallest difference iteration
volatile float32 n2pi = 0;               // 2 Pi Accumulator variable

// Align RFFT Buffers to 2 * FFT_SIZE in Linker File
#pragma DATA_SECTION(RFFTinBuff, "RFFTdata1");      // Define Input Buffer Data Section
float32 RFFTinBuff[RFFT_SIZE];
#pragma DATA_SECTION(RFFToutBuff, "RFFTdata2");     // Define Output Buffer Data Section
float32 RFFToutBuff[RFFT_SIZE];
#pragma DATA_SECTION(RFFTmagBuff, "RFFTdata3");     // Define Magnitude Buffer Data Section
float32 RFFTmagBuff[RFFT_SIZE/2 + 1];
#pragma DATA_SECTION(RFFTF32Coef, "RFFTdata4");     // Define Coefficient Buffer Data Section
float32 RFFTF32Coef[RFFT_SIZE];
#pragma DATA_SECTION(RFFTphaseBuff, "RFFTdata5");   // Define Phase Buffer Data Section
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
    magMax = 0;         // Reset maximum magnitude
    magIndex = 0;       // Reset maximum magnitude index
    for (int i = 0; i < (RFFT_SIZE / 2); i++) {
        if (handler_rfft->MagBuf[i] > magMax) {
            magMax = handler_rfft->MagBuf[i];
            magIndex = i;
        }
    }

    // Calculate frequency normally for comparison later
    resFFT = (((float32) magIndex) / RFFT_SIZE) * NYQT_FREQ;

    // Save phase value at the same index as maximum magnitude
    *phase2 = handler_rfft->PhaseBuf[magIndex];

    // Run Phase Vocoder Analysis Routine
    n = 0;                  // Reset loop count
    n2pi = 0;               // Reset 2pi count
    smallest = INFINITY;    // Reset smallest difference to positive infinity (float)
    nSmall = 0;             // Reset smallest difference pi value

    // Phase Analysis cannot determine what the right frequency will be so
    // the equation will need to loop and increase by 2pi each time until
    // a frequency value similar to the FFT result is found
    phaseDifference = *phase2 - *phase1;
    while (n < PV_LOOP_COUNT) {

        // Calculate Phase Estimation
        test_est = (phaseDifference + n2pi) / (DELTA_T_2_PI);

        // Use Absolute Value (L1 Norm) to measure accuracy
        absDiff = fabsf(resFFT - test_est);

        if (absDiff < smallest) {
            smallest = absDiff; // Update smallest difference
            nSmall = n2pi;      // Save phase iteration that generates the smallest difference
        }

        n2pi += M_2_PI;         // Increment by 2pi for phase equation
        n++;                    // Increment loop
    }

    // Save phase for next iteration and return F0 estimation
    freq_est = (phaseDifference + nSmall) / (DELTA_T_2_PI);
    *phase1 = *phase2;
    return freq_est;
}


