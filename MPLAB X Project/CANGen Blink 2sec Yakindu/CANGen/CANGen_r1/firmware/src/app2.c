/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app2.c

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

#include "app2.h"
#include "./mytest_1.h"
#include "src/sc_types.h"
#include "src-gen/LightSwitch.h"
#include "scutil/sc_timer_service.h"


// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
#define MAX_TIMERS 20 //number of timers our timer service can use
#define CYCLE_PERIOD 100 //number of milliseconds that pass between each statechart cycle
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
    void APP2_Initialize ( void )

  Remarks:
    See prototype in app2.h.
 */

static sc_timer_service_t timer_service;
static sc_timer_t timers[MAX_TIMERS];

int count = 0;
int start = 0;

LightSwitch handle;

void APP2_Initialize ( void )
{
    led_init();
    sc_timer_service_init(
			&timer_service,
			timers,
			MAX_TIMERS,
			(sc_raise_time_event_fp) &lightSwitch_raiseTimeEvent
			);
    
    lightSwitch_init(&handle);
    lightSwitch_enter(&handle);
}


/******************************************************************************
  Function:
    void APP2_Tasks ( void )

  Remarks:
    See prototype in app2.h.
 */

void runCycle(){
      
      count += 100;
      sc_timer_service_proceed( &timer_service, count - start);

      start = count ;

      lightSwitch_runCycle(&handle);
}

void APP2_Tasks ( void )
{
    // This function will be called every 100ms
    FM14_tasks();
    mytest1_Task();
    
//    if(count < 10000){
//          led_toggle(LED_GREEN);
//          count += 100;
//    }
    
    runCycle();
    
    // call XCP function
    //For Debugging
    //SYS_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_8);
    //XcpReceiveCommand();
    //For Debugging
    //SYS_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_8);

}

void lightSwitchIface_setLight(const LightSwitch* handle, const sc_boolean lightOn){
      if(lightOn){
            led_on(LED_GREEN);
      }else{
            led_off(LED_GREEN);
      }
}

//! callback implementation for the setting up time events
void lightSwitch_setTimer(LightSwitch* handle, const sc_eventid evid, const sc_integer time_ms, const sc_boolean periodic){
	sc_timer_start(&timer_service, (void*) handle, evid, time_ms, periodic);
}

//! callback implementation for canceling time events.
void lightSwitch_unsetTimer(LightSwitch* handle, const sc_eventid evid) {
	sc_timer_cancel(&timer_service, evid);
}

/*******************************************************************************
 End of File
 */
