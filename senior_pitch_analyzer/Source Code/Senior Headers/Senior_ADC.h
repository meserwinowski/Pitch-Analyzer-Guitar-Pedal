/*
 * Senior_ADC.h
 *
 *  Created on: Oct 13, 2018
 *      Author: meser
 */

#ifndef _SENIOR_ADC_H_
#define _SENIOR_ADC_H_

#include "F28x_Project.h"

/*** Analog to Digital Converter (ADC) ***/
#define EX_ADC_RESOLUTION       16

// Function Prototypes
void configureADCs(void);
void initializeADCs(void);
void initADC(void);

/* ------------------------------------------------------------------------------ */

#endif /* _SENIOR_ADC_H_ */
