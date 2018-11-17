/**
 * spi_driver.c - Receive data and send to SPI buffer to drive APA102C LEDs
 */

#include "F28x_Project.h"

void SpiFIFOInit() {
    // Initialize SPI FIFO Registers
    SpiaRegs.SPIFFTX.all = 0xE040; // SPI FIFO Transmit
    SpiaRegs.SPIFFRX.all = 0x2044; // SPI FIFO Receive
    SpiaRegs.SPIFFCT.all = 0x0;

    // Initialize Core SPI Registers
    InitSpi();
}

//void sendFrame(Uint16 data) {
//    int i;
//    Uint16 rdata;
////    for (i = 0; i < 4; i++) {
//    SpiaRegs.SPITXBUF = (data << 8); // Fill Transmit Buffer
//    while(SpiaRegs.SPIFFRX.bit.RXFFST != 1); // Wait for Receive Buffer to Fill
//    rdata = SpiaRegs.SPIRXBUF; // Read Receive Buffer
////    }
//}

void delay_loop()
{
    long i;
    for (i = 0; i < 2500; i++) {}
}

int main(void)
{

    // Initialize System Control
    InitSysCtrl();

    // Initialize SPI GPIO
    InitSpiGpio();

    // Clear Interrupts
    DINT;

    // Initialize PIE Control Registers
    InitPieCtrl();

    // Disable CPU __interrupts and clear CPU __interrupt flags
    IER = 0x0000;
    IFR = 0x0000;

    // Initialize PIE Vector Tables with pointers to shell ISRs
    InitPieVectTable();

    // Initialize Device Peripherals
    SpiFIFOInit();
    Uint32 data[7] = {0x00000000, // Start Frame
                      0xE1000000, // Red
                      0xE1000000, // Green
                      0xE1000000, // Blue
                      0xE13F003F, // Purpink
                      0xE13F3F3F,
                      0xF0000000}; // End Frame

    int dataLength = 7;
    Uint16 red = 0x00;
    Uint16 green = 0x00;
    Uint16 blue = 0x00;
    Uint32 bright = 0xE1000000;
    Uint16 iter = 0;
    // Send Data
    for(;;) {
        // Send Frame
        int i, j;
        Uint32 rdata = 0;
      Uint16 temp;
        for (i = 0; i < dataLength - 1; i++) {
            rdata = data[i];
            for (j = 0; j < 4; j++) {
                SpiaRegs.SPITXBUF = ((rdata & 0xFF000000) >> 16); // Fill Transmit Buffer
                while(SpiaRegs.SPIFFRX.bit.RXFFST != 1); // Wait for Receive Buffer to Fill
                temp = SpiaRegs.SPIRXBUF; // Read Receive Buffer
                rdata = rdata << 8;
            }
        }
        SpiaRegs.SPITXBUF = (0x11 << 8); // Fill Transmit Buffer
        while(SpiaRegs.SPIFFRX.bit.RXFFST != 1); // Wait for Receive Buffer to Fill
        temp = SpiaRegs.SPIRXBUF; // Read Receive Buffer

        if (iter % 50 == 0) {
            red++;
            blue++;
            green++;
        }
        iter++;

        data[1] = (red % 0x3F);
        data[1] |= bright;
        data[2] = ((green % 0x3F) << 8);
        data[2] |= bright;
        Uint32 b = (blue % 0x3F) << 8;
        data[3] = (b << 8);
        data[3] |= bright;

//        delay_loop();
    }
}
