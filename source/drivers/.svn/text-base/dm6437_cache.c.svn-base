/******************************************************************************

   Copyright (C), 2014-,    Du-Health Electron Co.    All rights reserved. 

*******************************************************************************
 * File Name : dm6437_cache.c
 * Version : 1.0
 * Author : gzz
 * Created : 2014/9/3
 * Last Modified :
  Description   : dm6437 cache module
 * Function List :
              Cache_InitCache
              Cache_Invalid
              Cache_WriteBack
              Cache_WriteBackInvalid
 * Modification History :
   1.Date : 2014/9/3
     Author : gzz
     Modification : Created file
 
******************************************************************************/


#include "dm6437_cache.h"
#include <csl_cache.h>


/*!
\brief
Cache初始化函数
  - Function:             void Cache_InitCache()
  - Description:          Cache初始化
  - Calls:                   none
  - Called by:            Main
  - Table Accessed:      none   
  - Table Updated:        none
  - Input:                 
  
    - Output:                  none
    - Return:                   none
    - Others:                  none        
    
*/
void Cache_InitCache()
{
  /* Turn data caching off. */
#ifdef CACHEON

	CACHE_invAllL1p(CACHE_WAIT);
	CACHE_wbInvAllL1d(CACHE_WAIT);
	CACHE_wbInvAllL2(CACHE_WAIT);
	CACHE_setL1pSize(CACHE_L1_32KCACHE);//L1P 32kb
	CACHE_setL1dSize(CACHE_L1_32KCACHE); //L1d 32kb
	CACHE_setL2Size(CACHE_64KCACHE);  //L2 64kb

	CACHE_enableCaching(CACHE_EMIFA_CE00);
	CACHE_enableCaching(CACHE_EMIFA_CE01);
	CACHE_enableCaching(CACHE_EMIFA_CE02);
	CACHE_enableCaching(CACHE_EMIFA_CE03); 
       CACHE_enableCaching(CACHE_EMIFA_CE04);
	CACHE_enableCaching(CACHE_EMIFA_CE05);
	CACHE_enableCaching(CACHE_EMIFA_CE06);
	CACHE_enableCaching(CACHE_EMIFA_CE07); //128M DDR2 All Cache Enable,MAR128-MAR135
	
#else

  CACHE_setL1pSize(CACHE_L1_0KCACHE);
  CACHE_setL1dSize(CACHE_L1_0KCACHE);
  CACHE_setL2Size(CACHE_0KCACHE);

#endif
}

/*!
\brief
 Cache无效函数
  - Function:             void Cache_Invalid()
  - Description:           Cache无效
  - Calls:                   none
  - Called by:            
  - Table Accessed:      none   
  - Table Updated:        none
  - Input:                 
  
    - Output:                  none
    - Return:                   none
    - Others:                  none        
    
*/
void Cache_Invalid(void *blockPtr,Uint32 byteCnt)
{
#ifdef CACHEON
     CACHE_invL1d(blockPtr, byteCnt, CACHE_WAIT);
     CACHE_invL2(blockPtr, byteCnt, CACHE_WAIT);

#endif
}

/*!
\brief
Cache写回函数
  - Function:             void Cache_WriteBack()
  - Description:          Cache写回函数
  - Calls:                   none
  - Called by:           
  - Table Accessed:      none   
  - Table Updated:        none
  - Input:                 
  
    - Output:                  none
    - Return:                   none
    - Others:                  none        
    
*/
void Cache_WriteBack(void *blockPtr,Uint32 byteCnt)
{
#ifdef CACHEON
     CACHE_wbL1d(blockPtr, byteCnt, CACHE_WAIT);
     CACHE_wbL2(blockPtr, byteCnt, CACHE_WAIT);
#endif
}

/*!
\brief
Cache写回并无效函数
  - Function:             void Cache_InitCache()
  - Description:          Cache写回并无效
  - Calls:                   none
  - Called by:            
  - Table Accessed:      none   
  - Table Updated:        none
  - Input:                 
  
    - Output:                  none
    - Return:                   none
    - Others:                  none        
    
*/
void Cache_WriteBackInvalid(void *blockPtr,Uint32 byteCnt)
{
#ifdef CACHEON
     CACHE_wbInvL1d(blockPtr, byteCnt, CACHE_WAIT);
     CACHE_wbInvL2(blockPtr, byteCnt, CACHE_WAIT);
#endif
}

