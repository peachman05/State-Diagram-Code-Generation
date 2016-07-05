
#include <stdlib.h>
#include <string.h>
#include "..\src\sc_types.h"
#include "CallHandling.h"
#include "CallHandlingRequired.h"
/*! \file Implementation of the state machine 'CallHandling'
*/

/* prototypes of all internal functions */
static sc_boolean callHandling_check_main_region_Idle_tr0_tr0(const CallHandling* handle);
static sc_boolean callHandling_check_main_region_Incoming_Call_tr0_tr0(const CallHandling* handle);
static sc_boolean callHandling_check_main_region_Incoming_Call_tr1_tr1(const CallHandling* handle);
static sc_boolean callHandling_check_main_region_Active_Call_tr0_tr0(const CallHandling* handle);
static sc_boolean callHandling_check_main_region_Active_Call_lr0_lr0(const CallHandling* handle);
static sc_boolean callHandling_check_main_region_Dismiss_Call_tr0_tr0(const CallHandling* handle);
static void callHandling_effect_main_region_Idle_tr0(CallHandling* handle);
static void callHandling_effect_main_region_Incoming_Call_tr0(CallHandling* handle);
static void callHandling_effect_main_region_Incoming_Call_tr1(CallHandling* handle);
static void callHandling_effect_main_region_Active_Call_tr0(CallHandling* handle);
static void callHandling_effect_main_region_Active_Call_lr0_lr0(CallHandling* handle);
static void callHandling_effect_main_region_Dismiss_Call_tr0(CallHandling* handle);
static void callHandling_enact_main_region_Active_Call(CallHandling* handle);
static void callHandling_enact_main_region_Dismiss_Call(CallHandling* handle);
static void callHandling_exact_main_region_Active_Call(CallHandling* handle);
static void callHandling_exact_main_region_Dismiss_Call(CallHandling* handle);
static void callHandling_enseq_main_region_Idle_default(CallHandling* handle);
static void callHandling_enseq_main_region_Incoming_Call_default(CallHandling* handle);
static void callHandling_enseq_main_region_Active_Call_default(CallHandling* handle);
static void callHandling_enseq_main_region_Dismiss_Call_default(CallHandling* handle);
static void callHandling_enseq_main_region_default(CallHandling* handle);
static void callHandling_exseq_main_region_Idle(CallHandling* handle);
static void callHandling_exseq_main_region_Incoming_Call(CallHandling* handle);
static void callHandling_exseq_main_region_Active_Call(CallHandling* handle);
static void callHandling_exseq_main_region_Dismiss_Call(CallHandling* handle);
static void callHandling_exseq_main_region(CallHandling* handle);
static void callHandling_react_main_region_Idle(CallHandling* handle);
static void callHandling_react_main_region_Incoming_Call(CallHandling* handle);
static void callHandling_react_main_region_Active_Call(CallHandling* handle);
static void callHandling_react_main_region_Dismiss_Call(CallHandling* handle);
static void callHandling_react_main_region__entry_Default(CallHandling* handle);
static void callHandling_clearInEvents(CallHandling* handle);
static void callHandling_clearOutEvents(CallHandling* handle);


void callHandling_init(CallHandling* handle)
{
	sc_integer i;

	for (i = 0; i < CALLHANDLING_MAX_ORTHOGONAL_STATES; ++i)
	{
		handle->stateConfVector[i] = CallHandling_last_state;
	}
	
	
	handle->stateConfVectorPosition = 0;

	callHandling_clearInEvents(handle);
	callHandling_clearOutEvents(handle);

	/* Default init sequence for statechart CallHandling */
	handle->ifacePhone.duration = 0;

}

void callHandling_enter(CallHandling* handle)
{
	/* Default enter sequence for statechart CallHandling */
	callHandling_enseq_main_region_default(handle);
}

void callHandling_exit(CallHandling* handle)
{
	/* Default exit sequence for statechart CallHandling */
	callHandling_exseq_main_region(handle);
}

