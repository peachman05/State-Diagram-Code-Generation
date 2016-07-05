
#include <stdlib.h>
#include <string.h>
#include "..\src\sc_types.h"
#include "TrafficLightCtrl.h"
#include "TrafficLightCtrlRequired.h"
/*! \file Implementation of the state machine 'TrafficLightCtrl'
*/

/* prototypes of all internal functions */
static sc_boolean trafficLightCtrl_check__lr0(const TrafficLightCtrl* handle);
static sc_boolean trafficLightCtrl_check_main_region_on_tr0_tr0(const TrafficLightCtrl* handle);
static sc_boolean trafficLightCtrl_check_main_region_on_r1_StreetGreen_tr0_tr0(const TrafficLightCtrl* handle);
static sc_boolean trafficLightCtrl_check_main_region_on_r1_PedWaiting_tr0_tr0(const TrafficLightCtrl* handle);
static sc_boolean trafficLightCtrl_check_main_region_on_r1_PedWaiting_r1_waitOn_tr0_tr0(const TrafficLightCtrl* handle);
static sc_boolean trafficLightCtrl_check_main_region_on_r1_PedWaiting_r1_waitOff_tr0_tr0(const TrafficLightCtrl* handle);
static sc_boolean trafficLightCtrl_check_main_region_on_r1_StreetAttention_tr0_tr0(const TrafficLightCtrl* handle);
static sc_boolean trafficLightCtrl_check_main_region_on_r1_StreetRed_tr0_tr0(const TrafficLightCtrl* handle);
static sc_boolean trafficLightCtrl_check_main_region_on_r1_PedestrianGreen_tr0_tr0(const TrafficLightCtrl* handle);
static sc_boolean trafficLightCtrl_check_main_region_on_r1_PedestrianRed_tr0_tr0(const TrafficLightCtrl* handle);
static sc_boolean trafficLightCtrl_check_main_region_on_r1_StreetPrepare_tr0_tr0(const TrafficLightCtrl* handle);
static sc_boolean trafficLightCtrl_check_main_region_on_r1_Safe_tr0_tr0(const TrafficLightCtrl* handle);
static sc_boolean trafficLightCtrl_check_main_region_off_tr0_tr0(const TrafficLightCtrl* handle);
static sc_boolean trafficLightCtrl_check_main_region_off_r1_YellowOn_tr0_tr0(const TrafficLightCtrl* handle);
static sc_boolean trafficLightCtrl_check_main_region_off_r1_YellowOff_tr0_tr0(const TrafficLightCtrl* handle);
static void trafficLightCtrl_effect__lr0(TrafficLightCtrl* handle);
static void trafficLightCtrl_effect_main_region_on_tr0(TrafficLightCtrl* handle);
static void trafficLightCtrl_effect_main_region_on_r1_StreetGreen_tr0(TrafficLightCtrl* handle);
static void trafficLightCtrl_effect_main_region_on_r1_PedWaiting_tr0(TrafficLightCtrl* handle);
static void trafficLightCtrl_effect_main_region_on_r1_PedWaiting_r1_waitOn_tr0(TrafficLightCtrl* handle);
static void trafficLightCtrl_effect_main_region_on_r1_PedWaiting_r1_waitOff_tr0(TrafficLightCtrl* handle);
static void trafficLightCtrl_effect_main_region_on_r1_StreetAttention_tr0(TrafficLightCtrl* handle);
static void trafficLightCtrl_effect_main_region_on_r1_StreetRed_tr0(TrafficLightCtrl* handle);
static void trafficLightCtrl_effect_main_region_on_r1_PedestrianGreen_tr0(TrafficLightCtrl* handle);
static void trafficLightCtrl_effect_main_region_on_r1_PedestrianRed_tr0(TrafficLightCtrl* handle);
static void trafficLightCtrl_effect_main_region_on_r1_StreetPrepare_tr0(TrafficLightCtrl* handle);
static void trafficLightCtrl_effect_main_region_on_r1_Safe_tr0(TrafficLightCtrl* handle);
static void trafficLightCtrl_effect_main_region_off_tr0(TrafficLightCtrl* handle);
static void trafficLightCtrl_effect_main_region_off_r1_YellowOn_tr0(TrafficLightCtrl* handle);
static void trafficLightCtrl_effect_main_region_off_r1_YellowOff_tr0(TrafficLightCtrl* handle);
static void trafficLightCtrl_enact(TrafficLightCtrl* handle);
static void trafficLightCtrl_enact_main_region_on_r1_StreetGreen(TrafficLightCtrl* handle);
static void trafficLightCtrl_enact_main_region_on_r1_PedWaiting(TrafficLightCtrl* handle);
static void trafficLightCtrl_enact_main_region_on_r1_PedWaiting_r1_waitOn(TrafficLightCtrl* handle);
static void trafficLightCtrl_enact_main_region_on_r1_PedWaiting_r1_waitOff(TrafficLightCtrl* handle);
static void trafficLightCtrl_enact_main_region_on_r1_StreetAttention(TrafficLightCtrl* handle);
static void trafficLightCtrl_enact_main_region_on_r1_StreetRed(TrafficLightCtrl* handle);
static void trafficLightCtrl_enact_main_region_on_r1_PedestrianGreen(TrafficLightCtrl* handle);
static void trafficLightCtrl_enact_main_region_on_r1_PedestrianRed(TrafficLightCtrl* handle);
static void trafficLightCtrl_enact_main_region_on_r1_StreetPrepare(TrafficLightCtrl* handle);
static void trafficLightCtrl_enact_main_region_on_r1_Safe(TrafficLightCtrl* handle);
static void trafficLightCtrl_enact_main_region_off(TrafficLightCtrl* handle);
static void trafficLightCtrl_enact_main_region_off_r1_YellowOn(TrafficLightCtrl* handle);
static void trafficLightCtrl_enact_main_region_off_r1_YellowOff(TrafficLightCtrl* handle);
static void trafficLightCtrl_exact(TrafficLightCtrl* handle);
static void trafficLightCtrl_exact_main_region_on_r1_PedWaiting(TrafficLightCtrl* handle);
static void trafficLightCtrl_exact_main_region_on_r1_PedWaiting_r1_waitOn(TrafficLightCtrl* handle);
static void trafficLightCtrl_exact_main_region_on_r1_PedWaiting_r1_waitOff(TrafficLightCtrl* handle);
static void trafficLightCtrl_exact_main_region_on_r1_StreetAttention(TrafficLightCtrl* handle);
static void trafficLightCtrl_exact_main_region_on_r1_StreetRed(TrafficLightCtrl* handle);
static void trafficLightCtrl_exact_main_region_on_r1_PedestrianGreen(TrafficLightCtrl* handle);
static void trafficLightCtrl_exact_main_region_on_r1_PedestrianRed(TrafficLightCtrl* handle);
static void trafficLightCtrl_exact_main_region_on_r1_StreetPrepare(TrafficLightCtrl* handle);
static void trafficLightCtrl_exact_main_region_on_r1_Safe(TrafficLightCtrl* handle);
static void trafficLightCtrl_exact_main_region_off_r1_YellowOn(TrafficLightCtrl* handle);
static void trafficLightCtrl_exact_main_region_off_r1_YellowOff(TrafficLightCtrl* handle);
static void trafficLightCtrl_enseq_main_region_on_default(TrafficLightCtrl* handle);
static void trafficLightCtrl_enseq_main_region_on_r1_StreetGreen_default(TrafficLightCtrl* handle);
static void trafficLightCtrl_enseq_main_region_on_r1_PedWaiting_default(TrafficLightCtrl* handle);
static void trafficLightCtrl_enseq_main_region_on_r1_PedWaiting_r1_waitOn_default(TrafficLightCtrl* handle);
static void trafficLightCtrl_enseq_main_region_on_r1_PedWaiting_r1_waitOff_default(TrafficLightCtrl* handle);
static void trafficLightCtrl_enseq_main_region_on_r1_StreetAttention_default(TrafficLightCtrl* handle);
static void trafficLightCtrl_enseq_main_region_on_r1_StreetRed_default(TrafficLightCtrl* handle);
static void trafficLightCtrl_enseq_main_region_on_r1_PedestrianGreen_default(TrafficLightCtrl* handle);
static void trafficLightCtrl_enseq_main_region_on_r1_PedestrianRed_default(TrafficLightCtrl* handle);
static void trafficLightCtrl_enseq_main_region_on_r1_StreetPrepare_default(TrafficLightCtrl* handle);
static void trafficLightCtrl_enseq_main_region_on_r1_Safe_default(TrafficLightCtrl* handle);
static void trafficLightCtrl_enseq_main_region_off_default(TrafficLightCtrl* handle);
static void trafficLightCtrl_enseq_main_region_off_r1_YellowOn_default(TrafficLightCtrl* handle);
static void trafficLightCtrl_enseq_main_region_off_r1_YellowOff_default(TrafficLightCtrl* handle);
static void trafficLightCtrl_enseq_main_region_default(TrafficLightCtrl* handle);
static void trafficLightCtrl_enseq_main_region_on_r1_default(TrafficLightCtrl* handle);
static void trafficLightCtrl_enseq_main_region_on_r1_PedWaiting_r1_default(TrafficLightCtrl* handle);
static void trafficLightCtrl_enseq_main_region_off_r1_default(TrafficLightCtrl* handle);
static void trafficLightCtrl_exseq_main_region_on(TrafficLightCtrl* handle);
static void trafficLightCtrl_exseq_main_region_on_r1_StreetGreen(TrafficLightCtrl* handle);
static void trafficLightCtrl_exseq_main_region_on_r1_PedWaiting(TrafficLightCtrl* handle);
static void trafficLightCtrl_exseq_main_region_on_r1_PedWaiting_r1_waitOn(TrafficLightCtrl* handle);
static void trafficLightCtrl_exseq_main_region_on_r1_PedWaiting_r1_waitOff(TrafficLightCtrl* handle);
static void trafficLightCtrl_exseq_main_region_on_r1_StreetAttention(TrafficLightCtrl* handle);
static void trafficLightCtrl_exseq_main_region_on_r1_StreetRed(TrafficLightCtrl* handle);
static void trafficLightCtrl_exseq_main_region_on_r1_PedestrianGreen(TrafficLightCtrl* handle);
static void trafficLightCtrl_exseq_main_region_on_r1_PedestrianRed(TrafficLightCtrl* handle);
static void trafficLightCtrl_exseq_main_region_on_r1_StreetPrepare(TrafficLightCtrl* handle);
static void trafficLightCtrl_exseq_main_region_on_r1_Safe(TrafficLightCtrl* handle);
static void trafficLightCtrl_exseq_main_region_off(TrafficLightCtrl* handle);
static void trafficLightCtrl_exseq_main_region_off_r1_YellowOn(TrafficLightCtrl* handle);
static void trafficLightCtrl_exseq_main_region_off_r1_YellowOff(TrafficLightCtrl* handle);
static void trafficLightCtrl_exseq_main_region(TrafficLightCtrl* handle);
static void trafficLightCtrl_exseq_main_region_on_r1(TrafficLightCtrl* handle);
static void trafficLightCtrl_exseq_main_region_on_r1_PedWaiting_r1(TrafficLightCtrl* handle);
static void trafficLightCtrl_exseq_main_region_off_r1(TrafficLightCtrl* handle);
static void trafficLightCtrl_react_main_region_on_r1_StreetGreen(TrafficLightCtrl* handle);
static void trafficLightCtrl_react_main_region_on_r1_PedWaiting_r1_waitOn(TrafficLightCtrl* handle);
static void trafficLightCtrl_react_main_region_on_r1_PedWaiting_r1_waitOff(TrafficLightCtrl* handle);
static void trafficLightCtrl_react_main_region_on_r1_StreetAttention(TrafficLightCtrl* handle);
static void trafficLightCtrl_react_main_region_on_r1_StreetRed(TrafficLightCtrl* handle);
static void trafficLightCtrl_react_main_region_on_r1_PedestrianGreen(TrafficLightCtrl* handle);
static void trafficLightCtrl_react_main_region_on_r1_PedestrianRed(TrafficLightCtrl* handle);
static void trafficLightCtrl_react_main_region_on_r1_StreetPrepare(TrafficLightCtrl* handle);
static void trafficLightCtrl_react_main_region_on_r1_Safe(TrafficLightCtrl* handle);
static void trafficLightCtrl_react_main_region_off_r1_YellowOn(TrafficLightCtrl* handle);
static void trafficLightCtrl_react_main_region_off_r1_YellowOff(TrafficLightCtrl* handle);
static void trafficLightCtrl_react_main_region__entry_Default(TrafficLightCtrl* handle);
static void trafficLightCtrl_react_main_region_on_r1_PedWaiting_r1__entry_Default(TrafficLightCtrl* handle);
static void trafficLightCtrl_react_main_region_on_r1__entry_Default(TrafficLightCtrl* handle);
static void trafficLightCtrl_react_main_region_off_r1__entry_Default(TrafficLightCtrl* handle);
static void trafficLightCtrl_clearInEvents(TrafficLightCtrl* handle);
static void trafficLightCtrl_clearOutEvents(TrafficLightCtrl* handle);


