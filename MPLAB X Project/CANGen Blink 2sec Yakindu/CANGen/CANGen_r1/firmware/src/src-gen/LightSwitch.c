
#include <stdlib.h>
#include <string.h>
#include "..\src\sc_types.h"
#include "LightSwitch.h"
#include "LightSwitchRequired.h"
/*! \file Implementation of the state machine 'LightSwitch'
*/

/* prototypes of all internal functions */
static sc_boolean lightSwitch_check_main_region_off_tr0_tr0(const LightSwitch* handle);
static sc_boolean lightSwitch_check_main_region_on_tr0_tr0(const LightSwitch* handle);
static void lightSwitch_effect_main_region_off_tr0(LightSwitch* handle);
static void lightSwitch_effect_main_region_on_tr0(LightSwitch* handle);
static void lightSwitch_enact_main_region_off(LightSwitch* handle);
static void lightSwitch_enact_main_region_on(LightSwitch* handle);
static void lightSwitch_exact_main_region_off(LightSwitch* handle);
static void lightSwitch_exact_main_region_on(LightSwitch* handle);
static void lightSwitch_enseq_main_region_off_default(LightSwitch* handle);
static void lightSwitch_enseq_main_region_on_default(LightSwitch* handle);
static void lightSwitch_enseq_main_region_default(LightSwitch* handle);
static void lightSwitch_exseq_main_region_off(LightSwitch* handle);
static void lightSwitch_exseq_main_region_on(LightSwitch* handle);
static void lightSwitch_exseq_main_region(LightSwitch* handle);
static void lightSwitch_react_main_region_off(LightSwitch* handle);
static void lightSwitch_react_main_region_on(LightSwitch* handle);
static void lightSwitch_react_main_region__entry_Default(LightSwitch* handle);
static void lightSwitch_clearInEvents(LightSwitch* handle);
static void lightSwitch_clearOutEvents(LightSwitch* handle);


void lightSwitch_init(LightSwitch* handle)
{
	sc_integer i;

	for (i = 0; i < LIGHTSWITCH_MAX_ORTHOGONAL_STATES; ++i)
	{
		handle->stateConfVector[i] = LightSwitch_last_state;
	}
	
	
	handle->stateConfVectorPosition = 0;

	lightSwitch_clearInEvents(handle);
	lightSwitch_clearOutEvents(handle);


}

void lightSwitch_enter(LightSwitch* handle)
{
	/* Default enter sequence for statechart LightSwitch */
	lightSwitch_enseq_main_region_default(handle);
}

void lightSwitch_exit(LightSwitch* handle)
{
	/* Default exit sequence for statechart LightSwitch */
	lightSwitch_exseq_main_region(handle);
}

sc_boolean lightSwitch_isActive(const LightSwitch* handle)
{
	sc_boolean result;
	if (handle->stateConfVector[0] != LightSwitch_last_state)
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
sc_boolean lightSwitch_isFinal(const LightSwitch* handle)
{
   return bool_false;
}

static void lightSwitch_clearInEvents(LightSwitch* handle)
{
	handle->timeEvents.lightSwitch_main_region_off_tev0_raised = bool_false;
	handle->timeEvents.lightSwitch_main_region_on_tev0_raised = bool_false;
}

static void lightSwitch_clearOutEvents(LightSwitch* handle)
{
}

void lightSwitch_runCycle(LightSwitch* handle)
{
	
	lightSwitch_clearOutEvents(handle);
	
	for (handle->stateConfVectorPosition = 0;
		handle->stateConfVectorPosition < LIGHTSWITCH_MAX_ORTHOGONAL_STATES;
		handle->stateConfVectorPosition++)
		{
			
		switch (handle->stateConfVector[handle->stateConfVectorPosition])
		{
		case LightSwitch_main_region_off :
		{
			lightSwitch_react_main_region_off(handle);
			break;
		}
		case LightSwitch_main_region_on :
		{
			lightSwitch_react_main_region_on(handle);
			break;
		}
		default:
			break;
		}
	}
	
	lightSwitch_clearInEvents(handle);
}

void lightSwitch_raiseTimeEvent(const LightSwitch* handle, sc_eventid evid)
{
	if ( ((sc_intptr_t)evid) >= ((sc_intptr_t)&(handle->timeEvents))
		&&  ((sc_intptr_t)evid) < ((sc_intptr_t)&(handle->timeEvents)) + sizeof(LightSwitchTimeEvents))
		{
		*(sc_boolean*)evid = bool_true;
	}		
}

sc_boolean lightSwitch_isStateActive(const LightSwitch* handle, LightSwitchStates state)
{
	sc_boolean result = bool_false;
	switch (state)
	{
		case LightSwitch_main_region_off :
			result = (sc_boolean) (handle->stateConfVector[0] == LightSwitch_main_region_off
			);
			break;
		case LightSwitch_main_region_on :
			result = (sc_boolean) (handle->stateConfVector[0] == LightSwitch_main_region_on
			);
			break;
		default:
			result = bool_false;
			break;
	}
	return result;
}




/* implementations of all internal functions */

static sc_boolean lightSwitch_check_main_region_off_tr0_tr0(const LightSwitch* handle)
{
	return handle->timeEvents.lightSwitch_main_region_off_tev0_raised;
}

static sc_boolean lightSwitch_check_main_region_on_tr0_tr0(const LightSwitch* handle)
{
	return handle->timeEvents.lightSwitch_main_region_on_tev0_raised;
}

static void lightSwitch_effect_main_region_off_tr0(LightSwitch* handle)
{
	lightSwitch_exseq_main_region_off(handle);
	lightSwitchIface_setLight(handle, bool_true);
	lightSwitch_enseq_main_region_on_default(handle);
}

static void lightSwitch_effect_main_region_on_tr0(LightSwitch* handle)
{
	lightSwitch_exseq_main_region_on(handle);
	lightSwitchIface_setLight(handle, bool_false);
	lightSwitch_enseq_main_region_off_default(handle);
}

/* Entry action for state 'off'. */
static void lightSwitch_enact_main_region_off(LightSwitch* handle)
{
	/* Entry action for state 'off'. */
	lightSwitch_setTimer(handle, (sc_eventid) &(handle->timeEvents.lightSwitch_main_region_off_tev0_raised) , 2 * 1000, bool_false);
}

/* Entry action for state 'on'. */
static void lightSwitch_enact_main_region_on(LightSwitch* handle)
{
	/* Entry action for state 'on'. */
	lightSwitch_setTimer(handle, (sc_eventid) &(handle->timeEvents.lightSwitch_main_region_on_tev0_raised) , 2 * 1000, bool_false);
}

/* Exit action for state 'off'. */
static void lightSwitch_exact_main_region_off(LightSwitch* handle)
{
	/* Exit action for state 'off'. */
	lightSwitch_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.lightSwitch_main_region_off_tev0_raised) );		
}

