/**********************************************************************
* File: Main_9.c -- Solution File for Lab 9
* Devices: TMS320F28x7x
* Author: C2000 Technical Training, Texas Instruments
**********************************************************************/

#include "Lab.h"                        // Main include file
#include "F28x_Project.h"

#pragma DATA_SECTION(GPIO34_count, "Cla1Data1");
Uint16 GPIO34_count = 0;

#pragma DATA_SECTION(data, "Cla1Data1");
Uint32 data[7] = {0x00000000, // Start Frame
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
	InitGpio();							// Initialize the shared GPIO pins (FILE: Gpio.c)
	//initialize GPIO34 for debug
	EALLOW;
	GpioCtrlRegs.GPBGMUX1.bit.GPIO34 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1; // 1=OUTput, 0=INput
    GpioDataRegs.GPBSET.bit.GPIO34 = 1; // Set High initially
    GpioCtrlRegs.GPBCSEL1.bit.GPIO34 = 0;   // 0=CPU1, 1=CPU1.CLA1, 2=CPU2, 3=CPU2.CLA
    EDIS;

	InitPieCtrl();						// Initialize and enable the PIE (FILE: PieCtrl.c)
	InitWatchdog();						// Initialize the Watchdog Timer (FILE: WatchDog.c)

//--- Peripheral Initialization
	InitEPwm();							// Initialize the EPwm (FILE: EPwm.c)
	IER |= M_INT3;
	PieCtrlRegs.PIEIER3.bit.INTx2 = 1;
	InitCla();							// Initialize the Cla (FILE: Cla.c)

// Initialize SPI GPIO
    InitSpiGpio();
    SpiFIFOInit();

//--- Enable global interrupts
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global real-time interrupt DBGM

//--- Main Loop
	while(1)							// endless loop - wait for an interrupt
	{
	    if(GPIO34_count> 5000)                  // Toggle slowly to see the LED blink
        {
            GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;  // Toggle the pin
            GPIO34_count = 0;                       // Reset the counter
        }
	}


} //end of main()


/*** end of file *****************************************************/
