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
uint16_t adcCResult1; // C2, C3 - String 6 - SOCC 1
uint16_t adcBResult0; // B0, B1 - String 5 - SOCB 0
uint16_t adcAResult1; // A2, A3 - String 4 - SOCA 1
uint16_t adcDResult0; // D0, D1 - String 3 - SOCD 0
uint16_t adcAResult0; // A0, A1 - String 2 - SOCA 0
uint16_t adcDResult1; // D2, D3 - String 1 - SOCD 1

#pragma DATA_SECTION(CircularBuffer1, "CircBuff1");
#pragma DATA_SECTION(CircularBuffer2, "CircBuff2");
#pragma DATA_SECTION(CircularBuffer3, "CircBuff3");
//#pragma DATA_SECTION(CircularBuffer4, "CircBuff4");
//#pragma DATA_SECTION(CircularBuffer5, "CircBuff5");
//#pragma DATA_SECTION(CircularBuffer6, "CircBuff6");
uint16_t CircularBuffer1[CIRC_BUFF_SIZE];
uint16_t CircularBuffer2[CIRC_BUFF_SIZE];
uint16_t CircularBuffer3[CIRC_BUFF_SIZE];
//uint16_t CircularBuffer4[CIRC_BUFF_SIZE];
//uint16_t CircularBuffer5[CIRC_BUFF_SIZE];
//uint16_t CircularBuffer6[CIRC_BUFF_SIZE];
volatile uint16_t x;
volatile uint16_t done2 = 0;

float32 freq_est1;
float32 freq_est2;
float32 freq_est3;
float32 freq_est4;
float32 freq_est5;
float32 freq_est6;

// External Reference to FFT Handler declared in FFT Source
extern RFFT_F32_STRUCT_Handle handler_rfft;

float32 phaseOld_2 = 0;
float32 phaseNew_2 = 0;

// Interrupts
__interrupt void DMACH2_ISR(void);

// Functions
void initMain(void);

// Main Routine
int main(void) {

    initMain();

    while(1) {
        __asm(" NOP");
        if (done2) {
            // Refill FFT Input Buffer with new values
            // (Can't just change pointer because mem alignment/circular buffer)
            for(int i = 0; i < RFFT_SIZE; i++) {
                handler_rfft->InBuf[i] = (float32) ((int16_t) (CircularBuffer2[(x + i) & CIRC_MASK] - INT16_MAX));
            }
            // Pass in Phases by reference?
            freq_est2 = vocodeAnalysis(&phaseNew_2, &phaseOld_2);
            done2 = 0;
        }
    }

    ESTOP0;
}

#pragma CODE_SECTION(DMACH2_ISR, ".TI.ramfunc");
__interrupt void DMACH2_ISR(void) {

    // Move DMA Buffer Pointer
    x = (x + DMA_BUFFER_SIZE) & CIRC_MASK;
    DMACH2AddrConfig(&CircularBuffer2[x], &AdcaResultRegs.ADCRESULT0);

    // Acknowledge Interrupt
    done2 = 1;
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
    PieVectTable.DMA_CH2_INT = &DMACH2_ISR;
    EDIS;

    // Initialize ADCs and DMA
    initADC();
    initDMA(CircularBuffer2);
    initEPWM();
    initFFT(handler_rfft);

    // Enable global Interrupts and higher priority real-time debug events
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM
}

