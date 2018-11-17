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

    Uint16 ReceivedChar;
    char *msg;

// Step 4. User specific code:
    LoopCount = 0;

    initSCIBFIFO();       // Initialize the SCI FIFO
    initSCIB();   // Initialize SCI for echoback

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

//  scib_echoback_init - Test 1,scib  DLB, 8-bit word, baud rate 0x000F,
//                       default, 1 STOP bit, no parity
void initSCIB(void)
{
    //
    // Note: Clocks were turned on to the scib peripheral
    // in the InitSysCtrl() function
    //

    ScibRegs.SCICCR.all = 0x0007;   // 1 stop bit,  No loopback
                                    // No parity,8 char bits,
                                    // async mode, idle-line protocol
    ScibRegs.SCICTL1.all = 0x0003;  // enable TX, RX, internal SCICLK,
                                    // Disable RX ERR, SLEEP, TXWAKE
    ScibRegs.SCICTL2.all = 0x0003;
    ScibRegs.SCICTL2.bit.TXINTENA = 1;
    ScibRegs.SCICTL2.bit.RXBKINTENA = 1;

    //
    // scib at 9600 baud
    // @LSPCLK = 50 MHz (200 MHz SYSCLK) HBAUD = 0x02 and LBAUD = 0x8B.
    // @LSPCLK = 30 MHz (120 MHz SYSCLK) HBAUD = 0x01 and LBAUD = 0x86.
    //
    ScibRegs.SCIHBAUD.all = 0x0002;
    ScibRegs.SCILBAUD.all = 0x008B;

    ScibRegs.SCICTL1.all = 0x0023;  // Relinquish SCI from Reset
}

// scib_xmit - Transmit a character from the SCI
void SCIB_TX(int a)
{
    while (ScibRegs.SCIFFTX.bit.TXFFST != 0) {}
    ScibRegs.SCITXBUF.all =a;
}

// scib_msg - Transmit message via scib
void SCIB_MSG(char *msg)
{
    int i;
    i = 0;
    while(msg[i] != '\0')
    {
        SCIB_TX(msg[i]);
        i++;
    }
}

// scib_fifo_init - Initialize the SCI FIFO
void initSCIBFIFO(void)
{
    ScibRegs.SCIFFTX.all = 0xE040;
    ScibRegs.SCIFFRX.all = 0x2044;
    ScibRegs.SCIFFCT.all = 0x0;
}
/* ------------------------------------------------------------------------------ */

// End of File