void trafficLightCtrl_init(TrafficLightCtrl* handle)
{
	sc_integer i;

	for (i = 0; i < TRAFFICLIGHTCTRL_MAX_ORTHOGONAL_STATES; ++i)
	{
		handle->stateConfVector[i] = TrafficLightCtrl_last_state;
	}
	
	
	handle->stateConfVectorPosition = 0;

	trafficLightCtrl_clearInEvents(handle);
	trafficLightCtrl_clearOutEvents(handle);

	/* Default init sequence for statechart TrafficLightCtrl */
	handle->ifaceTrafficLight.red = bool_false;
	handle->ifaceTrafficLight.yellow = bool_false;
	handle->ifaceTrafficLight.green = bool_false;
	handle->ifacePedestrian.request = bool_false;
	handle->ifacePedestrian.red = bool_false;
	handle->ifacePedestrian.green = bool_false;

}

void trafficLightCtrl_enter(TrafficLightCtrl* handle)
{
	/* Default enter sequence for statechart TrafficLightCtrl */
	trafficLightCtrl_enact(handle);
	trafficLightCtrl_enseq_main_region_default(handle);
}

void trafficLightCtrl_exit(TrafficLightCtrl* handle)
{
	/* Default exit sequence for statechart TrafficLightCtrl */
	trafficLightCtrl_exseq_main_region(handle);
	trafficLightCtrl_exact(handle);
}

