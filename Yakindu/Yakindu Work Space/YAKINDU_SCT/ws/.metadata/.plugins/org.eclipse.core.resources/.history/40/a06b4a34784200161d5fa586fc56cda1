
#ifndef LIGHTSWITCH_H_
#define LIGHTSWITCH_H_

#include "..\src\sc_types.h"
		
#ifdef __cplusplus
extern "C" { 
#endif 

/*! \file Header of the state machine 'LightSwitch'.
*/

/*! Enumeration of all states */ 
typedef enum
{
	LightSwitch_main_region_off,
	LightSwitch_main_region_on,
	LightSwitch_last_state
} LightSwitchStates;

/*! Type definition of the data structure for the LightSwitchInternal interface scope. */
typedef struct
{
	sc_boolean operate_raised;
} LightSwitchInternal;


/*! Define dimension of the state configuration vector for orthogonal states. */
#define LIGHTSWITCH_MAX_ORTHOGONAL_STATES 1

/*! 
 * Type definition of the data structure for the LightSwitch state machine.
 * This data structure has to be allocated by the client code. 
 */
typedef struct
{
	LightSwitchStates stateConfVector[LIGHTSWITCH_MAX_ORTHOGONAL_STATES];
	sc_ushort stateConfVectorPosition; 
	
	LightSwitchInternal internal;
} LightSwitch;

/*! Initializes the LightSwitch state machine data structures. Must be called before first usage.*/
extern void lightSwitch_init(LightSwitch* handle);

/*! Activates the state machine */
extern void lightSwitch_enter(LightSwitch* handle);

/*! Deactivates the state machine */
extern void lightSwitch_exit(LightSwitch* handle);

/*! Performs a 'run to completion' step. */
extern void lightSwitch_runCycle(LightSwitch* handle);



/*!
 * Checks whether the state machine is active (until 2.4.1 this method was used for states).
 * A state machine is active if it was entered. It is inactive if it has not been entered at all or if it has been exited.
 */
extern sc_boolean lightSwitch_isActive(const LightSwitch* handle);

/*!
 * Checks if all active states are final. 
 * If there are no active states then the state machine is considered being inactive. In this case this method returns false.
 */
extern sc_boolean lightSwitch_isFinal(const LightSwitch* handle);

/*! Checks if the specified state is active (until 2.4.1 the used method for states was called isActive()). */
extern sc_boolean lightSwitch_isStateActive(const LightSwitch* handle, LightSwitchStates state);

#ifdef __cplusplus
}
#endif 

#endif /* LIGHTSWITCH_H_ */
