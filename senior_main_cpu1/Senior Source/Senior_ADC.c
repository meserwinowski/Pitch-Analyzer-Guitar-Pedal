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

// ADCD01, ADCC23, ADCB23, ADCB01, ADCA23, ADCA01
uint16_t adcChannels[6] = {0, 2, 2, 0, 2, 0};

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
    IER |= M_INT1; // Enable INT1 in IER to enable PIE group

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
        acqps = 63; // 320ns
    }

    EALLOW;

    // ADCSOCx Control - Trigger Select to ePWM1 SOCA
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 5;

    // ADCSOCx Control - Map SOC to specific channels
    AdcaRegs.ADCSOC0CTL.bit.CHSEL = channel[5]; // SOC will convert on channel 6 - String 2
//    AdcaRegs.ADCSOC1CTL.bit.CHSEL = channel[4]; // SOC will convert on channel 5
//    AdcbRegs.ADCSOC0CTL.bit.CHSEL = channel[3]; // SOC will convert on channel 4
//    AdcbRegs.ADCSOC1CTL.bit.CHSEL = channel[2]; // SOC will convert on channel 3
//    AdccRegs.ADCSOC0CTL.bit.CHSEL = channel[1]; // SOC will convert on channel 2
//    AdcdRegs.ADCSOC0CTL.bit.CHSEL = channel[0]; // SOC will convert on channel 1

    // ADCSOCx Control - Set Acquisition Prescale/Sets window in SYSCLK cycles
    // Sample window is acqps + 1 SYSCLK Cycle
    AdcaRegs.ADCSOC0CTL.bit.ACQPS = acqps; // String 2
//    AdcaRegs.ADCSOC1CTL.bit.ACQPS = acqps;
//    AdcbRegs.ADCSOC0CTL.bit.ACQPS = acqps;
//    AdcbRegs.ADCSOC1CTL.bit.ACQPS = acqps;
//    AdccRegs.ADCSOC0CTL.bit.ACQPS = acqps;
//    AdcdRegs.ADCSOC0CTL.bit.ACQPS = acqps;

    // ADCINTx INT Flags
//    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 0; // Clear AINT1 flag
//    AdcaRegs.ADCINTSEL1N2.bit.INT2E = 0; // Clear AINT2 flag
//    AdcbRegs.ADCINTSEL1N2.bit.INT1E = 0; // Clear BINT1 flag
//    AdcbRegs.ADCINTSEL1N2.bit.INT2E = 0; // Clear BINT2 flag
//    AdccRegs.ADCINTSEL1N2.bit.INT1E = 0; // Clear CINT1 flag
//    AdcdRegs.ADCINTSEL1N2.bit.INT1E = 0; // Clear DINT1 flag

    // ADC Interrupt SOC Trigger Source (Which ADCINT triggers what SOC)
    AdcaRegs.ADCINTSOCSEL1.bit.SOC0 = 0; // ADCINT1 - String 2
//    AdcaRegs.ADCINTSOCSEL1.bit.SOC1 = 2; // ADCINT2
//    AdcbRegs.ADCINTSOCSEL1.bit.SOC0 = 1; // ADCINT1
//    AdcbRegs.ADCINTSOCSEL1.bit.SOC1 = 2; // ADCINT2
//    AdccRegs.ADCINTSOCSEL1.bit.SOC0 = 1; // ADCINT1
//    AdcdRegs.ADCINTSOCSEL1.bit.SOC0 = 1; // ADCINT1

    // ADCINTx Continuous Mode
    AdcaRegs.ADCINTSEL1N2.bit.INT1CONT = 1; // Enable AINT1 Continuous Mode - String 2
//    AdcaRegs.ADCINTSEL1N2.bit.INT2CONT = 1; // Enable AINT2 Continuous Mode
//    AdcbRegs.ADCINTSEL1N2.bit.INT1CONT = 1; // Enable BINT1 Continuous Mode
//    AdcbRegs.ADCINTSEL1N2.bit.INT2CONT = 1; // Enable BINT2 Continuous Mode
//    AdccRegs.ADCINTSEL1N2.bit.INT1CONT = 1; // Enable CINT1 Continuous Mode
//    AdcdRegs.ADCINTSEL1N2.bit.INT1CONT = 1; // Enable DINT1 Continuous Mode

    // Enable Interrupts and Clear Interrupt Flags for each ADC
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1; // String 2
//    AdcaRegs.ADCINTSEL1N2.bit.INT2E = 1;
//    AdcaRegs.ADCINTFLGCLR.all = 0x000F;
//    AdcbRegs.ADCINTSEL1N2.bit.INT1E = 1;
//    AdcbRegs.ADCINTSEL1N2.bit.INT2E = 1;
//    AdcbRegs.ADCINTFLGCLR.all = 0x000F;
//    AdccRegs.ADCINTSEL1N2.bit.INT1E = 1;
//    AdccRegs.ADCINTFLGCLR.all = 0x000F;
//    AdcdRegs.ADCINTSEL1N2.bit.INT1E = 1;
//    AdcdRegs.ADCINTFLGCLR.all = 0x000F;

    // ADCINTx EOC Source Select
    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 0; // AINT1 triggered by end of SOC0 - String 2
//    AdcaRegs.ADCINTSEL1N2.bit.INT2SEL = 1; // AINT2 triggered by end of SOC1
//    AdcbRegs.ADCINTSEL1N2.bit.INT1SEL = 0; // BINT1 triggered by end of SOC0
//    AdcbRegs.ADCINTSEL1N2.bit.INT2SEL = 1; // BINT2 triggered by end of SOC1
//    AdccRegs.ADCINTSEL1N2.bit.INT1SEL = 0; // CINT1 triggered by end of SOC0
//    AdcdRegs.ADCINTSEL1N2.bit.INT1SEL = 0; // DINT1 triggered by end of SOC0

    EDIS;
}

// Initialize/Setup ADCs and Configure ADC Settings
void initADC(void) {
    setupADCContinuous(adcChannels);
    configureADCs();
}

/* ------------------------------------------------------------------------------ */

// End of File
