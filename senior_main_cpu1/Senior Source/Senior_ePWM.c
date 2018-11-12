/*
 * Senior_ePWM.c
 *
 *  Created on: Oct 13, 2018
 *      Author: meser
 */

#include "F28379D_Senior_Design.h"
#include "F2837xD_device.h"
#include "F2837xD_Examples.h"

/*** Enhanced Pulse Width Modulation Functions (ePWM) ***/
void initEPWM(void) {
    EALLOW;

    // Configure the pre scale to the ePWM modules.  Max ePWM input clock is 100 MHz.
    ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV = 1; // SYSCLK/2 = 100MHz

    // Disable the clock to the ePWM modules to keep them synchronized
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;

    // Configure ePWM Modules
    initEPWM1(); // String 2
    initEPWM2(); // String 4
    initEPWM3(); // String 6


    //---------------------------------------------------------------------
    //--- Enable the clocks to the ePWM module.
    //--- Note: this should be done after all ePWM modules are configured
    //--- to ensure synchronization between the ePWM modules.
    //---------------------------------------------------------------------

    // Enable ePWM Peripheral Clock
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;

    EDIS;
}

void initEPWM1(void) {
    /* Configure ePWM2 to trigger ADC A SOCA at a 20 kHz rate */
    DevCfgRegs.SOFTPRES2.bit.EPWM1 = 1;     // ePWM1 is reset
    DevCfgRegs.SOFTPRES2.bit.EPWM1 = 0;     // ePWM1 is released from reset

    /* Configure Time Base Control register */
    // bit 15-14     11:     FREE/SOFT, 11 = ignore emulation suspend
    // bit 13        0:      PHSDIR,    0 = count down after sync event
    // bit 12-10     000:    CLKDIV,    000 => TBCLK = HSPCLK/1
    // bit 9-7       000:    HSPCLKDIV, 000 => HSPCLK = ePWMCLK/1
    // bit 6         0:      SWFSYNC,   0 = no software sync produced
    // bit 5-4       11:     SYNCOSEL,  11 = sync-out disabled
    // bit 3         0:      PRDLD,     0 = reload PRD on counter=0
    // bit 2         0:      PHSEN,     0 = phase control disabled
    // bit 1-0       11:     CTRMODE,   11 = timer stopped (disabled)
    EPwm1Regs.TBCTL.bit.CTRMODE = 0x3;      // Disable ePWM1 Timer

    // Clear Timer Counter Register
    EPwm1Regs.TBCTR = 0x0000;

    // Set Time Base Period Register
    EPwm1Regs.TBPRD = ADC_SAMPLE_PERIOD;

    // Set Time Base Phase High Register
    EPwm1Regs.TBPHS.bit.TBPHS = 0x0000;

    // Set the A output on zero and reset on CMPA
    EPwm1Regs.AQCTLA.bit.ZRO = AQ_SET;
    EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;

    // Set CMPA to 20us to get a 50% duty
    EPwm1Regs.CMPA.bit.CMPA = ADC_CMP_PERIOD;

    /* Configure Event Trigger Select */
    // bit 15        0:      SOCBEN,    0 = disable SOCB
    // bit 14-12     000:    SOCBSEL,   don't care
    // bit 11        1:      SOCAEN,    1 = enable SOCA
    // bit 10-8      010:    SOCASEL,   010 = SOCA on PRD event
    // bit 7-4       0000:   reserved
    // bit 3         0:      INTEN,     0 = disable interrupt
    // bit 2-0       000:    INTSEL,    don't care
    EPwm1Regs.ETSEL.all = 0x0A00;           // ePWM1 - Enable SOCA to ADC

    /* Configure Event Trigger Pre Scale */
    // bit 15-14     00:     ePWMxSOCB, read-only
    // bit 13-12     00:     SOCBPRD,   don't care
    // bit 11-10     00:     ePWMxSOCA, read-only
    // bit 9-8       01:     SOCAPRD,   01 = generate SOCA on first event
    // bit 7-4       0000:   reserved
    // bit 3-2       00:     INTCNT,    don't care
    // bit 1-0       00:     INTPRD,    don't care
    EPwm1Regs.ETPS.all = 0x0100;            // ePWM1 - Configure SOCA

    // Enable Event Trigger Counter Initialization Enable
    EPwm1Regs.ETCNTINITCTL.bit.SOCAINITEN = 1;

    // Enable timers to count up
    EPwm1Regs.TBCTL.bit.CTRMODE = 0x0;
}

