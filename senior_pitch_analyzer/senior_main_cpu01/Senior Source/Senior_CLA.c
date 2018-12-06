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

#pragma DATA_SECTION(colors, "Cla1Data1");
uint16_t colors[6][4] = {{0x01, 0x10, 0x00, 0x1F}, // String 1
                         {0x01, 0x00, 0x1F, 0x00}, // String 2
                         {0x01, 0x30, 0x12, 0x00}, // String 3
                         {0x01, 0x00, 0x00, 0x1F}, // String 4
                         {0x01, 0x1F, 0x1F, 0x00}, // String 5
                         {0x01, 0x1F, 0x00, 0x00}  // String 6
};

#pragma DATA_SECTION(frameLUT, "Cla1Data1");
LED_DATA frameLUT[6][25];

// Pentatonic Scale Lookup Tables - S1...S6
int16_t penta_ionian_LUT[6][3] = {{0, 2, 0}, {0, 2, 0}, {-1, 1, -1}, {-1, 2, -1}, {-1, 2, -1}, {0, 2, 0}};
int16_t penta_dorian_LUT[6][3] = {{0, 2, 0}, {0, 3, 0}, {-1, 2, -1}, {0, 2, 0}, {0, 2, 0}, {0, 2, 0}};
int16_t penta_phrygian_LUT[6][3] = {{0, 3, 0}, {1, 3, 1}, {0, 2, 0}, {0, 2, 0}, {0, 3, 0}, {0, 3, 0}};
int16_t penta_mixolydian_LUT[6][3] = {{0, 2, 0}, {0, 2, 0}, {-1, 2, -1}, {-1, 2, -1}, {0, 2, 0}, {0, 2, 0}};
int16_t penta_aeolian_LUT[6][3] = {{0, 3, 0}, {0, 3, 0}, {0, 2, 0}, {0, 2, 0}, {0, 2, 0}, {0, 3, 0}};

// Diatonic Scale Lookup Tables - S1...S6
int16_t dia_ionian_LUT[6][3] = {{-1, 0, 2}, {0, 2, 0}, {-1, 1, 2}, {-1, 1, 2}, {-1, 0, 2}, {0, 2, 0}};
int16_t dia_dorian_LUT[6][3] = {{0, 2, 3}, {0, 2, 3}, {-1, 0, 2}, {-1, 0, 2}, {0, 2, 3}, {0, 2, 3}};
int16_t dia_phrygian_LUT[6][3] = {{0, 1, 3}, {0, 1, 3}, {0, 2, 0}, {0, 2, 3}, {0, 2, 3}, {0, 1, 3}};
int16_t dia_lydian_LUT[6][3] = {{0, 2, 0}, {-1, 0, 2}, {-1, 1, 3}, {-1, 1, 2}, {-1, 1, 2}, {0, 2, 0}};
int16_t dia_mixolydian_LUT[6][3] = {{0, 2, 3}, {0, 2, 0}, {-1, 1, 2}, {-1, 0, 2}, {-1, 0, 2}, {0, 2, 0}};
int16_t dia_aeolian_LUT[6][3] = {{0, 2, 3}, {0, 1, 3}, {0, 2, 0}, {0, 2, 4}, {0, 2, 3}, {0, 2, 3}};
int16_t dia_locrian_LUT[6][3] = {{0, 1, 3}, {0, 2, 0}, {0, 2, 3}, {0, 2, 3}, {0, 1, 3}, {0, 1, 3}};

//int16_t* scaleLUT[12] = { &penta_ionian_LUT[0][0],
//                          &penta_dorian_LUT[0][0],
//                          &penta_phrygian_LUT[0][0],
//                          &penta_mixolydian_LUT[0][0],
//                          &penta_aeolian_LUT[0][0],
//                          &dia_ionian_LUT[0][0],
//                          &dia_dorian_LUT[0][0],
//                          &dia_phrygian_LUT[0][0],
//                          &dia_lydian_LUT[0][0],
//                          &dia_mixolydian_LUT[0][0],
//                          &dia_aeolian_LUT[0][0],
//                          &dia_locrian_LUT[0][0]};

uint16_t root_index;
int16_t* scale_pointer;


#pragma DATA_SECTION(fo_n_cpu, "CpuToCla1MsgRAM");
float32 fo_n_cpu[7] = {-1, -1, -1, -1, -1, -1, -1};

void initCLA(void) {

    extern uint32_t Cla1funcsRunStart, Cla1funcsLoadStart, Cla1funcsLoadSize;

    // Initialize Lookup Table
    initLUT();

    EALLOW;

    // GPIO For Red Status LED to make sure CLA is running
    GpioCtrlRegs.GPBGMUX1.bit.GPIO34 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;     // 1=OUTput, 0=INput
    GpioDataRegs.GPBSET.bit.GPIO34 = 1;     // Set High initially
    GpioCtrlRegs.GPBCSEL1.bit.GPIO34 = 0;   // 0=CPU1, 1=CPU1.CLA1, 2=CPU2, 3=CPU2.CLA

#ifdef _FLASH
    // Copy over code from FLASH to RAM for the CLA
    memcpy((uint32_t *) &Cla1funcsRunStart,
           (uint32_t *) &Cla1funcsLoadStart,
           (uint32_t) &Cla1funcsLoadSize);
#endif //_FLASH

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
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS3 = 1;    // 0=CLA data memory | 1=CLA program memory
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
    DmaClaSrcSelRegs.CLA1TASKSRCSEL1.bit.TASK1 = 40;   // 0=none       8=ADCBINT3  16=ADCDINT1  32=XINT4     42=EPWM7INT   70=TINT2     78=ECAP4INT   95=SD1INT     114=SPIRXINTC
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

    // Initialize and wait for CLA1ToCPUMsgRAM
    MemCfgRegs.MSGxINIT.bit.INIT_CLA1TOCPU = 1;
    while(MemCfgRegs.MSGxINITDONE.bit.INITDONE_CLA1TOCPU != 1){};

    // Initialize and wait for CPUToCLA1MsgRAM
    MemCfgRegs.MSGxINIT.bit.INIT_CPUTOCLA1 = 1;
    while(MemCfgRegs.MSGxINITDONE.bit.INITDONE_CPUTOCLA1 != 1){};

    // Enable use software to start a task (IACK)
    Cla1Regs.MCTL.bit.IACKE = 1;

    // Enable CLA task interrupts
    Cla1Regs.MIER.bit.INT1 = 1;             // Enable CLA interrupt 1 (and disable interrupt 8)

    // Enable the CLA interrupt
    PieCtrlRegs.PIEIER11.bit.INTx1 = 1;     // Enable CLA Task1 in PIE group #11
    IER |= M_INT11;                         // Enable INT11 in IER to enable PIE group 11

    EDIS;
}

// Initialize Lookup Table with data frame
void initLUT(void) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 25; j++) {
            frameLUT[i][j].sbright = 0x00E5;
            frameLUT[i][j].blue = 0x001F;
            frameLUT[i][j].green = 0x001F;
            frameLUT[i][j].red = 0x001F;
        }
    }
}

/* ------------------------------------------------------------------------------ */

// End of File
