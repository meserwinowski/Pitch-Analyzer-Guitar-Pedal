/*
 * Senior_ePWM.h
 *
 *  Created on: Oct 13, 2018
 *      Author: meser
 */

#ifndef _SENIOR_ePWM_H_
#define _SENIOR_ePWM_H_

/*** Enhanced Pulse Width Modulation Functions (ePWM) ***/
// Sampling Freq = 1 / Sampling Period
// Sampling Period = (TBPRD + 1) * TBCLK Period
#define SAMP_RATIO          (5000) // Samp Period (20kHz -> 0.00005) / CLK Period (100MHz -> 0.00000001)
#define ADC_CMP_PERIOD      (SAMP_RATIO >> 1)
#define ADC_SAMPLE_PERIOD   (SAMP_RATIO - 1)

// Function Prototypes
void initEPWM(void);
void initEPWM1(void);   // CPU1 - ADC A 01 (S2), 23 (S4)
void initEPWM2(void);   // CPU1 - ADC C 23 (S6)
void initEPWM3(void);   // CPU2 - ADC B 01 (S5)
void initEPWM4(void);   // CPU2 - ADC D 01 (S3), 23 (S1)
void initEPWM5(void);   // CPU1 - CLA Task 1 Interrupt

/* ------------------------------------------------------------------------------ */


#endif /* _SENIOR_ePWM_H_ */
