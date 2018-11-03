MEMORY
{
PAGE 0 : /* Program Memory */
   /* BEGIN is used for the "boot to SARAM" bootloader mode   */
   BEGIN		: origin = 0x000000, length = 0x000002
   BOOT_RSVD	: origin = 0x000002, length = 0x000120     /* Part of M0, BOOT rom will use this for stack */
   RAMM0		: origin = 0x000122, length = 0x0002DE
   RAMM1		: origin = 0x000400, length = 0x000400     /* on-chip RAM block M1 */
   RAMLS0		: origin = 0x008000, length = 0x000800
   RAMLS1		: origin = 0x008800, length = 0x000800
   RAMLS2		: origin = 0x009000, length = 0x000800
   RAMLS3		: origin = 0x009800, length = 0x000800
   RAMLS4		: origin = 0x00A000, length = 0x000800
   RAMLS5		: origin = 0x00A800, length = 0x000800
   RAMD0		: origin = 0x00B000, length = 0x000800
   RAMD1		: origin = 0x00B800, length = 0x000800
   RESET		: origin = 0x3FFFC0, length = 0x000002

   /* Flash sectors */
   FLASHA       : origin = 0x080002, length = 0x001FFE	/* on-chip Flash */
   FLASHB       : origin = 0x082000, length = 0x008000	/* on-chip Flash */
   //FLASHC       : origin = 0x084000, length = 0x002000	/* on-chip Flash */
   //FLASHD       : origin = 0x086000, length = 0x002000	/* on-chip Flash */
   //FLASHE       : origin = 0x088000, length = 0x008000	/* on-chip Flash */
   FLASHF       : origin = 0x090000, length = 0x008000	/* on-chip Flash */
   FLASHG       : origin = 0x098000, length = 0x008000	/* on-chip Flash */
   FLASHH       : origin = 0x0A0000, length = 0x008000	/* on-chip Flash */
   FLASHI       : origin = 0x0A8000, length = 0x008000	/* on-chip Flash */
   FLASHJ       : origin = 0x0B0000, length = 0x008000	/* on-chip Flash */
   FLASHK       : origin = 0x0B8000, length = 0x002000	/* on-chip Flash */
   FLASHL       : origin = 0x0BA000, length = 0x002000	/* on-chip Flash */
   FLASHM       : origin = 0x0BC000, length = 0x002000	/* on-chip Flash */
   FLASHN       : origin = 0x0BE000, length = 0x002000	/* on-chip Flash */

PAGE 1 : /* Data Memory */

   RAMGS0      : origin = 0x00C000, length = 0x001000
   RAMGS1      : origin = 0x00D000, length = 0x001000
   RAMGS2      : origin = 0x00E000, length = 0x001000
   RAMGS3      : origin = 0x00F000, length = 0x001000
   RAMGS4      : origin = 0x010000, length = 0x001000
   RAMGS5      : origin = 0x011000, length = 0x001000
   RAMGS6      : origin = 0x012000, length = 0x001000
   RAMGS7      : origin = 0x013000, length = 0x001000
   RAMGS8      : origin = 0x014000, length = 0x001000
   RAMGS9      : origin = 0x015000, length = 0x001000
   RAMGS10     : origin = 0x016000, length = 0x001000
   RAMGS11     : origin = 0x017000, length = 0x001000
   RAMGS12     : origin = 0x018000, length = 0x001000     /* Only Available on F28379D, F28377D, F28375D devices. Remove line on other devices. */
   RAMGS13     : origin = 0x019000, length = 0x001000     /* Only Available on F28379D, F28377D, F28375D devices. Remove line on other devices. */
   RAMGS14     : origin = 0x01A000, length = 0x001000     /* Only Available on F28379D, F28377D, F28375D devices. Remove line on other devices. */
   RAMGS15     : origin = 0x01B000, length = 0x001000     /* Only Available on F28379D, F28377D, F28375D devices. Remove line on other devices. */

   CPU2TOCPU1RAM   : origin = 0x03F800, length = 0x000400
   CPU1TOCPU2RAM   : origin = 0x03FC00, length = 0x000400

   CANA_MSG_RAM    : origin = 0x049000, length = 0x000800
   CANB_MSG_RAM    : origin = 0x04B000, length = 0x000800
}

--define RFFT_ALIGNMENT=256
#if !defined(RFFT_ALIGNMENT)
#error define RFFT_ALIGNMENT under C2000 Linker -> Advanced Options -> Command File Preprocessing -> --define
#endif

SECTIONS
{
   /* The ramfunc attribute is a TI compiler feature which allows code to easily specify
    that a function will be placed in and executed out of RAM. This allows the compiler to
    optimize functions for RAM execution, as well as to automatically copy functions to
    RAM on flash-based devices. */
   ramfuncs         : > RAMM0      PAGE = 0

   /* Allocate Program Areas */
   codestart        : > BEGIN,     PAGE = 0
   //.cinit			: > FLASHB,	   PAGE = 0 // Tables which initialize global variables
   .cinit			: > RAMGS14,   PAGE = 1
   .pinit           : > RAMM0,     PAGE = 0 // Table of C++ contructors called at startup
   .text            : >>RAMD0 | RAMD1 |  RAMLS0 | RAMLS1 | RAMLS2 | RAMLS3 | RAMLS4,   PAGE = 0 // Executable Code

   /* Uninitialized Sections */
   .stack           : > RAMM1,     PAGE = 0 // System Stack
   //.ebss            : >>FLASHF | FLASHG,    PAGE = 0 // Global Variables
   .ebss			: > RAMGS15,   PAGE = 1
   .esysmem         : > RAMLS5,    PAGE = 0 // Malloc Heap

   /* Initialized Sections */
   .switch          : > RAMM0,     PAGE = 0 // Jump Tables for certain switch statements
   .econst          : > RAMLS5,    PAGE = 0 // Initialized Global Variables

   /* Reset - Dummy Sections */
   .reset           : > RESET,     PAGE = 0, TYPE = DSECT /* not used, */

#ifdef __TI_COMPILER_VERSION__
   #if __TI_COMPILER_VERSION__ >= 15009000
   .TI.ramfunc 		: {} > RAMM0,  PAGE = 0
   #else
   ramfuncs    		: > RAMM0,     PAGE = 0
   #endif
#endif

   /* The following section definitions are required when using the IPC API Drivers */
    GROUP : > CPU1TOCPU2RAM, PAGE = 1
    {
        PUTBUFFER
        PUTWRITEIDX
        GETREADIDX
    }

    GROUP : > CPU2TOCPU1RAM, PAGE = 1
    {
        GETBUFFER :    TYPE = DSECT
        GETWRITEIDX :  TYPE = DSECT
        PUTREADIDX :   TYPE = DSECT
    }

   RFFTdata1        : > RAMGS0,		PAGE = 1, ALIGN = RFFT_ALIGNMENT
   RFFTdata2        : > RAMGS0,		PAGE = 1
   RFFTdata3        : > RAMGS1,		PAGE = 1
   RFFTdata4        : > RAMGS2,		PAGE = 1
   RFFTdata5		: > RAMGS3,		PAGE = 1
   FPUmathTables    : > RAMGS4,     PAGE = 1

   DMABuffer1       : > RAMGS4,		PAGE = 1
   CircBuff1		: > RAMGS10,	PAGE = 1
   CircBuff2		: > RAMGS11,	PAGE = 1
   CircBuff3		: > RAMGS12,	PAGE = 1
}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
