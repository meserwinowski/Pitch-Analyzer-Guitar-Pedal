/**********************************************************************
* File: Dma.c -- Lab File
* Devices: TMS320F28x7x
* Author: C2000 Technical Training, Texas Instruments
**********************************************************************/

#include "Lab.h"						// Main include file


/**********************************************************************
* Function: InitDma()
*
* Description: Initializes the DMA on the F28x7x
**********************************************************************/
void InitDma(void)
{
	asm(" EALLOW");								// Enable EALLOW protected register access

//---------------------------------------------------------------------
//--- Overall DMA setup
//---------------------------------------------------------------------
	DmaRegs.DMACTRL.bit.HARDRESET = 1;			// Reset entire DMA module
	asm(" NOP");								// 1 cycle delay for HARDRESET to take effect

	DmaRegs.DEBUGCTRL.bit.FREE = 1;				// 1 = DMA unaffected by emulation halt
	DmaRegs.PRIORITYCTRL1.bit.CH1PRIORITY = 0;	// Not using CH1 Priority mode

//---------------------------------------------------------------------
//--- Configure DMA channel 1 to read the ADC results         
//---------------------------------------------------------------------
	DmaRegs.CH1.MODE.all = 0x????;
// bit 15        ?:      CHINTE
// bit 14        ?:      DATASIZE
// bit 13-12     00:     reserved
// bit 11        ?:      CONTINUOUS
// bit 10        ?:      ONESHOT
// bit 9         ?:      CHINTMODE
// bit 8         ?:      PERINTE
// bit 7         ?:      OVRINTE
// bit 6-5       00:     reserved
// bit 4-0       ?????:  Set to channel number

//--- Select DMA interrupt source                 /******** TRIGGER SOURCE FOR EACH DMA CHANNEL (unlisted numbers are reserved) ********/
    DmaClaSrcSelRegs.DMACHSRCSEL1.bit.CH1 = ?;    // 0=none       6=ADCBINT1  12=ADCCINT2  18=ADCDINT3  32=XINT4      40=EPWM3SOCA  46=EPWM6SOCA  52=EPWM9SOCA   58=EPWM12SOCA  72=MREVTA    98=SD1FLT4    110=SPIRXDMAA     132=USBA_EPx_TX1
    DmaClaSrcSelRegs.DMACHSRCSEL1.bit.CH2 = 0;    // 1=ADCAINT1   7=ADCBINT2  13=ADCCINT3  19=ADCDINT4  33=XINT5      41=EPWM3SOCB  47=EPWM6SOCB  53=EPWM9SOCB   59=EPWM12SOCB  73=MXEVTB    99=SD2FLT1    111=SPITXDMAB     133=USBA_EPx_RX2
    DmaClaSrcSelRegs.DMACHSRCSEL1.bit.CH3 = 0;    // 2=ADCAINT2   8=ADCBINT3  14=ADCCINT4  20=ADCDEVT   36=EPWM1SOCA  42=EPWM4SOCA  48=EPWM7SOCA  54=EPWM10SOCA  68=TINT0       74=MREVTB   100=SD2FLT2    112=SPIRXDMAB     134=USBA_EPx_TX2
    DmaClaSrcSelRegs.DMACHSRCSEL1.bit.CH4 = 0;    // 3=ADCAINT3   9=ADCBINT4  15=ADCCEVT   29=XINT1     37=EPWM1SOCB  43=EPWM4SOCB  49=EPWM7SOCB  55=EPWM10SOCB  69=TINT1       95=SD1FLT1  101=SD2FLT3    113=SPITXDMAC     135=USBA_EPx_RX3
    DmaClaSrcSelRegs.DMACHSRCSEL2.bit.CH5 = 0;    // 4=ADCAINT4  10=ADCBEVT   16=ADCDINT1  30=XINT2     38=EPWM2SOCA  44=EPWM5SOCA  50=EPWM8SOCA  56=EPWM11SOCA  70=TINT2       96=SD1FLT2  102=SD2FLT4    114=SPIRXDMAC     136=USBA_EPx_TX3
    DmaClaSrcSelRegs.DMACHSRCSEL2.bit.CH6 = 0;    // 5=ADCAEVT   11=ADCCINT1  17=ADCDINT2  31=XINT3     39=EPWM2SOCB  45=EPWM5SOCB  51=EPWM8SOCB  57=EPWM11SOCB  71=MXEVTA      97=SD1FLT3  109=SPITXDMAA  131=USBA_EPx_RX1

//--- DMA trigger source lock
    DmaClaSrcSelRegs.DMACHSRCSELLOCK.bit.DMACHSRCSEL1 = 0;              // Write a 1 to lock (cannot be cleared once set)
    DmaClaSrcSelRegs.DMACHSRCSELLOCK.bit.DMACHSRCSEL2 = 0;              // Write a 1 to lock (cannot be cleared once set)

	
	DmaRegs.CH1.BURST_SIZE.bit.BURSTSIZE = 0;							// 0 means 1 word per burst
	DmaRegs.CH1.TRANSFER_SIZE = ADC_BUF_LEN-1;							// ADC_BUF_LEN bursts per transfer

	DmaRegs.CH1.SRC_TRANSFER_STEP = 0;									// 0 means add 0 to pointer each burst in a transfer
	DmaRegs.CH1.SRC_ADDR_SHADOW = (Uint32)&AdcaResultRegs.ADCRESULT0;	// SRC start address

	DmaRegs.CH1.DST_TRANSFER_STEP = 1;									// 1 = add 1 to pointer each burst in a transfer
	DmaRegs.CH1.DST_ADDR_SHADOW = (Uint32)AdcBufRaw;					// DST start address


	DmaRegs.CH1.CONTROL.all = 0x????;
// bit 15        0:      reserved
// bit 14        ?:      OVRFLG
// bit 13        ?:      RUNSTS
// bit 12        ?;      BURSTSTS
// bit 11        ?:      TRANSFERSTS
// bit 10-9      00:     reserved
// bit 8         ?:      PERINTFLG
// bit 7         ?:      ERRCLR
// bit 6-5       00:     reserved
// bit 4         ?:      PERINTCLR
// bit 3         ?:      PERINTFRC
// bit 2         ?:      SOFTRESET
// bit 1         ?:      HALT
// bit 0         ?:      RUN

//--- Finish up
	asm(" EDIS");						// Disable EALLOW protected register access

//--- Enable the DMA interrupt
	                                  	// Enable DINTCH1 in PIE group 7
	                                  	// Enable INT7 in IER to enable PIE group

} // end InitDma()


//*** end of file *****************************************************
