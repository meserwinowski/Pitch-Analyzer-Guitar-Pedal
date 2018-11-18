/*
 * Senior_CLA.h
 *
 *  Created on: Nov 17, 2018
 *      Author: meser
 */

#ifndef _SENIOR_CLA_H_
#define _SENIOR_CLA_H_

/*** Control Law Accelerator (CLA) - CPU1 ***/

// CLA Function Prototypes
extern interrupt void Cla1Task1();
extern interrupt void Cla1Task2();
extern interrupt void Cla1Task3();
extern interrupt void Cla1Task4();
extern interrupt void Cla1Task5();
extern interrupt void Cla1Task6();
extern interrupt void Cla1Task7();
extern interrupt void Cla1Task8();

// Function Prototypes
void initCLA(void);
void run_cla_blinky(void);

/* ------------------------------------------------------------------------------ */

#endif /* _SENIOR_CLA_H_ */
