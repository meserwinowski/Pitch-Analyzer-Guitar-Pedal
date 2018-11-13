/**
 * uart_driver.c - Receive data and send with the SCI module to receive commands over UART
 */

#include "F28x_Project.h"

void delay_loop()
{
    long i;
    for (i = 0; i < 2500; i++) {}
}

// Globals
Uint16 LoopCount;

// Function Prototypes
void scib_echoback_init(void);
void scib_fifo_init(void);
void scib_xmit(int a);
void scib_msg(char *msg);

// Main
void main(void)
{
    Uint16 ReceivedChar;
    char *msg;

// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2837xD_SysCtrl.c file.
   InitSysCtrl();

// Step 2. Initialize GPIO:
// This example function is found in the F2837xD_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
   InitGpio();

// For this example, only init the pins for the SCI-A port.
//  GPIO_SetupPinMux() - Sets the GPxMUX1/2 and GPyMUX1/2 register bits
//  GPIO_SetupPinOptions() - Sets the direction and configuration of the GPIOS
// These functions are found in the F2837xD_Gpio.c file.
   GPIO_SetupPinMux(19, GPIO_MUX_CPU1, 2); // Launchpad SCIB RX
   GPIO_SetupPinOptions(28, GPIO_INPUT, GPIO_PUSHPULL); // Launchpad SCIB TX
   GPIO_SetupPinMux(18, GPIO_MUX_CPU1, 2);
   GPIO_SetupPinOptions(29, GPIO_OUTPUT, GPIO_ASYNC);

// Step 3. Clear all __interrupts and initialize PIE vector table:
// Disable CPU __interrupts
   DINT;

// Initialize PIE control registers to their default state.
// The default state is all PIE __interrupts disabled and flags
// are cleared.
// This function is found in the F2837xD_PieCtrl.c file.
   InitPieCtrl();

// Disable CPU __interrupts and clear all CPU __interrupt flags:
   IER = 0x0000;
   IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the __interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in F2837xD_DefaultIsr.c.
// This function is found in F2837xD_PieVect.c.
   InitPieVectTable();

// Step 4. User specific code:
   LoopCount = 0;

   scib_fifo_init();       // Initialize the SCI FIFO
   scib_echoback_init();   // Initialize SCI for echoback

   msg = "\r\n\n\nHello World!\0";
   scib_msg(msg);

   msg = "\r\nYou will enter a character, and the DSP will echo it back! \n\0";
   scib_msg(msg);

   for(;;)
   {
       msg = "\r\nEnter a character: \0";
       scib_msg(msg);

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
       scib_msg(msg);
       scib_xmit(ReceivedChar);

       LoopCount++;
   }
}

//  scib_echoback_init - Test 1,scib  DLB, 8-bit word, baud rate 0x000F,
//                       default, 1 STOP bit, no parity
void scib_echoback_init()
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
void scib_xmit(int a)
{
    while (ScibRegs.SCIFFTX.bit.TXFFST != 0) {}
    ScibRegs.SCITXBUF.all =a;
}

// scib_msg - Transmit message via scib
void scib_msg(char * msg)
{
    int i;
    i = 0;
    while(msg[i] != '\0')
    {
        scib_xmit(msg[i]);
        i++;
    }
}

// scib_fifo_init - Initialize the SCI FIFO
void scib_fifo_init()
{
    ScibRegs.SCIFFTX.all = 0xE040;
    ScibRegs.SCIFFRX.all = 0x2044;
    ScibRegs.SCIFFCT.all = 0x0;
}

// End of file
