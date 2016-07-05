#include "led.h"

/*
 * function name    : void led_init()
 *
 * description      : initialize LED on Baseboard
 *
 * argument
 *
 * return
 */
void led_init()
{
    SYS_PORTS_PinDirectionSelect(PORTS_ID_0, SYS_PORTS_DIRECTION_OUTPUT, PORT_CHANNEL_G, PORTS_BIT_POS_12);
    SYS_PORTS_PinDirectionSelect(PORTS_ID_0, SYS_PORTS_DIRECTION_OUTPUT, PORT_CHANNEL_G, PORTS_BIT_POS_13);
    SYS_PORTS_PinDirectionSelect(PORTS_ID_0, SYS_PORTS_DIRECTION_OUTPUT, PORT_CHANNEL_G, PORTS_BIT_POS_14);

    SYS_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_12);
    SYS_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_13);
    SYS_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_14);
}

/*
 * function name    : void led_init()
 *
 * description      : initialize LED on Baseboard
 *
 * argument
 *
 * return
 */
void led_deinit()
{
    SYS_PORTS_PinDirectionSelect(PORTS_ID_0, SYS_PORTS_DIRECTION_INPUT, PORT_CHANNEL_G, PORTS_BIT_POS_12);
    SYS_PORTS_PinDirectionSelect(PORTS_ID_0, SYS_PORTS_DIRECTION_INPUT, PORT_CHANNEL_G, PORTS_BIT_POS_13);
    SYS_PORTS_PinDirectionSelect(PORTS_ID_0, SYS_PORTS_DIRECTION_INPUT, PORT_CHANNEL_G, PORTS_BIT_POS_14);
}

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
void led_on(led_color arg_led)
{
    switch(arg_led) {
        case LED_RED :
            // 14
            SYS_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_14);
            break;
        case LED_GREEN :
            // 13
            SYS_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_13);
            break;
        case LED_YELLOW :
            SYS_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_12);
            break;
        default :
            break;
    }
}

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
void led_off(led_color arg_led)
{
    switch(arg_led) {
        case LED_RED :
            // 14
            SYS_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_14);
            break;
        case LED_GREEN :
            // 13
            SYS_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_13);
            break;
        case LED_YELLOW :
            SYS_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_12);
            break;
        default :
            break;
    }
}

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
void led_toggle(led_color arg_led)
{
    switch(arg_led) {
        case LED_RED :
            SYS_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_14);
            break;
        case LED_GREEN :
            SYS_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_13);
            break;
        case LED_YELLOW :
            SYS_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_12);
            break;
        default :
            break;
    }
}

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
led_st led_status(led_color arg_led)
{
    switch(arg_led) {
        case LED_RED :
            return SYS_PORTS_PinRead(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_14);
        case LED_GREEN :
            return SYS_PORTS_PinRead(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_13);
        case LED_YELLOW :
            return SYS_PORTS_PinRead(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_12);
        default :
            break;
    }
}