/**********************************************************************
* File: Watchdog.c -- Lab File
* Devices: TMS320F28x7x
* Author: C2000 Technical Training, Texas Instruments
**********************************************************************/

#include "Lab.h"						// Main include file


/**********************************************************************
* Function: InitWatchdog()
*
* Description: Initializes Watchdog Timer for the F28x7x
**********************************************************************/
void InitWatchdog(void)
{
	asm(" EALLOW");						// Enable EALLOW protected register access

//--- Disable the Watchdog Timer
	WdRegs.WDCR.all = 0x????;
// bit 15-7      0's:    reserved
// bit 6         ?:      WDDIS
// bit 5-3       ???:    WDCHK
// bit 2-0       ???:    WDPS

//--- System and Control Register
	WdRegs.SCSR.all = 0x????;
// bit 15-3      0's:    reserved
// bit 2         ?:      WDINTS
// bit 1         ?:      WDENINT
// bit 0         ?:      WDOVERRIDE

	WdRegs.WDWCR.all = 0x0000;
// bit 15-9      0's:    reserved
// bit 8         0:      FIRSTKEY (read-only)
// bit 7-0       0x00:   MIN, minimum service interval - 0x00 is no minimum

	asm(" EDIS");						// Disable EALLOW protected register access

//--- Enable the Watchdog interrupt
                                        // Enable WAKEINT (LPM/WD) in PIE group #1
                                        // Enable INT1 in IER to enable PIE group 1

} // end of InitWatchdog()


//--- end of file -----------------------------------------------------
