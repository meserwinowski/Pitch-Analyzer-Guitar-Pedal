/*
 * Senior_SCI.h
 *
 *  Created on: Nov 16, 2018
 *      Author: meser
 */

#ifndef _SENIOR_SCI_H_
#define _SENIOR_SCI_H_

/*** Serial Communication Interface Functions (SCI) ***/

// Function Prototypes
void initSCI(void);
void initSCIB(void);
void initSCIBFIFO(void);
void SCIB_TX(int a);
void SCIB_MSG(char *msg);

/* ------------------------------------------------------------------------------ */

#endif /* _SENIOR_SCI_H_ */
