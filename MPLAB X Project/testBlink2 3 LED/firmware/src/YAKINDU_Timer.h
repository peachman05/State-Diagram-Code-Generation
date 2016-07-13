/* 
 * File:   YAKINDU_Timer.h
 * Author: trainee2
 *
 * Created on July 7, 2016, 1:08 PM
 */
#include "src/sc_types.h"
#include "scutil/sc_timer_service.h"

#ifndef YAKINDU_TIMER_H
#define	YAKINDU_TIMER_H

#ifdef	__cplusplus
extern "C" {
#endif

#define MAX_TIMERS 20 //number of timers our timer service can use

static sc_timer_service_t timer_service;  // timer service
static sc_timer_t timers[MAX_TIMERS];


 void YAKINDU_Timer_init(sc_raise_time_event_fp raise_event);
 
 void YAKINDU_Timer_updateTime(const sc_integer time_ms);
 
 
#ifdef	__cplusplus
}
#endif

#endif	/* YAKINDU_TIMER_H */

