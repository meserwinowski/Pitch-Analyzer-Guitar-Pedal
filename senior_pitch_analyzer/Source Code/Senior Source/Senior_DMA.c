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

#ifdef CPU1
    extern volatile uint16_t CircularBuffer2;
    extern volatile uint16_t CircularBuffer4;
    extern volatile uint16_t CircularBuffer6;
#endif

#ifdef CPU2
    extern volatile uint16_t CircularBuffer1;
    extern volatile uint16_t CircularBuffer3;
    extern volatile uint16_t CircularBuffer5;
#endif

/*** Direct Memory Access Functions ***/

void initDMA(void) {
    /* Initialize DMA to a known state - Hard Reset,
       DMA unaffected by emulation halt, and CH1 Priority
       disabled */
    DMAInitialize();

#ifdef CPU1
    /* Setup DMA Channels for 3 ADCs on CPU1 */
//    initDMA2(); // Initialize DMA2
//    initDMA4(); // Initialize DMA4
//    initDMA6(); // Initialize DMA6
#endif

#ifdef CPU2
    /* Setup DMA Channels for 3 ADCs on CPU2 */
//    initDMA1(); // Initialize DMA1
//    initDMA3(); // Initialize DMA3
//    initDMA5(); // Initialize DMA5
#endif

    // Enable Group 7 Interrupts
    IER |= M_INT7;
}

/*** Initialize DMA CHx ***/
/* CB - Pointer to Circular Buffer
 * ADCRR - Pointer to ADC Result Register
 * ADCINT - Define for what ADC Interrupt to trigger DMA
 * dma - DMA Channel Selector
 */
