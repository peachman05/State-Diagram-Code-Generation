/*----------------------------------------------------------------------------
| File:
|   XCP_CFG.H
|
| Project:
|   PC Emulation of a ECU using XCP on Ethernet or XCP on CAN
|
 ----------------------------------------------------------------------------*/

#if defined ( __XCP_CFG_H__ )
#else
#define __XCP_CFG_H__

/*----------------------------------------------------------------------------*/
/* Project specific includes for XCP20.C */
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>

#define ATMEL
#define XCP

#include "app.h"
#include "xcpBasic.h"


/*----------------------------------------------------------------------------*/
/* Test */
/* Use XCP_PRINT to generate diagnostic messages */

// #define XCP_ENABLE_TESTMODE
#ifdef XCP_ENABLE_TESTMODE
  /* Enable xcpPutchar */
  #define XCP_ENABLE_SERV_TEXT
  #define XCP_ENABLE_SERV_TEXT_PUTCHAR
  #define ApplXcpSendStall() 0
  #define ApplXcpPrint cprintf
  #define XCP_ASSERT(x) if (!(x)) cprintf("Assertion failed");
#else
  #define XCP_PRINT
  #define XCP_ASSERT(x)
#endif


/*----------------------------------------------------------------------------*/
/* XCP parameters */

  /* 8-Bit qualifier */
typedef unsigned char  vuint8;
typedef signed char    vsint8;   

/* 16-Bit qualifier */
typedef unsigned short vuint16;
typedef signed short   vsint16;

/* 32-Bit qualifier */
typedef unsigned long  vuint32; 
typedef signed long    vsint32;

                                     
/*----------------------------------------------------------------------------*/
/* XCP protocol parameters */

/* Byte order */
#define C_CPUTYPE_LITTLEENDIAN /* Intel */

/* XCP message length */
#define kXcpMaxCTO     64      /* Maximum CTO Message Lenght */
#define kXcpMaxDTO     14      /* Maximum DTO Message Lenght */


/*----------------------------------------------------------------------------*/
/* Disable/Enable Interrupts */

/* Has to be defined if XcpSendCallBack() can interrupt XcpEvent() */
extern unsigned char gInteruptLevel;
extern unsigned char gInterupt;
#define XCP_DISABLE_INTERRUPT  asm("CLI"); gInteruptLevel++;
#define XCP_ENABLE_INTERRUPT   if (--gInteruptLevel==0 && gInterupt==0) asm("SEI");
#define XCP_INTERUPT_CONTROL_ON gInterupt = 0;
#define XCP_INTERUPT_CONTROL_OFF gInterupt = 1;


/*----------------------------------------------------------------------------*/
/* Memory copy */

#define xcpMemCpy memcpy
#define xcpMemSet memset



/*----------------------------------------------------------------------------*/
/* XCP Data Acquisition Parameters */
                                  
/* Enable data acquisition */
#define XCP_ENABLE_DAQ                   

/* Memory space reserved for DAQ */
#define kXcpDaqMemSize 128
#define XCP_DISABLE_DAQ_HDR_ODT_DAQ

#endif


