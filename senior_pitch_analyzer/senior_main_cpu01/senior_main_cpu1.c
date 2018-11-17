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

volatile float32 freq_est_cpu1[7];

// CPU1 Phase Calculations
volatile float32 phaseOld_2 = 0;
volatile float32 phaseNew_2 = 0;
volatile float32 phaseOld_4 = 0;
volatile float32 phaseNew_4 = 0;
volatile float32 phaseOld_6 = 0;
volatile float32 phaseNew_6 = 0;

// CPU1 DMA Buffer Indices
volatile uint16_t x2;         // Circular Buffer 2 Index
volatile uint16_t x4;         // Circular Buffer 4 Index
volatile uint16_t x6;         // Circular Buffer 6 Index

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
//volatile uint16_t CircularBuffer1[CIRC_BUFF_SIZE];
volatile uint16_t CircularBuffer2[CIRC_BUFF_SIZE];
//volatile uint16_t CircularBuffer3[CIRC_BUFF_SIZE];
volatile uint16_t CircularBuffer4[CIRC_BUFF_SIZE];
//volatile uint16_t CircularBuffer5[CIRC_BUFF_SIZE];
volatile uint16_t CircularBuffer6[CIRC_BUFF_SIZE];

// External Reference to FFT Handler declared in FFT Source
extern RFFT_F32_STRUCT_Handle handler_rfft1;

// Interrupts
__interrupt void DMACH2_ISR(void); // Because DMA ISRs are in the same group, the lowest
__interrupt void DMACH4_ISR(void); // number has priority
__interrupt void DMACH6_ISR(void);
__interrupt void ADCCH2_ISR(void);
__interrupt void ADCCH4_ISR(void);
__interrupt void ADCCH6_ISR(void);
__interrupt void EPWM_5_ISR(void);

// Functions
void initMain(void);
void initCPU2(void);

// Main Routine
int main(void) {

    initMain();

    while(1) {
        // Sync CPUs across flag 0
        IpcSync(0);

        if (done2) { // String 2
            // Fill FFT Input Buffer with new values
            // (Can't just change pointer because mem alignment/circular buffer)
            for (int i = 0; i < RFFT_SIZE; i++) {
                handler_rfft1->InBuf[i] = (float32) ((int16_t) (CircularBuffer2[(x2 + i) & CIRC_MASK] - (INT16_MAX)));
            }

            // Pass in phases by reference
//            freq_est2 = vocodeAnalysis(&phaseOld_2, &phaseNew_2, handler_rfft1);
            freq_est_cpu1[2] = vocodeAnalysis(&phaseOld_2, &phaseNew_2, handler_rfft1);
            done2 = 0;
        }
        if (done4) { // String 4
            // Fill FFT Input Buffer with new values
            // (Can't just change pointer because mem alignment/circular buffer)
            for (int i = 0; i < RFFT_SIZE; i++) {
                handler_rfft1->InBuf[i] = (float32) ((int16_t) (CircularBuffer4[(x4 + i) & CIRC_MASK] - (INT16_MAX)));
            }

            // Pass in phases by reference
//            freq_est4 = vocodeAnalysis(&phaseOld_4, &phaseNew_4, handler_rfft1);
            freq_est_cpu1[4] = vocodeAnalysis(&phaseOld_4, &phaseNew_4, handler_rfft1);
            done4 = 0;
        }
        if (done6) { // String 6
            // Fill FFT Input Buffer with new values
            // (Can't just change pointer because mem alignment/circular buffer)
            for (int i = 0; i < RFFT_SIZE; i++) {
                handler_rfft1->InBuf[i] = (float32) ((int16_t) (CircularBuffer6[(x6 + i) & CIRC_MASK] - (INT16_MAX)));
            }

            // Pass in phases by reference
//            freq_est6 = vocodeAnalysis(&phaseOld_6, &phaseNew_6, handler_rfft1);
            freq_est_cpu1[6] = vocodeAnalysis(&phaseOld_6, &phaseNew_6, handler_rfft1);
            done6 = 0;
        }

//        for (int i = 1; i < 7; i+2) {
//            freq_est_cpu1[i] =
//        }

    }

    ESTOP0;
    return FAIL;
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
    DMACH4AddrConfig(&CircularBuffer4[x4], &AdcaResultRegs.ADCRESULT1);

    // Acknowledge Interrupt
    done4 = 1;                              // Set Done4 Flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7; // Clear Interrupt Flag

}

#pragma CODE_SECTION(DMACH6_ISR, ".TI.ramfunc");
__interrupt void DMACH6_ISR(void) {

    // Move DMA Buffer Pointer
    x6 = (x6 + DMA_BUFFER_SIZE) & CIRC_MASK;
    DMACH6AddrConfig(&CircularBuffer6[x6], &AdccResultRegs.ADCRESULT0);

    // Acknowledge Interrupt
    done6 = 1;                              // Set Done6 Flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7; // Clear Interrupt Flag

}

