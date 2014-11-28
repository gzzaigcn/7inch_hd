/******************************************************************************

   Copyright (C), 2013-,    Zjut Image Processing Lab.    All rights reserved. 

*******************************************************************************
 * File Name : key.h
 * Version : 1.0
 * Author : Gzz
 * Created : 2013/7/15
 * Last Modified :
 * Description : key.h header file
 * Function List :
 * Modification History :
   1.Date : 2013/7/15
     Author : Gzz
     Modification : Created file
 
******************************************************************************/

#ifndef __KEY_H__
#define __KEY_H__

#include "dm6437.h"
#include "dm6437_gpio.h"

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/*Four Key GPIO Bank id*/
#define KEY1_GPIO_ID               GPIO75
#define KEY2_GPIO_ID               GPIO76
#define KEY3_GPIO_ID               GPIO77
#define KEY4_GPIO_ID               GPIO78
#define ALL_KEY_GPIO_ID         GPIO75 | GPIO76 | GPIO77 | GPIO78

/*    Four Key ID    */
#define KEY_SW1 0x00
#define KEY_SW2 0x01
#define KEY_SW3 0x02
#define KEY_SW4 0x03

#define KEY_STATE_LONG
#define KEY_STATE_SHORT
#define KEY_STATE_RUNNING
#define KEY_STATE_IDLE

typedef void (*KEY_PROCESS)(Uint8 key_value);


void dm6437_key_init();
Int32 key_process();


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __KEY_H__ */
