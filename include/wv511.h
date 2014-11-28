/******************************************************************************

   Copyright (C), 2014-,    Du-Health Electron Co.    All rights reserved. 

*******************************************************************************
 * File Name : wv511.h
 * Version : 1.0
 * Author : gzz
 * Created : 2014/9/9
 * Last Modified :
 * Description : wv511.c header file
 * Function List :
 * Modification History :
   1.Date : 2014/9/9
     Author : gzz
     Modification : Created file
 
******************************************************************************/
#include "stdio.h"
#include "dm6437.h"

#ifndef __WV511_H__
#define __WV511_H__


typedef struct {

    Int32 work_status;

    Uint16 active_min;
    Uint16 active_max;
    Uint16 total_steps;

    Uint16 curr_pos;
    Uint16 curr_code;
    Uint16 *step_position_table;
    
}actuator_ctrl_t;


extern void wv511_set_code(Uint16 new_code);



#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __WV511_H__ */
