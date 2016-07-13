#include "YAKINDU_Timer.h"
#include "scutil/sc_timer_service.h"


void YAKINDU_Timer_init(sc_raise_time_event_fp raise_event){
    
         sc_timer_service_init(
			&timer_service,
			timers,
			MAX_TIMERS,
			raise_event
			);
         
}
 
void YAKINDU_Timer_updateTime(const sc_integer time_ms){
     sc_timer_service_proceed( &timer_service,time_ms );
}
