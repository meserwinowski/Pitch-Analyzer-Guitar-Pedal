/*
 * senior_main_cpu1.c
 *
 *  Created on: Oct 1, 2018
 *      Author: meser
 */

// Includes
#include "F28x_Project.h"
#include "F28379D_Senior_Design.h"

// Mode Select
extern uint16_t mode;
extern uint16_t colors[6][4];
extern LED_DATA frameLUT[6][25];
extern uint16_t root_index;
extern int16_t* scale_pointer;

// Fixed Frequency Array + Fret Index Estimations
extern float32 fn[7];
extern float32 fo_n_cpu[7];

// Frequency Estimation Buffers
float32 fo_n_cpu1[7] = {FREQ_NAN, FREQ_NAN, FREQ_NAN, FREQ_NAN, FREQ_NAN, FREQ_NAN, FREQ_NAN};
float32 fo_est_cpu1[7] = {FREQ_NAN, FREQ_NAN, FREQ_NAN, FREQ_NAN, FREQ_NAN, FREQ_NAN, FREQ_NAN};
extern float32 fo_n_cpu2[7];
extern float32 fo_est_cpu2[7];

// Extern String Structs
extern STRING_DATA string1;
extern STRING_DATA string2;
extern STRING_DATA string3;
extern STRING_DATA string4;
extern STRING_DATA string5;
extern STRING_DATA string6;

// CPU1 External Reference to FFT Handler declared in FFT Source
extern RFFT_F32_STRUCT_Handle handler_rfft1;

// CPU1 Interrupts
#pragma CODE_SECTION(DMACH2_ISR, ".TI.ramfunc");
interrupt void DMACH2_ISR(void); // Because DMA ISRs are in the same group, the lowest
#pragma CODE_SECTION(DMACH4_ISR, ".TI.ramfunc");
interrupt void DMACH4_ISR(void); // number has priority
#pragma CODE_SECTION(DMACH6_ISR, ".TI.ramfunc");
interrupt void DMACH6_ISR(void);
#pragma CODE_SECTION(ADCCH2_ISR, ".TI.ramfunc");
interrupt void ADCCH2_ISR(void);
#pragma CODE_SECTION(ADCCH4_ISR, ".TI.ramfunc");
interrupt void ADCCH4_ISR(void);
#pragma CODE_SECTION(ADCCH6_ISR, ".TI.ramfunc");
interrupt void ADCCH6_ISR(void);
#pragma CODE_SECTION(EPWM_5_ISR, ".TI.ramfunc");
interrupt void EPWM_5_ISR(void);
#pragma CODE_SECTION(CLA_ISR1, ".TI.ramfunc");
interrupt void CLA_ISR1(void);
#pragma CODE_SECTION(SCIB_ISR, ".TI.ramfunc");
interrupt void SCIB_ISR(void);

#pragma DATA_SECTION(GPIO34_count, "Cla1Data1");
uint16_t GPIO34_count = 0;

// Functions
void initMain(void);
void initCPU2(void);

