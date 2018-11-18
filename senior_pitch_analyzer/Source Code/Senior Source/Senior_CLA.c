/*
 * Senior_CLA.c
 *
 *  Created on: Nov 17, 2018
 *      Author: meser
 */

#include "F28379D_Senior_Design.h"
#include "F2837xD_device.h"
#include "F2837xD_Examples.h"

/*** Control Law Accelerator - CPU1 ***/
#pragma DATA_SECTION(GPIO34_count, "Cla1Data1");
Uint16 GPIO34_count = 0;

#pragma DATA_SECTION(data, "Cla1Data1");
Uint32 data[7] = { 0x00000000, // Start Frame
                   0xE1000000, // Red
                   0xE1000000, // Green
                   0xE1000000, // Blue
                   0xE13F003F, // Purpink
                   0xE13F3F3F,
                   0xF0000000}; // End Frame

#pragma DATA_SECTION(dataLength, "Cla1Data1");
Uint16 dataLength = 7;

#pragma DATA_SECTION(red, "Cla1Data1");
Uint16 red = 0x00;

#pragma DATA_SECTION(green, "Cla1Data1");
Uint16 green = 0x00;

#pragma DATA_SECTION(blue, "Cla1Data1");
Uint16 blue = 0x00;

#pragma DATA_SECTION(bright, "Cla1Data1");
Uint32 bright = 0xE1000000;

#pragma DATA_SECTION(iter, "Cla1Data1");
Uint16 iter = 0;

#pragma DATA_SECTION(i, "Cla1Data1");
Uint16 i = 0;

#pragma DATA_SECTION(j, "Cla1Data1");
Uint16 j = 0;

#pragma DATA_SECTION(rdata, "Cla1Data1");
Uint32 rdata = 0;

#pragma DATA_SECTION(b, "Cla1Data1");
Uint32 b = 0;

#pragma DATA_SECTION(temp, "Cla1Data1");
Uint16 temp = 0;

