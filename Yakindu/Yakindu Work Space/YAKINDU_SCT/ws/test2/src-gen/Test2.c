
#include <stdlib.h>
#include <string.h>
#include "..\src\sc_types.h"
#include "Test2.h"
/*! \file Implementation of the state machine 'test2'
*/

/* prototypes of all internal functions */
static void test2_enseq_main_region_StateA_default(Test2* handle);
static void test2_enseq_main_region_default(Test2* handle);
static void test2_exseq_main_region_StateA(Test2* handle);
static void test2_exseq_main_region(Test2* handle);
static void test2_react_main_region_StateA(Test2* handle);
static void test2_react_main_region__entry_Default(Test2* handle);
static void test2_clearInEvents(Test2* handle);
static void test2_clearOutEvents(Test2* handle);


void test2_init(Test2* handle)
{
	sc_integer i;

	for (i = 0; i < TEST2_MAX_ORTHOGONAL_STATES; ++i)
	{
		handle->stateConfVector[i] = Test2_last_state;
	}
	
	
	handle->stateConfVectorPosition = 0;

	test2_clearInEvents(handle);
	test2_clearOutEvents(handle);


}

void test2_enter(Test2* handle)
{
	/* Default enter sequence for statechart test2 */
	test2_enseq_main_region_default(handle);
}

void test2_exit(Test2* handle)
{
	/* Default exit sequence for statechart test2 */
	test2_exseq_main_region(handle);
}

sc_boolean test2_isActive(const Test2* handle)
{
	sc_boolean result;
	if (handle->stateConfVector[0] != Test2_last_state)
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
sc_boolean test2_isFinal(const Test2* handle)
{
   return bool_false;
}

static void test2_clearInEvents(Test2* handle)
{
}

static void test2_clearOutEvents(Test2* handle)
{
}

void test2_runCycle(Test2* handle)
{
	
	test2_clearOutEvents(handle);
	
	for (handle->stateConfVectorPosition = 0;
		handle->stateConfVectorPosition < TEST2_MAX_ORTHOGONAL_STATES;
		handle->stateConfVectorPosition++)
		{
			
		switch (handle->stateConfVector[handle->stateConfVectorPosition])
		{
		case Test2_main_region_StateA :
		{
			test2_react_main_region_StateA(handle);
			break;
		}
		default:
			break;
		}
	}
	
	test2_clearInEvents(handle);
}


sc_boolean test2_isStateActive(const Test2* handle, Test2States state)
{
	sc_boolean result = bool_false;
	switch (state)
	{
		case Test2_main_region_StateA :
			result = (sc_boolean) (handle->stateConfVector[0] == Test2_main_region_StateA
			);
			break;
		default:
			result = bool_false;
			break;
	}
	return result;
}




/* implementations of all internal functions */

/* 'default' enter sequence for state StateA */
static void test2_enseq_main_region_StateA_default(Test2* handle)
{
	/* 'default' enter sequence for state StateA */
	handle->stateConfVector[0] = Test2_main_region_StateA;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for region main region */
static void test2_enseq_main_region_default(Test2* handle)
{
	/* 'default' enter sequence for region main region */
	test2_react_main_region__entry_Default(handle);
}

/* Default exit sequence for state StateA */
static void test2_exseq_main_region_StateA(Test2* handle)
{
	/* Default exit sequence for state StateA */
	handle->stateConfVector[0] = Test2_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for region main region */
static void test2_exseq_main_region(Test2* handle)
{
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of test2.main_region) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case Test2_main_region_StateA :
		{
			test2_exseq_main_region_StateA(handle);
			break;
		}
		default: break;
	}
}

/* The reactions of state StateA. */
static void test2_react_main_region_StateA(Test2* handle)
{
	/* The reactions of state StateA. */
}

/* Default react sequence for initial entry  */
static void test2_react_main_region__entry_Default(Test2* handle)
{
	/* Default react sequence for initial entry  */
	test2_enseq_main_region_StateA_default(handle);
}


