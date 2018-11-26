--define RFFT_ALIGNMENT=2048
#if !defined(RFFT_ALIGNMENT)
#error define RFFT_ALIGNMENT under C2000 Linker -> Advanced Options -> Command File Preprocessing -> --define
#endif

MEMORY
{
PAGE 0: /*** Program Memory ***/

   /* Memory (RAM/FLASH) blocks can be moved to PAGE1 for data allocation */
   /* BEGIN is used for the "boot to Flash" bootloader mode   */
   BEGIN           	: origin = 0x080000, length = 0x000002
   BOOT_RSVD        : origin = 0x000002, length = 0x000120     /* Part of M0, BOOT rom will use this for stack */

   RAMM0           	: origin = 0x000122, length = 0x0002DE
   RAMM1            : origin = 0x000400, length = 0x000400     /* on-chip RAM block M1 */

   CLA1_MSGRAML 	: origin = 0x001480, length = 0x000080  /* CLA to CPU Message RAM, DCSM secure */
   CLA1_MSGRAMH 	: origin = 0x001500, length = 0x000080  /* CPU to CLA Message RAM, DCSM secure */

   RAMD0           	: origin = 0x00B000, length = 0x000800
   RAMD1            : origin = 0x00B800, length = 0x000800

   /*** Local Shared Memory ***/
   RAMLS0          	: origin = 0x008000, length = 0x000800
   RAMLS1          	: origin = 0x008800, length = 0x000800
   RAMLS2      		: origin = 0x009000, length = 0x000C00
   RAMLS3      		: origin = 0x009C00, length = 0x000400
   RAMLS4      		: origin = 0x00A000, length = 0x000800
   RAMLS5      		: origin = 0x00A800, length = 0x000800
   //RAMLS45			: origin = 0x00A000, length = 0x001000
   
   /*** Flash sectors ***/
   FLASHA           : origin = 0x080002, length = 0x001FFE	/* on-chip Flash */
   FLASHB           : origin = 0x082000, length = 0x002000	/* on-chip Flash */
   FLASHC           : origin = 0x084000, length = 0x002000	/* on-chip Flash */
   FLASHD           : origin = 0x086000, length = 0x002000	/* on-chip Flash */
   FLASHE           : origin = 0x088000, length = 0x008000	/* on-chip Flash */
   FLASHF           : origin = 0x090000, length = 0x008000	/* on-chip Flash */
   FLASHG           : origin = 0x098000, length = 0x008000	/* on-chip Flash */
   FLASHH           : origin = 0x0A0000, length = 0x008000	/* on-chip Flash */
   FLASHI           : origin = 0x0A8000, length = 0x008000	/* on-chip Flash */
   FLASHJ           : origin = 0x0B0000, length = 0x008000	/* on-chip Flash */
   FLASHK           : origin = 0x0B8000, length = 0x002000	/* on-chip Flash */
   FLASHL           : origin = 0x0BA000, length = 0x002000	/* on-chip Flash */
   FLASHM           : origin = 0x0BC000, length = 0x002000	/* on-chip Flash */
   FLASHN           : origin = 0x0BE000, length = 0x002000	/* on-chip Flash */

   RESET           	: origin = 0x3FFFC0, length = 0x000002

PAGE 1 : /*** Data Memory ***/

	/* Memory (RAM/FLASH) blocks can be moved to PAGE0 for program allocation */
   RAMGS0      		: origin = 0x00C000, length = 0x001000
   RAMGS1      		: origin = 0x00D000, length = 0x001000
   RAMGS2      		: origin = 0x00E000, length = 0x001000
   RAMGS3      		: origin = 0x00F000, length = 0x001000
   RAMGS4     		: origin = 0x010000, length = 0x001000
   RAMGS5      		: origin = 0x011000, length = 0x001000
   RAMGS6      		: origin = 0x012000, length = 0x001000
   RAMGS7      		: origin = 0x013000, length = 0x001000
   RAMGS8      		: origin = 0x014000, length = 0x001000
   RAMGS9      		: origin = 0x015000, length = 0x001000
   RAMGS10     		: origin = 0x016000, length = 0x001000
   RAMGS11     		: origin = 0x017000, length = 0x001000
   RAMGS12     		: origin = 0x018000, length = 0x001000
   RAMGS13     		: origin = 0x019000, length = 0x001000
   RAMGS14          : origin = 0x01A000, length = 0x001000
   RAMGS15          : origin = 0x01B000, length = 0x001000

   CPU2TOCPU1RAM   : origin = 0x03F800, length = 0x000400
   CPU1TOCPU2RAM   : origin = 0x03FC00, length = 0x000400

}