// Main Routine
int main(void) {

    initMain();

    while(1) {
        // Sync CPUs using IPC API and IPC Flag 0
        IpcSync(0);
        uint16_t x = 0;

        if (mode == MIRROR_MODE) {
            if (string2.done) { // String 2
                // Fill FFT Input Buffer with new values
                // (Can't just change pointer because mem alignment/circular buffer)
                for (int i = 0; i < RFFT_SIZE; i++) {
                    x = string2.cBuff[(string2.xDMA + i) & CIRC_MASK];
                    handler_rfft1->InBuf[i] = (float32) ((int16_t) (x - (INT16_MAX)));
                }

                // Pass in string struct and FFT handler by reference
                vocodeAnalysis(&string2, handler_rfft1);
                string2.done = 0;
            }
            if (string4.done) { // String 4
                // Fill FFT Input Buffer with new values
                // (Can't just change pointer because mem alignment/circular buffer)
                for (int i = 0; i < RFFT_SIZE; i++) {
                    x = string4.cBuff[(string4.xDMA + i) & CIRC_MASK];
                    handler_rfft1->InBuf[i] = (float32) ((int16_t) (x - (INT16_MAX)));
                }

                // Pass in string struct and FFT handler by reference
                vocodeAnalysis(&string4, handler_rfft1);
                string4.done = 0;
            }
            if (string6.done) { // String 6
                // Fill FFT Input Buffer with new values
                // (Can't just change pointer because mem alignment/circular buffer)
                for (int i = 0; i < RFFT_SIZE; i++) {
                    x = string6.cBuff[(string6.xDMA + i) & CIRC_MASK];
                    handler_rfft1->InBuf[i] = (float32) ((int16_t) (x - (INT16_MAX)));
                }

                // Pass in string struct and FFT handler by reference
                vocodeAnalysis(&string6, handler_rfft1);
                string6.done = 0;
            }

            // Fill CLA Message RAM with fret estimate results
            fo_n_cpu[1] = fo_n_cpu2[1];
            fo_n_cpu[2] = string2.n_est;
            fo_n_cpu[3] = fo_n_cpu2[3];
            fo_n_cpu[4] = string4.n_est;
            fo_n_cpu[5] = fo_n_cpu2[5];
            fo_n_cpu[6] = string6.n_est;
        }
        else if(mode == LEARNING_MODE) {
            /* Update LUT */
            for (int i = 0; i < 6; i++) {
                // Update LUT with detected note
                int16_t string_index = scale_pointer[(2 * i) + 0];
                frameLUT[i][root_index + string_index].red = colors[i][1];
                frameLUT[i][root_index + string_index].green = colors[i][2];
                frameLUT[i][root_index + string_index].blue = colors[i][3];

                string_index = scale_pointer[(2 * i) + 1];
                frameLUT[i][root_index + string_index].red = colors[i][1];
                frameLUT[i][root_index + string_index].green = colors[i][2];
                frameLUT[i][root_index + string_index].blue = colors[i][3];

            }

        }

    }

}

interrupt void DMACH2_ISR(void) {

    // Move DMA Buffer Pointer
    string2.xDMA = (string2.xDMA + DMA_BUFFER_SIZE) & CIRC_MASK;
    DMACH2AddrConfig(&string2.cBuff[string2.xDMA], &AdcaResultRegs.ADCRESULT0);

    // Acknowledge Interrupt
    string2.done = 1;                      // Set String 2 Done Flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7; // Clear Interrupt Flag

}

interrupt void DMACH4_ISR(void) {

    // Move DMA Buffer Pointer
    string4.xDMA = (string4.xDMA + DMA_BUFFER_SIZE) & CIRC_MASK;
    DMACH4AddrConfig(&string4.cBuff[string4.xDMA], &AdcaResultRegs.ADCRESULT1);

    // Acknowledge Interrupt
    string4.done = 1;                      // Set String 4 Done Flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7; // Clear Interrupt Flag

}

interrupt void DMACH6_ISR(void) {

    // Move DMA Buffer Pointer
    string6.xDMA = (string6.xDMA + DMA_BUFFER_SIZE) & CIRC_MASK;
    DMACH6AddrConfig(&string6.cBuff[string6.xDMA], &AdccResultRegs.ADCRESULT0);

    // Acknowledge Interrupt
    string6.done = 1;                      // Set String 6 Done Flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7; // Clear Interrupt Flag

}

