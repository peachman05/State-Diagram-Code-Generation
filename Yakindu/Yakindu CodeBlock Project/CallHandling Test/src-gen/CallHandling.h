
#ifndef CALLHANDLING_H_
#define CALLHANDLING_H_

#include "..\src\sc_types.h"
		
#ifdef __cplusplus
extern "C" { 
#endif 

/*! \file Header of the state machine 'CallHandling'.
*/

/*! Enumeration of all states */ 
typedef enum
{
	CallHandling_main_region_Idle,
	CallHandling_main_region_Incoming_Call,
	CallHandling_main_region_Active_Call,
	CallHandling_main_region_Dismiss_Call,
	CallHandling_last_state
} CallHandlingStates;

/*! Type definition of the data structure for the CallHandlingIfaceUser interface scope. */
typedef struct
{
	sc_boolean accept_call_raised;
	sc_boolean dismiss_call_raised;
} CallHandlingIfaceUser;

/*! Type definition of the data structure for the CallHandlingIfacePhone interface scope. */
typedef struct
{
	sc_integer duration;
	sc_boolean incoming_call_raised;
} CallHandlingIfacePhone;

/*! Type definition of the data structure for the CallHandlingTimeEvents interface scope. */
typedef struct
{
	sc_boolean callHandling_main_region_Active_Call_tev0_raised;
	sc_boolean callHandling_main_region_Dismiss_Call_tev0_raised;
} CallHandlingTimeEvents;


/*! Define dimension of the state configuration vector for orthogonal states. */
#define CALLHANDLING_MAX_ORTHOGONAL_STATES 1

/*! 
 * Type definition of the data structure for the CallHandling state machine.
 * This data structure has to be allocated by the client code. 
 */
typedef struct
{
	CallHandlingStates stateConfVector[CALLHANDLING_MAX_ORTHOGONAL_STATES];
	sc_ushort stateConfVectorPosition; 
	
	CallHandlingIfaceUser ifaceUser;
	CallHandlingIfacePhone ifacePhone;
	CallHandlingTimeEvents timeEvents;
} CallHandling;

/*! Initializes the CallHandling state machine data structures. Must be called before first usage.*/
extern void callHandling_init(CallHandling* handle);

/*! Activates the state machine */
extern void callHandling_enter(CallHandling* handle);

/*! Deactivates the state machine */
extern void callHandling_exit(CallHandling* handle);

/*! Performs a 'run to completion' step. */
extern void callHandling_runCycle(CallHandling* handle);

/*! Raises a time event. */
extern void callHandling_raiseTimeEvent(const CallHandling* handle, sc_eventid evid);

/*! Raises the in event 'accept_call' that is defined in the interface scope 'User'. */ 
extern void callHandlingIfaceUser_raise_accept_call(CallHandling* handle);

/*! Raises the in event 'dismiss_call' that is defined in the interface scope 'User'. */ 
extern void callHandlingIfaceUser_raise_dismiss_call(CallHandling* handle);

/*! Gets the value of the variable 'duration' that is defined in the interface scope 'Phone'. */ 
extern sc_integer callHandlingIfacePhone_get_duration(const CallHandling* handle);
/*! Sets the value of the variable 'duration' that is defined in the interface scope 'Phone'. */ 
extern void callHandlingIfacePhone_set_duration(CallHandling* handle, sc_integer value);
/*! Raises the in event 'incoming_call' that is defined in the interface scope 'Phone'. */ 
extern void callHandlingIfacePhone_raise_incoming_call(CallHandling* handle);


/*!
 * Checks whether the state machine is active (until 2.4.1 this method was used for states).
 * A state machine is active if it was entered. It is inactive if it has not been entered at all or if it has been exited.
 */
extern sc_boolean callHandling_isActive(const CallHandling* handle);

/*!
 * Checks if all active states are final. 
 * If there are no active states then the state machine is considered being inactive. In this case this method returns false.
 */
extern sc_boolean callHandling_isFinal(const CallHandling* handle);

/*! Checks if the specified state is active (until 2.4.1 the used method for states was called isActive()). */
extern sc_boolean callHandling_isStateActive(const CallHandling* handle, CallHandlingStates state);

#ifdef __cplusplus
}
#endif 

#endif /* CALLHANDLING_H_ */
