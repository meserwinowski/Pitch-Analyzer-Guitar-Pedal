/*
 * F28379D_Senior_Design.h
 *
 *  Created on: Oct 13, 2018
 *      Author: meser
 */

#ifndef _F28379D_SENIOR_DESIGN_H_
#define _F28379D_SENIOR_DESIGN_H_

#include "math.h"
#include "F28x_Project.h"
#include "Senior_ADC.h"
#include "Senior_DMA.h"
#include "Senior_ePWM.h"
#include "Senior_FFT.h"
#include "Senior_SPI.h"
#include "Senior_SCI.h"
#include "Senior_CLA.h"

#define M_PI            (3.1415926f)            // pi 32-bit floating
#define M_2_PI          (6.2831853f)            // 2pi 32-bit floating
#define SAMP_FREQ       (20000.0f)              // Sampling Frequency
#define SAMP_PER        (0.00005f)              // Sampling Period
#define NYQT_FREQ       (SAMP_FREQ / 2)         // Nyquist Frequency
#define NYQT_PER        (0.0001f)

// Constant for Inverse Equal Tempered Scale Calculations (Root 12 of 2)
#define ETSE_CONSTANT       1.0594631f
#define ETSE_CONSTANTL      logf(ETSE_CONSTANT)

#define CPU2TOCPU1_MSGRAM       0x0003F800

typedef struct LEDdata {
    uint_fast8_t sbright:   8;
    uint_fast8_t blue:      8;
    uint_fast8_t green:     8;
    uint_fast8_t red:       8;
} LED_DATA;

//uint_least8_t diatonic[7] = {2, 2, 1, 2, 2, 2, 1};
//uint_least8_t ionian[7] =   {2, 2, 1, 2, 2, 2, 1}; // Diatonic Ionian   - WWHWWWH
//uint_least8_t dorian[7] =   {2, 1, 2, 2, 2, 1, 2}; // Diatonic Dorian   - WHWWWHW
//uint_least8_t phrygian[7] = {1, 2, 2, 2, 1, 2, 2}; // Diatonic Phrygian - HWWWHWW
//uint_least8_t lydian[7] =   {2, 2, 2, 1, 2, 2, 1}; // Diatonic Lydian   - WWWHWWH
//uint_least8_t mixolydian[7] = {}; // Diatonic Mixolydian
//uint_least8_t aeolian[7] = {}; // Diatonic Aeolian
//uint_least8_t locrian[7] = {};

//uint_least8_t pentatonic[5] = {2, 2, 3, 2, 3};

#endif /* _F28379D_SENIOR_DESIGN_H_ */
