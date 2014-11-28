/******************************************************************************

   Copyright (C), 2014-,    Du-Health Electron Co.    All rights reserved. 

*******************************************************************************
 * File Name : edma3.c
 * Version : 1.0
 * Author : gzz
 * Created : 2014/9/3
 * Last Modified :
  Description   : dm6437 edma3 module
 * Function List :
              C64plusEdmaInit
              CloseTransferEdmaPaRam
              DisableEdma
              EDMA_init
              EnableEdma
              InitTransferEdmaPaRam
              SetParamSetup2D
              SetParamSetup3D
              StartEdma
              SwapEDMABuffer
              UpdateSrcDstParam
              UpdateSrcDstParam_UYVY
              WaitEdma
 * Modification History :
   1.Date : 2014/9/3
     Author : gzz
     Modification : Created file
 
******************************************************************************/
#include "dm6437.h"
#include "global.h"
#include "dm6437_edma3.h"
#include "img_alg.h"


/*allocate two 20KB slices  in L1 Data SRAM*/
#pragma DATA_SECTION(image_slice0, "L1_DATA0")
#pragma DATA_ALIGN(image_slice0, 64)
Uint8 image_slice0[SLICE_DIM+SLICE_DIM];

#pragma DATA_SECTION(image_slice1, "L1_DATA0")
#pragma DATA_ALIGN(image_slice1, 64)
Uint8 image_slice1[SLICE_DIM + SLICE_DIM];


/* edma寄存器地址*/
CSL_EdmaccRegsOvly pEdmaccRegs;
Uint8 * pEDMADstBuf0;
Uint8 * pEDMADstBuf1;
Uint8 * pEDMADstBuf2;
Uint8 * pEDMADstBuf3;
Uint8 * pEDMASrcBuf0;
Uint8 * pEDMASrcBuf1;


/*!
  \brief
   edma初始化
  */
void C64plusEdmaInit(CSL_EdmaccRegsOvly * ppEdmaccRegs)
{
    *ppEdmaccRegs = (CSL_EdmaccRegsOvly)CSL_EDMACC_0_REGS;
    (*ppEdmaccRegs)->ICR = 0XFFFFFFFF; /* 清DMA中断标志 */
    (*ppEdmaccRegs)->ICRH = 0XFFFFFFFF;

}


/*!
  \brief
   2维数据搬运参数设置
  */
void SetParamSetup2D(CSL_EdmaccRegsOvly pEdmaccRegs,
                   unsigned int CurChannel,
                   signed int NextChannel,
                   unsigned char * Src,
                   unsigned short SrcStride,
                   unsigned char * Dst,
                   unsigned short DstStride,
                   unsigned short Width,
                   unsigned short Height)
{

    CSL_EdmaccParamentryRegsOvly pEdmaccPaRamSet = &pEdmaccRegs->PARAMENTRY[CurChannel];

    if (NextChannel != -1)
        pEdmaccPaRamSet->OPT = CSL_EDMA_OPT_MAKE(FALSE,TRUE,FALSE,TRUE,NextChannel,
        CSL_EDMA_TCC_NORMAL,CSL_EDMA_FIFOWIDTH_NONE,TRUE,CSL_EDMA_SYNC_AB,
        CSL_EDMA_ADDRMODE_INCR,CSL_EDMA_ADDRMODE_INCR);//最后一个TR后会启动下一个通道的传输

    else /* NextChannel为-1，表示CurChannel为chain的最后一个channel，并且在次通道产生中断  */
        pEdmaccPaRamSet->OPT = CSL_EDMA_OPT_MAKE(FALSE,FALSE,FALSE,TRUE,CurChannel,
        CSL_EDMA_TCC_NORMAL,CSL_EDMA_FIFOWIDTH_NONE,TRUE,CSL_EDMA_SYNC_AB,
        CSL_EDMA_ADDRMODE_INCR,CSL_EDMA_ADDRMODE_INCR);//一个2D完成传输后产生中断，但不使能chain传输

    pEdmaccPaRamSet->SRC = (unsigned int)Src;

    pEdmaccPaRamSet->A_B_CNT = CSL_EDMA_CNT_MAKE(Width, Height);

    pEdmaccPaRamSet->DST = (unsigned int)Dst;

    pEdmaccPaRamSet->SRC_DST_BIDX = CSL_EDMA_BIDX_MAKE(SrcStride,DstStride);//一个Frame中ARRY之间的跨度

    pEdmaccPaRamSet->LINK_BCNTRLD = CSL_EDMA_LINKBCNTRLD_MAKE(CSL_EDMA_LINK_NULL,0);

    pEdmaccPaRamSet->SRC_DST_CIDX = CSL_EDMA_CIDX_MAKE(0, 0);

    pEdmaccPaRamSet->CCNT = 1;

    return ;

}


