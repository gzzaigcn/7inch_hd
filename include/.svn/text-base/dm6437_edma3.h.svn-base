/******************************************************************************

   Copyright (C), 2013-,    Zjut Image Processing Lab.    All rights reserved. 

*******************************************************************************
 * File Name : edma.h
 * Version : 1.0
 * Author : Gzz
 * Created : 2013/9/16
 * Last Modified :
 * Description : edma.c header file
 * Function List :
 * Modification History :
   1.Date : 2013/9/16
     Author : Gzz
     Modification : Created file
 
******************************************************************************/

#ifndef __EDMA_H__
#define __EDMA_H__

#include "global.h"
#include <csl_edma.h>
#include <csl_edmaAux.h>
#include <soc.h>
#include <cslr_edmacc.h> 

extern CSL_EdmaccRegsOvly pEdmaccRegs; 
extern Uint8 * pEDMADstBuf0;
extern Uint8 * pEDMADstBuf1;
extern Uint8 * pEDMADstBuf2;
extern Uint8 * pEDMADstBuf3; 
extern Uint8 * pEDMASrcBuf0; 
extern Uint8 * pEDMASrcBuf1; 


#define DstChannel0 55
#define DstChannel1 56
#define DstChannel2 57
#define DstChannel3 58
#define SrcChannel0 59 
#define SrcChannel1 60 
#define MEChannel0 61 
#define MEChannel1 62  


#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

extern void C64plusEdmaInit(CSL_EdmaccRegsOvly * ppEdmaccRegs);
extern void CloseTransferEdmaPaRam(CSL_EdmaccRegsOvly pEdmaccRegs, Uint32 Channel);
extern void DisableEdma(CSL_EdmaccRegsOvly pEdmaccRegs,
                          unsigned int Channel);
extern void EDMA_init();
extern void EnableEdma(CSL_EdmaccRegsOvly pEdmaccRegs,
                         unsigned int Channel);
extern void InitTransferEdmaPaRam(CSL_EdmaccRegsOvly pEdmaccRegs,
                                         Uint32 Channel,
                                         Uint8 * src,
                                         Uint32 SrcStride,
                                         Uint8 * dst,
                                         Uint32 DstStride,
                                         Uint32 Width,
         								Uint32 Height);
extern void SetParamSetup2D(CSL_EdmaccRegsOvly pEdmaccRegs,
                            unsigned int CurChannel,
                            signed int NextChannel,
                            unsigned char * Src,
                            unsigned short SrcStride,
                            unsigned char * Dst,
                            unsigned short DstStride,
                            unsigned short Width,
                            unsigned short Height);
extern void SetParamSetup3D(CSL_EdmaccRegsOvly pEdmaccRegs,
                            unsigned int CurChannel,
                            signed int NextChannel,
                            unsigned char * Src,
                            unsigned short SrcSmallStride,
                            unsigned short SrcStride,
                            unsigned char * Dst,
                            unsigned short DstSmallStride,
                            unsigned short DstStride,
                            unsigned short Width,
                            unsigned short Height);
extern void StartEdma(CSL_EdmaccRegsOvly pEdmaccRegs,
                        unsigned int Channel);
extern void SwapEDMABuffer();
extern void UpdateSrcDstParam(CSL_EdmaccRegsOvly pEdmaccRegs,
                                unsigned int CurChannel,
                                unsigned char * Src,
                                unsigned char * Dst);
extern void UpdateSrcDstParam_UYVY(CSL_EdmaccRegsOvly pEdmaccRegs,
                                unsigned int CurChannel,
                                unsigned char * Src,
                                unsigned char * Dst,
                                unsigned short Height);
extern void WaitEdma(CSL_EdmaccRegsOvly pEdmaccRegs,
                       unsigned int Channel);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __EDMA_H__ */
