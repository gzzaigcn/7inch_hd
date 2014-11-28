/******************************************************************************

   Copyright (C), 2014-,    Zjut Image Processing Lab.    All rights reserved. 

*******************************************************************************
 * File Name : coefs.h
 * Version : 1.0
 * Author : gzz
 * Created : 2014/6/10
 * Last Modified :
 * Description : coefs.h header file
 * Function List :
 * Modification History :
   1.Date : 2014/6/10
     Author : gzz
     Modification : Created file
 
******************************************************************************/


#ifndef __COEFS_H__
#define __COEFS_H__


#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */


static Int16 coefs[2][32] = {

    {
        
         -1, 19, 108, 112, 19, -1, 0, 0, 
            0, 6, 88, 126, 37, -1, 0, 0, 0, 0, 61, 134, 61, 0, 0, 0, 0, -1, 37, 
        126, 88, 6, 0, 0


     },

     /*vertical resizing filter coefficients: */
     {
   
    -1, 19, 108, 112, 19, -1, 0, 0, 
       0, 6, 88, 126, 37, -1, 0, 0, 0, 0, 61, 134, 61, 0, 0, 0, 0, -1, 37, 
   126, 88, 6, 0, 0
   
     }

};

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __COEFS_H__ */
