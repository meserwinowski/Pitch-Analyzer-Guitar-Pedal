/**********************************************************************
* File: ECap.c -- Lab File
* Devices: TMS320F28x7x
* Author: C2000 Technical Training, Texas Instruments
**********************************************************************/

#include "Lab.h"						// Main include file


/**********************************************************************
* Function: InitECap()
*
* Description: Initializes the Enhanced Capture modules on the F28x7x
**********************************************************************/
void InitECap(void)
{
//---------------------------------------------------------------------
//--- Configure eCAP1 unit for capture                        
//---------------------------------------------------------------------
	asm(" EALLOW");							// Enable EALLOW protected register access
	DevCfgRegs.SOFTPRES3.bit.ECAP1 = 1;		// eCAP1 is reset
	DevCfgRegs.SOFTPRES3.bit.ECAP1 = 0;		// eCAP1 is released from reset
	asm(" EDIS");

	ECap1Regs.ECEINT.all = 0;					// Disable all eCAP interrupts
	ECap1Regs.ECCTL1.bit.CAPLDEN = 0;			// Disabled loading of capture results
	ECap1Regs.ECCTL2.bit.TSCTRSTOP = 0;			// Stop the counter

	ECap1Regs.TSCTR = 0;						// Clear the counter
	ECap1Regs.CTRPHS = 0;						// Clear the counter phase register

	ECap1Regs.ECCTL2.all = 0x????;				// ECAP control register 2
// bit 15-11     00000:  reserved
// bit 10        ?:      APWMPOL
// bit 9         ?:      CAP/APWM
// bit 8         ?:      SWSYNC
// bit 7-6       ??:     SYNCO_SEL
// bit 5         ?:      SYNCI_EN
// bit 4         ?:      TSCTRSTOP
// bit 3         ?:      RE-ARM
// bit 2-1       ??:     STOP_WRAP
// bit 0         ?:      CONT/ONESHT

	ECap1Regs.ECCTL1.all = 0x????;				// ECAP control register 1
// bit 15-14     11:     FREE/SOFT, 11 = ignore emulation suspend
// bit 13-9      ?????:  PRESCALE
// bit 8         ?:      CAPLDEN
// bit 7         ?:      CTRRST4
// bit 6         ?:      CAP4POL
// bit 5         ?:      CTRRST3
// bit 4         ?:      CAP3POL
// bit 3         ?:      CTRRST2
// bit 2         ?:      CAP2POL
// bit 1         ?:      CTRRST1
// bit 0         ?:      CAP1POL

	ECap1Regs.ECEINT.all = 0x????;				// Enable desired eCAP interrupts
// bit 15-8      0's:    reserved
// bit 7         ?:      CTR=CMP
// bit 6         ?:      CTR=PRD
// bit 5         ?:      CTROVF
// bit 4         ?:      CEVT4
// bit 3         ?:      CEVT3
// bit 2         ?:      CEVT2
// bit 1         ?:      CEVT1
// bit 0         0:      reserved

	                                  	// Enable ECAP1_INT in PIE group 4
	                                  	// Enable INT4 in IER to enable PIE group 4

} // end InitECap()


//--- end of file -----------------------------------------------------
