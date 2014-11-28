/******************************************************************************

   Copyright (C), 2013-,    Zjut Image Processing Lab.    All rights reserved. 

*******************************************************************************
 * File Name : buzzer.h
 * Version : 1.0
 * Author : Gzz
 * Created : 2013/7/15
 * Last Modified :
 * Description : buzzer.h header file
 * Function List :
 * Modification History :
   1.Date : 2013/7/15
     Author : Gzz
     Modification : Created file
 
******************************************************************************/

#ifndef __BUZZER_H__
#define __BUZZER_H__

#include "dm6437.h"
#include "dm6437_gpio.h"

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#define BUZZER_GPIO_ID GPIO04

#define BUZZER_ONE_MODE    1
#define BUZZER_CONTINUOUS_MODE    2
#define BUZZER_TICKS_MODE 3

#define BUZZER_4KHZ      0x1A5E
#define BUZZER_3KHZ      0x2328
#define BUZZER_2KHZ      0x34BC
#define BUZZER_1KHZ      0x6978
#define BUZZER_500HZ    0xD2F0

#define BUZZER_POWERON_REPT_NUM       1000
#define BUZZER_ALARM_REPT_NUM 200

typedef struct {

    Uint32 pid;
    Uint32 pcr;
    Uint32 cfg;
    Uint32 start;
    Uint32 rpt;
    Uint32 per;
    Uint32 ph1d;

}pwm_reg;

typedef struct {
    
    pwm_reg *reg;
    Uint8 work_type;
    Uint8 work_cfg;
    Uint32 work_times;
    Uint32 rept;
    Uint32 period;
    Uint32 ph1d;
    Uint8 end_flag;
    
}buzzer_obj;
typedef buzzer_obj* buzzer_handle;

extern void dm6437_buzzer_init(Uint8 work_type, Uint32 buzzer_freq, Uint32 rept_num, Uint32 times);
extern void config_dm6437_buzzer(Uint8 work_type, Uint32 buzzer_freq, Uint32 rept_num, Uint32 times);
extern void dm6437_buzzer_off();
extern void dm6437_buzzer_on();


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __BUZZER_H__ */

