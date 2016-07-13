/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
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

#include "app.h"
#include "src/sc_types.h"
#include "src-gen/LightSwitch2.h"
#include "scutil/sc_timer_service.h" // timer library
#include "driver/baseboard/drv_led/led.h"
#include "YAKINDU_TIMER.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback funtions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

//#define MAX_TIMERS 20 //number of timers our timer service can use
//
//static sc_timer_service_t timer_service;  // timer service
//static sc_timer_t timers[MAX_TIMERS];

LightSwitch2 handle;
int count = 0,start = 0;

void APP_Initialize ( void )
{ 
    led_init();
    YAKINDU_Timer_init((sc_raise_time_event_fp) &lightSwitch2_raiseTimeEvent);
    
//     sc_timer_service_init(
//			&timer_service,
//			timers,
//			MAX_TIMERS,
//			(sc_raise_time_event_fp) &lightSwitch2_raiseTimeEvent
//			);
        
       lightSwitch2_init(&handle);
       lightSwitch2_enter(&handle);
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void runCycle(){    
   
    uint32_t diff = 0;
    
   appData.last_tick = appData.curr_tick;
   appData.curr_tick = xTaskGetTickCount();
   
   if(appData.curr_tick < appData.last_tick ){ // over flow
       diff = (0xFFFFFFFF - appData.last_tick) + appData.curr_tick;
   }else{
       diff = appData.curr_tick - appData.last_tick ;
   }
   
   // sc_timer_service_proceed( &timer_service,  diff ); // update timer by put diff
   YAKINDU_Timer_updateTime(diff);
   // start = count ; // start to capture time
    lightSwitch2_runCycle(&handle);
}

void APP_Tasks ( void )
{
    runCycle();
}
 

void lightSwitch2Iface_setLight(const LightSwitch2* handle, const sc_boolean lightOn , const sc_integer numberLED){
    
    switch(lightOn){
        case true : led_on(numberLED-1);
            break;
        case false : led_off(numberLED-1);
            break;
    }
    
}

//! callback implementation for the setting up time events
void lightSwitch2_setTimer(LightSwitch2* handle, const sc_eventid evid, const sc_integer time_ms, const sc_boolean periodic){
	sc_timer_start(&timer_service, (void*) handle, evid, time_ms, periodic);
}

//! callback implementation for canceling time events.
void lightSwitch2_unsetTimer(LightSwitch2* handle, const sc_eventid evid) {
	sc_timer_cancel(&timer_service, evid);
}

/*******************************************************************************
 End of File
 */
