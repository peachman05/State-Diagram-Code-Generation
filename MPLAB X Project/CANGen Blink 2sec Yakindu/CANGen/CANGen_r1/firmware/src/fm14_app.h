/* 
 * File:   fm14_app.h
 * Author: HWUser12
 *
 * Created on January 20, 2016, 2:41 PM
 */

#ifndef FM14_APP_H
#define	FM14_APP_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"

// *****************************************************************************

#define XCPDATA_BEGINADDRESS 0xA0005000
#define XCPDATA_DUTINADDRESS 0xA0005048

// *****************************************************************************

typedef struct
{
    uint8_t nbyte;
    uint8_t Ins;
    uint8_t writebuffer[34];
    uint8_t readbuffer[36];


}fm14_t;



// *****************************************************************************

void FM14_tasks (void);

#endif	/* FM14_APP_H */