SECTIONS
{
   /* Allocate program areas: */
   .cinit              : > FLASHB,		PAGE = 0, ALIGN(4)
   .pinit              : > FLASHB,		PAGE = 0, ALIGN(4)
   .text               : >>FLASHB | FLASHC | FLASHD | FLASHE, PAGE = 0, ALIGN(4)
   codestart           : > BEGIN,		PAGE = 0, ALIGN(4)

   /*** Uninitialized Sections ***/
   .stack              : > RAMM1,		PAGE = 0 /* System Stack */
   .ebss               : > RAMD1,		PAGE = 0 /* Global Variables */
   .esysmem            : > RAMD0,		PAGE = 0 /* Malloc Heap */
   .cio				   : > RAMD0,		PAGE = 0

   /*** Initialized Sections - Goes in Flash ***/
   .econst             : >>FLASHF | FLASHG | FLASHH, 	PAGE = 0, ALIGN(4) /* Initialized Global Variables */
   .switch             : > FLASHB,						PAGE = 0, ALIGN(4) /* Jump Tables for certain switch statements */

   /*** Reset - Dummy Sections ***/
   .reset              : > RESET,     	PAGE = 0, TYPE = DSECT /* Not used */

   /*** CLA Compiler Required Sections ***/
   .scratchpad         : > RAMLS0,    	PAGE = 0 /* Scratchpad memory for the CLA C Compiler */

       /* CLA specific sections */
   Cla1Prog         : LOAD = FLASHD,
                      RUN = RAMLS2,
                      LOAD_START(_Cla1funcsLoadStart),
                      LOAD_END(_Cla1funcsLoadEnd),
                      RUN_START(_Cla1funcsRunStart),
                      LOAD_SIZE(_Cla1funcsLoadSize),
                      PAGE = 0, ALIGN(4)

   /* The ramfunc attribute is a TI compiler feature which allows code to easily specify
    that a function will be placed in and executed out of RAM. This allows the compiler to
    optimize functions for RAM execution, as well as to automatically copy functions to
    RAM on flash-based devices. */

#ifdef __TI_COMPILER_VERSION__
   #if __TI_COMPILER_VERSION__ >= 15009000
    .TI.ramfunc 	   : {} LOAD = FLASHB | FLASHC | FLASHD | FLASHE
                         RUN = RAMLS4 | RAMLS5,
                         LOAD_START(_RamfuncsLoadStart),
                         LOAD_SIZE(_RamfuncsLoadSize),
                         LOAD_END(_RamfuncsLoadEnd),
                         RUN_START(_RamfuncsRunStart),
                         RUN_SIZE(_RamfuncsRunSize),
                         RUN_END(_RamfuncsRunEnd),
                         PAGE = 0, ALIGN(4)
   #else
      ramfuncs         : LOAD = FLASHB | FLASHC | FLASHD | FLASHE,
                         RUN = RAMLS4 | RAMLS5,
                         LOAD_START(_RamfuncsLoadStart),
                         LOAD_SIZE(_RamfuncsLoadSize),
                         LOAD_END(_RamfuncsLoadEnd),
                         RUN_START(_RamfuncsRunStart),
                         RUN_SIZE(_RamfuncsRunSize),
                         RUN_END(_RamfuncsRunEnd),
                         PAGE = 0, ALIGN(4)
   #endif
#endif

   /*** The following section definitions are required when using the IPC API Drivers ***/
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

/*** User Defined Sections ***/
   /*** RFFT Buffers - Align input on 2*FFT_SIZE ***/
   RFFT1Input       : > RAMGS0,		PAGE = 1,	ALIGN = RFFT_ALIGNMENT  // 0x3FF
   RFFT1Output      : > RAMGS0,		PAGE = 1							// 0x3FF
   RFFT1Magnitude   : > RAMGS1,		PAGE = 1						 	// 0x3FF / 2
   RFFT1F32Coef     : > RAMGS1,		PAGE = 1						 	// 0x3FF
   RFFT1Phase		: > RAMGS1,		PAGE = 1						 	// 0x3FF / 2

   RFFT2Input		: > RAMGS2,		PAGE = 1,	ALIGN = RFFT_ALIGNMENT
   RFFT2Output		: > RAMGS2,		PAGE = 1
   RFFT2Magnitude   : > RAMGS3,		PAGE = 1
   RFFT2F32Coef		: > RAMGS3,		PAGE = 1
   RFFT2Phase		: > RAMGS3,		PAGE = 1

   RFFTwindow		: > RAMGS4,		PAGE = 1
   FPUmathTables    : > RAMGS4,     PAGE = 1

   /*** Circular Buffers ***/
   CircBuff2		: > RAMGS5,		PAGE = 1 // CPU1
   CircBuff4		: > RAMGS5,		PAGE = 1
   CircBuff6		: > RAMGS6,		PAGE = 1
   CircBuff1		: > RAMGS7,		PAGE = 1 // CPU2
   CircBuff3		: > RAMGS7,		PAGE = 1
   CircBuff5		: > RAMGS8,		PAGE = 1

   /*** CLA Memory Regions ***/
   Cla1ToCpuMsgRAM  : > CLA1_MSGRAML,	PAGE = 0    /* Link to CLA Message RAM */
   CpuToCla1MsgRAM  : > CLA1_MSGRAMH,	PAGE = 0	/* Link to CLA Message RAM */
   Cla1Data1        : > RAMLS1,     	PAGE = 0    /* Link to CLA Data RAM */
   //Cla1Data2        : > RAMLS2,     PAGE = 0        /* Link to CLA Data RAM */

   FE_CPU2_MSG		: > CPU2TOCPU1RAM, PAGE = 1

}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
