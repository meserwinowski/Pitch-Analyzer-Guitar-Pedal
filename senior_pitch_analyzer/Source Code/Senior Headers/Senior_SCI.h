/*
 * Senior_SCI.h
 *
 *  Created on: Nov 16, 2018
 *      Author: meser
 */

#ifndef _SENIOR_SCI_H_
#define _SENIOR_SCI_H_

/*** Serial Communication Interface Functions (SCI) ***/

// Defines
/*--- Commands ---*/
#define CHANGE_MODE         0x01
#define CHANGE_COLOR        0x02
#define CHANGE_TUNING_S1    0x11
#define CHANGE_TUNING_S2    0x12
#define CHANGE_TUNING_S3    0x13
#define CHANGE_TUNING_S4    0x14
#define CHANGE_TUNING_S5    0x15
#define CHANGE_TUNING_S6    0x16

#define MIRROR_MODE         0x01
#define LEARNING_MODE       0x02

/* Scales */
#define PENTA_IONIAN        0x01
#define PENTA_DORIAN        0x02
#define PENTA_PHRYGIAN      0x03
#define PENTA_MIXOLYDIAN    0x04
#define PENTA_AEOLIAN       0x05
#define IONIAN              0x06
#define DORIAN              0x07
#define PHRYGIAN            0x08
#define LYDIAN              0x09
#define MIXOLYDIAN          0x0A
#define AEOLIAN             0x0B
#define LOCRIAN             0x0C

/* Root Notes */
#define C_n                 0x01
#define CsDb_n              0x02
#define D_n                 0x03
#define DsEb_n              0x04
#define E_n                 0x05
#define F_n                 0x06
#define FsGb_n              0x07
#define G_n                 0x08
#define GsAb_n              0x09
#define A_n                 0x0A
#define AsBb_n              0x0B
#define B_n                 0x0C

#define ACK                 0x41 // 'A'
#define NACK                0x00

// Function Prototypes
void initSCI(void);
void initSCIB(void);
void initSCIBFIFO(void);
void SCIB_TX(uint_fast8_t a);
void SCIB_MSG(char *msg);
void determineCommand(void);

/* ------------------------------------------------------------------------------ */

#endif /* _SENIOR_SCI_H_ */
