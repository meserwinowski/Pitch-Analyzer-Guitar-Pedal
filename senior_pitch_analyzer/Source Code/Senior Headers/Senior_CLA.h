/*
 * Senior_CLA.h
 *
 *  Created on: Nov 17, 2018
 *      Author: meser
 */

#ifndef _SENIOR_CLA_H_
#define _SENIOR_CLA_H_

/*** Control Law Accelerator (CLA) - CPU1 ***/

/* CLA Function Prototypes */
extern interrupt void Cla1Task1();
extern interrupt void Cla1Task2();
extern interrupt void Cla1Task3();
extern interrupt void Cla1Task4();
extern interrupt void Cla1Task5();
extern interrupt void Cla1Task6();
extern interrupt void Cla1Task7();
extern interrupt void Cla1Task8();

/* CLA Data */
#define DEFAULT_FRAME       0xE0000000
#define DEFAULT_LED_WHITE   0xE21F1F1F
#define DEFAULT_LED_BLUE    0xE21F0000
#define DEFAULT_LED_RED     0xE200001F
#define START_FRAME         0x00000000
#define END_FRAME           0xF0000000

/* Function Prototypes */
void initCLA(void);
void initLUT(void);

/* ------------------------------------------------------------------------------ */

#endif /* _SENIOR_CLA_H_ */
