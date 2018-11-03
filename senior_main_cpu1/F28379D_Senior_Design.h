/*
 * F28379D_Senior_Design.h
 *
 *  Created on: Oct 13, 2018
 *      Author: meser
 */

#ifndef _F28379D_SENIOR_DESIGN_H_
#define _F28379D_SENIOR_DESIGN_H_

#include "F28x_Project.h"
#include "Senior Headers/Senior_ADC.h"
#include "Senior Headers/Senior_DMA.h"
#include "Senior Headers/Senior_ePWM.h"
#include "Senior Headers/Senior_FFT.h"
#include "Senior Headers/Senior_SPI.h"

#define M_PI            3.1415926                    // pi 32-bit floating
#define M_2_PI          6.2831853                    // 2pi 32-bit floating
#define SAMP_FREQ       23000                        // Sampling Frequency
#define SAMP_PER        1 / SAMP_FREQ                // Sampling Period
#define NYQT_FREQ       SAMP_FREQ / 2                // Nyquist Frequency

#endif /* _F28379D_SENIOR_DESIGN_H_ */
