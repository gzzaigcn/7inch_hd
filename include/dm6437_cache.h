/******************************************************************************

   Copyright (C), 2013-,    Zjut Image Processing Lab.    All rights reserved. 

*******************************************************************************
 * File Name : dm6437_cache.h
 * Version : 1.0
 * Author : Gzz
 * Created : 2013/8/5
 * Last Modified :
 * Description : dm6437_cache.c header file
 * Function List :
 * Modification History :
   1.Date : 2013/8/5
     Author : Gzz
     Modification : Created file
 
******************************************************************************/

#ifndef __DM6437_CACHE_H__
#define __DM6437_CACHE_H__

#include "dm6437.h"

#define CACHEON

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

void Cache_InitCache();
void Cache_Invalid(void *blockPtr,Uint32 byteCnt);
void Cache_WriteBack(void *blockPtr,Uint32 byteCnt);
void Cache_WriteBackInvalid(void *blockPtr,Uint32 byteCnt);

#if __cplusplus
}
#endif /* __cplusplus */


#endif /* __DM6437_CACHE_H__ */
