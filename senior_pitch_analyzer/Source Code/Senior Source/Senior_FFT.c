/*
 * Senior_FFT.c
 *
 *  Created on: Oct 20, 2018
 *      Author: meser
 */

#include "F28379D_Senior_Design.h"

uint16_t mode = MIRROR_MODE;

// Variables
float32 n = 0.0f;                // Phase Vocoder Estimation Iteration
float32 magMax = 0.0f;           // FFT Magnitude Maximum Value
uint16_t magIndex = 0;           // FFT Magnitude Maximum Index
float32 phaseDifference = 0.0f;  // Difference between the two given phase values
float32 test_est = 0.0f;         // Temporary variable to hold phase estimation
float32 absDiff = 0.0f;          // Absolute difference between FFT estimate and Phase estimate
float32 smallest;                // Temporary Loop value to hold the smallest difference
float32 nSmall = 0.0f;           // Pi value of smallest difference iteration
float32 n2pi = 0.0f;             // 2 Pi Accumulator variable

// Fixed String Frequencies
float32 fn[7] = { 0,
                  329.63,     // E4 - String 1
                  246.94,     // B3 - String 2
                  195.998,    // G3 - String 3
                  146.838,   // D3 - String 4
                  110.0,    // A2 - String 5
                  82.41};   // E2 - String 6

// CPU1 Circular Buffers
#pragma DATA_SECTION(CircularBuffer2, "CircBuff2");
#pragma DATA_SECTION(CircularBuffer4, "CircBuff4");
#pragma DATA_SECTION(CircularBuffer6, "CircBuff6");
uint16_t CircularBuffer2[CIRC_BUFF_SIZE];
uint16_t CircularBuffer4[CIRC_BUFF_SIZE];
uint16_t CircularBuffer6[CIRC_BUFF_SIZE];

// CPU2 Circular Buffers
#pragma DATA_SECTION(CircularBuffer1, "CircBuff1");
#pragma DATA_SECTION(CircularBuffer3, "CircBuff3");
#pragma DATA_SECTION(CircularBuffer5, "CircBuff5");
uint16_t CircularBuffer1[CIRC_BUFF_SIZE];
uint16_t CircularBuffer3[CIRC_BUFF_SIZE];
uint16_t CircularBuffer5[CIRC_BUFF_SIZE];

// Declare and initialize CPU1 Strings
INIT_STRINGDATA(string2, 2, &CircularBuffer2[0], 1000000.0f);
INIT_STRINGDATA(string4, 4, &CircularBuffer4[0], 1000000.0f);
INIT_STRINGDATA(string6, 6, &CircularBuffer6[0], 1000000.0f);

// Declare and Initialize CPU2 Strings
INIT_STRINGDATA(string1, 1, &CircularBuffer1[0], 1000000.0f);
INIT_STRINGDATA(string3, 3, &CircularBuffer3[0], 1000000.0f);
INIT_STRINGDATA(string5, 5, &CircularBuffer5[0], 1000000.0f);

#pragma DATA_SECTION(fo_est_cpu2, "FE_CPU2_MSG");
float32 fo_est_cpu2[7] = {FREQ_NAN, FREQ_NAN, FREQ_NAN, FREQ_NAN, FREQ_NAN, FREQ_NAN, FREQ_NAN};

#pragma DATA_SECTION(fo_n_cpu2, "FE_CPU2_MSG");
float32 fo_n_cpu2[7] = {-1, -1, -1, -1, -1, -1, -1};

// Initialize and Define Windowing Filter
#pragma DATA_SECTION(RFFTwindow, "RFFTwindow");
float32 RFFTwindow[RFFT_SIZE/2] = HANN1024;

#ifdef CPU1
    /*** Align RFFT Buffers to 2 * FFT_SIZE in Linker File ***/
    // CPU1 FFT Buffers
    #pragma DATA_SECTION(RFFT1inBuff, "RFFT1Input");        // Define Input Buffer Data Section 1
    float32 RFFT1inBuff[RFFT_SIZE];
    #pragma DATA_SECTION(RFFT1outBuff, "RFFT1Output");      // Define Output Buffer Data Section 1
    float32 RFFT1outBuff[RFFT_SIZE];
    #pragma DATA_SECTION(RFFT1magBuff, "RFFT1Magnitude");   // Define Magnitude Buffer Data Section 1
    float32 RFFT1magBuff[RFFT_SIZE/2];
    #pragma DATA_SECTION(RFFT1F32Coef, "RFFT1F32Coef");     // Define Coefficient Buffer Data Section 1
    float32 RFFT1F32Coef[RFFT_SIZE];
    #pragma DATA_SECTION(RFFT1phaseBuff, "RFFT1Phase");     // Define Phase Buffer Data Section 1
    float32 RFFT1phaseBuff[RFFT_SIZE/2];

    // Instantiate RFFT Struct
    RFFT_F32_STRUCT rfft1;
    RFFT_F32_STRUCT_Handle handler_rfft1 = &rfft1; // Pointer to CPU1 struct (required by library)
#endif

#ifdef CPU2
    // CPU2 FFT Buffers
    #pragma DATA_SECTION(RFFT2inBuff, "RFFT2Input");        // Define Input Buffer Data Section 2
    float32 RFFT2inBuff[RFFT_SIZE];
    #pragma DATA_SECTION(RFFT2outBuff, "RFFT2Output");      // Define Output Buffer Data Section 2
    float32 RFFT2outBuff[RFFT_SIZE];
    #pragma DATA_SECTION(RFFT2magBuff, "RFFT2Magnitude");   // Define Magnitude Buffer Data Section 2
    float32 RFFT2magBuff[RFFT_SIZE/2];
    #pragma DATA_SECTION(RFFT2F32Coef, "RFFT2F32Coef");     // Define Coefficient Buffer Data Section 2
    float32 RFFT2F32Coef[RFFT_SIZE];
    #pragma DATA_SECTION(RFFT2phaseBuff, "RFFT2Phase");     // Define Phase Buffer Data Section 2
    float32 RFFT2phaseBuff[RFFT_SIZE/2];

    // Instantiate RFFT Struct
    RFFT_F32_STRUCT rfft2;
    RFFT_F32_STRUCT_Handle handler_rfft2 = &rfft2; // Pointer to CPU2 struct
