#include <stdio.h>
#include <stdlib.h>
#include <sys\timeb.h>  // for struct timeb to get time

#include "src/sc_types.h"
#include "src-gen/LightSwitch2.h"
#include "scutil/sc_timer_service.h" // timer library

#define MAX_TIMERS 20 //number of timers our timer service can use

struct timeb start, end;
int diff;

static sc_timer_service_t timer_service;  // timer service
static sc_timer_t timers[MAX_TIMERS];

LightSwitch2 handle;

void runCycle(){

      ftime(&end); // get current time to "end" variable
      diff = (int) (1000.0 * (end.time - start.time) + (end.millitm - start.millitm)); // find different between end and start time (elapsed time)

     // sc_timer_service_proceed( &timer_service, diff ); // update timer by put diff
      lightSwitch2_raiseTimeEvent(&handle, 100);
      start = end ; // start to capture time

      lightSwitch2_runCycle(&handle); // update state
}


int main()
{
    // initialize function
    sc_timer_service_init(
			&timer_service,
			timers,
			MAX_TIMERS,
			(sc_raise_time_event_fp) &lightSwitch2_raiseTimeEvent // function pointer
			);  // initialize timer

    lightSwitch2_init(&handle); // initialize state code
    lightSwitch2_enter(&handle); // enter to first state .. "off" state

    ftime(&start); // get current time to "start" variable

    // loop function

    while(1){
         runCycle();
    }

    return 0;
}

//! implement setLight function in diagram
void lightSwitch2Iface_setLight(const LightSwitch2* handle, const sc_boolean lightOn, const sc_integer numberLED){
      if(lightOn){
            printf("on %d \n",numberLED);
      }else{
             printf("off %d \n",numberLED);
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

