/* 
 * File:   bb_no_led.h
 * Author: HWUser13
 *
 * Created on July 27, 2015, 10:31 AM
 */

#ifndef BB_NO_LED_H
#define	BB_NO_LED_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "system_definitions.h"

    typedef enum {
        LED_RED,
                LED_GREEN,
                LED_YELLOW,
    }led_color;

    typedef enum {
        LED_ON,
                LED_OFF,
    }led_st;

/*
 * function name    : void led_init()
 *
 * description      : initialize LED on Baseboard
 *
 * argument
 *
 * return
 */
extern void led_init();

/*
 * function name    : void led_init()
 *
 * description      : initialize LED on Baseboard
 *
 * argument
 *
 * return
 */
extern void led_deinit();

/*
 * function name    : void led_on()
 *
 * description      : turn on LED on Baseboard
 *
 * argument
 *      arg_led     :   color of LED
 *
 * return
 */
extern void led_on(led_color arg_led);

/*
 * function name    : void led_off()
 *
 * description      : turn off LED on Baseboard
 *
 * argument
 *      arg_led     :   color of LED
 *
 * return
 */
extern void led_off(led_color arg_led);

/*
 * function name    : void led_toggle()
 *
 * description      : toggle LED on Baseboard
 *
 * argument
 *      arg_led     :   color of LED
 *
 * return
 */
extern void led_toggle(led_color arg_led);

/*
 * function name    : void led_status()
 *
 * description      : read LED status on Baseboard
 *
 * argument
 *      arg_led     :   color of LED
 *
 * return
 *      led_st      :   status of LED
 */
extern led_st led_status(led_color arg_led);


#ifdef	__cplusplus
}
#endif

#endif	/* BB_NO_LED_H */