#pragma CODE_SECTION(ADCCH2_ISR, ".TI.ramfunc");
__interrupt void ADCCH2_ISR(void) {

    // Acknowledge Interrupt Triggered by ePWM1 SOCA
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; // clear ADCA INT1 flag for channels 01
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

#pragma CODE_SECTION(ADCCH4_ISR, ".TI.ramfunc");
__interrupt void ADCCH4_ISR(void) {

    // Acknowledge Interrupt Triggered by ePWM1 SOCB
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT2 = 1; // Clear ADCA INT2 flag for channels 45
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

}

#pragma CODE_SECTION(ADCCH6_ISR, ".TI.ramfunc");
__interrupt void ADCCH6_ISR(void) {

    // Acknowledge Interrupt Triggered by ePWM2 SOCA
    AdccRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; // Clear ADCC INT2 flag for channels 23
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

}

#pragma CODE_SECTION(EPWM_5_ISR, ".TI.ramfunc");
__interrupt void EPWM_5_ISR(void) {

    // Acknowledge Interrupt Triggered by ePWM5
    EPwm5Regs.ETCLR.bit.INT = 1; // Clear EPWM5 INT flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

}

void initMain(void) {

    // Initialize System Control
    InitSysCtrl();

    // Initialize GPIO
    InitGpio();

    // Initialize PIE Control Registers
    InitPieCtrl();

    GPIO_SetupPinMux(19, GPIO_MUX_CPU1, 2); // Launchpad SCIB RX
    GPIO_SetupPinOptions(19, GPIO_INPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(18, GPIO_MUX_CPU1, 2); // Launchpad SCIB TX
    GPIO_SetupPinOptions(18, GPIO_OUTPUT, GPIO_ASYNC);
    // Clear Interrupts, Disable CPU __interrupts and clear CPU __interrupt flags
    DINT;
    IER = 0x0000;
    IFR = 0x0000;

    // Initialize PIE Vector Tables with pointers to shell ISRs
    InitPieVectTable();

    // Connect ISRs to Main Defined Interrupts
    EALLOW;
    PieVectTable.DMA_CH2_INT = &DMACH2_ISR;
    PieVectTable.DMA_CH4_INT = &DMACH4_ISR;
    PieVectTable.DMA_CH6_INT = &DMACH6_ISR;
    PieVectTable.ADCA1_INT = &ADCCH2_ISR;
    PieVectTable.ADCA2_INT = &ADCCH4_ISR;
    PieVectTable.ADCC1_INT = &ADCCH6_ISR;
    PieVectTable.EPWM5_INT = &EPWM_5_ISR;
    EDIS;

    // Initialize ADCs and DMA
    initSCI();
    initCPU2();
    initADC();
    initDMA();
    initDMAx(&CircularBuffer2[0], &AdcaResultRegs.ADCRESULT0, DMA_ADCAINT1, 2);
    initDMAx(&CircularBuffer4[0], &AdcaResultRegs.ADCRESULT1, DMA_ADCAINT2, 4);
    initDMAx(&CircularBuffer6[0], &AdccResultRegs.ADCRESULT0, DMA_ADCCINT1, 6);
    initEPWM();
    initFFT(handler_rfft1);

    // Enable global Interrupts and higher priority real-time debug events
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global real-time interrupt DBGM

}

void initCPU2(void) {
    EALLOW;
    // Transfer Memory Control to CPU2
    MemCfgRegs.MSGxINIT.bit.INIT_CPUTOCPU = 1;
    MemCfgRegs.GSxMSEL.bit.MSEL_GS2 = 1;    // RFFT2 Buffers
    MemCfgRegs.GSxMSEL.bit.MSEL_GS3 = 1;    // RFFT2 Buffers
    MemCfgRegs.GSxMSEL.bit.MSEL_GS7 = 1;    // Circular Buffers 1 & 3
    MemCfgRegs.GSxMSEL.bit.MSEL_GS8 = 1;    // Circular Buffer 5
    MemCfgRegs.GSxMSEL.bit.MSEL_GS11 = 1;   // .cinit
    MemCfgRegs.GSxMSEL.bit.MSEL_GS12 = 1;   // .ebss

    // Transfer Peripheral Control to CPU2
    DevCfgRegs.CPUSEL0.bit.EPWM3 = 1;
    DevCfgRegs.CPUSEL0.bit.EPWM4 = 1;

//    DevCfgRegs.CPUSEL5.bit.SCI_B = 1;

    DevCfgRegs.CPUSEL11.bit.ADC_B = 1;
    DevCfgRegs.CPUSEL11.bit.ADC_D = 1;
    EDIS;
//    IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_RAM);
}