sc_boolean callHandling_isActive(const CallHandling* handle)
{
	sc_boolean result;
	if (handle->stateConfVector[0] != CallHandling_last_state)
	{
		result =  bool_true;
	}
	else
	{
		result = bool_false;
	}
	return result;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
sc_boolean callHandling_isFinal(const CallHandling* handle)
{
   return bool_false;
}

static void callHandling_clearInEvents(CallHandling* handle)
{
	handle->ifaceUser.accept_call_raised = bool_false;
	handle->ifaceUser.dismiss_call_raised = bool_false;
	handle->ifacePhone.incoming_call_raised = bool_false;
	handle->timeEvents.callHandling_main_region_Active_Call_tev0_raised = bool_false;
	handle->timeEvents.callHandling_main_region_Dismiss_Call_tev0_raised = bool_false;
}

static void callHandling_clearOutEvents(CallHandling* handle)
{
}

void callHandling_runCycle(CallHandling* handle)
{
	
	callHandling_clearOutEvents(handle);
	
	for (handle->stateConfVectorPosition = 0;
		handle->stateConfVectorPosition < CALLHANDLING_MAX_ORTHOGONAL_STATES;
		handle->stateConfVectorPosition++)
		{
			
		switch (handle->stateConfVector[handle->stateConfVectorPosition])
		{
		case CallHandling_main_region_Idle :
		{
			callHandling_react_main_region_Idle(handle);
			break;
		}
		case CallHandling_main_region_Incoming_Call :
		{
			callHandling_react_main_region_Incoming_Call(handle);
			break;
		}
		case CallHandling_main_region_Active_Call :
		{
			callHandling_react_main_region_Active_Call(handle);
			break;
		}
		case CallHandling_main_region_Dismiss_Call :
		{
			callHandling_react_main_region_Dismiss_Call(handle);
			break;
		}
		default:
			break;
		}
	}
	
	callHandling_clearInEvents(handle);
}

void callHandling_raiseTimeEvent(const CallHandling* handle, sc_eventid evid)
{
	if ( ((sc_intptr_t)evid) >= ((sc_intptr_t)&(handle->timeEvents))
		&&  ((sc_intptr_t)evid) < ((sc_intptr_t)&(handle->timeEvents)) + sizeof(CallHandlingTimeEvents))
		{
		*(sc_boolean*)evid = bool_true;
	}		
}

sc_boolean callHandling_isStateActive(const CallHandling* handle, CallHandlingStates state)
{
	sc_boolean result = bool_false;
	switch (state)
	{
		case CallHandling_main_region_Idle :
			result = (sc_boolean) (handle->stateConfVector[0] == CallHandling_main_region_Idle
			);
			break;
		case CallHandling_main_region_Incoming_Call :
			result = (sc_boolean) (handle->stateConfVector[0] == CallHandling_main_region_Incoming_Call
			);
			break;
		case CallHandling_main_region_Active_Call :
			result = (sc_boolean) (handle->stateConfVector[0] == CallHandling_main_region_Active_Call
			);
			break;
		case CallHandling_main_region_Dismiss_Call :
			result = (sc_boolean) (handle->stateConfVector[0] == CallHandling_main_region_Dismiss_Call
			);
			break;
		default:
			result = bool_false;
			break;
	}
	return result;
}



void callHandlingIfaceUser_raise_accept_call(CallHandling* handle)
{
	handle->ifaceUser.accept_call_raised = bool_true;
}
void callHandlingIfaceUser_raise_dismiss_call(CallHandling* handle)
{
	handle->ifaceUser.dismiss_call_raised = bool_true;
}


void callHandlingIfacePhone_raise_incoming_call(CallHandling* handle)
{
	handle->ifacePhone.incoming_call_raised = bool_true;
}


sc_integer callHandlingIfacePhone_get_duration(const CallHandling* handle)
{
	return handle->ifacePhone.duration;
}
void callHandlingIfacePhone_set_duration(CallHandling* handle, sc_integer value)
{
	handle->ifacePhone.duration = value;
}

/* implementations of all internal functions */

static sc_boolean callHandling_check_main_region_Idle_tr0_tr0(const CallHandling* handle)
{
	return handle->ifacePhone.incoming_call_raised;
}

static sc_boolean callHandling_check_main_region_Incoming_Call_tr0_tr0(const CallHandling* handle)
{
	return handle->ifaceUser.accept_call_raised;
}

static sc_boolean callHandling_check_main_region_Incoming_Call_tr1_tr1(const CallHandling* handle)
{
	return handle->ifaceUser.dismiss_call_raised;
}

static sc_boolean callHandling_check_main_region_Active_Call_tr0_tr0(const CallHandling* handle)
{
	return handle->ifaceUser.dismiss_call_raised;
}

static sc_boolean callHandling_check_main_region_Active_Call_lr0_lr0(const CallHandling* handle)
{
	return handle->timeEvents.callHandling_main_region_Active_Call_tev0_raised;
}

static sc_boolean callHandling_check_main_region_Dismiss_Call_tr0_tr0(const CallHandling* handle)
{
	return handle->timeEvents.callHandling_main_region_Dismiss_Call_tev0_raised;
}

static void callHandling_effect_main_region_Idle_tr0(CallHandling* handle)
{
	callHandling_exseq_main_region_Idle(handle);
	callHandling_enseq_main_region_Incoming_Call_default(handle);
}

static void callHandling_effect_main_region_Incoming_Call_tr0(CallHandling* handle)
{
	callHandling_exseq_main_region_Incoming_Call(handle);
	callHandling_enseq_main_region_Active_Call_default(handle);
}

static void callHandling_effect_main_region_Incoming_Call_tr1(CallHandling* handle)
{
	callHandling_exseq_main_region_Incoming_Call(handle);
	callHandling_enseq_main_region_Dismiss_Call_default(handle);
}

static void callHandling_effect_main_region_Active_Call_tr0(CallHandling* handle)
{
	callHandling_exseq_main_region_Active_Call(handle);
	callHandling_enseq_main_region_Dismiss_Call_default(handle);
}

static void callHandling_effect_main_region_Active_Call_lr0_lr0(CallHandling* handle)
{
	handle->ifacePhone.duration += 1;
}

static void callHandling_effect_main_region_Dismiss_Call_tr0(CallHandling* handle)
{
	callHandling_exseq_main_region_Dismiss_Call(handle);
	callHandling_enseq_main_region_Idle_default(handle);
}

/* Entry action for state 'Active Call'. */
static void callHandling_enact_main_region_Active_Call(CallHandling* handle)
{
	/* Entry action for state 'Active Call'. */
	callHandling_setTimer(handle, (sc_eventid) &(handle->timeEvents.callHandling_main_region_Active_Call_tev0_raised) , 1 * 1000, bool_true);
}

/* Entry action for state 'Dismiss Call'. */
static void callHandling_enact_main_region_Dismiss_Call(CallHandling* handle)
{
	/* Entry action for state 'Dismiss Call'. */
	callHandling_setTimer(handle, (sc_eventid) &(handle->timeEvents.callHandling_main_region_Dismiss_Call_tev0_raised) , 2 * 1000, bool_false);
}

/* Exit action for state 'Active Call'. */
static void callHandling_exact_main_region_Active_Call(CallHandling* handle)
{
	/* Exit action for state 'Active Call'. */
	callHandling_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.callHandling_main_region_Active_Call_tev0_raised) );		
}

