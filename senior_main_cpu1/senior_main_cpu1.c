/*
 * senior_main_cpu1.c
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
float32 freq_est2;
float32 freq_est4;
float32 freq_est6;

// CPU1 Phase Calculations
float32 phaseOld_2 = 0;
float32 phaseNew_2 = 0;
float32 phaseOld_4 = 0;
float32 phaseNew_4 = 0;
float32 phaseOld_6 = 0;
float32 phaseNew_6 = 0;

// CPU1 DMA Buffer Indices
volatile uint16_t x2;           // Circular Buffer 2 Index
volatile uint16_t x4;           // Circular Buffer 4 Index
volatile uint16_t x6;           // Circular Buffer 6 Index

// CPU1 DMA Done Flags
volatile bool_t done2 = 0;    // String 2 DMA Interrupt Done Flag
volatile bool_t done4 = 0;    // String 4 DMA Interrupt Done Flag
volatile bool_t done6 = 0;    // String 6 DMA Interrupt Done Flag

// Circular Buffers
//#pragma DATA_SECTION(CircularBuffer1, "CircBuff1");
#pragma DATA_SECTION(CircularBuffer2, "CircBuff2");
//#pragma DATA_SECTION(CircularBuffer3, "CircBuff3");
#pragma DATA_SECTION(CircularBuffer4, "CircBuff4");
//#pragma DATA_SECTION(CircularBuffer5, "CircBuff5");
#pragma DATA_SECTION(CircularBuffer6, "CircBuff6");
//uint16_t CircularBuffer1[CIRC_BUFF_SIZE];
volatile uint16_t CircularBuffer2[CIRC_BUFF_SIZE];
//uint16_t CircularBuffer3[CIRC_BUFF_SIZE];
volatile uint16_t CircularBuffer4[CIRC_BUFF_SIZE];
//uint16_t CircularBuffer5[CIRC_BUFF_SIZE];
volatile uint16_t CircularBuffer6[CIRC_BUFF_SIZE];

// External Reference to FFT Handler declared in FFT Source
extern RFFT_F32_STRUCT_Handle handler_rfft;

// Interrupts
__interrupt void DMACH2_ISR(void); // Because DMA ISRs are in the same group, the lowest
__interrupt void DMACH4_ISR(void); // number has priority
__interrupt void DMACH6_ISR(void);
__interrupt void ADCCH2_ISR(void);
__interrupt void ADCCH4_ISR(void);
__interrupt void ADCCH6_ISR(void);

// Functions
void initMain(void);

// Main Routine
int main(void) {

    initMain();

    while(1) {

        if (done2) { // String 2
            // Fill FFT Input Buffer with new values
            // (Can't just change pointer because mem alignment/circular buffer)
            for (int i = 0; i < RFFT_SIZE; i++) {
                handler_rfft->InBuf[i] = (float32) ((int16_t) (CircularBuffer2[(x2 + i) & CIRC_MASK] - (INT16_MAX)));
            }

            // Pass in phases by reference
            freq_est2 = vocodeAnalysis(&phaseOld_2, &phaseNew_2);
            done2 = 0;
        }
        if (done4) { // String 4
            // Fill FFT Input Buffer with new values
            // (Can't just change pointer because mem alignment/circular buffer)
            for (int i = 0; i < RFFT_SIZE; i++) {
                handler_rfft->InBuf[i] = (float32) ((int16_t) (CircularBuffer4[(x4 + i) & CIRC_MASK] - (INT16_MAX)));
            }

            // Pass in phases by reference
            freq_est4 = vocodeAnalysis(&phaseOld_4, &phaseNew_4);
            done4 = 0;
        }
        if (done6) { // String 6
            // Fill FFT Input Buffer with new values
            // (Can't just change pointer because mem alignment/circular buffer)
            for (int i = 0; i < RFFT_SIZE; i++) {
                handler_rfft->InBuf[i] = (float32) ((int16_t) (CircularBuffer6[(x6 + i) & CIRC_MASK] - (INT16_MAX)));
            }

            // Pass in phases by reference
            freq_est6 = vocodeAnalysis(&phaseOld_6, &phaseNew_6);
            done6 = 0;
        }

    }

    ESTOP0;

}

#pragma CODE_SECTION(DMACH2_ISR, ".TI.ramfunc");
__interrupt void DMACH2_ISR(void) {

    // Move DMA Buffer Pointer
    x2 = (x2 + DMA_BUFFER_SIZE) & CIRC_MASK;
    DMACH2AddrConfig(&CircularBuffer2[x2], &AdcaResultRegs.ADCRESULT0);

    // Acknowledge Interrupt
    done2 = 1;                              // Set Done2 Flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7; // Clear Interrupt Flag

}

#pragma CODE_SECTION(DMACH4_ISR, ".TI.ramfunc");
__interrupt void DMACH4_ISR(void) {

    // Move DMA Buffer Pointer
    x4 = (x4 + DMA_BUFFER_SIZE) & CIRC_MASK;
    DMACH4AddrConfig(&CircularBuffer4[x4], &AdcaResultRegs.ADCRESULT4);

    // Acknowledge Interrupt
    done4 = 1;                              // Set Done4 Flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7; // Clear Interrupt Flag

}

#pragma CODE_SECTION(DMACH6_ISR, ".TI.ramfunc");
__interrupt void DMACH6_ISR(void) {

    // Move DMA Buffer Pointer
    x6 = (x6 + DMA_BUFFER_SIZE) & CIRC_MASK;
    DMACH6AddrConfig(&CircularBuffer6[x6], &AdccResultRegs.ADCRESULT2);

    // Acknowledge Interrupt
    done6 = 1;                              // Set Done6 Flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7; // Clear Interrupt Flag

}

#pragma CODE_SECTION(ADCCH2_ISR, ".TI.ramfunc");
__interrupt void ADCCH2_ISR(void) {

    // Acknowledge Interrupt Triggered by ePWM1
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; // clear ADCA01 INT1 flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

#pragma CODE_SECTION(ADCCH4_ISR, ".TI.ramfunc");
__interrupt void ADCCH4_ISR(void) {

    // Acknowledge Interrupt Triggered by ePWM2
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT2 = 1; // Clear ADCA45 INT2 flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

}

#pragma CODE_SECTION(ADCCH6_ISR, ".TI.ramfunc");
__interrupt void ADCCH6_ISR(void) {

    // Acknowledge Interrupt Triggered by ePWM3
    AdccRegs.ADCINTFLGCLR.bit.ADCINT2 = 1; // Clear ADCC23 INT2 flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

}

void initMain(void) {

    // Initialize System Control
    InitSysCtrl();

    // Initialize GPIO
    InitGpio();

    // Initialize PIE Control Registers
    InitPieCtrl();

    // Clear Interrupts, Disable CPU __interrupts and clear CPU __interrupt flags
    DINT;
    IER = 0x0000;
    IFR = 0x0000;

    // Initialize PIE Vector Tables with pointers to shell ISRs
    InitPieVectTable();

    // Connect ISRs to DMA Channel Interrupts
    EALLOW;
    PieVectTable.DMA_CH2_INT = &DMACH2_ISR;
    PieVectTable.DMA_CH4_INT = &DMACH4_ISR;
    PieVectTable.DMA_CH6_INT = &DMACH6_ISR;
    PieVectTable.ADCA1_INT = &ADCCH2_ISR;
    PieVectTable.ADCA2_INT = &ADCCH4_ISR;
    PieVectTable.ADCC2_INT = &ADCCH6_ISR;
    EDIS;

    // Initialize ADCs and DMA
    initADC();
    initDMA();
    initEPWM();
    initFFT(handler_rfft);

    // Enable global Interrupts and higher priority real-time debug events
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global real-time interrupt DBGM

}

