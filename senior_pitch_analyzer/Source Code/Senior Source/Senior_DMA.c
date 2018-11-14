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

extern volatile uint16_t CircularBuffer1;
extern volatile uint16_t CircularBuffer2;
extern volatile uint16_t CircularBuffer3;
extern volatile uint16_t CircularBuffer4;
extern volatile uint16_t CircularBuffer5;
extern volatile uint16_t CircularBuffer6;

/*** Direct Memory Access Functions ***/

void initDMA(void) {
    /* Initialize DMA to a known state - Hard Reset,
       DMA unaffected by emulation halt, and CH1 Priority
       disabled */
    DMAInitialize();

#ifdef CPU1
    /* Setup DMA Channels for 3 ADCs on CPU1 */
    initDMA2();
    initDMA4();
    initDMA6();
#endif

#ifdef CPU2
    /* Setup DMA Channels for 3 ADCs on CPU2 */
    initDMA1();
    initDMA3();
    initDMA5();
#endif

    // Enable Group 7 Interrupts
    IER |= M_INT7;
}

void initDMA1(void) {

    /* DMA Channel 1 - ADCD CH23 - String 1 */
    DMACH1AddrConfig(&CircularBuffer1, &AdcdResultRegs.ADCRESULT1);

    /* TRANSFER_SIZE=256, SRC_T_STEP=0, DES_T_STEP=1 */
    DMACH1TransferConfig(DMA_BUFFER_SIZE - 1, 0, 1);

    /* DMA CH1 Mode Settings
     * Peripheral Interrupt Source - ADCD INT1
     * Peripheral Interrupt Enabled
     * Oneshot Disabled
     * Continuous Enabled
     * Sync Disabled
     * Sync Source
     * Overflow Disabled
     * 16-bit Data Size
     * Channel Interrupt Enabled at Start */
    DMACH1ModeConfig(DMA_ADCDINT2, PERINT_ENABLE, ONESHOT_DISABLE, CONT_ENABLE,
                     SYNC_DISABLE, SYNC_SRC, OVRFLOW_DISABLE, SIXTEEN_BIT,
                     CHINT_END, CHINT_ENABLE);

    /* Start DMAs */
    StartDMACH1();

    PieCtrlRegs.PIEIER7.bit.INTx1 = 1; // Enable Group 7 Interrupt 1 - DMA1
}

void initDMA2(void) {

    /* DMA Channel 2 - ADCA CH01 - String 2 */
    DMACH2AddrConfig(&CircularBuffer2, &AdcaResultRegs.ADCRESULT0);

    /* TRANSFER_SIZE=256, SRC_T_STEP=0, DES_T_STEP=1 */
    DMACH2TransferConfig(DMA_BUFFER_SIZE - 1, 0, 1);

    /* DMA CH2 Mode Settings
     * Peripheral Interrupt Source - ADCA INT1
     * Peripheral Interrupt Enabled
     * Oneshot Disabled
     * Continuous Enabled
     * Sync Disabled
     * Sync Source
     * Overflow Disabled
     * 16-bit Data Size
     * Channel Interrupt Enabled at Start */
    DMACH2ModeConfig(DMA_ADCAINT1, PERINT_ENABLE, ONESHOT_DISABLE, CONT_ENABLE,
                     SYNC_DISABLE, SYNC_SRC, OVRFLOW_DISABLE, SIXTEEN_BIT,
                     CHINT_END, CHINT_ENABLE);

    /* Start DMAs */
    StartDMACH2();

    PieCtrlRegs.PIEIER7.bit.INTx2 = 1; // Enable Group 7 Interrupt 2 - DMA2

}

void initDMA3(void) {

    /* DMA Channel 3 - ADCD CH01 - String 3 */
    DMACH3AddrConfig(&CircularBuffer3, &AdcdResultRegs.ADCRESULT0);

    /* TRANSFER_SIZE=256, SRC_T_STEP=0, DES_T_STEP=1 */
    DMACH3TransferConfig(DMA_BUFFER_SIZE - 1, 0, 1);

    /* DMA CH3 Mode Settings
     * Peripheral Interrupt Source - ADCA INT1
     * Peripheral Interrupt Enabled
     * Oneshot Disabled
     * Continuous Enabled
     * Sync Disabled
     * Sync Source
     * Overflow Disabled
     * 16-bit Data Size
     * Channel Interrupt Enabled at Start */
    DMACH3ModeConfig(DMA_ADCDINT1, PERINT_ENABLE, ONESHOT_DISABLE, CONT_ENABLE,
                     SYNC_DISABLE, SYNC_SRC, OVRFLOW_DISABLE, SIXTEEN_BIT,
                     CHINT_END, CHINT_ENABLE);

    /* Start DMAs */
    StartDMACH3();

    PieCtrlRegs.PIEIER7.bit.INTx3 = 1; // Enable Group 7 Interrupt 3 - DMA3

}