interrupt void ADCCH2_ISR(void) {

    // Acknowledge Interrupt Triggered by ePWM1 SOCA
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; // clear ADCA INT1 flag for channels 01
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

interrupt void ADCCH4_ISR(void) {

    // Acknowledge Interrupt Triggered by ePWM1 SOCB
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT2 = 1; // Clear ADCA INT2 flag for channels 45
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

}

interrupt void ADCCH6_ISR(void) {

    // Acknowledge Interrupt Triggered by ePWM2 SOCA
    AdccRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; // Clear ADCC INT2 flag for channels 23
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

}

interrupt void EPWM_5_ISR(void) {

    // Acknowledge Interrupt Triggered by ePWM5
    EPwm5Regs.ETCLR.bit.INT = 1; // Clear EPWM5 INT flag
    PieCtrlRegs.PIEACK.all |= PIEACK_GROUP3;

}

interrupt void CLA_ISR1(void) {

    // Acknowledge Interrupt Triggered by end of CLA Task 1
    PieCtrlRegs.PIEACK.all |= PIEACK_GROUP11;

}

interrupt void SCIB_ISR(void) {

    determineCommand();

    // Clear RX FIFO Flags
    ScibRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
    ScibRegs.SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag

    // Acknowledge Interrupt Triggered by SCIB Receive
    PieCtrlRegs.PIEACK.all |= PIEACK_GROUP9;

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

    // Transfer ADC Control to CPU2
    DevCfgRegs.CPUSEL11.bit.ADC_B = 1;
    DevCfgRegs.CPUSEL11.bit.ADC_D = 1;

    // Initialize and wiat for CPUtoCPUMsgRAM
    MemCfgRegs.MSGxINIT.bit.INIT_CPUTOCPU = 1;
    while(MemCfgRegs.MSGxINITDONE.bit.INITDONE_CPUTOCPU != 1){};

#ifdef _STANDALONE
#ifdef _FLASH
    //  Send boot command to allow the CPU02 application to begin execution
    IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_FLASH);
#endif
#endif

    EDIS;

}

void initMain(void) {

    // Initialize System Control
    InitSysCtrl();

    // Initialize GPIO
    InitGpio();

    // Initialize PIE Control Registers
    InitPieCtrl();
    EnableInterrupts();

    // Clear Interrupts, Disable CPU __interrupts and clear CPU __interrupt flags
    DINT;
    IER = 0x0000;
    IFR = 0x0000;

    // Initialize PIE Vector Tables with pointers to shell ISRs
    InitPieVectTable();
    initCPU2();                 // Initialize CPU2

    // Connect ISRs to Main Defined Interrupts
    EALLOW;
    PieVectTable.DMA_CH2_INT = &DMACH2_ISR;
    PieVectTable.DMA_CH4_INT = &DMACH4_ISR;
    PieVectTable.DMA_CH6_INT = &DMACH6_ISR;
    PieVectTable.ADCA1_INT = &ADCCH2_ISR;
    PieVectTable.ADCA2_INT = &ADCCH4_ISR;
    PieVectTable.ADCC1_INT = &ADCCH6_ISR;
    PieVectTable.EPWM5_INT = &EPWM_5_ISR;
    PieVectTable.CLA1_1_INT = &CLA_ISR1;
    PieVectTable.SCIB_RX_INT = &SCIB_ISR;
    EDIS;

    // Initialize CPU2, CLA, Peripherals and FFT Handler
    initSCI();                  // Initialize Serial Communications Interface - UART
    initSPI();                  // Initialize Serial Peripheral Interface
    initCLA();                  // Initialize Control Law Accelerator - CPU1

    initEPWM();                 // Initialize Enchanced Pulse Width Modulation Channels
    initADC();                  // Initialize Analog-to-Digital Convertors
    initDMA();                  // Initialize Direct Memory Access Channels
    initDMAx(&string2.cBuff[0], &AdcaResultRegs.ADCRESULT0, DMA_ADCAINT1, 2);
    initDMAx(&string4.cBuff[0], &AdcaResultRegs.ADCRESULT1, DMA_ADCAINT2, 4);
    initDMAx(&string6.cBuff[0], &AdccResultRegs.ADCRESULT0, DMA_ADCCINT1, 6);
    initFFT(handler_rfft1);     // Initialize Fast Fourier Transform Handler

    // Enable global Interrupts and higher priority real-time debug events
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global real-time interrupt DBGM

}