void initEPWM2(void) {
    /* Configure ePWM2 to trigger ADC A SOCA at a 20 kHz rate */
    DevCfgRegs.SOFTPRES2.bit.EPWM2 = 1;     // ePWM1 is reset
    DevCfgRegs.SOFTPRES2.bit.EPWM2 = 0;     // ePWM1 is released from reset

    /* Configure Time Base Control register */
    // bit 15-14     11:     FREE/SOFT, 11 = ignore emulation suspend
    // bit 13        0:      PHSDIR,    0 = count down after sync event
    // bit 12-10     000:    CLKDIV,    000 => TBCLK = HSPCLK/1
    // bit 9-7       000:    HSPCLKDIV, 000 => HSPCLK = ePWMCLK/1
    // bit 6         0:      SWFSYNC,   0 = no software sync produced
    // bit 5-4       11:     SYNCOSEL,  11 = sync-out disabled
    // bit 3         0:      PRDLD,     0 = reload PRD on counter=0
    // bit 2         0:      PHSEN,     0 = phase control disabled
    // bit 1-0       11:     CTRMODE,   11 = timer stopped (disabled)
    EPwm2Regs.TBCTL.bit.CTRMODE = 0x3;      // Disable ePWM1 Timer

    // Clear Timer Counter Register
    EPwm2Regs.TBCTR = 0x0000;

    // Set Time Base Period Register
    EPwm2Regs.TBPRD = ADC_CMP_PERIOD;

    // Set Time Base Phase High Register
    EPwm2Regs.TBPHS.bit.TBPHS = 0x0000;

    // Set the A output on zero and reset on CMPA
    EPwm2Regs.AQCTLA.bit.ZRO = AQ_SET;
    EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;

    // Set CMPA to 20us to get a 50% duty
    EPwm2Regs.CMPA.bit.CMPA = ADC_CMP_PERIOD;

    /* Configure Event Trigger Select */
    // bit 15        0:      SOCBEN,    0 = disable SOCB
    // bit 14-12     000:    SOCBSEL,   don't care
    // bit 11        1:      SOCAEN,    1 = enable SOCA
    // bit 10-8      010:    SOCASEL,   010 = SOCA on PRD event
    // bit 7-4       0000:   reserved
    // bit 3         0:      INTEN,     0 = disable interrupt
    // bit 2-0       000:    INTSEL,    don't care
    EPwm2Regs.ETSEL.all = 0x0A00;           // ePWM1 - Enable SOCA to ADC

    /* Configure Event Trigger Pre Scale */
    // bit 15-14     00:     ePWMxSOCB, read-only
    // bit 13-12     00:     SOCBPRD,   don't care
    // bit 11-10     00:     ePWMxSOCA, read-only
    // bit 9-8       10:     SOCAPRD,   10 = generate SOCA on second event
    // bit 7-4       0000:   reserved
    // bit 3-2       00:     INTCNT,    don't care
    // bit 1-0       00:     INTPRD,    don't care
    EPwm2Regs.ETPS.all = 0x0200;            // ePWM1 - Configure SOCA

    // Enable Event Trigger Counter Initialization Enable
    EPwm2Regs.ETCNTINITCTL.bit.SOCAINITEN = 1;

    // Enable timers to count up
    EPwm2Regs.TBCTL.bit.CTRMODE = 0x0;
}

void initEPWM3(void) {
    /* Configure ePWM3 to trigger ADC C SOCA at a 20 kHz rate */
    DevCfgRegs.SOFTPRES2.bit.EPWM3 = 1;     // ePWM3 is reset
    DevCfgRegs.SOFTPRES2.bit.EPWM3 = 0;     // ePWM3 is released from reset

    /* Configure Time Base Control register */
    // bit 15-14     11:     FREE/SOFT, 11 = ignore emulation suspend
    // bit 13        0:      PHSDIR,    0 = count down after sync event
    // bit 12-10     000:    CLKDIV,    000 => TBCLK = HSPCLK/1
    // bit 9-7       000:    HSPCLKDIV, 000 => HSPCLK = ePWMCLK/1
    // bit 6         0:      SWFSYNC,   0 = no software sync produced
    // bit 5-4       11:     SYNCOSEL,  11 = sync-out disabled
    // bit 3         0:      PRDLD,     0 = reload PRD on counter=0
    // bit 2         0:      PHSEN,     0 = phase control disabled
    // bit 1-0       11:     CTRMODE,   11 = timer stopped (disabled)
    EPwm3Regs.TBCTL.bit.CTRMODE = 0x3;      // Disable ePWM3 Timer

    // Clear Timer Counter Register
    EPwm3Regs.TBCTR = 0x0000;

    // Set Time Base Period Register
    EPwm3Regs.TBPRD = ADC_SAMPLE_PERIOD;

    // Set Time Base Phase High Register
    EPwm3Regs.TBPHS.bit.TBPHS = 0x0000;

    // Set the A output on zero and reset on CMPA
    EPwm3Regs.AQCTLA.bit.ZRO = AQ_SET;
    EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR;

    // Set CMPA to 20us to get a 50% duty
    EPwm3Regs.CMPA.bit.CMPA = ADC_CMP_PERIOD;

    /* Configure Event Trigger Select */
    // bit 15        0:      SOCBEN,    0 = disable SOCB
    // bit 14-12     000:    SOCBSEL,   don't care
    // bit 11        1:      SOCAEN,    1 = enable SOCA
    // bit 10-8      010:    SOCASEL,   010 = SOCA on PRD event
    // bit 7-4       0000:   reserved
    // bit 3         0:      INTEN,     0 = disable interrupt
    // bit 2-0       000:    INTSEL,    don't care
    EPwm3Regs.ETSEL.all = 0x0A00;           // ePWM3 - Enable SOCA to ADC

    /* Configure Event Trigger Pre Scale */
    // bit 15-14     00:     ePWMxSOCB, read-only
    // bit 13-12     00:     SOCBPRD,   don't care
    // bit 11-10     00:     ePWMxSOCA, read-only
    // bit 9-8       01:     SOCAPRD,   01 = generate SOCA on first event
    // bit 7-4       0000:   reserved
    // bit 3-2       00:     INTCNT,    don't care
    // bit 1-0       00:     INTPRD,    don't care
    EPwm3Regs.ETPS.all = 0x0100;            // ePWM3 - Configure SOCA

    // Enable Event Trigger Counter Initialization Enable
    EPwm3Regs.ETCNTINITCTL.bit.SOCAINITEN = 1;

    // Enable timers to count up
    EPwm3Regs.TBCTL.bit.CTRMODE = 0x0;
}

/* ------------------------------------------------------------------------------ */

// End of File
