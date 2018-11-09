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

void initDMA(void);
void initDMA2(void);
void initDMA4(void);
void initDMA6(void);

/* ------------------------------------------------------------------------------ */

#endif /* _SENIOR_DMA_H_ */
