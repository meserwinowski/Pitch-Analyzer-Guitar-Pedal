/*
 * Senior_DMA.c
 *
 *  Created on: Oct 13, 2018
 *      Author: meser
 */

//#include "Senior Headers/Senior_DMA.h"
#include "F28379D_Senior_Design.h"
#include "F2837xD_device.h"
#include "F2837xD_Examples.h"

/*** Direct Memory Access Functions ***/
void initDMA(uint16_t* buffer1) {

    /* Initialize DMA to a known state - Hard Reset,
       DMA unaffected by emulation halt, and CH1 Priority
       disabled */
    DMAInitialize();

    /* Setup DMA Channels for 3 ADCs */

    /* DMA Channel 1 - ADCA CH01 - String X */
//    DMACH1AddrConfig(buffer1, &AdcaResultRegs.ADCRESULT0);
    DMACH1AddrConfig(buffer1, &AdcaResultRegs.ADCRESULT0);

    /* TRANSFER_SIZE=256, SRC_T_STEP=0, DES_T_STEP=1 */
    DMACH1TransferConfig(DMA_BUFFER_SIZE - 1, 0, 1);

    /* DMA CH1 Mode Settings
     * Peripheral Interrupt Source - ADCA INT1
     * Peripheral Interrupt Enabled
     * Oneshot Disabled
     * Continuous Enabled
     * Sync Disabled
     * Sync Source
     * Overflow Disabled
     * 16-bit Data Size
     * Channel Interrupt Enabled at Start */
    DMACH1ModeConfig(DMA_ADCAINT1, PERINT_ENABLE, ONESHOT_DISABLE, CONT_ENABLE,
                     SYNC_DISABLE, SYNC_SRC, OVRFLOW_DISABLE, SIXTEEN_BIT,
                     CHINT_END, CHINT_ENABLE);

    /* Start DMAs */
    StartDMACH1();

    PieCtrlRegs.PIEIER7.bit.INTx1 = 1; // Enable Group 7 Interrupt 1 - DMA
    IER |= M_INT7;

}

// DMACH1AddrConfig32bit - DMA Channel 1 address configuration for 32bit Floating Point
void DMACH1AddrConfig32bitF(volatile float32 *DMA_Dest, volatile Uint16 *DMA_Source)
{
    EALLOW;

    //
    // Set up SOURCE address:
    //
    DmaRegs.CH1.SRC_BEG_ADDR_SHADOW = (Uint32)DMA_Source; // Point to beginning
                                                          // of source buffer
    DmaRegs.CH1.SRC_ADDR_SHADOW =     (Uint32)DMA_Source;

    //
    // Set up DESTINATION address:
    //
    DmaRegs.CH1.DST_BEG_ADDR_SHADOW = (Uint32)DMA_Dest;  // Point to beginning
                                                         // of destination
                                                         // buffer
    DmaRegs.CH1.DST_ADDR_SHADOW =     (Uint32)DMA_Dest;

    EDIS;
}

/* ------------------------------------------------------------------------------ */

// End of File
