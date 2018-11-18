/*
 * Senior_DMA.h
 *
 *  Created on: Oct 13, 2018
 *      Author: meser
 */

#ifndef _SENIOR_DMA_H_
#define _SENIOR_DMA_H_

#include "F28x_Project.h"

/*** Direct Memory Access Functions (DMA) ***/
#define DMA_BUFFER_SIZE     256

// Function Prototypes
void initDMA(void);
void initDMAx(volatile uint16_t * CB, volatile uint16_t * ADCRR, uint16_t ADCINT, uint16_t dma);

/* ------------------------------------------------------------------------------ */

#endif /* _SENIOR_DMA_H_ */
