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
#define CHANGE_TUNING       0x03

#define STRING1             0x01
#define STRING2             0x02
#define STRING3             0x03
#define STRING4             0x04
#define STRING5             0x05
#define STRING6             0x06

#define MIRROR_MODE         0x01
#define LEARNING_MODE       0x02
#define TUNING_MODE         0x03

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
#define F_n                 0x01
#define FsGb_n              0x02
#define G_n                 0x03
#define GsAb_n              0x04
#define A_n                 0x05
#define AsBb_n              0x06
#define B_n                 0x07
#define C_n                 0x08
#define CsDb_n              0x09
#define D_n                 0x0A
#define DsEb_n              0x0B
#define E_n                 0x0C

/* Trasmit Acknowledge */
#define ACK                 0x41 // 'A'
#define NACK                0x00

/* Function Prototypes */
void initSCI(void);
void initSCIB(void);
void initSCIBFIFO(void);
void SCIB_TX(uint_fast8_t a);
void SCIB_MSG(char *msg);
void determineCommand(void);

/* ------------------------------------------------------------------------------ */

#endif /* _SENIOR_SCI_H_ */
