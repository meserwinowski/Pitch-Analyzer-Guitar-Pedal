/*
 * Senior_ePWM.h
 *
 *  Created on: Oct 13, 2018
 *      Author: meser
 */

#ifndef SENIOR_ePWM_H_
#define SENIOR_ePWM_H_

/*** Enhanced Pulse Width Modulation Functions (ePWM) ***/
// Sampling Freq = 1 / Sampling Period
// Sampling Period = (TBPRD + 1) * TBCLK Period
#define SAMP_RATIO          (5000) // Samp Period (20kHz -> 0.00005) / CLK Period (100MHz -> 0.00000001)
#define ADC_CMP_PERIOD      (SAMP_RATIO >> 1)
#define ADC_SAMPLE_PERIOD   (SAMP_RATIO - 1) // Put this number into TBPRD

void initEPWM(void);
void initEPWM1(void);
void initEPWM2(void);
void initEPWM3(void);

/* ------------------------------------------------------------------------------ */


#endif /* SENIOR_ePWM_H_ */
