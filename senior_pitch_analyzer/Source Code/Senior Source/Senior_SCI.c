/*
 * Senior_SCI.c
 *
 *  Created on: Nov 16, 2018
 *      Author: meser
 */

#include "F28379D_Senior_Design.h"
#include "F2837xD_device.h"
#include "F2837xD_Examples.h"

extern uint16_t mode;
extern int16_t* scale_pointer;
extern int16_t* scaleLUT;
extern int16_t penta_ionian_LUT;
extern int16_t penta_dorian_LUT;
extern int16_t penta_phrygian_LUT;
extern int16_t penta_mixolydian_LUT;
extern int16_t penta_aeolian_LUT;
extern int16_t dia_ionian_LUT;
extern int16_t dia_dorian_LUT;
extern int16_t dia_phrygian_LUT;
extern int16_t dia_lydian_LUT;
extern int16_t dia_mixolydian_LUT;
extern int16_t dia_aeolian_LUT;
extern int16_t dia_locrian_LUT;
extern uint16_t root_index;
extern uint16_t colors[6][4];
extern float32 fn[7];

#pragma DATA_SECTION(diatonic, "Cla1Data1");
uint_least8_t diatonic[7] = {2, 2, 1, 2, 2, 2, 1};

#pragma DATA_SECTION(pentatonic, "Cla1Data1");
uint_least8_t pentatonic[5] = {2, 2, 3, 2, 3};

