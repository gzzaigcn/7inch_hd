/******************************************************************************

   Copyright (C), 2013-,    Zjut Image Processing Lab.    All rights reserved. 

*******************************************************************************
 * File Name : jpeg_alg.h
 * Version : 1.0
 * Author : Gzz
 * Created : 2013/10/16
 * Last Modified :
 * Description : jpeg_alg.c header file
 * Function List :
 * Modification History :
   1.Date : 2013/10/16
     Author : Gzz
     Modification : Created file
 
******************************************************************************/

#ifndef __JPEG_ALG_H__
#define __JPEG_ALG_H__

#include <std.h>
#include <ti/xdais/xdas.h>
#include <ti/xdais/ialg.h>
#include <ti/xdais/dm/iimgenc1.h>
#include <ti/xdais/dm/xdm.h>



#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */



extern void jpeg_alg_init();
extern void jpeg_decode(Uint8 *pin_buf, Uint8 *pout_buf, Uint32 dim );
extern void jpeg_encode(Uint8 *pin_buf, Uint8 *pout_buf);


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __JPEG_ALG_H__ */
