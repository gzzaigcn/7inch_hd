/******************************************************************************

   Copyright (C), 2014-,    Du-Health Electron Co.    All rights reserved. 

*******************************************************************************
 * File Name : debug.h
 * Version : 1.0
 * Author : gzz
 * Created : 2014/9/14
 * Last Modified :
 * Description : debug.h header file for sys/drivers debug
 * Function List :
 * Modification History :
   1.Date : 2014/9/14
     Author : gzz
     Modification : Created file
 
******************************************************************************/
#include "stdio.h"

#ifndef __DEBUG_H__
#define __DEBUG_H__

#define DBG_EN 1
#define ERR_EN 1

#if DBG_EN

/*system app debug*/
#define SYS_DBG(fmt, arg...) printf(fmt"\n",##arg); 

/*device drivers debug*/
#define DEV_DBG(fmt, arg...) printf("[" MODULE_NAME "]"fmt"\n",##arg); 

#else

#define SYS_DBG(fmt, arg...) 
#define DEV_DBG(fmt, arg...)

#endif


#if ERR_EN

#define SYS_ERR(fmt, arg...) \
    do{\
        printf("file: %s, func: %s, line: %d\n", __FILE__,  __FUNCTION__, __LINE__);\
        printf("SYS_ERR:"fmt"\n",##arg);  \
    }while(0)

/*error awlays printf*/
#define DEV_ERR(fmt, arg...) printf("[" MODULE_NAME "]" "DEV ERR:" fmt "\n",##arg); 

#else

#define SYS_ERR(fmt, arg...) 
#define DEV_ERR(fmt, arg...)

#endif



#endif /* __DEBUG_H__ */

