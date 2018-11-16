/**********************************************************************
* File: Main_9.c -- Solution File for Lab 9
* Devices: TMS320F28x7x
* Author: C2000 Technical Training, Texas Instruments
**********************************************************************/

#include "Lab.h"                        // Main include file
#include "F28x_Project.h"

#pragma DATA_SECTION(GPIO34_count, "Cla1Data1");
Uint16 GPIO34_count = 0;

#pragma DATA_SECTION(rdata, "Cla1Data1");
Uint32 rdata = 0;

#pragma DATA_SECTION(temp, "Cla1Data1");
Uint16 temp = 0;

#pragma DATA_SECTION(i, "Cla1Data1");
Uint16 i = 0;
#pragma DATA_SECTION(j, "Cla1Data1");
Uint16 j = 0;

void SpiFIFOInit() {
    // Initialize SPI FIFO Registers
    SpiaRegs.SPIFFTX.all = 0xE040; // SPI FIFO Transmit
    SpiaRegs.SPIFFRX.all = 0x2044; // SPI FIFO Receive
    SpiaRegs.SPIFFCT.all = 0x0;

    // Initialize Core SPI Registers
    InitSpi();
}

/**********************************************************************
* Function: main()
*
* Description: Main function for C28x workshop labs
**********************************************************************/
void main(void)
{
//--- CPU Initialization
	InitSysCtrl();						// Initialize the CPU (FILE: SysCtrl.c)
	InitGpio();							// Initialize the shared GPIO pins (FILE: Gpio.c) and initializes GPIO34 for debug
	InitPieCtrl();						// Initialize and enable the PIE (FILE: PieCtrl.c)
	InitWatchdog();						// Initialize the Watchdog Timer (FILE: WatchDog.c)

    // Initialize SPI GPIO
    InitSpiGpio();
    SpiFIFOInit();

//--- Peripheral Initialization
	InitEPwm();							// Initialize the EPwm (FILE: EPwm.c)
	IER |= M_INT3;
	PieCtrlRegs.PIEIER3.bit.INTx2 = 1;
	InitCla();							// Initialize the Cla (FILE: Cla.c) 

//--- Enable global interrupts
//	asm(" CLRC INTM, DBGM");			// Enable global interrupts and realtime debug
    // Enable global Interrupts and higher priority real-time debug events
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global real-time interrupt DBGM

//--- Main Loop
	while(1)							// endless loop - wait for an interrupt
	{
	    //Force SW triggered CLA task
//	    asm("  IACK  #0x0001");                // IACK - CLA task force instruction - Software Trigger Task 1
        asm("  RPT #3 || NOP");                // Wait at least 4 cycles
//        EPwm2Regs.ETFRC.bit.INT = 1;
        while(Cla1Regs.MIRUN.bit.INT1 == 1);   // Loop until task completes         - Software Poll CLA Task 1 Run Flag

	    if(GPIO34_count> 50000)                  // Toggle slowly to see the LED blink
        {
            GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;  // Toggle the pin
            GPIO34_count = 0;                       // Reset the counter
            DelayUs(50000);
        }
	}


} //end of main()


/*** end of file *****************************************************/
