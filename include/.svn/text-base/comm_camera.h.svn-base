/******************************************************************************

   Copyright (C), 2014-,    Du-Health Electron Co.    All rights reserved. 

*******************************************************************************
 * File Name : camera_common.h
 * Version : 1.0
 * Author : gzz
 * Created : 2014/9/4
 * Last Modified :
 * Description : ov2710.c header file
 * Function List :
 * Modification History :
   1.Date : 2014/9/4
     Author : gzz
     Modification : Created file
 
******************************************************************************/

#ifndef __COMM_CAMERA_H__
#define __COMM_CAMERA_H__

#include "dm6437.h"
#include "dm6437_gpio.h"


#define SUPPORT_CAMERA_NUM 2

typedef enum {

    CAMERA_OV2710 = 0,
    CAMERA_OV5640,
    
}CAMERA_DEVICE_NAME;


#define CAMERA_GPIO_POWER GPIO64
#define CAMERA_GPIO_STBY    GPIO34
#define CAMERA_GPIO_RESET  GPIO35

#define ARRAY_SIZE(array)  (sizeof(array)/sizeof(array[0]))

struct reg_list_a8_d8 {
  unsigned char addr;
  unsigned char data;
};

struct reg_list_a8_d16 {
  unsigned char addr;
  unsigned short data;
};

struct reg_list_a16_d8 {
  unsigned short addr;
  unsigned char data;
};


typedef enum power_type{

    CAMERA_CTRL_PWR_ON = 0x00,
    CAMERA_CTRL_PWR_OFF,
    CAMERA_CTRL_STBY_ON,
    CAMERA_CTRL_STBY_OFF
    
}CAMERA_CTRL_POWER_TYPE;

typedef Int8 (*pcamera_init)(void);
typedef Int8 (*pcamera_ctrl_power)(Uint8 ctrl_id);

typedef struct {

    char *camera_name;
    pcamera_init camera_init;
    pcamera_ctrl_power camera_ctrl_power;

}camera_ops;


#define camera_list_item(name) { \
    .camera_name = #name,\
    .camera_init = camera_##name##_init, \
    .camera_ctrl_power = camera_##name##_ctrl_power,\
}\



#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __OV2710_H__ */
