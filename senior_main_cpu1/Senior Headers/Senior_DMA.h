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

void initDMA(uint16_t* buffer1);
void DMACH1AddrConfig32bitF(volatile float32 *DMA_Dest, volatile Uint16 *DMA_Source);

/* ------------------------------------------------------------------------------ */

#endif /* _SENIOR_DMA_H_ */