#endif

// Initialize FFTs
void initFFT(RFFT_F32_STRUCT_Handle handler_rfft) {

#ifdef CPU1
    // Define buffers in the RFFT Structure through it's handler
    handler_rfft->FFTSize = RFFT_SIZE;
    handler_rfft->FFTStages = RFFT_STAGES;
    handler_rfft->InBuf = &RFFT1inBuff[0];
    handler_rfft->OutBuf = &RFFT1outBuff[0];
    handler_rfft->MagBuf = &RFFT1magBuff[0];
    handler_rfft->PhaseBuf = &RFFT1phaseBuff[0];

    // Fill Cos Sin Table with Twiddle Factors (?)
#ifdef USE_TABLES
    handler_rfft->CosSinBuf = RFFT_f32_twiddleFactors;
#else
    handler_rfft->CosSinBuf = &RFFT1F32Coef[0];
    RFFT_f32_sincostable(handler_rfft);
#endif

#endif

#ifdef CPU2
    // Define buffers in the RFFT Structure through it's handler
    handler_rfft->FFTSize = RFFT_SIZE;
    handler_rfft->FFTStages = RFFT_STAGES;
    handler_rfft->InBuf = &RFFT2inBuff[0];
    handler_rfft->OutBuf = &RFFT2outBuff[0];
    handler_rfft->MagBuf = &RFFT2magBuff[0];
    handler_rfft->PhaseBuf = &RFFT2phaseBuff[0];

    // Fill Cos Sin Table with Twiddle Factors (?)
#ifdef USE_TABLES
    handler_rfft->CosSinBuf = RFFT_f32_twiddleFactors;
#else
    handler_rfft->CosSinBuf = &RFFT2F32Coef[0];
    RFFT_f32_sincostable(handler_rfft);
#endif

#endif

}

/*** Phase Vocoder Analysis Function ***/
// Takes in two phase values by reference
// Returns a fundamental frequency estimation
void vocodeAnalysis(STRING_DATA* string, RFFT_F32_STRUCT_Handle handler_rfft) {
    // Window Input Data
    RFFT_f32_win(handler_rfft->InBuf,  (float *)&RFFTwindow, RFFT_SIZE);

    // Run RFFT
    RFFT_f32(handler_rfft);

    // Calculate Magnitude and Phase
    RFFT_f32_mag_TMU0(handler_rfft);
    RFFT_f32_phase_TMU0(handler_rfft);

    // Find index of Magnitude Peak
    magMax = 0;         // Reset maximum magnitude
    magIndex = 0;       // Reset maximum magnitude index
    string->mBuff[0] = 0.0f;
    string->mBCount = 0;
    for (int i = 1; i < (RFFT_SIZE / 2); i++) {
        magMax = handler_rfft->MagBuf[i];
        if ((handler_rfft->MagBuf[i - 1] < magMax) && (magMax > handler_rfft->MagBuf[i + 1] ) && (magMax >= string->magThresh)) {
            magMax = handler_rfft->MagBuf[i];
            magIndex = i;

            // Calculate frequency normally for comparison later
            string->mBuff[string->mBCount & 0x7] = ((float32) (magIndex) / RFFT_SIZE) * NYQT_FREQ;
            string->mBCount++;
        }
    }

    // Exponential Moving Average
    string->resFFT = ((0.1 * string->resFFT) + (0.9 * string->mBuff[0]));

    // If calculated frequency is below A1 (55 Hz) return NaN
    if ((string->resFFT < 55)) {
        string->fn_est = FREQ_NAN;
    }

    // Save phase value at the same index as maximum magnitude
    string->phaseNew = handler_rfft->PhaseBuf[magIndex];

    // Run Phase Vocoder Analysis Routine
    n = 0;                  // Reset loop count
    n2pi = 0;               // Reset 2pi count
    smallest = INFINITY;    // Reset smallest difference to positive infinity (float)
    nSmall = 0;             // Reset smallest difference pi value

    // Phase Analysis cannot determine what the right frequency will be so
    // the equation will need to loop and increase by 2pi each time until
    // a frequency value similar to the FFT result is found
    phaseDifference = string->phaseNew - string->phaseOld;
    while (n < PV_LOOP_COUNT) {

        // Calculate Phase Estimation
        test_est = (phaseDifference + n2pi) / (DELTA_T_2_PI);

        // Use Absolute Value (L1 Norm) to measure accuracy
        absDiff = fabsf(string->resFFT - test_est);

        if (absDiff < smallest) {
            smallest = absDiff; // Update smallest difference
            nSmall = n2pi;      // Save phase iteration that generates the smallest difference
        }

        n2pi += M_2_PI;         // Increment by 2pi for phase equation
        n++;                    // Increment loop
    }

    // Save phase for next iteration and return F0 estimation
    string->phaseOld = string->phaseNew;
    string->fn_est = ((phaseDifference + nSmall) / (DELTA_T_2_PI));
    string->n_est = roundf(logf(string->fn_est / fn[string->str]) / ETSE_CONSTANTL);
//    return 0.0;
//    return ((phaseDifference + nSmall) / (DELTA_T_2_PI));
}

/* ------------------------------------------------------------------------------ */

// End of File

