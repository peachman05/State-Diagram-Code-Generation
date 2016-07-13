#include "src/sc_types.h"
#include "src-gen/CallHandling.h"
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {
	CallHandling handle;
    callHandling_init(&handle);
    callHandling_enter(&handle);

    callHandlingIfacePhone_raise_incoming_call(&handle);
    callHandling_runCycle(&handle);

    callHandlingIfaceUser_raise_accept_call(&handle);
    callHandling_runCycle(&handle);
    int i;
    for (i = 0; i < 50; i++) {
          delay(200);
          callHandling_runCycle(&handle);  //  sm.runCycle();
    }

          // Before hang-up, output the duration of the call:
     printf("The phone call took %d seconds.",callHandlingIfacePhone_get_duration(&handle));
     callHandlingIfaceUser_raise_dismiss_call(&handle);
     callHandling_runCycle(&handle);
}
