//###########################################################################
//
// FILE:   F2837xD_Spi.c
//
// TITLE:  F2837xD SPI Initialization & Support Functions.
//
//###########################################################################
// $TI Release: F2837xD Support Library v200 $
// $Release Date: Tue Jun 21 13:00:02 CDT 2016 $
// $Copyright: Copyright (C) 2013-2016 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

//
// Included Files
//
#include "F2837xD_device.h"
#include "F2837xD_Examples.h"

// Pragma to Calculate Baud Rate
// BRR: 7-bit Baud Rate Register
// SPI CLK Frequency = 300kHz
// LSP CLK Frequency = CPU Frequency / 4 (Default)
// BRR               = (LSPCLK / SPICLK) - 1
#if CPU_FRQ_200MHZ
#define SPI_BRR     ((200E6 / 4) / 1E6) - 1
#endif

// InitSpi - Initialize core SPI registers
void InitSpi() {
    // Initialize SPI-A
    SpiaRegs.SPICCR.bit.SPISWRESET = 0; // Set RESET low before config changes
    SpiaRegs.SPICCR.bit.CLKPOLARITY = 1; // Clock Polarity (0 -> Rising, 1 -> Falling)
    SpiaRegs.SPICCR.bit.SPICHAR = (8 - 1); // 16-Bit Character
    SpiaRegs.SPICCR.bit.SPILBK = 1; // Enable Loopback

    SpiaRegs.SPICTL.bit.MASTER_SLAVE = 1; // Enable Master (0 -> Slave, 1 -> Master)
    SpiaRegs.SPICTL.bit.TALK = 1; // Enable Transmission (Talk)
    SpiaRegs.SPICTL.bit.CLK_PHASE = 0; // Clock Phase (0 -> Slave, 1 -> Master)
    SpiaRegs.SPICTL.bit.SPIINTENA = 0; // SPI Interrupts are Disabled

    // Set Baud Rate
    SpiaRegs.SPIBRR.bit.SPI_BIT_RATE = (int) SPI_BRR;

    // Set FREE Bit - Halting on breakpoint will not stop SPI
    SpiaRegs.SPIPRI.bit.FREE = 1;

    // Release SPI from RESET
    SpiaRegs.SPICCR.bit.SPISWRESET = 1;
}

//
// InitSpiGpio - This function initializes GPIO pins to function as SPI pins.
//               Each GPIO pin can be configured as a GPIO pin or up to 3
//               different peripheral functional pins. By default all pins come
//               up as GPIO inputs after reset.
//
//               Caution:
//               For each SPI peripheral
//               Only one GPIO pin should be enabled for SPISOMO operation.
//               Only one GPIO pin should be enabled for SPISOMI operation.
//               Only one GPIO pin should be enabled for SPICLK  operation.
//               Only one GPIO pin should be enabled for SPISTE  operation.
//               Comment out other unwanted lines.
//

void InitSpiGpio()
{
   InitSpiaGpio();
}

//
// InitSpiaGpio - Initialize SPIA GPIOs
//
void InitSpiaGpio()
{
    EALLOW;

    // Configure SPI-A GPIO MUX for High-Speed
    GpioCtrlRegs.GPBGMUX2.bit.GPIO58 = 3; // Configure GPIO58 MUX as SPI SIMO A
    GpioCtrlRegs.GPBGMUX2.bit.GPIO59 = 3; // Configure GPIO59 MUX as SPI SOMI A
    GpioCtrlRegs.GPBGMUX2.bit.GPIO60 = 3; // Configure GPIO60 MUX as SPI CLK A
    GpioCtrlRegs.GPBGMUX2.bit.GPIO61 = 3; // Configure GPIO61 MUX as SPI CS A/SPISTEA

    //
    // Configure SPI-A pins using GPIO Registers
    //
    // This specifies which of the possible GPIO pins will be SPI functional
    // pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPBMUX2.bit.GPIO58 = 3; // Configure GPIO58 as SPI SIMO A
    GpioCtrlRegs.GPBMUX2.bit.GPIO59 = 3; // Configure GPIO58 as SPI SOMI A
    GpioCtrlRegs.GPBMUX2.bit.GPIO60 = 3; // Configure GPIO58 as SPI CLK A
    GpioCtrlRegs.GPBMUX2.bit.GPIO61 = 3; // Configure GPIO58 as SPI CS A

    //
    // Set qualification for selected pins to asynch only
    //
    // This will select asynch (no qualification) for the selected pins.
    // Comment out other unwanted lines.
    //

    GpioCtrlRegs.GPBQSEL2.bit.GPIO58 = 3; // Asynch output GPIO58 SPI SIMO A
    GpioCtrlRegs.GPBQSEL2.bit.GPIO59 = 3; // Asynch output GPIO59 SPI SOMI A
    GpioCtrlRegs.GPBQSEL2.bit.GPIO60 = 3; // Asynch output GPIO60 SPI CLK A
    GpioCtrlRegs.GPBQSEL2.bit.GPIO61 = 3; // Asynch output GPIO61 SPI CS A

    //
    // Enable internal pull-up for the selected pins
    //
    // Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //

    GpioCtrlRegs.GPBPUD.bit.GPIO58 = 0; // Enable internal pull-up for GPIO58
    GpioCtrlRegs.GPBPUD.bit.GPIO59 = 0; // Enable internal pull-up for GPIO59
    GpioCtrlRegs.GPBPUD.bit.GPIO60 = 0; // Enable internal pull-up for GPIO60
    GpioCtrlRegs.GPBPUD.bit.GPIO61 = 0; // Enable internal pull-up for GPIO61

    EDIS;
}

//
// End of file
//
