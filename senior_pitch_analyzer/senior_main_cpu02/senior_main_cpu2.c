/*
 * senior_main_cpu2.c
 *
 *  Created on: Oct 1, 2018
 *      Author: meser
 */

// Includes
#include "F28x_Project.h"
#include "F28379D_Senior_Design.h"

// Defines

// Global Variables

// CPU1 Frequency Estimations
float32 freq_est1;
float32 freq_est3;
float32 freq_est5;

#pragma DATA_SECTION(freq_est_cpu2, "FECPU2");
volatile float32 freq_est_cpu2[7];

// CPU1 Phase Calculations
volatile float32 phaseOld_1 = 0;
volatile float32 phaseNew_1 = 0;
volatile float32 phaseOld_3 = 0;
volatile float32 phaseNew_3 = 0;
volatile float32 phaseOld_5 = 0;
volatile float32 phaseNew_5 = 0;

// CPU1 DMA Buffer Indices
volatile uint16_t x1;         // Circular Buffer 1 Index
volatile uint16_t x3;         // Circular Buffer 3 Index
volatile uint16_t x5;         // Circular Buffer 5 Index

// CPU1 DMA Done Flags
volatile bool_t done1 = 0;    // String 1 DMA Interrupt Done Flag
volatile bool_t done3 = 0;    // String 3 DMA Interrupt Done Flag
volatile bool_t done5 = 0;    // String 5 DMA Interrupt Done Flag

// Circular Buffers
#pragma DATA_SECTION(CircularBuffer1, "CircBuff1");
//#pragma DATA_SECTION(CircularBuffer2, "CircBuff2");
#pragma DATA_SECTION(CircularBuffer3, "CircBuff3");
//#pragma DATA_SECTION(CircularBuffer4, "CircBuff4");
#pragma DATA_SECTION(CircularBuffer5, "CircBuff5");
//#pragma DATA_SECTION(CircularBuffer6, "CircBuff6");
volatile uint16_t CircularBuffer1[CIRC_BUFF_SIZE];
//volatile uint16_t CircularBuffer2[CIRC_BUFF_SIZE];
volatile uint16_t CircularBuffer3[CIRC_BUFF_SIZE];
//volatile uint16_t CircularBuffer4[CIRC_BUFF_SIZE];
volatile uint16_t CircularBuffer5[CIRC_BUFF_SIZE];
//volatile uint16_t CircularBuffer6[CIRC_BUFF_SIZE];

// External Reference to FFT Handler declared in FFT Source
extern RFFT_F32_STRUCT_Handle handler_rfft2;

// Interrupts
__interrupt void DMACH1_ISR(void); // Because DMA ISRs are in the same group, the lowest
__interrupt void DMACH3_ISR(void); // number has priority
__interrupt void DMACH5_ISR(void);
__interrupt void ADCCH1_ISR(void);
__interrupt void ADCCH3_ISR(void);
__interrupt void ADCCH5_ISR(void);

// Functions
void initMain(void);

// Main Routine
int main(void) {

    initMain();

    while(1) {
        // Sync CPUs across flag 0
        IpcSync(0);

        if (done1) { // String 1
            // Fill FFT Input Buffer with new values
            // (Can't just change pointer because mem alignment/circular buffer)
            for (int i = 0; i < RFFT_SIZE; i++) {
                handler_rfft2->InBuf[i] = (float32) ((int16_t) (CircularBuffer1[(x1 + i) & CIRC_MASK] - (INT16_MAX)));
            }

            // Pass in phases by reference
//            freq_est1 = vocodeAnalysis(&phaseOld_1, &phaseNew_1, handler_rfft2);
            freq_est_cpu2[1] = vocodeAnalysis(&phaseOld_1, &phaseNew_1, handler_rfft2);
            done1 = 0;
        }
        if (done3) { // String 3
            // Fill FFT Input Buffer with new values
            // (Can't just change pointer because mem alignment/circular buffer)
            for (int i = 0; i < RFFT_SIZE; i++) {
                handler_rfft2->InBuf[i] = (float32) ((int16_t) (CircularBuffer3[(x3 + i) & CIRC_MASK] - (INT16_MAX)));
            }

            // Pass in phases by reference
//            freq_est3 = vocodeAnalysis(&phaseOld_3, &phaseNew_3, handler_rfft2);
            freq_est_cpu2[3] = vocodeAnalysis(&phaseOld_3, &phaseNew_3, handler_rfft2);
            done3 = 0;
        }
        if (done5) { // String 5
            // Fill FFT Input Buffer with new values
            // (Can't just change pointer because mem alignment/circular buffer)
            for (int i = 0; i < RFFT_SIZE; i++) {
                handler_rfft2->InBuf[i] = (float32) ((int16_t) (CircularBuffer5[(x5 + i) & CIRC_MASK] - (INT16_MAX)));
            }

            // Pass in phases by reference
//            freq_est5 = vocodeAnalysis(&phaseOld_5, &phaseNew_5, handler_rfft2);
            freq_est_cpu2[5] = vocodeAnalysis(&phaseOld_5, &phaseNew_5, handler_rfft2);
            done5 = 0;
        }

    }

    ESTOP0;
    return FAIL;
}

