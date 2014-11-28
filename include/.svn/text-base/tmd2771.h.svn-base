/******************************************************************************

   Copyright (C), 2014-,    Du-Health Electron Co.    All rights reserved. 

*******************************************************************************
 * File Name : tmd2771.h
 * Version : 1.0
 * Author : gzz
 * Created : 2014/9/13
 * Last Modified :
 * Description : tmd2771.c header file
 * Function List :
 * Modification History :
   1.Date : 2014/9/13
     Author : gzz
     Modification : Created file
 
******************************************************************************/


#ifndef __TMD2771_H__
#define __TMD2771_H__

#define TMD2771_HIGH_BYTE_MASK 1
#define TMD2771_LOW_BYTE_MASK 0

#define TMD2771_ALS_CH0 0
#define TMD2771_ALS_CH1 1


/*tmd2771 default init paramers */
#define TMD2771_DEF_ALS_UPPER  3000
#define TMD2771_DEF_ALS_LOWER  10

#define TMD2771_DEF_PROX_UPPER 500
#define TMD2771_DEF_PROX_LOWER 400


#define TMD2771_DEF_ATIME 0xff
#define TMD2771_DEF_PTIME  0xff
#define TMD2771_DEF_WTIME 0xff
#define TMD2771_DEF_PERS    0x11
#define TMD2771_DEF_PPULSE 0x08

/*Marco for Enable Register*/
#define TMD2771_ENABLE_AEN     (1 << 1)
#define TMD2771_ENABLE_PEN     (1 << 2)
#define TMD2771_ENALBE_WEN    (1 << 3)
#define TMD2771_ENALBE_AIEN    (1 << 4)
#define TMD2771_ENALBE_PIEN    (1 << 5)


/*Enum value for TMd2771 Control Register  to the analog block*/
//LED Drive Strength
typedef enum {

    LED_STRENGTH_100 = 0,   //100%
    LED_STRENGTH_50 ,           //50%
    LED_STRENGTH_25,            //25%
    LED_STRENGTH_12_5,  //12.5%

}CTRL_LED_DRIVE;


//Proximity Diode Select
typedef enum {

    PROX_DIODE_0 = 1,    //Proximity uses the Channel 0 diode
    PROX_DIODE_1,          //Proximity uses the Channel 1 diode
    PROX_DIODE_BOTH,    //Proximity uses both diode
    
}CTRL_PROX_DIODE;


//ALS Gain Control
typedef enum {

    ALS_GAIN_1 = 0,    //1X
    ALS_GAIN_8,         //8X
    ALS_GAIN_16,        //16X
    ALS_GAIN_120,    //120X
    
}CTRL_ALS_GAINS;



#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

extern void tmd2771_cfg_timer(Uint16 atime, Uint16 ptime, Uint8 wtime, Uint8 ppluse, Uint8 pers);
extern void tmd2771_clear_int_flag(Uint8 type);
extern void tmd2771_ctrl_analog_block(CTRL_ALS_GAINS als_gain, CTRL_PROX_DIODE pdiode, CTRL_LED_DRIVE pdrive);

extern void tmd2771_disable();

extern void tmd2771_enable(Uint8 en_cfg);

extern Uint16 tmd2771_get_als_data(Uint8 channel);
extern Uint16 tmd2771_get_prox_adc_data();

extern void tmd2771_set_als_thrd(Uint16 thrd, Uint8 mark);
extern void tmd2771_set_prox_thrd(Uint16 thrd, Uint8 mark);

extern Int8 tmd2771_init();

extern void tmd2771_clear_int();


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __TMD2771_H__ */