/* Exit action for state 'on'. */
static void lightSwitch_exact_main_region_on(LightSwitch* handle)
{
	/* Exit action for state 'on'. */
	lightSwitch_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.lightSwitch_main_region_on_tev0_raised) );		
}

/* 'default' enter sequence for state off */
static void lightSwitch_enseq_main_region_off_default(LightSwitch* handle)
{
	/* 'default' enter sequence for state off */
	lightSwitch_enact_main_region_off(handle);
	handle->stateConfVector[0] = LightSwitch_main_region_off;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state on */
static void lightSwitch_enseq_main_region_on_default(LightSwitch* handle)
{
	/* 'default' enter sequence for state on */
	lightSwitch_enact_main_region_on(handle);
	handle->stateConfVector[0] = LightSwitch_main_region_on;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for region main region */
static void lightSwitch_enseq_main_region_default(LightSwitch* handle)
{
	/* 'default' enter sequence for region main region */
	lightSwitch_react_main_region__entry_Default(handle);
}

/* Default exit sequence for state off */
static void lightSwitch_exseq_main_region_off(LightSwitch* handle)
{
	/* Default exit sequence for state off */
	handle->stateConfVector[0] = LightSwitch_last_state;
	handle->stateConfVectorPosition = 0;
	lightSwitch_exact_main_region_off(handle);
}

/* Default exit sequence for state on */
static void lightSwitch_exseq_main_region_on(LightSwitch* handle)
{
	/* Default exit sequence for state on */
	handle->stateConfVector[0] = LightSwitch_last_state;
	handle->stateConfVectorPosition = 0;
	lightSwitch_exact_main_region_on(handle);
}

/* Default exit sequence for region main region */
static void lightSwitch_exseq_main_region(LightSwitch* handle)
{
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of LightSwitch.main_region) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case LightSwitch_main_region_off :
		{
			lightSwitch_exseq_main_region_off(handle);
			break;
		}
		case LightSwitch_main_region_on :
		{
			lightSwitch_exseq_main_region_on(handle);
			break;
		}
		default: break;
	}
}

/* The reactions of state off. */
static void lightSwitch_react_main_region_off(LightSwitch* handle)
{
	/* The reactions of state off. */
	if (lightSwitch_check_main_region_off_tr0_tr0(handle) == bool_true)
	{ 
		lightSwitch_effect_main_region_off_tr0(handle);
	} 
}

/* The reactions of state on. */
static void lightSwitch_react_main_region_on(LightSwitch* handle)
{
	/* The reactions of state on. */
	if (lightSwitch_check_main_region_on_tr0_tr0(handle) == bool_true)
	{ 
		lightSwitch_effect_main_region_on_tr0(handle);
	} 
}

/* Default react sequence for initial entry  */
static void lightSwitch_react_main_region__entry_Default(LightSwitch* handle)
{
	/* Default react sequence for initial entry  */
	lightSwitch_enseq_main_region_off_default(handle);
}