/* Exit action for state 'Dismiss Call'. */
static void callHandling_exact_main_region_Dismiss_Call(CallHandling* handle)
{
	/* Exit action for state 'Dismiss Call'. */
	callHandling_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.callHandling_main_region_Dismiss_Call_tev0_raised) );		
	handle->ifacePhone.duration = 0;
}

/* 'default' enter sequence for state Idle */
static void callHandling_enseq_main_region_Idle_default(CallHandling* handle)
{
	/* 'default' enter sequence for state Idle */
	handle->stateConfVector[0] = CallHandling_main_region_Idle;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state Incoming Call */
static void callHandling_enseq_main_region_Incoming_Call_default(CallHandling* handle)
{
	/* 'default' enter sequence for state Incoming Call */
	handle->stateConfVector[0] = CallHandling_main_region_Incoming_Call;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state Active Call */
static void callHandling_enseq_main_region_Active_Call_default(CallHandling* handle)
{
	/* 'default' enter sequence for state Active Call */
	callHandling_enact_main_region_Active_Call(handle);
	handle->stateConfVector[0] = CallHandling_main_region_Active_Call;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state Dismiss Call */
static void callHandling_enseq_main_region_Dismiss_Call_default(CallHandling* handle)
{
	/* 'default' enter sequence for state Dismiss Call */
	callHandling_enact_main_region_Dismiss_Call(handle);
	handle->stateConfVector[0] = CallHandling_main_region_Dismiss_Call;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for region main region */
static void callHandling_enseq_main_region_default(CallHandling* handle)
{
	/* 'default' enter sequence for region main region */
	callHandling_react_main_region__entry_Default(handle);
}

/* Default exit sequence for state Idle */
static void callHandling_exseq_main_region_Idle(CallHandling* handle)
{
	/* Default exit sequence for state Idle */
	handle->stateConfVector[0] = CallHandling_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state Incoming Call */
static void callHandling_exseq_main_region_Incoming_Call(CallHandling* handle)
{
	/* Default exit sequence for state Incoming Call */
	handle->stateConfVector[0] = CallHandling_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state Active Call */
static void callHandling_exseq_main_region_Active_Call(CallHandling* handle)
{
	/* Default exit sequence for state Active Call */
	handle->stateConfVector[0] = CallHandling_last_state;
	handle->stateConfVectorPosition = 0;
	callHandling_exact_main_region_Active_Call(handle);
}

/* Default exit sequence for state Dismiss Call */
static void callHandling_exseq_main_region_Dismiss_Call(CallHandling* handle)
{
	/* Default exit sequence for state Dismiss Call */
	handle->stateConfVector[0] = CallHandling_last_state;
	handle->stateConfVectorPosition = 0;
	callHandling_exact_main_region_Dismiss_Call(handle);
}

/* Default exit sequence for region main region */
static void callHandling_exseq_main_region(CallHandling* handle)
{
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of CallHandling.main_region) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case CallHandling_main_region_Idle :
		{
			callHandling_exseq_main_region_Idle(handle);
			break;
		}
		case CallHandling_main_region_Incoming_Call :
		{
			callHandling_exseq_main_region_Incoming_Call(handle);
			break;
		}
		case CallHandling_main_region_Active_Call :
		{
			callHandling_exseq_main_region_Active_Call(handle);
			break;
		}
		case CallHandling_main_region_Dismiss_Call :
		{
			callHandling_exseq_main_region_Dismiss_Call(handle);
			break;
		}
		default: break;
	}
}

/* The reactions of state Idle. */
static void callHandling_react_main_region_Idle(CallHandling* handle)
{
	/* The reactions of state Idle. */
	if (callHandling_check_main_region_Idle_tr0_tr0(handle) == bool_true)
	{ 
		callHandling_effect_main_region_Idle_tr0(handle);
	} 
}

/* The reactions of state Incoming Call. */
static void callHandling_react_main_region_Incoming_Call(CallHandling* handle)
{
	/* The reactions of state Incoming Call. */
	if (callHandling_check_main_region_Incoming_Call_tr0_tr0(handle) == bool_true)
	{ 
		callHandling_effect_main_region_Incoming_Call_tr0(handle);
	}  else
	{
		if (callHandling_check_main_region_Incoming_Call_tr1_tr1(handle) == bool_true)
		{ 
			callHandling_effect_main_region_Incoming_Call_tr1(handle);
		} 
	}
}

/* The reactions of state Active Call. */
static void callHandling_react_main_region_Active_Call(CallHandling* handle)
{
	/* The reactions of state Active Call. */
	if (callHandling_check_main_region_Active_Call_tr0_tr0(handle) == bool_true)
	{ 
		callHandling_effect_main_region_Active_Call_tr0(handle);
	}  else
	{
		if (callHandling_check_main_region_Active_Call_lr0_lr0(handle) == bool_true)
		{ 
			callHandling_effect_main_region_Active_Call_lr0_lr0(handle);
		} 
	}
}

/* The reactions of state Dismiss Call. */
static void callHandling_react_main_region_Dismiss_Call(CallHandling* handle)
{
	/* The reactions of state Dismiss Call. */
	if (callHandling_check_main_region_Dismiss_Call_tr0_tr0(handle) == bool_true)
	{ 
		callHandling_effect_main_region_Dismiss_Call_tr0(handle);
	} 
}

/* Default react sequence for initial entry  */
static void callHandling_react_main_region__entry_Default(CallHandling* handle)
{
	/* Default react sequence for initial entry  */
	callHandling_enseq_main_region_Idle_default(handle);
}