void initDMAx(volatile uint16_t * CB, volatile uint16_t * ADCRR, uint16_t ADCINT, uint16_t dma) {
    switch(dma) {
        case 1:
            /* DMA Channel 1 */
            DMACH1AddrConfig(CB, ADCRR);

            /* TRANSFER_SIZE=256, SRC_T_STEP=0, DES_T_STEP=1 */
            DMACH1TransferConfig(DMA_BUFFER_SIZE - 1, 0, 1);

            /* DMA CH1 Mode Settings
             * Peripheral Interrupt Source
             * Peripheral Interrupt Enabled
             * Oneshot Disabled
             * Continuous Enabled
             * Sync Disabled
             * Sync Source
             * Overflow Disabled
             * 16-bit Data Size
             * Channel Interrupt Enabled at Start */
            DMACH1ModeConfig(ADCINT, PERINT_ENABLE, ONESHOT_DISABLE, CONT_ENABLE,
                             SYNC_DISABLE, SYNC_SRC, OVRFLOW_DISABLE, SIXTEEN_BIT,
                             CHINT_END, CHINT_ENABLE);

            /* Start DMAs */
            StartDMACH1();

            PieCtrlRegs.PIEIER7.bit.INTx1 = 1; // Enable Group 7 Interrupt 1 - DMA1
            break;

        case 2:
            /* DMA Channel 2 */
            DMACH2AddrConfig(CB, ADCRR);

            /* TRANSFER_SIZE=256, SRC_T_STEP=0, DES_T_STEP=1 */
            DMACH2TransferConfig(DMA_BUFFER_SIZE - 1, 0, 1);

            /* DMA CH2 Mode Settings
             * Peripheral Interrupt Source
             * Peripheral Interrupt Enabled
             * Oneshot Disabled
             * Continuous Enabled
             * Sync Disabled
             * Sync Source
             * Overflow Disabled
             * 16-bit Data Size
             * Channel Interrupt Enabled at Start */
            DMACH2ModeConfig(ADCINT,
                             PERINT_ENABLE, ONESHOT_DISABLE, CONT_ENABLE,
                             SYNC_DISABLE, SYNC_SRC, OVRFLOW_DISABLE, SIXTEEN_BIT,
                             CHINT_END, CHINT_ENABLE);

            /* Start DMAs */
            StartDMACH2();

            PieCtrlRegs.PIEIER7.bit.INTx2 = 1; // Enable Group 7 Interrupt 2 - DMA2
            break;

        case 3:
            /* DMA Channel 3 */
            DMACH3AddrConfig(CB, ADCRR);

            /* TRANSFER_SIZE=256, SRC_T_STEP=0, DES_T_STEP=1 */
            DMACH3TransferConfig(DMA_BUFFER_SIZE - 1, 0, 1);

            /* DMA CH3 Mode Settings
             * Peripheral Interrupt Source
             * Peripheral Interrupt Enabled
             * Oneshot Disabled
             * Continuous Enabled
             * Sync Disabled
             * Sync Source
             * Overflow Disabled
             * 16-bit Data Size
             * Channel Interrupt Enabled at Start */
            DMACH3ModeConfig(ADCINT,
                             PERINT_ENABLE, ONESHOT_DISABLE, CONT_ENABLE,
                             SYNC_DISABLE, SYNC_SRC, OVRFLOW_DISABLE, SIXTEEN_BIT,
                             CHINT_END, CHINT_ENABLE);

            /* Start DMAs */
            StartDMACH3();

            PieCtrlRegs.PIEIER7.bit.INTx3 = 1; // Enable Group 7 Interrupt 3 - DMA3
            break;

        case 4:
            /* DMA Channel 4 */
            DMACH4AddrConfig(CB, ADCRR);

            /* TRANSFER_SIZE=256, SRC_T_STEP=0, DES_T_STEP=1 */
            DMACH4TransferConfig(DMA_BUFFER_SIZE - 1, 0, 1);

            /* DMA CH4 Mode Settings
             * Peripheral Interrupt Source
             * Peripheral Interrupt Enabled
             * Oneshot Disabled
             * Continuous Enabled
             * Sync Disabled
             * Sync Source
             * Overflow Disabled
             * 16-bit Data Size
             * Channel Interrupt Enabled at Start */
            DMACH4ModeConfig(ADCINT,
                             PERINT_ENABLE, ONESHOT_DISABLE, CONT_ENABLE,
                             SYNC_DISABLE, SYNC_SRC, OVRFLOW_DISABLE, SIXTEEN_BIT,
                             CHINT_END, CHINT_ENABLE);

            /* Start DMAs */
            StartDMACH4();

            PieCtrlRegs.PIEIER7.bit.INTx4 = 1; // Enable Group 7 Interrupt 4 - DMA4
            break;

        case 5:
            /* DMA Channel 5 - ADCB CH01 - String 5 */
            DMACH5AddrConfig(CB, ADCRR);

            /* TRANSFER_SIZE=256, SRC_T_STEP=0, DES_T_STEP=1 */
            DMACH5TransferConfig(DMA_BUFFER_SIZE - 1, 0, 1);

            /* DMA CH5 Mode Settings
             * Peripheral Interrupt Source
             * Peripheral Interrupt Enabled
             * Oneshot Disabled
             * Continuous Enabled
             * Sync Disabled
             * Sync Source
             * Overflow Disabled
             * 16-bit Data Size
             * Channel Interrupt Enabled at Start */
            DMACH5ModeConfig(ADCINT,
                             PERINT_ENABLE, ONESHOT_DISABLE, CONT_ENABLE,
                             SYNC_DISABLE, SYNC_SRC, OVRFLOW_DISABLE, SIXTEEN_BIT,
                             CHINT_END, CHINT_ENABLE);

            /* Start DMAs */
            StartDMACH5();

            PieCtrlRegs.PIEIER7.bit.INTx5 = 1; // Enable Group 7 Interrupt 5 - DMA5
            break;

        case 6:
            /* DMA Channel 6 */
            DMACH6AddrConfig(CB, ADCRR);

            /* TRANSFER_SIZE=256, SRC_T_STEP=0, DES_T_STEP=1 */
            DMACH6TransferConfig(DMA_BUFFER_SIZE - 1, 0, 1);

            /* DMA CH6 Mode Settings
             * Peripheral Interrupt Source
             * Peripheral Interrupt Enabled
             * Oneshot Disabled
             * Continuous Enabled
             * Sync Disabled
             * Sync Source
             * Overflow Disabled
             * 16-bit Data Size
             * Channel Interrupt Enabled at Start */
            DMACH6ModeConfig(ADCINT,
                             PERINT_ENABLE, ONESHOT_DISABLE, CONT_ENABLE,
                             SYNC_DISABLE, SYNC_SRC, OVRFLOW_DISABLE, SIXTEEN_BIT,
                             CHINT_END, CHINT_ENABLE);

            /* Start DMAs */
            StartDMACH6();

            PieCtrlRegs.PIEIER7.bit.INTx6 = 1; // Enable Group 7 Interrupt 6 - DMA6
            break;
    }
}


/* ------------------------------------------------------------------------------ */

// End of File
