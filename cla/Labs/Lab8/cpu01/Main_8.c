/**********************************************************************
* File: Main_8.c -- File for Lab 8
* Devices: TMS320F28x7x
* Author: C2000 Technical Training, Texas Instruments
**********************************************************************/

#include "Lab.h"                        // Main include file

//--- Global Variables
Uint16 DEBUG_TOGGLE = 1;                // Used for realtime mode investigation test
Uint16 SINE_ENABLE = 0;                 // Used for DAC waveform generation
Uint16 PWM_MODULATE = 0;                // Used for PWM modulation
Uint16 AdcBuf[ADC_BUF_LEN];             // ADC buffer allocation
Uint16 DacOffset;                       // DAC offset
Uint16 DacOutput;                       // DAC output
Uint32 PwmDuty;                         // measured PWM duty cycle
Uint32 PwmPeriod;                       // measured PWM period

#pragma DATA_SECTION(AdcBufRaw, "dmaMemBufs");
Uint16 AdcBufRaw[2*ADC_BUF_LEN];			// ADC raw data buffer allocation


/**********************************************************************
* Function: main()
*
* Description: Main function for C28x workshop labs
**********************************************************************/
void main(void)
{
//--- CPU Initialization
	InitSysCtrl();						// Initialize the CPU (FILE: SysCtrl.c)
	InitGpio();							// Initialize the shared GPIO pins (FILE: Gpio.c)
	InitXbar();							// Initialize the input, output & ePWM X-Bar (FILE: Xbar.c)
	InitPieCtrl();						// Initialize and enable the PIE (FILE: PieCtrl.c)
	InitWatchdog();						// Initialize the Watchdog Timer (FILE: WatchDog.c)

//--- Peripheral Initialization
	InitAdca();							// Initialize the ADC-A (FILE: Adc.c)
	InitDacb();                         // Initialize the DAC-B (File: Dac.c)
	InitEPwm();							// Initialize the EPwm (FILE: EPwm.c) 
	InitECap();							// Initialize the ECap (FILE: ECap.c) 
                                        // Initialize the DMA (FILE: Dma.c)

//--- Enable global interrupts
	asm(" CLRC INTM, DBGM");			// Enable global interrupts and realtime debug

//--- Main Loop
	while(1)							// endless loop - wait for an interrupt
	{
		asm(" NOP");
	}


} //end of main()


/*** end of file *****************************************************/
