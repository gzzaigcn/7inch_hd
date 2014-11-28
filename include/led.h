/******************************************************************************

   Copyright (C), 2013-,    Zjut Image Processing Lab.    All rights reserved. 

*******************************************************************************
 * File Name : led.h
 * Version : 1.0
 * Author : Gzz
 * Created : 2013/7/15
 * Last Modified :
 * Description : led.h header file
 * Function List :
 * Modification History :
   1.Date : 2013/7/15
     Author : Gzz
     Modification : Created file
 
******************************************************************************/

#ifndef __LED_H__
#define __LED_H__

#include "dm6437.h"
#include "dm6437_gpio.h"

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */


#define LED0_GPIO_ID  GPIO02
#define LED_ON       1
#define LED_OFF     0


#define LED_PERIOD_BLINK_MODE 0
#define LED_AWALYS_BLINK_MODE 1

#define LED_BLINK_PERIOD 100000 

volatile extern Uint8 led_blink_mode;
volatile extern Uint32 led_blink_num;
volatile extern Uint8 led_blink_stop_flag;

void dm6437_timer1_init();
void dm6437_led_init(Uint16 led_gpio_id);
void dm6437_led_on( Uint16 led_gpio_id);
void dm6437_led_period_blink( Uint16 led_gpio_id, Uint32 period, Uint32 blinknum );
void dm6437_led_awalys_blink( Uint16 led_gpio_id, Uint32 period);
void dm6437_led_off (Uint16 led_gpio_id);




#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __LED_H__ */