/*!
  \brief
   3维数据搬运参数设置
  */
void SetParamSetup3D(CSL_EdmaccRegsOvly pEdmaccRegs,
                   unsigned int CurChannel,
                   signed int NextChannel,
                   unsigned char * Src,
                   unsigned short SrcSmallStride,
                   unsigned short SrcStride,
                   unsigned char * Dst,
                   unsigned short DstSmallStride,
                   unsigned short DstStride,
                   unsigned short Width,
                   unsigned short Height)
{

    CSL_EdmaccParamentryRegsOvly pEdmaccPaRamSet = &pEdmaccRegs->PARAMENTRY[CurChannel];

    /* NextChannel为-1，表示CurChannel为chain的最后一个channel，并且在次通道产生中断  */
    //配置为非static，并可Intermediate final chain到自己，只需要一次event完成搬运。
    pEdmaccPaRamSet->OPT = CSL_EDMA_OPT_MAKE(TRUE,TRUE,FALSE,TRUE,CurChannel,
    CSL_EDMA_TCC_NORMAL,CSL_EDMA_FIFOWIDTH_NONE,FALSE,CSL_EDMA_SYNC_AB,
    CSL_EDMA_ADDRMODE_INCR,CSL_EDMA_ADDRMODE_INCR);
    pEdmaccPaRamSet->SRC = (unsigned int)Src;

    pEdmaccPaRamSet->A_B_CNT = CSL_EDMA_CNT_MAKE(1, Width);

    pEdmaccPaRamSet->DST = (unsigned int)Dst;

    pEdmaccPaRamSet->SRC_DST_BIDX = CSL_EDMA_BIDX_MAKE(SrcSmallStride,DstSmallStride);

    pEdmaccPaRamSet->LINK_BCNTRLD = CSL_EDMA_LINKBCNTRLD_MAKE(CSL_EDMA_LINK_NULL,0);

    pEdmaccPaRamSet->SRC_DST_CIDX = CSL_EDMA_CIDX_MAKE(SrcStride, DstStride);

    pEdmaccPaRamSet->CCNT = Height;

    return ;

}


/*!
  \brief
   更新源和目的地址参数
  */
void UpdateSrcDstParam(CSL_EdmaccRegsOvly pEdmaccRegs,
                       unsigned int CurChannel,
                       unsigned char * Src,
                       unsigned char * Dst)
{
    
    CSL_EdmaccParamentryRegsOvly pEdmaccPaRamSet = &pEdmaccRegs->PARAMENTRY[CurChannel];
    pEdmaccPaRamSet->SRC = (unsigned int)Src;
    pEdmaccPaRamSet->DST = (unsigned int)Dst;
    
    return ;
    
}

/*!
  \brief
   更新源和目的地址参数
  */
void UpdateSrcDstParam_UYVY(CSL_EdmaccRegsOvly pEdmaccRegs,
                       unsigned int CurChannel,
                       unsigned char * Src,
                       unsigned char * Dst,
                       unsigned short Height)
{

    CSL_EdmaccParamentryRegsOvly pEdmaccPaRamSet = &pEdmaccRegs->PARAMENTRY[CurChannel];
    pEdmaccPaRamSet->SRC = (unsigned int)Src;
    pEdmaccPaRamSet->DST = (unsigned int)Dst;
    pEdmaccPaRamSet->CCNT = Height;

    return ;

}

