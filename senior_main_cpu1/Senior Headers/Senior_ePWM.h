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
#define ADC_SAMPLE_PERIOD   4999 // Put this number into TBPRD

void initEPWM(void);

/* ------------------------------------------------------------------------------ */


#endif /* SENIOR_ePWM_H_ */
