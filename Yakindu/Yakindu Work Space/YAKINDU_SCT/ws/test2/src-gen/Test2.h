
#ifndef TEST2_H_
#define TEST2_H_

#include "..\src\sc_types.h"
		
#ifdef __cplusplus
extern "C" { 
#endif 

/*! \file Header of the state machine 'test2'.
*/

/*! Enumeration of all states */ 
typedef enum
{
	Test2_main_region_StateA,
	Test2_last_state
} Test2States;


/*! Define dimension of the state configuration vector for orthogonal states. */
#define TEST2_MAX_ORTHOGONAL_STATES 1

/*! 
 * Type definition of the data structure for the Test2 state machine.
 * This data structure has to be allocated by the client code. 
 */
typedef struct
{
	Test2States stateConfVector[TEST2_MAX_ORTHOGONAL_STATES];
	sc_ushort stateConfVectorPosition; 
	
} Test2;

/*! Initializes the Test2 state machine data structures. Must be called before first usage.*/
extern void test2_init(Test2* handle);

/*! Activates the state machine */
extern void test2_enter(Test2* handle);

/*! Deactivates the state machine */
extern void test2_exit(Test2* handle);

/*! Performs a 'run to completion' step. */
extern void test2_runCycle(Test2* handle);



/*!
 * Checks whether the state machine is active (until 2.4.1 this method was used for states).
 * A state machine is active if it was entered. It is inactive if it has not been entered at all or if it has been exited.
 */
extern sc_boolean test2_isActive(const Test2* handle);

/*!
 * Checks if all active states are final. 
 * If there are no active states then the state machine is considered being inactive. In this case this method returns false.
 */
extern sc_boolean test2_isFinal(const Test2* handle);

/*! Checks if the specified state is active (until 2.4.1 the used method for states was called isActive()). */
extern sc_boolean test2_isStateActive(const Test2* handle, Test2States state);

#ifdef __cplusplus
}
#endif 

#endif /* TEST2_H_ */
