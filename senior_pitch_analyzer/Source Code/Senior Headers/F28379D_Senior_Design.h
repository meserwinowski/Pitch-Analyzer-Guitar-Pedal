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

#define M_PI            (3.1415926)                  // pi 32-bit floating
#define M_2_PI          (6.2831853)                  // 2pi 32-bit floating
#define SAMP_FREQ       (20000)                      // Sampling Frequency
#define SAMP_PER        (1 / SAMP_FREQ)              // Sampling Period
#define NYQT_FREQ       (SAMP_FREQ / 2)              // Nyquist Frequency
#define NYQT_PER        (1 / NYQT_FREQ)

#define CPU2TOCPU1_MSGRAM       0x0003F800

#endif /* _F28379D_SENIOR_DESIGN_H_ */
