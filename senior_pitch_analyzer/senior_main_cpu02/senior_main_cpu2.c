/*
 * senior_main_cpu2.c
 *
 *  Created on: Oct 1, 2018
 *      Author: meser
 */

// Includes
#include "F28x_Project.h"
#include "F28379D_Senior_Design.h"

// Mode Select
extern uint16_t mode;

// Fixed Frequency Array
extern float32 fn[7];

// Frequency Estimation Buffers
extern float32 fo_est_cpu2[7];
extern float32 fo_n_cpu2[7];

// Declare String Structs
extern STRING_DATA string1;
extern STRING_DATA string3;
extern STRING_DATA string5;

// CPU2 External Reference to FFT Handler declared in FFT Source
extern RFFT_F32_STRUCT_Handle handler_rfft2;

// CPU2 Interrupts
#pragma CODE_SECTION(DMACH1_ISR, ".TI.ramfunc");
interrupt void DMACH1_ISR(void); // Because DMA ISRs are in the same group, the lowest
#pragma CODE_SECTION(DMACH3_ISR, ".TI.ramfunc");
interrupt void DMACH3_ISR(void); // number has priority
#pragma CODE_SECTION(DMACH5_ISR, ".TI.ramfunc");
interrupt void DMACH5_ISR(void);
#pragma CODE_SECTION(ADCCH1_ISR, ".TI.ramfunc");
interrupt void ADCCH1_ISR(void);
#pragma CODE_SECTION(ADCCH3_ISR, ".TI.ramfunc");
interrupt void ADCCH3_ISR(void);
#pragma CODE_SECTION(ADCCH5_ISR, ".TI.ramfunc");
interrupt void ADCCH5_ISR(void);

// Functions
void initMain(void);

// Main Routine
int main(void) {

    initMain();

    while(1) {
        // Sync CPUs across IPC Flag 0
        IpcSync(0);
        uint16_t x = 0;

        if (mode == MIRROR_MODE) {
            if (string1.done) { // String 1
                // Fill FFT Input Buffer with new values
                for (int i = 0; i < RFFT_SIZE; i++) {
                    x = string1.cBuff[(string1.xDMA + i) & CIRC_MASK];
                    handler_rfft2->InBuf[i] = (float32) ((int16_t) (x - (INT16_MAX)));
                }

                // Pass in string struct and FFT handler by reference
                vocodeAnalysis(&string1, handler_rfft2);
                string1.done = 0;

                // Send fret estimate to CPU1
                fo_n_cpu2[1] = string1.n_est;
            }
            if (string3.done) { // String 3
                // Fill FFT Input Buffer with new values
                for (int i = 0; i < RFFT_SIZE; i++) {
                    x = string3.cBuff[(string3.xDMA + i) & CIRC_MASK];
                    handler_rfft2->InBuf[i] = (float32) ((int16_t) (x - (INT16_MAX)));
                }

                // Pass in string struct and FFT handler by reference
                vocodeAnalysis(&string3, handler_rfft2);
                string3.done = 0;

                // Send fret estimate to CPU1
                fo_n_cpu2[3] = string3.n_est;
            }
            if (string5.done) { // String 5
                // Fill FFT Input Buffer with new values
                for (int i = 0; i < RFFT_SIZE; i++) {
                    x = string5.cBuff[(string5.xDMA + i) & CIRC_MASK];
                    handler_rfft2->InBuf[i] = (float32) ((int16_t) (x - (INT16_MAX)));
                }

                // Pass in string struct and FFT handler by reference
                vocodeAnalysis(&string5, handler_rfft2);
                string5.done = 0;

                // Send fret estimate to CPU1
                fo_n_cpu2[5] = string5.n_est;
            }

        }

    }

}

interrupt void DMACH1_ISR(void) {

    // Move DMA Buffer Pointer
    string1.xDMA = (string1.xDMA + DMA_BUFFER_SIZE) & CIRC_MASK;
    DMACH1AddrConfig(&string1.cBuff[string1.xDMA], &AdcdResultRegs.ADCRESULT1);

    // Acknowledge Interrupt
    string1.done = 1;                       // Set String 1 Done Flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7; // Clear Interrupt Flag

}

interrupt void DMACH3_ISR(void) {

    // Move DMA Buffer Pointer
    string3.xDMA = (string3.xDMA + DMA_BUFFER_SIZE) & CIRC_MASK;
    DMACH3AddrConfig(&string3.cBuff[string3.xDMA], &AdcdResultRegs.ADCRESULT0);

    // Acknowledge Interrupt
    string3.done = 1;                       // Set String 3 Done Flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7; // Clear Interrupt Flag

}

interrupt void DMACH5_ISR(void) {

    // Move DMA Buffer Pointer
    string5.xDMA = (string5.xDMA + DMA_BUFFER_SIZE) & CIRC_MASK;
    DMACH5AddrConfig(&string5.cBuff[string5.xDMA], &AdcbResultRegs.ADCRESULT0);

    // Acknowledge Interrupt
    string5.done = 1;                       // Set String 5 Done Flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7; // Clear Interrupt Flag

}

interrupt void ADCCH1_ISR(void) {

    // Acknowledge Interrupt Triggered by ePWM4 SOCB
    AdcdRegs.ADCINTFLGCLR.bit.ADCINT2 = 1; // clear ADCD INT2 flag for channels 23
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
}

interrupt void ADCCH3_ISR(void) {

    // Acknowledge Interrupt Triggered by ePWM4 SOCA
    AdcdRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; // Clear ADCD INT1 flag for channels 01
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

}

interrupt void ADCCH5_ISR(void) {

    // Acknowledge Interrupt Triggered by ePWM3 SOCA
    AdcbRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; // Clear ADCB INT1 flag for channels 01
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

}

void initMain(void) {

    // Initialize System Control
    InitSysCtrl();

    // Initialize GPIO - Disabled for CPU2
//    InitGpio();

    // Initialize PIE Control Registers
    InitPieCtrl();

    // Clear Interrupts, Disable CPU __interrupts and clear CPU __interrupt flags
    DINT;
    IER = 0x0000;
    IFR = 0x0000;

    // Initialize PIE Vector Tables with pointers to shell ISRs
    InitPieVectTable();

    // Connect ISRs to Main Defined Interrupts
    EALLOW;
    PieVectTable.DMA_CH1_INT = &DMACH1_ISR;
    PieVectTable.DMA_CH3_INT = &DMACH3_ISR;
    PieVectTable.DMA_CH5_INT = &DMACH5_ISR;
    PieVectTable.ADCD2_INT = &ADCCH1_ISR;
    PieVectTable.ADCD1_INT = &ADCCH3_ISR;
    PieVectTable.ADCB1_INT = &ADCCH5_ISR;
    EDIS;

    // Initialize Peripherals and FFT Handler
    initEPWM();
    initADC();
    initDMA();
    initDMAx(&string1.cBuff[0], &AdcdResultRegs.ADCRESULT1, DMA_ADCDINT2, 1);
    initDMAx(&string3.cBuff[0], &AdcdResultRegs.ADCRESULT0, DMA_ADCDINT1, 3);
    initDMAx(&string5.cBuff[0], &AdcbResultRegs.ADCRESULT0, DMA_ADCBINT1, 5);
    initFFT(handler_rfft2);

    // Enable global Interrupts and higher priority real-time debug events
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global real-time interrupt DBGM
}




