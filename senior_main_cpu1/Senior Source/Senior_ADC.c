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
uint16_t adcChannels[6] = {2, 0, 2, 0, 0, 2};

/*** Analog to Digital Converters ***/
// ConfigureADC - Write and power up configurations for ADCs A/B/C/D
void configureADCs(void) {
    EALLOW;

    // Write Configurations - Set resolution and signal mode.
    // Function also performs ADC Calibration
    AdcSetMode(ADC_ADCA, ADC_RESOLUTION_16BIT, ADC_SIGNALMODE_DIFFERENTIAL);
    AdcSetMode(ADC_ADCB, ADC_RESOLUTION_16BIT, ADC_SIGNALMODE_DIFFERENTIAL);
    AdcSetMode(ADC_ADCC, ADC_RESOLUTION_16BIT, ADC_SIGNALMODE_DIFFERENTIAL);
    AdcSetMode(ADC_ADCD, ADC_RESOLUTION_16BIT, ADC_SIGNALMODE_DIFFERENTIAL);

    // Set ADC Interrupt Pulse Positions - 0 -> Occur at end of Acquisition Window
    // 1 -> Occur at EOC (Late)
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdcbRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdccRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdcdRegs.ADCCTL1.bit.INTPULSEPOS = 1;

    // ADC Prescale - Peripheral Clock Enabled in SysCtrl
    AdcaRegs.ADCCTL2.bit.PRESCALE = 6; // Set divider to ADCCLK/4 for A
    AdcbRegs.ADCCTL2.bit.PRESCALE = 6; // Set divider to ADCCLK/4 for B
    AdccRegs.ADCCTL2.bit.PRESCALE = 6; // Set divider to ADCCLK/4 for C
    AdcdRegs.ADCCTL2.bit.PRESCALE = 6; // Set divider to ADCCLK/4 for D

    // Enable ADC Interrupts
    IER |= M_INT1; // Enable PIE Group 1 for ADC INT1s
    IER |= M_INT10;// Enable PIE Group 10 for other ADC INTs

    // ADC Power Up Sequence
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1; // Power up ADCA
    AdcbRegs.ADCCTL1.bit.ADCPWDNZ = 1; // Power up ADCB
    AdccRegs.ADCCTL1.bit.ADCPWDNZ = 1; // Power up ADCC
    AdcdRegs.ADCCTL1.bit.ADCPWDNZ = 1; // Power up ADCD

    DELAY_US(1000); // Delay for 1ms to allow ADCs time to power up

    EDIS;
}

// Setup the ADC to continuously convert
void setupADCContinuous(Uint16* channel) {

    // Determine minimum acquisition window (in SYSCLKS) based on resolution
    uint16_t acqps;
    if (AdcaRegs.ADCCTL2.bit.RESOLUTION == ADC_RESOLUTION_12BIT) {
        acqps = 14; // 75ns
    }
    else // Resolution is 16-bit
    {
        acqps = 315; // 320ns
    }

    EALLOW;

    // ADCSOCx Control
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 0x5; // Trigger Select to ePWM1 SOCA
    AdcaRegs.ADCSOC4CTL.bit.TRIGSEL = 0x7; // Trigger Select to ePWM2 SOCA
    AdccRegs.ADCSOC2CTL.bit.TRIGSEL = 0x9; // Trigger Select to ePWM3 SOCA

    // ADCSOCx Control - Map SOC to specific channels
    // ADC D SOC1 will convert on channel 5 - String 1
    AdcaRegs.ADCSOC0CTL.bit.CHSEL = channel[4]; // ADC A SOC0 will convert on channel 4 - String 2
    // ADC D SOC0 will convert on channel 3 - String 3
    AdcaRegs.ADCSOC4CTL.bit.CHSEL = 4; // ADC A SOC2 will convert on channel 2 - String 4
    // ADC B SOC0 will convert on channel 1 - String 5
    AdccRegs.ADCSOC2CTL.bit.CHSEL = 2; // ADC C SOC2 will convert on channel 0 - String 6

    // ADCSOCx Control - Set Acquisition Prescale/Sets window in SYSCLK cycles
    // Sample window is acqps + 1 SYSCLK Cycle
    // String 1
    AdcaRegs.ADCSOC0CTL.bit.ACQPS = acqps; // String 2
    // String 3
    AdcaRegs.ADCSOC4CTL.bit.ACQPS = acqps; // String 4
    // String 5
    AdccRegs.ADCSOC2CTL.bit.ACQPS = acqps; // String 6

    // ADCINTx Continuous Mode
//    AdcaRegs.ADCINTSEL1N2.bit.INT1CONT = 1; // Enable AINT1 Continuous Mode - String 2
//    AdcaRegs.ADCINTSEL1N2.bit.INT2CONT = 1; // Enable AINT2 Continuous Mode - String 4
//    AdccRegs.ADCINTSEL1N2.bit.INT2CONT = 1; // Enable AINT2 Continuous Mode - String 6

    // ADCINTx Select EOC Conversion
    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 0; // ADC A EOC0
    AdcaRegs.ADCINTSEL1N2.bit.INT2SEL = 4; // ADC A EOC4
    AdccRegs.ADCINTSEL1N2.bit.INT2SEL = 2; // ADC C EOC2

    // Enable Interrupts and Clear Interrupt Flags for each ADC
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1; // String 2
    AdcaRegs.ADCINTSEL1N2.bit.INT2E = 1; // String 4
    AdccRegs.ADCINTSEL1N2.bit.INT2E = 1; // String 6

    AdcaRegs.ADCINTFLGCLR.all = 0x000F;
    AdccRegs.ADCINTFLGCLR.all = 0x000F;

    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;
    PieCtrlRegs.PIEIER10.bit.INTx2 = 1;
    PieCtrlRegs.PIEIER10.bit.INTx10 = 1;

    EDIS;
}

// Initialize/Setup ADCs and Configure ADC Settings
void initADC(void) {
    setupADCContinuous(adcChannels);
    configureADCs();
}

/* ------------------------------------------------------------------------------ */

// End of File