sc_boolean trafficLightCtrl_isActive(const TrafficLightCtrl* handle)
{
	sc_boolean result;
	if (handle->stateConfVector[0] != TrafficLightCtrl_last_state)
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
sc_boolean trafficLightCtrl_isFinal(const TrafficLightCtrl* handle)
{
   return bool_false;
}

static void trafficLightCtrl_clearInEvents(TrafficLightCtrl* handle)
{
	handle->iface.pedestrianRequest_raised = bool_false;
	handle->iface.onOff_raised = bool_false;
	handle->timeEvents.trafficLightCtrl_main_region_on_r1_PedWaiting_tev0_raised = bool_false;
	handle->timeEvents.trafficLightCtrl_main_region_on_r1_PedWaiting_r1_waitOn_tev0_raised = bool_false;
	handle->timeEvents.trafficLightCtrl_main_region_on_r1_PedWaiting_r1_waitOff_tev0_raised = bool_false;
	handle->timeEvents.trafficLightCtrl_main_region_on_r1_StreetAttention_tev0_raised = bool_false;
	handle->timeEvents.trafficLightCtrl_main_region_on_r1_StreetRed_tev0_raised = bool_false;
	handle->timeEvents.trafficLightCtrl_main_region_on_r1_PedestrianGreen_tev0_raised = bool_false;
	handle->timeEvents.trafficLightCtrl_main_region_on_r1_PedestrianRed_tev0_raised = bool_false;
	handle->timeEvents.trafficLightCtrl_main_region_on_r1_StreetPrepare_tev0_raised = bool_false;
	handle->timeEvents.trafficLightCtrl_main_region_on_r1_Safe_tev0_raised = bool_false;
	handle->timeEvents.trafficLightCtrl_main_region_off_r1_YellowOn_tev0_raised = bool_false;
	handle->timeEvents.trafficLightCtrl_main_region_off_r1_YellowOff_tev0_raised = bool_false;
	handle->timeEvents.trafficLightCtrl_tev0_raised = bool_false;
}

static void trafficLightCtrl_clearOutEvents(TrafficLightCtrl* handle)
{
}

void trafficLightCtrl_runCycle(TrafficLightCtrl* handle)
{
	
	trafficLightCtrl_clearOutEvents(handle);
	
	for (handle->stateConfVectorPosition = 0;
		handle->stateConfVectorPosition < TRAFFICLIGHTCTRL_MAX_ORTHOGONAL_STATES;
		handle->stateConfVectorPosition++)
		{
			
		switch (handle->stateConfVector[handle->stateConfVectorPosition])
		{
		case TrafficLightCtrl_main_region_on_r1_StreetGreen :
		{
			trafficLightCtrl_react_main_region_on_r1_StreetGreen(handle);
			break;
		}
		case TrafficLightCtrl_main_region_on_r1_PedWaiting_r1_waitOn :
		{
			trafficLightCtrl_react_main_region_on_r1_PedWaiting_r1_waitOn(handle);
			break;
		}
		case TrafficLightCtrl_main_region_on_r1_PedWaiting_r1_waitOff :
		{
			trafficLightCtrl_react_main_region_on_r1_PedWaiting_r1_waitOff(handle);
			break;
		}
		case TrafficLightCtrl_main_region_on_r1_StreetAttention :
		{
			trafficLightCtrl_react_main_region_on_r1_StreetAttention(handle);
			break;
		}
		case TrafficLightCtrl_main_region_on_r1_StreetRed :
		{
			trafficLightCtrl_react_main_region_on_r1_StreetRed(handle);
			break;
		}
		case TrafficLightCtrl_main_region_on_r1_PedestrianGreen :
		{
			trafficLightCtrl_react_main_region_on_r1_PedestrianGreen(handle);
			break;
		}
		case TrafficLightCtrl_main_region_on_r1_PedestrianRed :
		{
			trafficLightCtrl_react_main_region_on_r1_PedestrianRed(handle);
			break;
		}
		case TrafficLightCtrl_main_region_on_r1_StreetPrepare :
		{
			trafficLightCtrl_react_main_region_on_r1_StreetPrepare(handle);
			break;
		}
		case TrafficLightCtrl_main_region_on_r1_Safe :
		{
			trafficLightCtrl_react_main_region_on_r1_Safe(handle);
			break;
		}
		case TrafficLightCtrl_main_region_off_r1_YellowOn :
		{
			trafficLightCtrl_react_main_region_off_r1_YellowOn(handle);
			break;
		}
		case TrafficLightCtrl_main_region_off_r1_YellowOff :
		{
			trafficLightCtrl_react_main_region_off_r1_YellowOff(handle);
			break;
		}
		default:
			break;
		}
	}
	
	trafficLightCtrl_clearInEvents(handle);
}

void trafficLightCtrl_raiseTimeEvent(const TrafficLightCtrl* handle, sc_eventid evid)
{
	if ( ((sc_intptr_t)evid) >= ((sc_intptr_t)&(handle->timeEvents))
		&&  ((sc_intptr_t)evid) < ((sc_intptr_t)&(handle->timeEvents)) + sizeof(TrafficLightCtrlTimeEvents))
		{
		*(sc_boolean*)evid = bool_true;
	}		
}

sc_boolean trafficLightCtrl_isStateActive(const TrafficLightCtrl* handle, TrafficLightCtrlStates state)
{
	sc_boolean result = bool_false;
	switch (state)
	{
		case TrafficLightCtrl_main_region_on :
			result = (sc_boolean) (handle->stateConfVector[0] >= TrafficLightCtrl_main_region_on
				&& handle->stateConfVector[0] <= TrafficLightCtrl_main_region_on_r1_Safe);
			break;
		case TrafficLightCtrl_main_region_on_r1_StreetGreen :
			result = (sc_boolean) (handle->stateConfVector[0] == TrafficLightCtrl_main_region_on_r1_StreetGreen
			);
			break;
		case TrafficLightCtrl_main_region_on_r1_PedWaiting :
			result = (sc_boolean) (handle->stateConfVector[0] >= TrafficLightCtrl_main_region_on_r1_PedWaiting
				&& handle->stateConfVector[0] <= TrafficLightCtrl_main_region_on_r1_PedWaiting_r1_waitOff);
			break;
		case TrafficLightCtrl_main_region_on_r1_PedWaiting_r1_waitOn :
			result = (sc_boolean) (handle->stateConfVector[0] == TrafficLightCtrl_main_region_on_r1_PedWaiting_r1_waitOn
			);
			break;
		case TrafficLightCtrl_main_region_on_r1_PedWaiting_r1_waitOff :
			result = (sc_boolean) (handle->stateConfVector[0] == TrafficLightCtrl_main_region_on_r1_PedWaiting_r1_waitOff
			);
			break;
		case TrafficLightCtrl_main_region_on_r1_StreetAttention :
			result = (sc_boolean) (handle->stateConfVector[0] == TrafficLightCtrl_main_region_on_r1_StreetAttention
			);
			break;
		case TrafficLightCtrl_main_region_on_r1_StreetRed :
			result = (sc_boolean) (handle->stateConfVector[0] == TrafficLightCtrl_main_region_on_r1_StreetRed
			);
			break;
		case TrafficLightCtrl_main_region_on_r1_PedestrianGreen :
			result = (sc_boolean) (handle->stateConfVector[0] == TrafficLightCtrl_main_region_on_r1_PedestrianGreen
			);
			break;
		case TrafficLightCtrl_main_region_on_r1_PedestrianRed :
			result = (sc_boolean) (handle->stateConfVector[0] == TrafficLightCtrl_main_region_on_r1_PedestrianRed
			);
			break;
		case TrafficLightCtrl_main_region_on_r1_StreetPrepare :
			result = (sc_boolean) (handle->stateConfVector[0] == TrafficLightCtrl_main_region_on_r1_StreetPrepare
			);
			break;
		case TrafficLightCtrl_main_region_on_r1_Safe :
			result = (sc_boolean) (handle->stateConfVector[0] == TrafficLightCtrl_main_region_on_r1_Safe
			);
			break;
		case TrafficLightCtrl_main_region_off :
			result = (sc_boolean) (handle->stateConfVector[0] >= TrafficLightCtrl_main_region_off
				&& handle->stateConfVector[0] <= TrafficLightCtrl_main_region_off_r1_YellowOff);
			break;
		case TrafficLightCtrl_main_region_off_r1_YellowOn :
			result = (sc_boolean) (handle->stateConfVector[0] == TrafficLightCtrl_main_region_off_r1_YellowOn
			);
			break;
		case TrafficLightCtrl_main_region_off_r1_YellowOff :
			result = (sc_boolean) (handle->stateConfVector[0] == TrafficLightCtrl_main_region_off_r1_YellowOff
			);
			break;
		default:
			result = bool_false;
			break;
	}
	return result;
}



sc_boolean trafficLightCtrlIfaceTrafficLight_get_red(const TrafficLightCtrl* handle)
{
	return handle->ifaceTrafficLight.red;
}
void trafficLightCtrlIfaceTrafficLight_set_red(TrafficLightCtrl* handle, sc_boolean value)
{
	handle->ifaceTrafficLight.red = value;
}
sc_boolean trafficLightCtrlIfaceTrafficLight_get_yellow(const TrafficLightCtrl* handle)
{
	return handle->ifaceTrafficLight.yellow;
}
void trafficLightCtrlIfaceTrafficLight_set_yellow(TrafficLightCtrl* handle, sc_boolean value)
{
	handle->ifaceTrafficLight.yellow = value;
}
sc_boolean trafficLightCtrlIfaceTrafficLight_get_green(const TrafficLightCtrl* handle)
{
	return handle->ifaceTrafficLight.green;
}
void trafficLightCtrlIfaceTrafficLight_set_green(TrafficLightCtrl* handle, sc_boolean value)
{
	handle->ifaceTrafficLight.green = value;
}


sc_boolean trafficLightCtrlIfacePedestrian_get_request(const TrafficLightCtrl* handle)
{
	return handle->ifacePedestrian.request;
}
void trafficLightCtrlIfacePedestrian_set_request(TrafficLightCtrl* handle, sc_boolean value)
{
	handle->ifacePedestrian.request = value;
}
sc_boolean trafficLightCtrlIfacePedestrian_get_red(const TrafficLightCtrl* handle)
{
	return handle->ifacePedestrian.red;
}
void trafficLightCtrlIfacePedestrian_set_red(TrafficLightCtrl* handle, sc_boolean value)
{
	handle->ifacePedestrian.red = value;
}
sc_boolean trafficLightCtrlIfacePedestrian_get_green(const TrafficLightCtrl* handle)
{
	return handle->ifacePedestrian.green;
}
void trafficLightCtrlIfacePedestrian_set_green(TrafficLightCtrl* handle, sc_boolean value)
{
	handle->ifacePedestrian.green = value;
}
void trafficLightCtrlIface_raise_pedestrianRequest(TrafficLightCtrl* handle)
{
	handle->iface.pedestrianRequest_raised = bool_true;
}
void trafficLightCtrlIface_raise_onOff(TrafficLightCtrl* handle)
{
	handle->iface.onOff_raised = bool_true;
}



/* implementations of all internal functions */

static sc_boolean trafficLightCtrl_check__lr0(const TrafficLightCtrl* handle)
{
	return handle->timeEvents.trafficLightCtrl_tev0_raised;
}

static sc_boolean trafficLightCtrl_check_main_region_on_tr0_tr0(const TrafficLightCtrl* handle)
{
	return handle->iface.onOff_raised;
}

static sc_boolean trafficLightCtrl_check_main_region_on_r1_StreetGreen_tr0_tr0(const TrafficLightCtrl* handle)
{
	return handle->iface.pedestrianRequest_raised;
}

static sc_boolean trafficLightCtrl_check_main_region_on_r1_PedWaiting_tr0_tr0(const TrafficLightCtrl* handle)
{
	return handle->timeEvents.trafficLightCtrl_main_region_on_r1_PedWaiting_tev0_raised;
}

static sc_boolean trafficLightCtrl_check_main_region_on_r1_PedWaiting_r1_waitOn_tr0_tr0(const TrafficLightCtrl* handle)
{
	return handle->timeEvents.trafficLightCtrl_main_region_on_r1_PedWaiting_r1_waitOn_tev0_raised;
}

static sc_boolean trafficLightCtrl_check_main_region_on_r1_PedWaiting_r1_waitOff_tr0_tr0(const TrafficLightCtrl* handle)
{
	return handle->timeEvents.trafficLightCtrl_main_region_on_r1_PedWaiting_r1_waitOff_tev0_raised;
}

static sc_boolean trafficLightCtrl_check_main_region_on_r1_StreetAttention_tr0_tr0(const TrafficLightCtrl* handle)
{
	return handle->timeEvents.trafficLightCtrl_main_region_on_r1_StreetAttention_tev0_raised;
}

static sc_boolean trafficLightCtrl_check_main_region_on_r1_StreetRed_tr0_tr0(const TrafficLightCtrl* handle)
{
	return handle->timeEvents.trafficLightCtrl_main_region_on_r1_StreetRed_tev0_raised;
}

static sc_boolean trafficLightCtrl_check_main_region_on_r1_PedestrianGreen_tr0_tr0(const TrafficLightCtrl* handle)
{
	return handle->timeEvents.trafficLightCtrl_main_region_on_r1_PedestrianGreen_tev0_raised;
}

static sc_boolean trafficLightCtrl_check_main_region_on_r1_PedestrianRed_tr0_tr0(const TrafficLightCtrl* handle)
{
	return handle->timeEvents.trafficLightCtrl_main_region_on_r1_PedestrianRed_tev0_raised;
}

static sc_boolean trafficLightCtrl_check_main_region_on_r1_StreetPrepare_tr0_tr0(const TrafficLightCtrl* handle)
{
	return handle->timeEvents.trafficLightCtrl_main_region_on_r1_StreetPrepare_tev0_raised;
}

static sc_boolean trafficLightCtrl_check_main_region_on_r1_Safe_tr0_tr0(const TrafficLightCtrl* handle)
{
	return handle->timeEvents.trafficLightCtrl_main_region_on_r1_Safe_tev0_raised;
}

static sc_boolean trafficLightCtrl_check_main_region_off_tr0_tr0(const TrafficLightCtrl* handle)
{
	return handle->iface.onOff_raised;
}

static sc_boolean trafficLightCtrl_check_main_region_off_r1_YellowOn_tr0_tr0(const TrafficLightCtrl* handle)
{
	return handle->timeEvents.trafficLightCtrl_main_region_off_r1_YellowOn_tev0_raised;
}

static sc_boolean trafficLightCtrl_check_main_region_off_r1_YellowOff_tr0_tr0(const TrafficLightCtrl* handle)
{
	return handle->timeEvents.trafficLightCtrl_main_region_off_r1_YellowOff_tev0_raised;
}

static void trafficLightCtrl_effect__lr0(TrafficLightCtrl* handle)
{
	trafficLightCtrlIface_synchronize(handle);
}

static void trafficLightCtrl_effect_main_region_on_tr0(TrafficLightCtrl* handle)
{
	trafficLightCtrl_exseq_main_region_on(handle);
	trafficLightCtrl_enseq_main_region_off_default(handle);
}

static void trafficLightCtrl_effect_main_region_on_r1_StreetGreen_tr0(TrafficLightCtrl* handle)
{
	trafficLightCtrl_exseq_main_region_on_r1_StreetGreen(handle);
	trafficLightCtrl_enseq_main_region_on_r1_PedWaiting_default(handle);
}

static void trafficLightCtrl_effect_main_region_on_r1_PedWaiting_tr0(TrafficLightCtrl* handle)
{
	trafficLightCtrl_exseq_main_region_on_r1_PedWaiting(handle);
	trafficLightCtrl_enseq_main_region_on_r1_StreetAttention_default(handle);
}

static void trafficLightCtrl_effect_main_region_on_r1_PedWaiting_r1_waitOn_tr0(TrafficLightCtrl* handle)
{
	trafficLightCtrl_exseq_main_region_on_r1_PedWaiting_r1_waitOn(handle);
	trafficLightCtrl_enseq_main_region_on_r1_PedWaiting_r1_waitOff_default(handle);
}

static void trafficLightCtrl_effect_main_region_on_r1_PedWaiting_r1_waitOff_tr0(TrafficLightCtrl* handle)
{
	trafficLightCtrl_exseq_main_region_on_r1_PedWaiting_r1_waitOff(handle);
	trafficLightCtrl_enseq_main_region_on_r1_PedWaiting_r1_waitOn_default(handle);
}

static void trafficLightCtrl_effect_main_region_on_r1_StreetAttention_tr0(TrafficLightCtrl* handle)
{
	trafficLightCtrl_exseq_main_region_on_r1_StreetAttention(handle);
	trafficLightCtrl_enseq_main_region_on_r1_StreetRed_default(handle);
}

static void trafficLightCtrl_effect_main_region_on_r1_StreetRed_tr0(TrafficLightCtrl* handle)
{
	trafficLightCtrl_exseq_main_region_on_r1_StreetRed(handle);
	trafficLightCtrl_enseq_main_region_on_r1_PedestrianGreen_default(handle);
}

static void trafficLightCtrl_effect_main_region_on_r1_PedestrianGreen_tr0(TrafficLightCtrl* handle)
{
	trafficLightCtrl_exseq_main_region_on_r1_PedestrianGreen(handle);
	trafficLightCtrl_enseq_main_region_on_r1_PedestrianRed_default(handle);
}

static void trafficLightCtrl_effect_main_region_on_r1_PedestrianRed_tr0(TrafficLightCtrl* handle)
{
	trafficLightCtrl_exseq_main_region_on_r1_PedestrianRed(handle);
	trafficLightCtrl_enseq_main_region_on_r1_StreetPrepare_default(handle);
}

static void trafficLightCtrl_effect_main_region_on_r1_StreetPrepare_tr0(TrafficLightCtrl* handle)
{
	trafficLightCtrl_exseq_main_region_on_r1_StreetPrepare(handle);
	trafficLightCtrl_enseq_main_region_on_r1_StreetGreen_default(handle);
}

static void trafficLightCtrl_effect_main_region_on_r1_Safe_tr0(TrafficLightCtrl* handle)
{
	trafficLightCtrl_exseq_main_region_on_r1_Safe(handle);
	trafficLightCtrl_enseq_main_region_on_r1_StreetPrepare_default(handle);
}

static void trafficLightCtrl_effect_main_region_off_tr0(TrafficLightCtrl* handle)
{
	trafficLightCtrl_exseq_main_region_off(handle);
	trafficLightCtrl_enseq_main_region_on_default(handle);
}

static void trafficLightCtrl_effect_main_region_off_r1_YellowOn_tr0(TrafficLightCtrl* handle)
{
	trafficLightCtrl_exseq_main_region_off_r1_YellowOn(handle);
	trafficLightCtrl_enseq_main_region_off_r1_YellowOff_default(handle);
}

static void trafficLightCtrl_effect_main_region_off_r1_YellowOff_tr0(TrafficLightCtrl* handle)
{
	trafficLightCtrl_exseq_main_region_off_r1_YellowOff(handle);
	trafficLightCtrl_enseq_main_region_off_r1_YellowOn_default(handle);
}

/* Entry action for statechart 'TrafficLightCtrl'. */
static void trafficLightCtrl_enact(TrafficLightCtrl* handle)
{
	/* Entry action for statechart 'TrafficLightCtrl'. */
	trafficLightCtrl_setTimer(handle, (sc_eventid) &(handle->timeEvents.trafficLightCtrl_tev0_raised) , 200, bool_true);
}

/* Entry action for state 'StreetGreen'. */
static void trafficLightCtrl_enact_main_region_on_r1_StreetGreen(TrafficLightCtrl* handle)
{
	/* Entry action for state 'StreetGreen'. */
	handle->ifaceTrafficLight.red = bool_false;
	handle->ifaceTrafficLight.yellow = bool_false;
	handle->ifaceTrafficLight.green = bool_true;
	handle->ifacePedestrian.red = bool_true;
	handle->ifacePedestrian.green = bool_false;
	handle->ifacePedestrian.request = bool_false;
}

/* Entry action for state 'PedWaiting'. */
static void trafficLightCtrl_enact_main_region_on_r1_PedWaiting(TrafficLightCtrl* handle)
{
	/* Entry action for state 'PedWaiting'. */
	trafficLightCtrl_setTimer(handle, (sc_eventid) &(handle->timeEvents.trafficLightCtrl_main_region_on_r1_PedWaiting_tev0_raised) , 7 * 1000, bool_false);
}

/* Entry action for state 'waitOn'. */
static void trafficLightCtrl_enact_main_region_on_r1_PedWaiting_r1_waitOn(TrafficLightCtrl* handle)
{
	/* Entry action for state 'waitOn'. */
	trafficLightCtrl_setTimer(handle, (sc_eventid) &(handle->timeEvents.trafficLightCtrl_main_region_on_r1_PedWaiting_r1_waitOn_tev0_raised) , 500, bool_false);
	handle->ifacePedestrian.request = bool_true;
}

/* Entry action for state 'waitOff'. */
static void trafficLightCtrl_enact_main_region_on_r1_PedWaiting_r1_waitOff(TrafficLightCtrl* handle)
{
	/* Entry action for state 'waitOff'. */
	trafficLightCtrl_setTimer(handle, (sc_eventid) &(handle->timeEvents.trafficLightCtrl_main_region_on_r1_PedWaiting_r1_waitOff_tev0_raised) , 500, bool_false);
	handle->ifacePedestrian.request = bool_false;
}

/* Entry action for state 'StreetAttention'. */
static void trafficLightCtrl_enact_main_region_on_r1_StreetAttention(TrafficLightCtrl* handle)
{
	/* Entry action for state 'StreetAttention'. */
	trafficLightCtrl_setTimer(handle, (sc_eventid) &(handle->timeEvents.trafficLightCtrl_main_region_on_r1_StreetAttention_tev0_raised) , 2 * 1000, bool_false);
	handle->ifaceTrafficLight.red = bool_false;
	handle->ifaceTrafficLight.yellow = bool_true;
	handle->ifaceTrafficLight.green = bool_false;
}

/* Entry action for state 'StreetRed'. */
static void trafficLightCtrl_enact_main_region_on_r1_StreetRed(TrafficLightCtrl* handle)
{
	/* Entry action for state 'StreetRed'. */
	trafficLightCtrl_setTimer(handle, (sc_eventid) &(handle->timeEvents.trafficLightCtrl_main_region_on_r1_StreetRed_tev0_raised) , 2 * 1000, bool_false);
	handle->ifaceTrafficLight.red = bool_true;
	handle->ifaceTrafficLight.yellow = bool_false;
	handle->ifaceTrafficLight.green = bool_false;
}

/* Entry action for state 'PedestrianGreen'. */
static void trafficLightCtrl_enact_main_region_on_r1_PedestrianGreen(TrafficLightCtrl* handle)
{
	/* Entry action for state 'PedestrianGreen'. */
	trafficLightCtrl_setTimer(handle, (sc_eventid) &(handle->timeEvents.trafficLightCtrl_main_region_on_r1_PedestrianGreen_tev0_raised) , 7 * 1000, bool_false);
	handle->ifacePedestrian.red = bool_false;
	handle->ifacePedestrian.green = bool_true;
}

/* Entry action for state 'PedestrianRed'. */
static void trafficLightCtrl_enact_main_region_on_r1_PedestrianRed(TrafficLightCtrl* handle)
{
	/* Entry action for state 'PedestrianRed'. */
	trafficLightCtrl_setTimer(handle, (sc_eventid) &(handle->timeEvents.trafficLightCtrl_main_region_on_r1_PedestrianRed_tev0_raised) , 5 * 1000, bool_false);
	handle->ifacePedestrian.red = bool_true;
	handle->ifacePedestrian.green = bool_false;
}

/* Entry action for state 'StreetPrepare'. */
static void trafficLightCtrl_enact_main_region_on_r1_StreetPrepare(TrafficLightCtrl* handle)
{
	/* Entry action for state 'StreetPrepare'. */
	trafficLightCtrl_setTimer(handle, (sc_eventid) &(handle->timeEvents.trafficLightCtrl_main_region_on_r1_StreetPrepare_tev0_raised) , 2 * 1000, bool_false);
	handle->ifaceTrafficLight.red = bool_true;
	handle->ifaceTrafficLight.yellow = bool_true;
	handle->ifaceTrafficLight.green = bool_false;
}

/* Entry action for state 'Safe'. */
static void trafficLightCtrl_enact_main_region_on_r1_Safe(TrafficLightCtrl* handle)
{
	/* Entry action for state 'Safe'. */
	trafficLightCtrl_setTimer(handle, (sc_eventid) &(handle->timeEvents.trafficLightCtrl_main_region_on_r1_Safe_tev0_raised) , 10 * 1000, bool_false);
	handle->ifaceTrafficLight.red = bool_true;
	handle->ifaceTrafficLight.yellow = bool_false;
	handle->ifaceTrafficLight.green = bool_false;
	handle->ifacePedestrian.red = bool_true;
	handle->ifacePedestrian.green = bool_false;
	handle->ifacePedestrian.request = bool_false;
}

/* Entry action for state 'off'. */
static void trafficLightCtrl_enact_main_region_off(TrafficLightCtrl* handle)
{
	/* Entry action for state 'off'. */
	handle->ifaceTrafficLight.red = bool_false;
	handle->ifaceTrafficLight.green = bool_false;
	handle->ifaceTrafficLight.yellow = bool_false;
	handle->ifacePedestrian.red = bool_false;
	handle->ifacePedestrian.green = bool_false;
}

/* Entry action for state 'YellowOn'. */
static void trafficLightCtrl_enact_main_region_off_r1_YellowOn(TrafficLightCtrl* handle)
{
	/* Entry action for state 'YellowOn'. */
	trafficLightCtrl_setTimer(handle, (sc_eventid) &(handle->timeEvents.trafficLightCtrl_main_region_off_r1_YellowOn_tev0_raised) , 500, bool_false);
	handle->ifaceTrafficLight.yellow = bool_true;
	handle->ifacePedestrian.request = bool_true;
}

/* Entry action for state 'YellowOff'. */
static void trafficLightCtrl_enact_main_region_off_r1_YellowOff(TrafficLightCtrl* handle)
{
	/* Entry action for state 'YellowOff'. */
	trafficLightCtrl_setTimer(handle, (sc_eventid) &(handle->timeEvents.trafficLightCtrl_main_region_off_r1_YellowOff_tev0_raised) , 500, bool_false);
	handle->ifaceTrafficLight.yellow = bool_false;
	handle->ifacePedestrian.request = bool_false;
}

/* Exit action for state 'TrafficLightCtrl'. */
static void trafficLightCtrl_exact(TrafficLightCtrl* handle)
{
	/* Exit action for state 'TrafficLightCtrl'. */
	trafficLightCtrl_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.trafficLightCtrl_tev0_raised) );		
}

