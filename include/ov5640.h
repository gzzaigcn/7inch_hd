/******************************************************************************

   Copyright (C), 2014-,    Du-Health Electron Co.    All rights reserved. 

*******************************************************************************
 * File Name : ov5640.h
 * Version : 1.0
 * Author : gzz
 * Created : 2014/9/5
 * Last Modified :
 * Description : ov5640.c header file
 * Function List :
 * Modification History :
   1.Date : 2014/9/5
     Author : gzz
     Modification : Created file
 
******************************************************************************/
#ifndef __OV5640_H__
#define __OV5640_H__


#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

extern Int8 camera_ov5640_ctrl_power(Uint8 ctrl_id);

extern Int8 camera_ov5640_init();


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __OV5640_H__ */