void initDMA4(void) {

    /* DMA Channel 4 - ADCA CH23 - String 4 */
    DMACH4AddrConfig(&CircularBuffer4, &AdcaResultRegs.ADCRESULT1);

    /* TRANSFER_SIZE=256, SRC_T_STEP=0, DES_T_STEP=1 */
    DMACH4TransferConfig(DMA_BUFFER_SIZE - 1, 0, 1);

    /* DMA CH4 Mode Settings
     * Peripheral Interrupt Source - ADCA INT2
     * Peripheral Interrupt Enabled
     * Oneshot Disabled
     * Continuous Enabled
     * Sync Disabled
     * Sync Source
     * Overflow Disabled
     * 16-bit Data Size
     * Channel Interrupt Enabled at Start */
    DMACH4ModeConfig(DMA_ADCAINT2, PERINT_ENABLE, ONESHOT_DISABLE, CONT_ENABLE,
                     SYNC_DISABLE, SYNC_SRC, OVRFLOW_DISABLE, SIXTEEN_BIT,
                     CHINT_END, CHINT_ENABLE);

    /* Start DMAs */
    StartDMACH4();

    PieCtrlRegs.PIEIER7.bit.INTx4 = 1; // Enable Group 7 Interrupt 4 - DMA4

}

void initDMA5(void) {

    /* DMA Channel 5 - ADCB CH01 - String 5 */
    DMACH5AddrConfig(&CircularBuffer5, &AdcbResultRegs.ADCRESULT0);

    /* TRANSFER_SIZE=256, SRC_T_STEP=0, DES_T_STEP=1 */
    DMACH5TransferConfig(DMA_BUFFER_SIZE - 1, 0, 1);

    /* DMA CH5 Mode Settings
     * Peripheral Interrupt Source - ADCA INT1
     * Peripheral Interrupt Enabled
     * Oneshot Disabled
     * Continuous Enabled
     * Sync Disabled
     * Sync Source
     * Overflow Disabled
     * 16-bit Data Size
     * Channel Interrupt Enabled at Start */
    DMACH5ModeConfig(DMA_ADCBINT1, PERINT_ENABLE, ONESHOT_DISABLE, CONT_ENABLE,
                     SYNC_DISABLE, SYNC_SRC, OVRFLOW_DISABLE, SIXTEEN_BIT,
                     CHINT_END, CHINT_ENABLE);

    /* Start DMAs */
    StartDMACH5();

    PieCtrlRegs.PIEIER7.bit.INTx5 = 1; // Enable Group 7 Interrupt 5 - DMA5

}

void initDMA6(void) {

    /* DMA Channel 6 - ADCC CH23 - String 6 */
    DMACH6AddrConfig(&CircularBuffer6, &AdccResultRegs.ADCRESULT0);

    /* TRANSFER_SIZE=256, SRC_T_STEP=0, DES_T_STEP=1 */
    DMACH6TransferConfig(DMA_BUFFER_SIZE - 1, 0, 1);

    /* DMA CH6 Mode Settings
     * Peripheral Interrupt Source - ADCC INT2
     * Peripheral Interrupt Enabled
     * Oneshot Disabled
     * Continuous Enabled
     * Sync Disabled
     * Sync Source
     * Overflow Disabled
     * 16-bit Data Size
     * Channel Interrupt Enabled at Start */
    DMACH6ModeConfig(DMA_ADCCINT1, PERINT_ENABLE, ONESHOT_DISABLE, CONT_ENABLE,
                     SYNC_DISABLE, SYNC_SRC, OVRFLOW_DISABLE, SIXTEEN_BIT,
                     CHINT_END, CHINT_ENABLE);

    /* Start DMAs */
    StartDMACH6();

    PieCtrlRegs.PIEIER7.bit.INTx6 = 1; // Enable Group 7 Interrupt 6 - DMA6

}

/* ------------------------------------------------------------------------------ */

// End of File