/* Exit action for state 'PedWaiting'. */
static void trafficLightCtrl_exact_main_region_on_r1_PedWaiting(TrafficLightCtrl* handle)
{
	/* Exit action for state 'PedWaiting'. */
	trafficLightCtrl_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.trafficLightCtrl_main_region_on_r1_PedWaiting_tev0_raised) );		
	handle->ifacePedestrian.request = bool_false;
}

/* Exit action for state 'waitOn'. */
static void trafficLightCtrl_exact_main_region_on_r1_PedWaiting_r1_waitOn(TrafficLightCtrl* handle)
{
	/* Exit action for state 'waitOn'. */
	trafficLightCtrl_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.trafficLightCtrl_main_region_on_r1_PedWaiting_r1_waitOn_tev0_raised) );		
}

/* Exit action for state 'waitOff'. */
static void trafficLightCtrl_exact_main_region_on_r1_PedWaiting_r1_waitOff(TrafficLightCtrl* handle)
{
	/* Exit action for state 'waitOff'. */
	trafficLightCtrl_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.trafficLightCtrl_main_region_on_r1_PedWaiting_r1_waitOff_tev0_raised) );		
}

/* Exit action for state 'StreetAttention'. */
static void trafficLightCtrl_exact_main_region_on_r1_StreetAttention(TrafficLightCtrl* handle)
{
	/* Exit action for state 'StreetAttention'. */
	trafficLightCtrl_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.trafficLightCtrl_main_region_on_r1_StreetAttention_tev0_raised) );		
}

