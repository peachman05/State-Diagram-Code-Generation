/*******************************************************************************
 System Tasks File

  File Name:
    system_tasks.c

  Summary:
    This file contains source code necessary to maintain system's polled state
    machines.

  Description:
    This file contains source code necessary to maintain system's polled state
    machines.  It implements the "SYS_Tasks" function that calls the individual
    "Tasks" functions for all the MPLAB Harmony modules in the system.

  Remarks:
    This file requires access to the systemObjects global data structure that
    contains the object handles to all MPLAB Harmony module objects executing
    polled in the system.  These handles are passed into the individual module
    "Tasks" functions to identify the instance of the module to maintain.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "system_config.h"
#include "system_definitions.h"
#include "app.h"
#include "app1.h"
#include "app2.h"
// *****************************************************************************
// *****************************************************************************
// Section: Local Prototypes
// *****************************************************************************
// *****************************************************************************


 


void _SYS_Tasks(void);
void _APP_Tasks(void);
void _APP1_Tasks(void);
void _APP2_Tasks(void);

// *****************************************************************************
// *****************************************************************************
// Section: System "Tasks" Routine
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void SYS_Tasks ( void )

  Remarks:
    See prototype in system/common/sys_module.h.
*/
void SYS_Tasks ( void )
{
    /* Maintain the state machines of all library modules executing polled in
    the system. */

    /* create task for Sys Tasks */
    xTaskCreate((TaskFunction_t) _SYS_Tasks,
    "Sys Tasks",
    1024,
    NULL,
    1, 
    NULL);


    /* Maintain the application's state machine. */
    /* This section never use task 1 ms and 10 ms in power output project*/
    /* becuase we use only task 2 (100 ms)*/
    /* create task for App Tasks */
    xTaskCreate((TaskFunction_t) _APP_Tasks,
    "App Tasks",
    1024,
    NULL,
    2,
    NULL);

    /* create task for App1 Tasks */
    xTaskCreate((TaskFunction_t) _APP1_Tasks,
    "App1 Tasks",
    1024,
    NULL,
    3,
    NULL);

    /* create task for App2 Tasks */
    xTaskCreate((TaskFunction_t) _APP2_Tasks,
    "App2 Tasks",
    1024,
    NULL,
    4, 
    NULL);

    /* Indicate initialized */
    led_off(LED_RED);

    /* Start multitasking (i.e. give control to RTOS). This function never returns */
    vTaskStartScheduler();
}
 
 void _SYS_Tasks(void)
{
    while(1)
    {
        /* Maintain system services */
        /* Maintain the DEVCON system state machine. */
        SYS_DEVCON_Tasks(sysObj.sysDevcon);

        //For Debugging
        //SYS_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_8);
        /* Maintain Device Drivers */
        /* USB Device layer tasks routine */
        USB_DEVICE_Tasks(sysObj.usbDevObject0);
        //For Debugging
        //SYS_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_8);
    }
}

void _APP_Tasks(void)
{
    TickType_t xLastWakeTime;

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();

    while(1)
    {
        vTaskDelayUntil( &xLastWakeTime, 1 );
        APP_Tasks();
    }
}
void _APP1_Tasks(void)
{
    TickType_t xLastWakeTime;

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();

    while(1)
    {
        vTaskDelayUntil( &xLastWakeTime, 10 );
        APP1_Tasks();
    }
}
void _APP2_Tasks(void)
{
    TickType_t xLastWakeTime;

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();

    while(1)
    {
        vTaskDelayUntil( &xLastWakeTime, 100 );
        APP2_Tasks();
    }
}


/*******************************************************************************
 End of File
 */

