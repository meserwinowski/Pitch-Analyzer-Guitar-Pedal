/*
 * Senior_SPI.h
 *
 *  Created on: Nov 1, 2018
 *      Author: meser
 */

#ifndef _SENIOR_SPI_H_
#define _SENIOR_SPI_H_

#include "F28x_Project.h"

/* Define to Calculate Baud Rate
 * BRR: 7-bit Baud Rate Register
 * SPI CLK Frequency = 300kHz
 * LSP CLK Frequency = CPU Frequency / 4 (Default)
 * BRR               = (LSPCLK / SPICLK) - 1
 */

#if CPU_FRQ_200MHZ
    #define SPI_BRR     ((200E6 / 4) / 1E6) - 1
#endif

/*** Serial Peripheral Interface Functions (SPI) ***/

// Function Prototypes
void initSPI(void);
void init_SPIA_GPIO(void);

/* ------------------------------------------------------------------------------ */

#endif /* _SENIOR_SPI_H_ */
