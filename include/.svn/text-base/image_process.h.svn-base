/******************************************************************************

   Copyright (C), 2013-,    Zjut Image Processing Lab.    All rights reserved. 

*******************************************************************************
 * File Name : image_process.h
 * Version : 1.0
 * Author : Gzz
 * Created : 2013/8/5
 * Last Modified :
 * Description : image_process.c header file
 * Function List :
 * Modification History :
   1.Date : 2013/8/5
     Author : Gzz
     Modification : Created file
 
******************************************************************************/

#ifndef __IMAGE_PROCESS_H__
#define __IMAGE_PROCESS_H__


typedef struct
{
    
    Uint8 recog_asiic[2]; // recongise asiic
    Uint8 recog_direct[2];//recognise direction
    Int8 x_offset;
    Int8 y_offset;
    Uint8 move_flag; //goal move exist flag
    
}recog_result;

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

extern void copy_vpfe_to_vpbe(Uint8 *vpfe_buf, Uint8 *vpbe_buf);

extern void copy_vpfe_to_resize(Uint8 *vpfe_buf, Uint8 *resize_buf);

extern Uint8 image_process();

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __IMAGE_PROCESS_H__ */