/*** Serial Communication Interface ***/
void initSCI(void) {

//    GPIO_SetupPinMux(19, GPIO_MUX_CPU1, 2); // Launchpad SCIB RX
//    GPIO_SetupPinOptions(19, GPIO_INPUT, GPIO_PUSHPULL);
//    GPIO_SetupPinMux(18, GPIO_MUX_CPU1, 2); // Launchpad SCIB TX
//    GPIO_SetupPinOptions(18, GPIO_OUTPUT, GPIO_ASYNC);

    // Set GPIO
    GPIO_SetupPinMux(87, GPIO_MUX_CPU1, 5); // Main Board SCIB RX
    GPIO_SetupPinOptions(87, GPIO_INPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(86, GPIO_MUX_CPU1, 5); // Main Board SCIB TX
    GPIO_SetupPinOptions(86, GPIO_OUTPUT, GPIO_ASYNC);

    initSCIBFIFO();        // Initialize the SCI FIFO
    initSCIB();            // Initialize SCI for Echoback

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

    IER |= M_INT9;                          // Enable Group 9 Interrupts (SCI)
    PieCtrlRegs.PIEIER9.bit.INTx3 = 1;      // Enable SCIB RX Interrupt

    ScibRegs.SCICTL1.bit.SWRESET = 1;       // Relinquish SCI from Reset
}

// initSCIBFIFO - Initialize the SCI FIFO
// Interrupts on 5 Receives, and 1 Transmit
void initSCIBFIFO(void) {
    // SCI FIFO Transmit Register
    ScibRegs.SCIFFTX.bit.SCIRST = 1;        // Release FIFO TX from Reset
    ScibRegs.SCIFFTX.bit.SCIFFENA = 1;      // Enable SCI FIFO TX
    ScibRegs.SCIFFTX.bit.TXFFST = 0x0;      // TX FIFO is Empty
    ScibRegs.SCIFFTX.bit.TXFFINTCLR = 1;    // Clear TX FIFO Interrupt Flag
    ScibRegs.SCIFFTX.bit.TXFFIENA = 1;      // Enable TX FIFO Interrupt

    // SCI FIFO Receive Register
    ScibRegs.SCIFFRX.bit.RXFFST = 0x0;      // RX FIFO is Empty
    ScibRegs.SCIFFRX.bit.RXFFINTCLR = 1;    // Clear RX FIFO Interrupt Flag
    ScibRegs.SCIFFRX.bit.RXFFIENA = 1;      // Enable RX FIFO Interrupt
    ScibRegs.SCIFFRX.bit.RXFFIL = 0x6;      // Receive FIFO Interrupt Level Bits

    // SCI FIFO Control Register
    ScibRegs.SCIFFCT.all = 0x0;

    ScibRegs.SCIFFTX.bit.TXFIFORESET = 1;   // Re-enable TX FIFO Operation
    ScibRegs.SCIFFRX.bit.RXFIFORESET = 1;   // Re-enable RX FIFO Operation
}

// Determine Command from GUI
void determineCommand(void) {
    uint_fast8_t cmd;
    uint_fast8_t data1;
    uint_fast8_t data2;
    uint_fast8_t data3;
    uint_fast8_t data4;
    uint_fast8_t data5;
    uint32_t dataPacket;
    float32 tuning;

    cmd = ScibRegs.SCIRXBUF.all;   //        | CMode | CColor | CTuning
    data1 = ScibRegs.SCIRXBUF.all; // MSByte | Mode  | String | String
    data2 = ScibRegs.SCIRXBUF.all; //        | Scale | Bright | BA4
    data3 = ScibRegs.SCIRXBUF.all; //        | Root  | Red    | BA3
    data4 = ScibRegs.SCIRXBUF.all; //        | XXXX  | Green  | BA2
    data5 = ScibRegs.SCIRXBUF.all; // LSByte | XXXX  | Blue   | BA1

    // Merge data transmission (May be unused)
    dataPacket = data2 << 8 | data3;
    dataPacket = dataPacket << 8 | data4;
    dataPacket = dataPacket << 8 | data5;
    tuning = (float32) dataPacket;

    /*** Determine Command ***/
    if (cmd == CHANGE_MODE) {
        // Real-time Mirror Mode
        if (data1 == MIRROR_MODE) {
            mode = MIRROR_MODE;
        }
        // Learning Mode
        else if (data1 == LEARNING_MODE) {
            mode = LEARNING_MODE;
            // Determine Scale
            if (data2 == 0x01) { // Pentatonic Ionian
                scale_pointer = &penta_ionian_LUT;
            }
            else if (data2 == 0x02) { // Pentatonic Dorian
                scale_pointer = &penta_dorian_LUT;
            }
            else if (data2 == 0x03) { // Pentatonic Phrygian
                scale_pointer = &penta_phrygian_LUT;
            }
            else if (data2 == 0x04) { // Pentatonic Mixolydian
                scale_pointer = &penta_mixolydian_LUT;
            }
            else if (data2 == 0x05) { // Pentatonic Aeolian
                scale_pointer = &penta_aeolian_LUT;
            }
            else if (data2 == 0x06) {
                scale_pointer = &dia_ionian_LUT;
            }
            else if (data2 == 0x07) {
                scale_pointer = &dia_dorian_LUT;
            }
            else if (data2 == 0x08) {
                scale_pointer = &dia_phrygian_LUT;
            }
            else if (data2 == 0x09) {
                scale_pointer = &dia_lydian_LUT;
            }
            else if (data2 == 0x0A) {
                scale_pointer = &dia_mixolydian_LUT;
            }
            else if (data2 == 0x0B) {
                scale_pointer = &dia_aeolian_LUT;
            }
            else if(data2 == 0x0C) {
                scale_pointer = &dia_locrian_LUT;
            }

            // Determine Root
            root_index = data3;
        }
        else if (cmd == TUNING_MODE) {
            mode = TUNING_MODE;
        }
        // Invalid Data
        else {
            SCIB_TX(NACK);
            return;
        }
    }
    // Change Color of String
    else if (cmd == CHANGE_COLOR) {
        colors[data1][0] = data2; // Bright
        colors[data1][1] = data3; // Red
        colors[data1][2] = data4; // Green
        colors[data1][3] = data5; // Blue
    }
    // Change Tuning of String
    else if (cmd == CHANGE_TUNING) {
        fn[data1] = tuning;
    }
    // Invalid Command
    else {
        SCIB_TX(NACK);
        return;
    }

    // Send Acknowledge to GUI
    SCIB_TX(ACK);
}

// SCIB_TX - Transmit a character from the SCIB
void SCIB_TX(uint_fast8_t a) {
    while (ScibRegs.SCIFFTX.bit.TXFFST != 0) {}
    ScibRegs.SCITXBUF.all = a;
}

// SCIB_MSG - Transmit message via SCIB
void SCIB_MSG(char *msg) {
    uint16_t i = 0;
    while(msg[i] != '\0') {
        SCIB_TX(msg[i]);
        i++;
    }
}

/* ------------------------------------------------------------------------------ */

// End of File
