/*
 * Senior_SCI.c
 *
 *  Created on: Nov 16, 2018
 *      Author: meser
 */


#include "F28379D_Senior_Design.h"
#include "F2837xD_device.h"
#include "F2837xD_Examples.h"

// Globals
Uint16 LoopCount;

/*** Serial Communication Interface ***/
void initSCI(void) {

    GPIO_SetupPinMux(19, GPIO_MUX_CPU1, 2); // Launchpad SCIB RX
    GPIO_SetupPinOptions(19, GPIO_INPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(18, GPIO_MUX_CPU1, 2); // Launchpad SCIB TX
    GPIO_SetupPinOptions(18, GPIO_OUTPUT, GPIO_ASYNC);

    Uint16 ReceivedChar;
    char *msg;

// Step 4. User specific code:
    LoopCount = 0;

    initSCIBFIFO();        // Initialize the SCI FIFO
    initSCIB();            // Initialize SCI for Echoback

    msg = "\r\n\n\nHello World!\0";
    SCIB_MSG(msg);

    msg = "\r\nYou will enter a character, and the DSP will echo it back! \n\0";
    SCIB_MSG(msg);

    for(;;) {
        msg = "\r\nEnter a character: \0";
        SCIB_MSG(msg);

       //
       // Wait for inc character
       //
        while(ScibRegs.SCIFFRX.bit.RXFFST == 0) { } // wait for empty state

       //
       // Get character
       //
        ReceivedChar = ScibRegs.SCIRXBUF.all;

       //
       // Echo character back
       //
        msg = "  You sent: \0";
        SCIB_MSG(msg);
        SCIB_TX(ReceivedChar);

        LoopCount++;
    }
}

// SCIB DLB, 8-bit word, baud rate 0x000F, default, 1 STOP bit, no parity
void initSCIB(void) {
    // Note: Clocks were turned on for the SCIB peripheral
    // in the InitSysCtrl() function

    // SCI Communications Control Register
    ScibRegs.SCICCR.bit.STOPBITS = 0;       // 1 Stop Bit
    ScibRegs.SCICCR.bit.PARITY = 0;         // Odd Parity (No Parity)
    ScibRegs.SCICCR.bit.PARITYENA = 0;      // Party Disabled
    ScibRegs.SCICCR.bit.LOOPBKENA = 0;      // Loopback Test Mode Disabled
    ScibRegs.SCICCR.bit.ADDRIDLE_MODE = 0;  // Idle-line mode protocol (No extra bit)
    ScibRegs.SCICCR.bit.SCICHAR = 0x7;      // SCICHAR Length = 8-bits

    // SCI Control Register 1
    ScibRegs.SCICTL1.bit.RXERRINTENA = 0;   // Disable RX Error Interrupt
    ScibRegs.SCICTL1.bit.SWRESET = 0;       // Initialize SCI State Machine and Flags to reset
    ScibRegs.SCICTL1.bit.TXWAKE = 0;        // Disable TXWAKE
    ScibRegs.SCICTL1.bit.SLEEP = 0;         // Disable SCI Sleep
    ScibRegs.SCICTL1.bit.TXENA = 1;         // Enable SCI Transmitter (TX)
    ScibRegs.SCICTL1.bit.RXENA = 1;         // Enable SCI Receiver (RX)

    // SCI Control Register 2
    ScibRegs.SCICTL2.bit.RXBKINTENA = 1;    // Enable Receiver-buffer/break Interrupt
    ScibRegs.SCICTL2.bit.TXINTENA = 1;      // Enable TXBUF Interrupt (Ready for next character)

    // SCI Baud Rate - SCI Async Baud -> BRR = LSPCLK / (SCI Sync Baud * 8) - 1
    // SCIB at 9600 Baud
    // @LSPCLK = 50 MHz (200 MHz SYSCLK) HBAUD = 0x02 and LBAUD = 0x8B
    ScibRegs.SCIHBAUD.bit.BAUD = 0x02;      // MS Byte
    ScibRegs.SCILBAUD.bit.BAUD = 0x8B;      // LS Byte

    ScibRegs.SCICTL1.bit.SWRESET = 1;       // Relinquish SCI from Reset
}

// SCIB_TX - Transmit a character from the SCIB
void SCIB_TX(int a) {
    while (ScibRegs.SCIFFTX.bit.TXFFST != 0) {}
    ScibRegs.SCITXBUF.all = a;
}

// SCIB_MSG - Transmit message via SCIB
void SCIB_MSG(char *msg) {
    int i;
    i = 0;
    while(msg[i] != '\0') {
        SCIB_TX(msg[i]);
        i++;
    }
}

// scib_fifo_init - Initialize the SCI FIFO
void initSCIBFIFO(void) {
    // SCI FIFO Transmit Register
//    ScibRegs.SCIFFTX.all = 0xE040;
    ScibRegs.SCIFFTX.bit.SCIFFENA = 1;      // Enable SCI FIFO TX
    ScibRegs.SCIFFTX.bit.TXFIFORESET = 1;   // Re-enable TX FIFO Operation
    ScibRegs.SCIFFTX.bit.TXFFST = 0x0;      // TX FIFO is Empty
    ScibRegs.SCIFFTX.bit.TXFFINTCLR = 1;    // Clear TX FIFO Interrupt Flag
    ScibRegs.SCIFFTX.bit.SCIRST = 1;        // Release FIFO TX from Reset

    // SCI FIFO Receive Register
//    ScibRegs.SCIFFRX.all = 0x2044;
    ScibRegs.SCIFFRX.bit.RXFIFORESET = 1;   // Re-enable RX FIFO Operation
    ScibRegs.SCIFFRX.bit.RXFFST = 0x0;      // RX FIFO is Empty
    ScibRegs.SCIFFRX.bit.RXFFINTCLR = 1;    // Clear RX FIFO Interrupt Flag
    ScibRegs.SCIFFRX.bit.RXFFIL = 0x4;      // Receive FIFO Interrupt Level Bits

    // SCI FIFO Control Register
    ScibRegs.SCIFFCT.all = 0x0;
}

/* ------------------------------------------------------------------------------ */

// End of File
