/*
 * senior_main_cpu1.c
 *
 *  Created on: Oct 1, 2018
 *      Author: meser
 */

// Includes
#include "F28x_Project.h"
#include "F28379D_Senior_Design.h"
//#include "math.h"

// Defines

// Global Variables
uint16_t adcAResult0; // String 6 - SOCA 0
uint16_t adcAResult1; // String 5 - SOCA 1
uint16_t adcBResult0; // String 4 - SOCB 0
uint16_t adcBResult1; // String 3 - SOCB 1
uint16_t adcCResult0; // String 2 - SOCC 0
uint16_t adcDResult0; // String 1 - SOCD 0

//#pragma DATA_SECTION(DMACH1_ADCA01, "DMABuffer1");
#pragma DATA_SECTION(CircularBuffer1, "CircBuff1");
#pragma DATA_SECTION(CircularBuffer2, "CircBuff2");
#pragma DATA_SECTION(CircularBuffer3, "CircBuff3");
uint16_t CircularBuffer1[CIRC_BUFF_SIZE];
float32 CircularBuffer2[CIRC_BUFF_SIZE];
float32 CircularBuffer3[CIRC_BUFF_SIZE];
uint16_t DMACH1_ADCA01[DMA_BUFFER_SIZE];
volatile uint16_t x;
volatile uint16_t done1 = 0;
float32 freq_est;

// External Reference to FFT Handler declared in FFT Source
extern RFFT_F32_STRUCT_Handle handler_rfft;

float32 phaseOld_1 = 0;
float32 phaseNew_1 = 0;

// Interrupts
__interrupt void DMACH1_ISR(void);

// Functions
void initMain(void);
//float32 vocodeAnalysis(void);

// Main Routine
int main(void) {

    initMain();

    while(1) {
        __asm(" NOP");
        if (done1) {
            // Refill FFT Input Buffer with new values
            // (Can't just change pointer because mem alignment/circular buffer)
            for(int i = 0; i < RFFT_SIZE; i++) {
                handler_rfft->InBuf[i] = (float32)((int16_t) CircularBuffer1[(x + i) & CIRC_MASK]);
            }
            // Pass in Phases by reference?
            freq_est = vocodeAnalysis(&phaseNew_1, &phaseOld_1);
            done = 0;
        }
    }

    ESTOP0;
}

#pragma CODE_SECTION(DMACH1_ISR, ".TI.ramfunc");
__interrupt void DMACH1_ISR(void) {

    // Move DMA Buffer Pointer
    x = (x + DMA_BUFFER_SIZE) & CIRC_MASK;
    DMACH1AddrConfig(&CircularBuffer1[x], &AdcaResultRegs.ADCRESULT0);

    // Acknowledge Interrupt
    done1 = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;
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
    PieVectTable.DMA_CH1_INT = &DMACH1_ISR;
    EDIS;

    // Initialize ADCs and DMA
    initADC();
    initDMA(CircularBuffer1);
    initEPWM();
    initFFT(handler_rfft);

    // Enable global Interrupts and higher priority real-time debug events
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM
}

