/*
 * Senior_ADC.c
 *
 *  Created on: Oct 13, 2018
 *      Author: meser
 */


#include "F28379D_Senior_Design.h"
#include "F2837xD_device.h"
#include "F2837xD_Examples.h"

/*** Globals ***/
// Str 6 - Str 5 - Str 4 - Str 3 - Str 2 - Str 1
// ADCC23, ADCB01, ADCA23, ADCD01, ADCA01, ADCD23

/*** Analog to Digital Converters ***/

// ConfigureADC - Write and power up configurations for ADCs A/B/C/D
void configureADCs(void) {
    EALLOW;

#ifdef CPU1
    // Write Configurations - Set resolution and signal mode.
    // Function also performs ADC Calibration
    AdcSetMode(ADC_ADCA, ADC_RESOLUTION_16BIT, ADC_SIGNALMODE_DIFFERENTIAL);
    AdcSetMode(ADC_ADCC, ADC_RESOLUTION_16BIT, ADC_SIGNALMODE_DIFFERENTIAL);

    // Set ADC Interrupt Pulse Positions - 0 -> Occur at end of Acquisition Window
    // 1 -> Occur at EOC (Late)
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdccRegs.ADCCTL1.bit.INTPULSEPOS = 1;

    // ADC Prescale - Peripheral Clock Enabled in SysCtrl
    AdcaRegs.ADCCTL2.bit.PRESCALE = 6; // Set divider to ADCCLK/4 for A
    AdccRegs.ADCCTL2.bit.PRESCALE = 6; // Set divider to ADCCLK/4 for C

    // ADC Power Up Sequence
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1; // Power up ADCA
    AdccRegs.ADCCTL1.bit.ADCPWDNZ = 1; // Power up ADCC

#endif

#ifdef CPU2
    // Write Configurations - Set resolution and signal mode.
    // Function also performs ADC Calibration
    AdcSetMode(ADC_ADCB, ADC_RESOLUTION_16BIT, ADC_SIGNALMODE_DIFFERENTIAL);
    AdcSetMode(ADC_ADCD, ADC_RESOLUTION_16BIT, ADC_SIGNALMODE_DIFFERENTIAL);

    // Set ADC Interrupt Pulse Positions - 0 -> Occur at end of Acquisition Window
    // 1 -> Occur at EOC (Late)
    AdcbRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdcdRegs.ADCCTL1.bit.INTPULSEPOS = 1;

    // ADC Prescale - Peripheral Clock Enabled in SysCtrl
    AdcbRegs.ADCCTL2.bit.PRESCALE = 6; // Set divider to ADCCLK/4 for B
    AdcdRegs.ADCCTL2.bit.PRESCALE = 6; // Set divider to ADCCLK/4 for D

    // ADC Power Up Sequence
    AdcbRegs.ADCCTL1.bit.ADCPWDNZ = 1; // Power up ADCB
    AdcdRegs.ADCCTL1.bit.ADCPWDNZ = 1; // Power up ADCD

#endif

    // Enable ADC Interrupts
    IER |= M_INT1; // Enable PIE Group 1 for ADC INT1s
    IER |= M_INT10;// Enable PIE Group 10 for other ADC INTs

//    DELAY_US(1000); // Delay for 1ms to allow ADCs time to power up
    for (int i = 0; i < 1000; i++) {}

    EDIS;
}