/*!
  \brief
   使能edma通道
  */
void EnableEdma(CSL_EdmaccRegsOvly pEdmaccRegs,
                unsigned int Channel)
{
    if (Channel < 32)
    {
//        pEdmaccRegs->SECR = (1 << Channel); // clear SER since a TR of NULL
        pEdmaccRegs->EESR = (1 << Channel); //enable EER
    }
    else
    {
//        pEdmaccRegs->SECRH = (1 << (Channel - 32));
        pEdmaccRegs->EESRH = (1 << (Channel - 32) );
    }
    return ;
    
}

/*!
  \brief
   关闭edma通道
  */
void DisableEdma(CSL_EdmaccRegsOvly pEdmaccRegs,
                 unsigned int Channel)
{
    
    if (Channel < 32)
        pEdmaccRegs->EECR = (1 << Channel);
    else
        pEdmaccRegs->EECRH = (1 << (Channel - 32));

    return ;

}

/*!
  \brief
   开启edma通道传输
  */
void StartEdma(CSL_EdmaccRegsOvly pEdmaccRegs,
               unsigned int Channel)
{

    if (Channel < 32)
        pEdmaccRegs->ESR = (1 << Channel);
    else
        pEdmaccRegs->ESRH = (1 << (Channel - 32));

    return ;

}

/*!
  \brief
   等待edma通道传输完成
  */
void WaitEdma(CSL_EdmaccRegsOvly pEdmaccRegs,
              unsigned int Channel)
{

    //GetCyclesBegin();

    if (Channel < 32)
    {
        while ( !(pEdmaccRegs->IPR & (1 << Channel)));
        pEdmaccRegs->ICR = (1 << Channel);
    }
    else
    {
        while ( !(pEdmaccRegs->IPRH & (1 << (Channel - 32))) );
        pEdmaccRegs->ICRH = (1 << (Channel - 32));
    }

    //GetCyclesEnd();

    return ;
    
}



void InitTransferEdmaPaRam(CSL_EdmaccRegsOvly pEdmaccRegs,
                                Uint32 Channel,
                                Uint8 * src,
                                Uint32 SrcStride,
                                Uint8 * dst,
                                Uint32 DstStride,
                                Uint32 Width,
								Uint32 Height)
{
    SetParamSetup2D(pEdmaccRegs, Channel, -1, src, SrcStride, dst, DstStride, Width, Height);
    EnableEdma(pEdmaccRegs, Channel);
}



void CloseTransferEdmaPaRam(CSL_EdmaccRegsOvly pEdmaccRegs, Uint32 Channel)
{
    DisableEdma(pEdmaccRegs, Channel);
}


/*!
  \brief
   初始化edma
  */
void EDMA_init()
{

    C64plusEdmaInit(&pEdmaccRegs);
    
    pEDMADstBuf0 = image_slice0;
    pEDMASrcBuf0 = image_slice0 + SLICE_DIM;//next 10KB slice

    SetParamSetup2D(pEdmaccRegs, DstChannel0, -1, (Uint8 *)0, IMAGE_W << 1, pEDMADstBuf0, SLICE_W << 1, SLICE_W << 1, SLICE_H);
    SetParamSetup2D(pEdmaccRegs, SrcChannel0, -1, pEDMASrcBuf0, SLICE_W << 1, (Uint8 *)0, IMAGE_W << 1, SLICE_W << 1, SLICE_H);
    EnableEdma(pEdmaccRegs, DstChannel0);
    EnableEdma(pEdmaccRegs, SrcChannel0);
    
}


void SwapEDMABuffer()
{
    
    if(pEDMADstBuf0 == image_slice0)
    {
        pEDMADstBuf0 = image_slice1;
        pEDMASrcBuf0 = image_slice1 + SLICE_DIM;//next 10KB slice
    }
    else
    {
        pEDMADstBuf0 = image_slice0;
        pEDMASrcBuf0 = image_slice0 + SLICE_DIM;//next 10KB slice
    }
    
}