/* Exit action for state 'StreetRed'. */
static void trafficLightCtrl_exact_main_region_on_r1_StreetRed(TrafficLightCtrl* handle)
{
	/* Exit action for state 'StreetRed'. */
	trafficLightCtrl_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.trafficLightCtrl_main_region_on_r1_StreetRed_tev0_raised) );		
}

/* Exit action for state 'PedestrianGreen'. */
static void trafficLightCtrl_exact_main_region_on_r1_PedestrianGreen(TrafficLightCtrl* handle)
{
	/* Exit action for state 'PedestrianGreen'. */
	trafficLightCtrl_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.trafficLightCtrl_main_region_on_r1_PedestrianGreen_tev0_raised) );		
}

/* Exit action for state 'PedestrianRed'. */
static void trafficLightCtrl_exact_main_region_on_r1_PedestrianRed(TrafficLightCtrl* handle)
{
	/* Exit action for state 'PedestrianRed'. */
	trafficLightCtrl_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.trafficLightCtrl_main_region_on_r1_PedestrianRed_tev0_raised) );		
}

/* Exit action for state 'StreetPrepare'. */
static void trafficLightCtrl_exact_main_region_on_r1_StreetPrepare(TrafficLightCtrl* handle)
{
	/* Exit action for state 'StreetPrepare'. */
	trafficLightCtrl_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.trafficLightCtrl_main_region_on_r1_StreetPrepare_tev0_raised) );		
}

/* Exit action for state 'Safe'. */
static void trafficLightCtrl_exact_main_region_on_r1_Safe(TrafficLightCtrl* handle)
{
	/* Exit action for state 'Safe'. */
	trafficLightCtrl_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.trafficLightCtrl_main_region_on_r1_Safe_tev0_raised) );		
}

/* Exit action for state 'YellowOn'. */
static void trafficLightCtrl_exact_main_region_off_r1_YellowOn(TrafficLightCtrl* handle)
{
	/* Exit action for state 'YellowOn'. */
	trafficLightCtrl_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.trafficLightCtrl_main_region_off_r1_YellowOn_tev0_raised) );		
}

/* Exit action for state 'YellowOff'. */
static void trafficLightCtrl_exact_main_region_off_r1_YellowOff(TrafficLightCtrl* handle)
{
	/* Exit action for state 'YellowOff'. */
	trafficLightCtrl_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.trafficLightCtrl_main_region_off_r1_YellowOff_tev0_raised) );		
}

/* 'default' enter sequence for state on */
static void trafficLightCtrl_enseq_main_region_on_default(TrafficLightCtrl* handle)
{
	/* 'default' enter sequence for state on */
	trafficLightCtrl_enseq_main_region_on_r1_default(handle);
}