// Setup the ADCs to be triggered by ePWM events and to interrupt results into a DMA channel
void initializeADCs(void) {

    // Determine minimum acquisition window (in SYSCLKS) based on resolution
    uint16_t acqps = 63; // 320ns

    EALLOW;

#ifdef CPU1
    // ADCSOCx Trigger Select
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 0x5; // ePWM1 SOCA
    AdcaRegs.ADCSOC1CTL.bit.TRIGSEL = 0x6; // ePWM1 SOCB
    AdccRegs.ADCSOC0CTL.bit.TRIGSEL = 0x7; // ePWM2 SOCA

    // ADCSOCx Control - Map SOC to specific channels
    AdcaRegs.ADCSOC0CTL.bit.CHSEL = 0; // ADC A SOC0 will convert on channel 0 to ARES0 - String 2
    AdcaRegs.ADCSOC1CTL.bit.CHSEL = 4; // ADC A SOC1 will convert on channel 4 to ARES1 - String 4
    AdccRegs.ADCSOC0CTL.bit.CHSEL = 2; // ADC C SOC0 will convert on channel 2 to CRES0 - String 6

    // ADCSOCx Control - Set Acquisition Prescale/Sets window in SYSCLK cycles
    // Sample window is acqps + 1 SYSCLK Cycle
    AdcaRegs.ADCSOC0CTL.bit.ACQPS = acqps; // String 2
    AdcaRegs.ADCSOC1CTL.bit.ACQPS = acqps; // String 4
    AdccRegs.ADCSOC0CTL.bit.ACQPS = acqps; // String 6

    // ADCINTx Select EOC Conversion
    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 0;  // ADC A EOC0
    AdcaRegs.ADCINTSEL1N2.bit.INT2SEL = 1;  // ADC A EOC1
    AdccRegs.ADCINTSEL1N2.bit.INT1SEL = 0;  // ADC C EOC0

    // Enable Interrupts and Clear Interrupt Flags for each ADC
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;    // Enable AINT 1 for String 2
    AdcaRegs.ADCINTSEL1N2.bit.INT2E = 1;    // Enable AINT 2 for String 4
    AdccRegs.ADCINTSEL1N2.bit.INT1E = 1;    // Enable CINT 1 for String 6

    AdcaRegs.ADCINTFLGCLR.all = 0x000F;
    AdccRegs.ADCINTFLGCLR.all = 0x000F;

    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;      // Enable PI for ADC A INT 1
    PieCtrlRegs.PIEIER10.bit.INTx2 = 1;     // Enable PI for ADC A INT 2
    PieCtrlRegs.PIEIER1.bit.INTx3 = 1;      // Enable PI for ADC C INT 1

#endif

#ifdef CPU2
    // ADCSOCx Trigger Select
    AdcbRegs.ADCSOC0CTL.bit.TRIGSEL = 0x9; // ePWM3 SOCA
    AdcdRegs.ADCSOC0CTL.bit.TRIGSEL = 0xB; // ePWM4 SOCA
    AdcdRegs.ADCSOC1CTL.bit.TRIGSEL = 0xC; // ePWM4 SOCB

    // ADCSOCx Control - Map SOC to specific channels
    AdcbRegs.ADCSOC0CTL.bit.CHSEL = 0; // ADC B SOC0 will convert on channel 0 to BRES0 - String 5
    AdcdRegs.ADCSOC0CTL.bit.CHSEL = 0; // ADC D SOC0 will convert on channel 0 to DRES0 - String 3
    AdcdRegs.ADCSOC1CTL.bit.CHSEL = 2; // ADC D SOC1 will convert on channel 2 to DRES1 - String 1

    // ADCSOCx Control - Set Acquisition Prescale/Sets window in SYSCLK cycles
    // Sample window is acqps + 1 SYSCLK Cycle
    AdcbRegs.ADCSOC0CTL.bit.ACQPS = acqps; // String 5
    AdcdRegs.ADCSOC0CTL.bit.ACQPS = acqps; // String 3
    AdcdRegs.ADCSOC1CTL.bit.ACQPS = acqps; // String 1


    // ADCINTx Select EOC Conversion
    AdcbRegs.ADCINTSEL1N2.bit.INT1SEL = 0;  // ADC C EOC0
    AdcdRegs.ADCINTSEL1N2.bit.INT1SEL = 0;  // ADC D EOC0
    AdcdRegs.ADCINTSEL1N2.bit.INT2SEL = 1;  // ADC D EOC1

    // Enable Interrupts and Clear Interrupt Flags for each ADC
    AdcbRegs.ADCINTSEL1N2.bit.INT1E = 1;    // Enable BINT 1 for String 5
    AdcdRegs.ADCINTSEL1N2.bit.INT1E = 1;    // Enable DINT 1 for String 3
    AdcdRegs.ADCINTSEL1N2.bit.INT2E = 1;    // Enable DINT 2 for String 1

    AdcdRegs.ADCINTFLGCLR.all = 0x000F;
    AdcbRegs.ADCINTFLGCLR.all = 0x000F;

    PieCtrlRegs.PIEIER1.bit.INTx2 = 1;      // Enable PI for ADC B INT 1
    PieCtrlRegs.PIEIER1.bit.INTx6 = 1;      // Enable PI for ADC D INT 1
    PieCtrlRegs.PIEIER10.bit.INTx14 = 1;    // Enable PI for ADC D INT 2

#endif

    EDIS;
}

// Initialize/Setup ADCs and Configure ADC Settings
void initADC(void) {
    initializeADCs();
    configureADCs();
}

/* ------------------------------------------------------------------------------ */

// End of File
