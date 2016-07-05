#include <stdio.h>
#include <stdlib.h>
#include "src/sc_types.h"
#include "src-gen/LightSwitch.h"

LightSwitch handle;

int main()
{
    lightSwitch_init(&handle);

    lightSwitch_enter(&handle);

   // handle.internal.operate_raised = false;
    lightSwitch_runCycle(&handle);

    handle.internal.operate_raised = true;
    lightSwitch_runCycle(&handle); //just change to on state

   // handle.internal.operate_raised = true;
    lightSwitch_runCycle(&handle);

    lightSwitch_runCycle(&handle);

  //  handle.internal.operate_raised = true;
   // lightSwitch_runCycle(&handle);



    return 0;
}
