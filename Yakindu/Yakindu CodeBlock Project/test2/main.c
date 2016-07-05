#include "src/sc_types.h"
#include "src-gen/CallHandling.h"
#include "scutil/sc_timer_service.h"
#include<stdio.h>
#include<stdlib.h>
#include <sys\timeb.h>

#define MAX_TIMERS 20 //number of timers our timer service can use
#define CYCLE_PERIOD 100 //number of milliseconds that pass between each statechart cycle

struct timeb start, end;
int diff;

static sc_timer_service_t timer_service;
static sc_timer_t timers[MAX_TIMERS];

CallHandling handle;

//! callback implementation for the setting up time events
void callHandling_setTimer(CallHandling* handle, const sc_eventid evid, const sc_integer time_ms, const sc_boolean periodic){
	sc_timer_start(&timer_service, (void*) handle, evid, time_ms, periodic);
}

//! callback implementation for canceling time events.
void callHandling_unsetTimer(CallHandling* handle, const sc_eventid evid) {
	sc_timer_cancel(&timer_service, evid);
}

int main(int argc, char *argv[]) {


    ftime(&start);

	sc_timer_service_init(
			&timer_service,
			timers,
			MAX_TIMERS,
			(sc_raise_time_event_fp) &callHandling_raiseTimeEvent
			);


   // runCycle();

    callHandling_init(&handle);
    callHandling_enter(&handle);

    callHandlingIfacePhone_raise_incoming_call(&handle);
    runCycle();

    callHandlingIfaceUser_raise_accept_call(&handle);
    runCycle();
    int i,c,d;
    for (i = 0; i < 50; i++) {
        for ( c = 1 ; c <= 32767 ; c++ )
       for ( d = 1 ; d <= 3000 ; d++ )
       {}
          runCycle();  //  sm.runCycle();
    }

          // Before hang-up, output the duration of the call:
     printf("The phone call took %d seconds.",callHandlingIfacePhone_get_duration(&handle));
     callHandlingIfaceUser_raise_dismiss_call(&handle);
     runCycle();
}

void runCycle(){

      ftime(&end);
      diff = (int) (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));

      sc_timer_service_proceed( &timer_service, diff );

      start = end ;

      callHandling_runCycle(&handle);
}