/* 'default' enter sequence for state StreetGreen */
static void trafficLightCtrl_enseq_main_region_on_r1_StreetGreen_default(TrafficLightCtrl* handle)
{
	/* 'default' enter sequence for state StreetGreen */
	trafficLightCtrl_enact_main_region_on_r1_StreetGreen(handle);
	handle->stateConfVector[0] = TrafficLightCtrl_main_region_on_r1_StreetGreen;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state PedWaiting */
static void trafficLightCtrl_enseq_main_region_on_r1_PedWaiting_default(TrafficLightCtrl* handle)
{
	/* 'default' enter sequence for state PedWaiting */
	trafficLightCtrl_enact_main_region_on_r1_PedWaiting(handle);
	trafficLightCtrl_enseq_main_region_on_r1_PedWaiting_r1_default(handle);
}

/* 'default' enter sequence for state waitOn */
static void trafficLightCtrl_enseq_main_region_on_r1_PedWaiting_r1_waitOn_default(TrafficLightCtrl* handle)
{
	/* 'default' enter sequence for state waitOn */
	trafficLightCtrl_enact_main_region_on_r1_PedWaiting_r1_waitOn(handle);
	handle->stateConfVector[0] = TrafficLightCtrl_main_region_on_r1_PedWaiting_r1_waitOn;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state waitOff */
static void trafficLightCtrl_enseq_main_region_on_r1_PedWaiting_r1_waitOff_default(TrafficLightCtrl* handle)
{
	/* 'default' enter sequence for state waitOff */
	trafficLightCtrl_enact_main_region_on_r1_PedWaiting_r1_waitOff(handle);
	handle->stateConfVector[0] = TrafficLightCtrl_main_region_on_r1_PedWaiting_r1_waitOff;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state StreetAttention */
static void trafficLightCtrl_enseq_main_region_on_r1_StreetAttention_default(TrafficLightCtrl* handle)
{
	/* 'default' enter sequence for state StreetAttention */
	trafficLightCtrl_enact_main_region_on_r1_StreetAttention(handle);
	handle->stateConfVector[0] = TrafficLightCtrl_main_region_on_r1_StreetAttention;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state StreetRed */
static void trafficLightCtrl_enseq_main_region_on_r1_StreetRed_default(TrafficLightCtrl* handle)
{
	/* 'default' enter sequence for state StreetRed */
	trafficLightCtrl_enact_main_region_on_r1_StreetRed(handle);
	handle->stateConfVector[0] = TrafficLightCtrl_main_region_on_r1_StreetRed;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state PedestrianGreen */
static void trafficLightCtrl_enseq_main_region_on_r1_PedestrianGreen_default(TrafficLightCtrl* handle)
{
	/* 'default' enter sequence for state PedestrianGreen */
	trafficLightCtrl_enact_main_region_on_r1_PedestrianGreen(handle);
	handle->stateConfVector[0] = TrafficLightCtrl_main_region_on_r1_PedestrianGreen;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state PedestrianRed */
static void trafficLightCtrl_enseq_main_region_on_r1_PedestrianRed_default(TrafficLightCtrl* handle)
{
	/* 'default' enter sequence for state PedestrianRed */
	trafficLightCtrl_enact_main_region_on_r1_PedestrianRed(handle);
	handle->stateConfVector[0] = TrafficLightCtrl_main_region_on_r1_PedestrianRed;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state StreetPrepare */
static void trafficLightCtrl_enseq_main_region_on_r1_StreetPrepare_default(TrafficLightCtrl* handle)
{
	/* 'default' enter sequence for state StreetPrepare */
	trafficLightCtrl_enact_main_region_on_r1_StreetPrepare(handle);
	handle->stateConfVector[0] = TrafficLightCtrl_main_region_on_r1_StreetPrepare;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state Safe */
static void trafficLightCtrl_enseq_main_region_on_r1_Safe_default(TrafficLightCtrl* handle)
{
	/* 'default' enter sequence for state Safe */
	trafficLightCtrl_enact_main_region_on_r1_Safe(handle);
	handle->stateConfVector[0] = TrafficLightCtrl_main_region_on_r1_Safe;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state off */
static void trafficLightCtrl_enseq_main_region_off_default(TrafficLightCtrl* handle)
{
	/* 'default' enter sequence for state off */
	trafficLightCtrl_enact_main_region_off(handle);
	trafficLightCtrl_enseq_main_region_off_r1_default(handle);
}

/* 'default' enter sequence for state YellowOn */
static void trafficLightCtrl_enseq_main_region_off_r1_YellowOn_default(TrafficLightCtrl* handle)
{
	/* 'default' enter sequence for state YellowOn */
	trafficLightCtrl_enact_main_region_off_r1_YellowOn(handle);
	handle->stateConfVector[0] = TrafficLightCtrl_main_region_off_r1_YellowOn;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state YellowOff */
static void trafficLightCtrl_enseq_main_region_off_r1_YellowOff_default(TrafficLightCtrl* handle)
{
	/* 'default' enter sequence for state YellowOff */
	trafficLightCtrl_enact_main_region_off_r1_YellowOff(handle);
	handle->stateConfVector[0] = TrafficLightCtrl_main_region_off_r1_YellowOff;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for region main region */
static void trafficLightCtrl_enseq_main_region_default(TrafficLightCtrl* handle)
{
	/* 'default' enter sequence for region main region */
	trafficLightCtrl_react_main_region__entry_Default(handle);
}

/* 'default' enter sequence for region r1 */
static void trafficLightCtrl_enseq_main_region_on_r1_default(TrafficLightCtrl* handle)
{
	/* 'default' enter sequence for region r1 */
	trafficLightCtrl_react_main_region_on_r1__entry_Default(handle);
}

/* 'default' enter sequence for region r1 */
static void trafficLightCtrl_enseq_main_region_on_r1_PedWaiting_r1_default(TrafficLightCtrl* handle)
{
	/* 'default' enter sequence for region r1 */
	trafficLightCtrl_react_main_region_on_r1_PedWaiting_r1__entry_Default(handle);
}

/* 'default' enter sequence for region r1 */
static void trafficLightCtrl_enseq_main_region_off_r1_default(TrafficLightCtrl* handle)
{
	/* 'default' enter sequence for region r1 */
	trafficLightCtrl_react_main_region_off_r1__entry_Default(handle);
}

/* Default exit sequence for state on */
static void trafficLightCtrl_exseq_main_region_on(TrafficLightCtrl* handle)
{
	/* Default exit sequence for state on */
	trafficLightCtrl_exseq_main_region_on_r1(handle);
}

/* Default exit sequence for state StreetGreen */
static void trafficLightCtrl_exseq_main_region_on_r1_StreetGreen(TrafficLightCtrl* handle)
{
	/* Default exit sequence for state StreetGreen */
	handle->stateConfVector[0] = TrafficLightCtrl_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state PedWaiting */
static void trafficLightCtrl_exseq_main_region_on_r1_PedWaiting(TrafficLightCtrl* handle)
{
	/* Default exit sequence for state PedWaiting */
	trafficLightCtrl_exseq_main_region_on_r1_PedWaiting_r1(handle);
	trafficLightCtrl_exact_main_region_on_r1_PedWaiting(handle);
}

/* Default exit sequence for state waitOn */
static void trafficLightCtrl_exseq_main_region_on_r1_PedWaiting_r1_waitOn(TrafficLightCtrl* handle)
{
	/* Default exit sequence for state waitOn */
	handle->stateConfVector[0] = TrafficLightCtrl_last_state;
	handle->stateConfVectorPosition = 0;
	trafficLightCtrl_exact_main_region_on_r1_PedWaiting_r1_waitOn(handle);
}

/* Default exit sequence for state waitOff */
static void trafficLightCtrl_exseq_main_region_on_r1_PedWaiting_r1_waitOff(TrafficLightCtrl* handle)
{
	/* Default exit sequence for state waitOff */
	handle->stateConfVector[0] = TrafficLightCtrl_last_state;
	handle->stateConfVectorPosition = 0;
	trafficLightCtrl_exact_main_region_on_r1_PedWaiting_r1_waitOff(handle);
}

/* Default exit sequence for state StreetAttention */
static void trafficLightCtrl_exseq_main_region_on_r1_StreetAttention(TrafficLightCtrl* handle)
{
	/* Default exit sequence for state StreetAttention */
	handle->stateConfVector[0] = TrafficLightCtrl_last_state;
	handle->stateConfVectorPosition = 0;
	trafficLightCtrl_exact_main_region_on_r1_StreetAttention(handle);
}

/* Default exit sequence for state StreetRed */
static void trafficLightCtrl_exseq_main_region_on_r1_StreetRed(TrafficLightCtrl* handle)
{
	/* Default exit sequence for state StreetRed */
	handle->stateConfVector[0] = TrafficLightCtrl_last_state;
	handle->stateConfVectorPosition = 0;
	trafficLightCtrl_exact_main_region_on_r1_StreetRed(handle);
}

/* Default exit sequence for state PedestrianGreen */
static void trafficLightCtrl_exseq_main_region_on_r1_PedestrianGreen(TrafficLightCtrl* handle)
{
	/* Default exit sequence for state PedestrianGreen */
	handle->stateConfVector[0] = TrafficLightCtrl_last_state;
	handle->stateConfVectorPosition = 0;
	trafficLightCtrl_exact_main_region_on_r1_PedestrianGreen(handle);
}

/* Default exit sequence for state PedestrianRed */
static void trafficLightCtrl_exseq_main_region_on_r1_PedestrianRed(TrafficLightCtrl* handle)
{
	/* Default exit sequence for state PedestrianRed */
	handle->stateConfVector[0] = TrafficLightCtrl_last_state;
	handle->stateConfVectorPosition = 0;
	trafficLightCtrl_exact_main_region_on_r1_PedestrianRed(handle);
}

/* Default exit sequence for state StreetPrepare */
static void trafficLightCtrl_exseq_main_region_on_r1_StreetPrepare(TrafficLightCtrl* handle)
{
	/* Default exit sequence for state StreetPrepare */
	handle->stateConfVector[0] = TrafficLightCtrl_last_state;
	handle->stateConfVectorPosition = 0;
	trafficLightCtrl_exact_main_region_on_r1_StreetPrepare(handle);
}

/* Default exit sequence for state Safe */
static void trafficLightCtrl_exseq_main_region_on_r1_Safe(TrafficLightCtrl* handle)
{
	/* Default exit sequence for state Safe */
	handle->stateConfVector[0] = TrafficLightCtrl_last_state;
	handle->stateConfVectorPosition = 0;
	trafficLightCtrl_exact_main_region_on_r1_Safe(handle);
}

/* Default exit sequence for state off */
static void trafficLightCtrl_exseq_main_region_off(TrafficLightCtrl* handle)
{
	/* Default exit sequence for state off */
	trafficLightCtrl_exseq_main_region_off_r1(handle);
}

/* Default exit sequence for state YellowOn */
static void trafficLightCtrl_exseq_main_region_off_r1_YellowOn(TrafficLightCtrl* handle)
{
	/* Default exit sequence for state YellowOn */
	handle->stateConfVector[0] = TrafficLightCtrl_last_state;
	handle->stateConfVectorPosition = 0;
	trafficLightCtrl_exact_main_region_off_r1_YellowOn(handle);
}

/* Default exit sequence for state YellowOff */
static void trafficLightCtrl_exseq_main_region_off_r1_YellowOff(TrafficLightCtrl* handle)
{
	/* Default exit sequence for state YellowOff */
	handle->stateConfVector[0] = TrafficLightCtrl_last_state;
	handle->stateConfVectorPosition = 0;
	trafficLightCtrl_exact_main_region_off_r1_YellowOff(handle);
}

/* Default exit sequence for region main region */
static void trafficLightCtrl_exseq_main_region(TrafficLightCtrl* handle)
{
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of TrafficLightCtrl.main_region) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case TrafficLightCtrl_main_region_on_r1_StreetGreen :
		{
			trafficLightCtrl_exseq_main_region_on_r1_StreetGreen(handle);
			break;
		}
		case TrafficLightCtrl_main_region_on_r1_PedWaiting_r1_waitOn :
		{
			trafficLightCtrl_exseq_main_region_on_r1_PedWaiting_r1_waitOn(handle);
			trafficLightCtrl_exact_main_region_on_r1_PedWaiting(handle);
			break;
		}
		case TrafficLightCtrl_main_region_on_r1_PedWaiting_r1_waitOff :
		{
			trafficLightCtrl_exseq_main_region_on_r1_PedWaiting_r1_waitOff(handle);
			trafficLightCtrl_exact_main_region_on_r1_PedWaiting(handle);
			break;
		}
		case TrafficLightCtrl_main_region_on_r1_StreetAttention :
		{
			trafficLightCtrl_exseq_main_region_on_r1_StreetAttention(handle);
			break;
		}
		case TrafficLightCtrl_main_region_on_r1_StreetRed :
		{
			trafficLightCtrl_exseq_main_region_on_r1_StreetRed(handle);
			break;
		}
		case TrafficLightCtrl_main_region_on_r1_PedestrianGreen :
		{
			trafficLightCtrl_exseq_main_region_on_r1_PedestrianGreen(handle);
			break;
		}
		case TrafficLightCtrl_main_region_on_r1_PedestrianRed :
		{
			trafficLightCtrl_exseq_main_region_on_r1_PedestrianRed(handle);
			break;
		}
		case TrafficLightCtrl_main_region_on_r1_StreetPrepare :
		{
			trafficLightCtrl_exseq_main_region_on_r1_StreetPrepare(handle);
			break;
		}
		case TrafficLightCtrl_main_region_on_r1_Safe :
		{
			trafficLightCtrl_exseq_main_region_on_r1_Safe(handle);
			break;
		}
		case TrafficLightCtrl_main_region_off_r1_YellowOn :
		{
			trafficLightCtrl_exseq_main_region_off_r1_YellowOn(handle);
			break;
		}
		case TrafficLightCtrl_main_region_off_r1_YellowOff :
		{
			trafficLightCtrl_exseq_main_region_off_r1_YellowOff(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region r1 */
static void trafficLightCtrl_exseq_main_region_on_r1(TrafficLightCtrl* handle)
{
	/* Default exit sequence for region r1 */
	/* Handle exit of all possible states (of TrafficLightCtrl.main_region.on.r1) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case TrafficLightCtrl_main_region_on_r1_StreetGreen :
		{
			trafficLightCtrl_exseq_main_region_on_r1_StreetGreen(handle);
			break;
		}
		case TrafficLightCtrl_main_region_on_r1_PedWaiting_r1_waitOn :
		{
			trafficLightCtrl_exseq_main_region_on_r1_PedWaiting_r1_waitOn(handle);
			trafficLightCtrl_exact_main_region_on_r1_PedWaiting(handle);
			break;
		}
		case TrafficLightCtrl_main_region_on_r1_PedWaiting_r1_waitOff :
		{
			trafficLightCtrl_exseq_main_region_on_r1_PedWaiting_r1_waitOff(handle);
			trafficLightCtrl_exact_main_region_on_r1_PedWaiting(handle);
			break;
		}
		case TrafficLightCtrl_main_region_on_r1_StreetAttention :
		{
			trafficLightCtrl_exseq_main_region_on_r1_StreetAttention(handle);
			break;
		}
		case TrafficLightCtrl_main_region_on_r1_StreetRed :
		{
			trafficLightCtrl_exseq_main_region_on_r1_StreetRed(handle);
			break;
		}
		case TrafficLightCtrl_main_region_on_r1_PedestrianGreen :
		{
			trafficLightCtrl_exseq_main_region_on_r1_PedestrianGreen(handle);
			break;
		}
		case TrafficLightCtrl_main_region_on_r1_PedestrianRed :
		{
			trafficLightCtrl_exseq_main_region_on_r1_PedestrianRed(handle);
			break;
		}
		case TrafficLightCtrl_main_region_on_r1_StreetPrepare :
		{
			trafficLightCtrl_exseq_main_region_on_r1_StreetPrepare(handle);
			break;
		}
		case TrafficLightCtrl_main_region_on_r1_Safe :
		{
			trafficLightCtrl_exseq_main_region_on_r1_Safe(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region r1 */
static void trafficLightCtrl_exseq_main_region_on_r1_PedWaiting_r1(TrafficLightCtrl* handle)
{
	/* Default exit sequence for region r1 */
	/* Handle exit of all possible states (of TrafficLightCtrl.main_region.on.r1.PedWaiting.r1) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case TrafficLightCtrl_main_region_on_r1_PedWaiting_r1_waitOn :
		{
			trafficLightCtrl_exseq_main_region_on_r1_PedWaiting_r1_waitOn(handle);
			break;
		}
		case TrafficLightCtrl_main_region_on_r1_PedWaiting_r1_waitOff :
		{
			trafficLightCtrl_exseq_main_region_on_r1_PedWaiting_r1_waitOff(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region r1 */
static void trafficLightCtrl_exseq_main_region_off_r1(TrafficLightCtrl* handle)
{
	/* Default exit sequence for region r1 */
	/* Handle exit of all possible states (of TrafficLightCtrl.main_region.off.r1) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case TrafficLightCtrl_main_region_off_r1_YellowOn :
		{
			trafficLightCtrl_exseq_main_region_off_r1_YellowOn(handle);
			break;
		}
		case TrafficLightCtrl_main_region_off_r1_YellowOff :
		{
			trafficLightCtrl_exseq_main_region_off_r1_YellowOff(handle);
			break;
		}
		default: break;
	}
}

/* The reactions of state StreetGreen. */
static void trafficLightCtrl_react_main_region_on_r1_StreetGreen(TrafficLightCtrl* handle)
{
	/* The reactions of state StreetGreen. */
	if (trafficLightCtrl_check__lr0(handle) == bool_true)
	{ 
		trafficLightCtrl_effect__lr0(handle);
	} 
	if (trafficLightCtrl_check_main_region_on_tr0_tr0(handle) == bool_true)
	{ 
		trafficLightCtrl_effect_main_region_on_tr0(handle);
	}  else
	{
		if (trafficLightCtrl_check_main_region_on_r1_StreetGreen_tr0_tr0(handle) == bool_true)
		{ 
			trafficLightCtrl_effect_main_region_on_r1_StreetGreen_tr0(handle);
		} 
	}
}

/* The reactions of state waitOn. */
static void trafficLightCtrl_react_main_region_on_r1_PedWaiting_r1_waitOn(TrafficLightCtrl* handle)
{
	/* The reactions of state waitOn. */
	if (trafficLightCtrl_check__lr0(handle) == bool_true)
	{ 
		trafficLightCtrl_effect__lr0(handle);
	} 
	if (trafficLightCtrl_check_main_region_on_tr0_tr0(handle) == bool_true)
	{ 
		trafficLightCtrl_effect_main_region_on_tr0(handle);
	}  else
	{
		if (trafficLightCtrl_check_main_region_on_r1_PedWaiting_tr0_tr0(handle) == bool_true)
		{ 
			trafficLightCtrl_effect_main_region_on_r1_PedWaiting_tr0(handle);
		}  else
		{
			if (trafficLightCtrl_check_main_region_on_r1_PedWaiting_r1_waitOn_tr0_tr0(handle) == bool_true)
			{ 
				trafficLightCtrl_effect_main_region_on_r1_PedWaiting_r1_waitOn_tr0(handle);
			} 
		}
	}
}

/* The reactions of state waitOff. */
static void trafficLightCtrl_react_main_region_on_r1_PedWaiting_r1_waitOff(TrafficLightCtrl* handle)
{
	/* The reactions of state waitOff. */
	if (trafficLightCtrl_check__lr0(handle) == bool_true)
	{ 
		trafficLightCtrl_effect__lr0(handle);
	} 
	if (trafficLightCtrl_check_main_region_on_tr0_tr0(handle) == bool_true)
	{ 
		trafficLightCtrl_effect_main_region_on_tr0(handle);
	}  else
	{
		if (trafficLightCtrl_check_main_region_on_r1_PedWaiting_tr0_tr0(handle) == bool_true)
		{ 
			trafficLightCtrl_effect_main_region_on_r1_PedWaiting_tr0(handle);
		}  else
		{
			if (trafficLightCtrl_check_main_region_on_r1_PedWaiting_r1_waitOff_tr0_tr0(handle) == bool_true)
			{ 
				trafficLightCtrl_effect_main_region_on_r1_PedWaiting_r1_waitOff_tr0(handle);
			} 
		}
	}
}

/* The reactions of state StreetAttention. */
static void trafficLightCtrl_react_main_region_on_r1_StreetAttention(TrafficLightCtrl* handle)
{
	/* The reactions of state StreetAttention. */
	if (trafficLightCtrl_check__lr0(handle) == bool_true)
	{ 
		trafficLightCtrl_effect__lr0(handle);
	} 
	if (trafficLightCtrl_check_main_region_on_tr0_tr0(handle) == bool_true)
	{ 
		trafficLightCtrl_effect_main_region_on_tr0(handle);
	}  else
	{
		if (trafficLightCtrl_check_main_region_on_r1_StreetAttention_tr0_tr0(handle) == bool_true)
		{ 
			trafficLightCtrl_effect_main_region_on_r1_StreetAttention_tr0(handle);
		} 
	}
}

/* The reactions of state StreetRed. */
static void trafficLightCtrl_react_main_region_on_r1_StreetRed(TrafficLightCtrl* handle)
{
	/* The reactions of state StreetRed. */
	if (trafficLightCtrl_check__lr0(handle) == bool_true)
	{ 
		trafficLightCtrl_effect__lr0(handle);
	} 
	if (trafficLightCtrl_check_main_region_on_tr0_tr0(handle) == bool_true)
	{ 
		trafficLightCtrl_effect_main_region_on_tr0(handle);
	}  else
	{
		if (trafficLightCtrl_check_main_region_on_r1_StreetRed_tr0_tr0(handle) == bool_true)
		{ 
			trafficLightCtrl_effect_main_region_on_r1_StreetRed_tr0(handle);
		} 
	}
}

/* The reactions of state PedestrianGreen. */
static void trafficLightCtrl_react_main_region_on_r1_PedestrianGreen(TrafficLightCtrl* handle)
{
	/* The reactions of state PedestrianGreen. */
	if (trafficLightCtrl_check__lr0(handle) == bool_true)
	{ 
		trafficLightCtrl_effect__lr0(handle);
	} 
	if (trafficLightCtrl_check_main_region_on_tr0_tr0(handle) == bool_true)
	{ 
		trafficLightCtrl_effect_main_region_on_tr0(handle);
	}  else
	{
		if (trafficLightCtrl_check_main_region_on_r1_PedestrianGreen_tr0_tr0(handle) == bool_true)
		{ 
			trafficLightCtrl_effect_main_region_on_r1_PedestrianGreen_tr0(handle);
		} 
	}
}

/* The reactions of state PedestrianRed. */
static void trafficLightCtrl_react_main_region_on_r1_PedestrianRed(TrafficLightCtrl* handle)
{
	/* The reactions of state PedestrianRed. */
	if (trafficLightCtrl_check__lr0(handle) == bool_true)
	{ 
		trafficLightCtrl_effect__lr0(handle);
	} 
	if (trafficLightCtrl_check_main_region_on_tr0_tr0(handle) == bool_true)
	{ 
		trafficLightCtrl_effect_main_region_on_tr0(handle);
	}  else
	{
		if (trafficLightCtrl_check_main_region_on_r1_PedestrianRed_tr0_tr0(handle) == bool_true)
		{ 
			trafficLightCtrl_effect_main_region_on_r1_PedestrianRed_tr0(handle);
		} 
	}
}

/* The reactions of state StreetPrepare. */
static void trafficLightCtrl_react_main_region_on_r1_StreetPrepare(TrafficLightCtrl* handle)
{
	/* The reactions of state StreetPrepare. */
	if (trafficLightCtrl_check__lr0(handle) == bool_true)
	{ 
		trafficLightCtrl_effect__lr0(handle);
	} 
	if (trafficLightCtrl_check_main_region_on_tr0_tr0(handle) == bool_true)
	{ 
		trafficLightCtrl_effect_main_region_on_tr0(handle);
	}  else
	{
		if (trafficLightCtrl_check_main_region_on_r1_StreetPrepare_tr0_tr0(handle) == bool_true)
		{ 
			trafficLightCtrl_effect_main_region_on_r1_StreetPrepare_tr0(handle);
		} 
	}
}

/* The reactions of state Safe. */
static void trafficLightCtrl_react_main_region_on_r1_Safe(TrafficLightCtrl* handle)
{
	/* The reactions of state Safe. */
	if (trafficLightCtrl_check__lr0(handle) == bool_true)
	{ 
		trafficLightCtrl_effect__lr0(handle);
	} 
	if (trafficLightCtrl_check_main_region_on_tr0_tr0(handle) == bool_true)
	{ 
		trafficLightCtrl_effect_main_region_on_tr0(handle);
	}  else
	{
		if (trafficLightCtrl_check_main_region_on_r1_Safe_tr0_tr0(handle) == bool_true)
		{ 
			trafficLightCtrl_effect_main_region_on_r1_Safe_tr0(handle);
		} 
	}
}

/* The reactions of state YellowOn. */
static void trafficLightCtrl_react_main_region_off_r1_YellowOn(TrafficLightCtrl* handle)
{
	/* The reactions of state YellowOn. */
	if (trafficLightCtrl_check__lr0(handle) == bool_true)
	{ 
		trafficLightCtrl_effect__lr0(handle);
	} 
	if (trafficLightCtrl_check_main_region_off_tr0_tr0(handle) == bool_true)
	{ 
		trafficLightCtrl_effect_main_region_off_tr0(handle);
	}  else
	{
		if (trafficLightCtrl_check_main_region_off_r1_YellowOn_tr0_tr0(handle) == bool_true)
		{ 
			trafficLightCtrl_effect_main_region_off_r1_YellowOn_tr0(handle);
		} 
	}
}

/* The reactions of state YellowOff. */
static void trafficLightCtrl_react_main_region_off_r1_YellowOff(TrafficLightCtrl* handle)
{
	/* The reactions of state YellowOff. */
	if (trafficLightCtrl_check__lr0(handle) == bool_true)
	{ 
		trafficLightCtrl_effect__lr0(handle);
	} 
	if (trafficLightCtrl_check_main_region_off_tr0_tr0(handle) == bool_true)
	{ 
		trafficLightCtrl_effect_main_region_off_tr0(handle);
	}  else
	{
		if (trafficLightCtrl_check_main_region_off_r1_YellowOff_tr0_tr0(handle) == bool_true)
		{ 
			trafficLightCtrl_effect_main_region_off_r1_YellowOff_tr0(handle);
		} 
	}
}

/* Default react sequence for initial entry  */
static void trafficLightCtrl_react_main_region__entry_Default(TrafficLightCtrl* handle)
{
	/* Default react sequence for initial entry  */
	trafficLightCtrl_enseq_main_region_off_default(handle);
}

/* Default react sequence for initial entry  */
static void trafficLightCtrl_react_main_region_on_r1_PedWaiting_r1__entry_Default(TrafficLightCtrl* handle)
{
	/* Default react sequence for initial entry  */
	trafficLightCtrl_enseq_main_region_on_r1_PedWaiting_r1_waitOn_default(handle);
}

/* Default react sequence for initial entry  */
static void trafficLightCtrl_react_main_region_on_r1__entry_Default(TrafficLightCtrl* handle)
{
	/* Default react sequence for initial entry  */
	trafficLightCtrl_enseq_main_region_on_r1_Safe_default(handle);
}

/* Default react sequence for initial entry  */
static void trafficLightCtrl_react_main_region_off_r1__entry_Default(TrafficLightCtrl* handle)
{
	/* Default react sequence for initial entry  */
	trafficLightCtrl_enseq_main_region_off_r1_YellowOn_default(handle);
}