#pragma CODE_SECTION(DMACH1_ISR, ".TI.ramfunc");
__interrupt void DMACH1_ISR(void) {

    // Move DMA Buffer Pointer
    x1 = (x1 + DMA_BUFFER_SIZE) & CIRC_MASK;
    DMACH1AddrConfig(&CircularBuffer1[x1], &AdcdResultRegs.ADCRESULT1);

    // Acknowledge Interrupt
    done1 = 1;                              // Set Done2 Flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7; // Clear Interrupt Flag

}

#pragma CODE_SECTION(DMACH3_ISR, ".TI.ramfunc");
__interrupt void DMACH3_ISR(void) {

    // Move DMA Buffer Pointer
    x3 = (x3 + DMA_BUFFER_SIZE) & CIRC_MASK;
    DMACH3AddrConfig(&CircularBuffer3[x3], &AdcdResultRegs.ADCRESULT0);

    // Acknowledge Interrupt
    done3 = 1;                              // Set Done4 Flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7; // Clear Interrupt Flag

}

#pragma CODE_SECTION(DMACH5_ISR, ".TI.ramfunc");
__interrupt void DMACH5_ISR(void) {

    // Move DMA Buffer Pointer
    x5 = (x5 + DMA_BUFFER_SIZE) & CIRC_MASK;
    DMACH5AddrConfig(&CircularBuffer5[x5], &AdcbResultRegs.ADCRESULT0);

    // Acknowledge Interrupt
    done5 = 1;                              // Set Done6 Flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7; // Clear Interrupt Flag

}

#pragma CODE_SECTION(ADCCH1_ISR, ".TI.ramfunc");
__interrupt void ADCCH1_ISR(void) {

    // Acknowledge Interrupt Triggered by ePWM4 SOCB
    AdcdRegs.ADCINTFLGCLR.bit.ADCINT2 = 1; // clear ADCD INT2 flag for channels 23
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
}

#pragma CODE_SECTION(ADCCH3_ISR, ".TI.ramfunc");
__interrupt void ADCCH3_ISR(void) {

    // Acknowledge Interrupt Triggered by ePWM4 SOCA
    AdcdRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; // Clear ADCD INT1 flag for channels 01
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

}

#pragma CODE_SECTION(ADCCH5_ISR, ".TI.ramfunc");
__interrupt void ADCCH5_ISR(void) {

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

    // Initialize ADCs and DMA
    initADC();
    initDMA();
    initDMAx(&CircularBuffer1[0], &AdcdResultRegs.ADCRESULT1, DMA_ADCDINT2, 1);
    initDMAx(&CircularBuffer3[0], &AdcdResultRegs.ADCRESULT0, DMA_ADCDINT1, 3);
    initDMAx(&CircularBuffer5[0], &AdcbResultRegs.ADCRESULT0, DMA_ADCBINT1, 5);
    initEPWM();
    initFFT(handler_rfft2);

    // Enable global Interrupts and higher priority real-time debug events
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global real-time interrupt DBGM
}

