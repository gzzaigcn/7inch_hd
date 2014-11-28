/******************************************************************************

   Copyright (C), 2014-,    Du-Health Electron Co.    All rights reserved. 

*******************************************************************************
 * File Name : img_alg.h
 * Version : 1.0
 * Author : gzz
 * Created : 2014/9/30
 * Last Modified :
 * Description : img_alg.c header file
 * Function List :
 * Modification History :
   1.Date : 2014/9/30
     Author : gzz
     Modification : Created file
 
******************************************************************************/
#ifndef __IMG_ALG_H__
#define __IMG_ALG_H__

#include "global.h"


/*Macro for one 10KB image slice in L0 DRAM*/
#define SLICE_W 80
#define SLICE_H 40
#define SLICE_DIM 1024*10 //10K
#define SLICE_XNUM      (IMAGE_W/SLICE_W)
#define SLICE_YNUM      (IMAGE_H/SLICE_H)


/*BLOCK Macro for OTSU local 10X4 blocks algorithm*/
#define OSTU_BLK_W   80
#define OSTU_BLK_H   120
#define OSTU_BLK_XNUM        (IMAGE_W /OSTU_BLK_W)
#define OSTU_BLK_YNUM        (IMAGE_H /OSTU_BLK_H)


typedef enum {

    TRUE_COLOR_MODE = 0,
    FLASE_COLOR_MODE,
    
}COLOR_MODE;


typedef enum {

    BLACK_WHITE_TYPE=0, 
    WHITE_BLACK_TYPE,
    
    BLUE_WHITE_TYPE,
    WHITE_BLUE_TYPE,
    
    BLACK_YELLOW_TYPE,
    YELLOW_BLACK_TYPE,
    
    BLUE_YELLOW_TYPE,
    YELLOW_BLUE_TYPE,

    BLACK_GRAY_TYPE,
    GRAY_BLACK_TYPE,

    BLACK_PURPLE_TYPE,
    PURPLE_BLACK_TYPE,

    BLACK_LIGHTBLUE_TYPE,
    LIGHTBLUE_BLACK_TYPE,

    BLACK_ORANGE_TYPE,
    ORANGE_BLACK_TYPE,

    BLACK_LIGHTORANGE_TYPE,
    LIGHTORANGE_BLACK_TYPE,

    GREEN_WHITE_TYPE,
    WHITE_GREEN_TYPE,

    PURPLE_WHITE_TYPE,
    WHITE_PURPLE_TYPE,

    RED_WHITE_TYPE,
    WHITE_RED_TYPE

}FLASE_COLOR_TYPE;



#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */


typedef void (FUN_TRUE_COLOR_TRANS)(Uint32 OutBuffer, Uint32 InBuffer, Uint32 DstStride, Uint32 SrcStride, Uint32 Width, Uint32 Height, Uint8* LUTable, Uint8* SATTable);
typedef FUN_TRUE_COLOR_TRANS * PFUN_TRUE_COLOR_TRANS;

typedef void (FUN_TRUE_COLOR_HIST_TRANS)(Uint32 OutBuffer, Uint32 InBuffer, Uint32 DstStride, Uint32 SrcStride, Uint32 Width, Uint32 Height, Uint8* LUTable, Uint8* SATTable, Uint32 *HistTable);
typedef FUN_TRUE_COLOR_HIST_TRANS * PFUN_TRUE_COLOR_HIST_TRANS;


typedef void (FUN_GRAY_COLOR_TRANS)(Uint32 OutBuffer, Uint32 InBuffer, Uint32 SrcStride, Uint32 DstStride, Uint32 Width, Uint32 Height, Uint8* LUTable);
typedef FUN_GRAY_COLOR_TRANS * PFUN_GRAY_COLOR_TRANS;

typedef void (FUN_GRAY_COLOR_HIST_TRANS)(Uint32 OutBuffer, Uint32 InBuffer, Uint32 SrcStride, Uint32 DstStride, Uint32 Width, Uint32 Height, Uint8* LUTable, Uint32 *HistTable);
typedef FUN_GRAY_COLOR_HIST_TRANS * PFUN_GRAY_COLOR_HIST_TRANS;


typedef void (FUN_FLASE_COLOR_TRANS)(Uint32 OutBuffer, Uint32 InBuffer, Uint32 SrcStride, Uint32 DstStride, Uint32 Width, Uint32 Height, Uint8* LUTableY, Uint8* LUTableCb, Uint8* LUTableCr);
typedef FUN_FLASE_COLOR_TRANS * PFUN_FLASE_COLOR_TRANS;

typedef void (FUN_FLASE_COLOR_HIST_TRANS)(Uint32 OutBuffer, Uint32 InBuffer, Uint32 SrcStride, Uint32 DstStride, Uint32 Width, Uint32 Height, Uint8* LUTableY, Uint8* LUTableCb, Uint8* LUTableCr, Uint32 *HistTable);
typedef FUN_FLASE_COLOR_HIST_TRANS * PFUN_FLASE_COLOR_HIST_TRANS;


extern void cal_gray_hist();
extern Uint32 cal_local_opt_thrd(Uint32 Width, Uint32 Height, Uint32 blk_index);
extern void clear_gray_hist();
extern void decide_global_threshold();

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __IMG_ALG_H__ */