void initCLA(void) {
    EALLOW;

    // Memory Configuration - Master CPU and CLA Select
    MemCfgRegs.LSxMSEL.bit.MSEL_LS0 = 1;        // 0=CPU | 1=CPU and CLA
    MemCfgRegs.LSxMSEL.bit.MSEL_LS1 = 1;        // 0=CPU | 1=CPU and CLA
    MemCfgRegs.LSxMSEL.bit.MSEL_LS2 = 1;        // 0=CPU | 1=CPU and CLA
    MemCfgRegs.LSxMSEL.bit.MSEL_LS3 = 1;        // 0=CPU | 1=CPU and CLA
    MemCfgRegs.LSxMSEL.bit.MSEL_LS4 = 0;        // 0=CPU | 1=CPU and CLA
    MemCfgRegs.LSxMSEL.bit.MSEL_LS5 = 0;        // 0=CPU | 1=CPU and CLA

    // Memory Configuration - CLA Data Memory and CLA Program Memory Select
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS0 = 0;    // 0=CLA data memory | 1=CLA program memory
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS1 = 0;    // 0=CLA data memory | 1=CLA program memory
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS2 = 1;    // 0=CLA data memory | 1=CLA program memory
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS3 = 0;    // 0=CLA data memory | 1=CLA program memory
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS4 = 0;    // 0=CLA data memory | 1=CLA program memory
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS5 = 0;    // 0=CLA data memory | 1=CLA program memory

    // Initialize CLA task interrupt vectors
    // On Type-1 CLAs the MVECT registers accept full 16-bit task addresses as opposed to offsets used on older Type-0 CLAs.
    Cla1Regs.MVECT1 = (uint16_t)(&Cla1Task1);
    Cla1Regs.MVECT2 = (uint16_t)(&Cla1Task2);
    Cla1Regs.MVECT3 = (uint16_t)(&Cla1Task3);
    Cla1Regs.MVECT4 = (uint16_t)(&Cla1Task4);
    Cla1Regs.MVECT5 = (uint16_t)(&Cla1Task5);
    Cla1Regs.MVECT6 = (uint16_t)(&Cla1Task6);
    Cla1Regs.MVECT7 = (uint16_t)(&Cla1Task7);
    Cla1Regs.MVECT8 = (uint16_t)(&Cla1Task8);

    // Select Task interrupt source                    /******** TRIGGER SOURCE FOR EACH TASK (unlisted numbers are reserved) ********/
    DmaClaSrcSelRegs.CLA1TASKSRCSEL1.bit.TASK1 = 37;   // 0=none       8=ADCBINT3  16=ADCDINT1  32=XINT4     42=EPWM7INT   70=TINT2     78=ECAP4INT   95=SD1INT     114=SPIRXINTC
    DmaClaSrcSelRegs.CLA1TASKSRCSEL1.bit.TASK2 = 0;    // 1=ADCAINT1   9=ADCBINT4  17=ADCDINT2  33=XINT5     43=EPWM8INT   71=MXEVTA    79=ECAP5INT   96=SD2INT
    DmaClaSrcSelRegs.CLA1TASKSRCSEL1.bit.TASK3 = 0;    // 2=ADCAINT2  10=ADCBEVT   18=ADCDINT3  36=EPWM1INT  44=EPWM9INT   72=MREVTA    80=ECAP6INT  107=UPP1INT
    DmaClaSrcSelRegs.CLA1TASKSRCSEL1.bit.TASK4 = 0;    // 3=ADCAINT3  11=ADCCINT1  19=ADCDINT4  37=EPWM2INT  45=EPWM10INT  73=MXEVTB    83=EQEP1INT  109=SPITXINTA
    DmaClaSrcSelRegs.CLA1TASKSRCSEL2.bit.TASK5 = 0;    // 4=ADCAINT4  12=ADCCINT2  20=ADCDEVT   38=EPWM3INT  46=EPWM11INT  74=MREVTB    84=EQEP2INT  110=SPIRXINTA
    DmaClaSrcSelRegs.CLA1TASKSRCSEL2.bit.TASK6 = 0;    // 5=ADCAEVT   13=ADCCINT3  29=XINT1     39=EPWM4INT  47=EPWM12INT  75=ECAP1INT  85=EQEP3INT  111=SPITXINTB
    DmaClaSrcSelRegs.CLA1TASKSRCSEL2.bit.TASK7 = 0;    // 6=ADCBINT1  14=ADCCINT4  30=XINT2     40=EPWM5INT  48=TINT0      76=ECAP2INT  87=HRCAP1INT 112=SPIRXINTB
    DmaClaSrcSelRegs.CLA1TASKSRCSEL2.bit.TASK8 = 0;    // 7=ADCBINT2  15=ADCCEVT   31=XINT3     41=EPWM6INT  69=TINT1      77=ECAP3INT  88=HRCAP2INT 113=SPITXINTC

    // CLA1TASKSRCSELx Register lock control
    DmaClaSrcSelRegs.CLA1TASKSRCSELLOCK.bit.CLA1TASKSRCSEL1 = 0;     // Write a 1 to lock (cannot be cleared once set)
    DmaClaSrcSelRegs.CLA1TASKSRCSELLOCK.bit.CLA1TASKSRCSEL2 = 0;     // Write a 1 to lock (cannot be cleared once set)

    // Enable use software to start a task (IACK)
    Cla1Regs.MCTL.bit.IACKE = 1;s

    // Force one-time initialization Task 8 - zero delay buffer
    Cla1Regs.MIER.all = M_INT8;             // Enable CLA interrupt 8
    asm("  IACK  #0x0080");                 // IACK - CLA task force instruction
    asm("  RPT #3 || NOP");                 // Wait at least 4 cycles
    while(Cla1Regs.MIRUN.bit.INT8 == 1);    // Loop until task completes

    // Enable CLA task interrupts
    Cla1Regs.MIER.all = 0x0001;             // Enable CLA interrupt 1 (and disable interrupt 8)

    EDIS;

    // Enable the CLA interrupt
    PieCtrlRegs.PIEIER11.bit.INTx1 = 1;     // Enable CLA Task1 in PIE group #11
    IER |= M_INT11;                         // Enable INT11 in IER to enable PIE group 11

}

/* ------------------------------------------------------------------------------ */

// End of File
