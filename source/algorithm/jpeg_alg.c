/******************************************************************************

   Copyright (C), 2013-,    Zjut Image Processing Lab.    All rights reserved.

*******************************************************************************
 * File Name : jpeg_alg.c
 * Version : 1.0
 * Author : Gzz
 * Created : 2013/10/16
 * Last Modified :
  Description   : TI JPEG Algorithm
 * Function List :
              create_jpeg_alg_decode
              jpeg_alg_alloc_mem
              jpeg_alg_init
              jpeg_decode
              jpeg_encode
 * Modification History :
   1.Date : 2013/10/16
     Author : Gzz
     Modification : Created file

******************************************************************************/
#include "stdio.h"
#include "std.h"
#include "jpeg_alg.h"
#include "dm6437.h"
#include "string.h"
#include "csl_cache.h"
#include "global.h"

#include "iimgdec1.h"
#include "ijpegdec.h"
#include "jpegdec.h"
#include "jpegdec_ti.h"
#include "idmjpge.h"
#include "dmjpge_tigem.h"
#include "idmjpge.h"

#define JPEG_ENCODE_INPUT_BUFFER_SIZE   2 * IMAGE_W* IMAGE_H
#define JPEG_ENCODE_OUTPUT_BUFFER_SIZE  IMAGE_W* IMAGE_H
#define JPEG_DECODE_INPUT_BUFFER_SIZE    IMAGE_W* IMAGE_H
#define JPEG_DECODE_OUTPUT_BUFFER_SIZE  2*IMAGE_W* IMAGE_H

#define JPEG_ENCODE_QP 80   //JPEG编码质量因数值


/*Buffers for Jpeg encode algorithm*/
#pragma DATA_SECTION(enc_mem_base, "L3_DATA4");
#pragma DATA_ALIGN(enc_mem_base, 128);
#pragma DATA_SECTION(enc_memTab, "L3_DATA4");
#pragma DATA_ALIGN(enc_memTab, 128);
static unsigned char enc_mem_base[8][10 * 1024];
static unsigned char enc_memTab[16][sizeof (IALG_MemRec)];

/*Buffers for Jpeg decode algorithm*/
#pragma DATA_SECTION(dec_mem_base, "L3_DATA4");
#pragma DATA_ALIGN(dec_mem_base, 128);
#pragma DATA_SECTION(dec_memTab, "L3_DATA4");
#pragma DATA_ALIGN(dec_memTab, 128);
static unsigned char dec_mem_base[8][32 * 1024];
static unsigned char dec_memTab[16][sizeof (IALG_MemRec)];

Uint8 jpeg[33052];
Uint8 yuv[2*640*480];

IALG_Handle jpeg_encode_handle;//Handle for encode alg
IALG_Handle jpeg_decode_handle;//Handle for decode alg

/*encode params for encoding*/
IIMGENC1_Params encode_static_params = {
                                           sizeof(IIMGENC1_Params),
                                           IMAGE_H,
                                           IMAGE_W,
                                           XDM_DEFAULT,
                                           XDM_BYTE, //output dataEndianness
                                           XDM_YUV_422P //output color format
                                           };

IIMGENC1_DynamicParams encode_dynamic_default_params = {
                                            sizeof(IIMGENC1_DynamicParams),
                                                0,
                                            XDM_YUV_422ILE,//input color format,UYVY
                                            IMAGE_H,
                                            IMAGE_W,
                                            0,
                                            0,
                                            JPEG_ENCODE_QP,
                                            };


/*decode params for encoding*/
JPEGDEC_Params decode_static_params = {
                                {sizeof(JPEGDEC_Params),
                                  IMAGE_H,
                                  IMAGE_W,
                                  15,
                                  XDM_BYTE,
                                  XDM_YUV_422ILE},
                                  0,
                                  0};
                                
JPEGDEC_DynamicParams  decode_dynamic_default_params  = {
                                {sizeof(JPEGDEC_DynamicParams),
                                    0,
                                    1,
                                    0},
                                0,0,0,0,0,0,0,0,0};



static Uint8 jpeg_encode_alg_alloc_mem(IALG_MemRec *memTab, Uint32 n)
{
    Uint32 i;
    for(i = 0; i < n; i++)
    {
        memTab[i].base = enc_mem_base[i];//对IALG算法需要的内存块表进行初始化
    }
    return TRUE;
}

static Uint8 jpeg_decode_alg_alloc_mem(IALG_MemRec *memTab, Uint32 n)
{
    Uint32 i;
    for(i = 0; i < n; i++)
    {
        memTab[i].base = dec_mem_base[i];//对IALG当前算法需要的内存块表进行初始化
    }
    return TRUE;
}

/*****************************************************************************
 * Prototype : create_jpeg_alg_encode
 * description  : create jpeg encode algorithm instance
 * Input :   IALG_Fxns *fxns      
                   IALG_Handle p        
                   IALG_Params *params  
 * Output : None
 * Return Value : static
 * Calls : 
 * Called By  : 
 
 * Modification History :
 * 1.Date : 2013/10/18
 *   Author : Gzz
 *   Modification : Created function
 
*****************************************************************************/
static IALG_Handle create_jpeg_alg_encode(IALG_Fxns *fxns, IALG_Handle p, IALG_Params *params)
{

    IALG_MemRec *memTab;
    Int n;
    IALG_Handle alg;
    IALG_Fxns *fxnsPtr;

    if (fxns != NULL)
    {
        n = fxns->algNumAlloc != NULL ? fxns->algNumAlloc() : IALG_DEFMEMRECS;//mem取默认的个数
        memTab = (IALG_MemRec *) enc_memTab;
        n = fxns->algAlloc(params, &fxnsPtr, memTab);//返回编码算法所需要的实际mem表数
        if (n <= 0)
        {
            return (NULL);
        }
        if (jpeg_encode_alg_alloc_mem(memTab, n))
        {
                alg = (IALG_Handle)memTab[0].base;
                alg->fxns = fxns;
                if (fxns->algInit(alg, memTab, p, params) == IALG_EOK)//设置下层算法实例的参数，设置APP层的mem信息的初始化等
                {
                    return (alg);
                }
                fxns->algFree(alg, memTab); //出错，直接free信息
        }
    }

    return (NULL);
}


/*****************************************************************************
 * Prototype : create_jpeg_alg_decode
 * description  : create jpeg decode algorithm instance
 * Input :   IALG_Fxns *fxns      
                   IALG_Handle p        
                   IALG_Params *params  
 * Output : None
 * Return Value : static
 * Calls : 
 * Called By  : 
 
 * Modification History :
 * 1.Date : 2013/10/18
 *   Author : Gzz
 *   Modification : Created function
 
*****************************************************************************/
static IALG_Handle create_jpeg_alg_decode(IALG_Fxns *fxns, IALG_Handle p, IALG_Params *params)
{

    IALG_MemRec *memTab;
    Int n;
    IALG_Handle alg;
    IALG_Fxns *fxnsPtr;

    if (fxns != NULL)
    {
        n = fxns->algNumAlloc != NULL ? fxns->algNumAlloc() : IALG_DEFMEMRECS;//mem取默认的个数
        memTab = (IALG_MemRec *) dec_memTab;
        n = fxns->algAlloc(params, &fxnsPtr, memTab);//返回解码算法所需要的实际mem表数
        if (n <= 0)
        {
            return (NULL);
        }
        if (jpeg_decode_alg_alloc_mem(memTab, n))
        {
                alg = (IALG_Handle)memTab[0].base;
                alg->fxns = fxns;
                if (fxns->algInit(alg, memTab, p, params) == IALG_EOK)//设置下层算法实例的参数，mem初始化等
                {
                    return (alg);
                }
                fxns->algFree(alg, memTab); //出错，直接free信息
        }
    }

    return (NULL);
}




void jpeg_alg_init()
{
    jpeg_encode_handle = create_jpeg_alg_encode((IALG_Fxns *)&DMJPGE_TIGEM_IDMJPGE, (IALG_Handle)NULL, (IALG_Params *)&encode_static_params);
    jpeg_decode_handle = create_jpeg_alg_decode((IALG_Fxns *)&JPEGDEC_TI_IJPEGDEC, (IALG_Handle)NULL, (IALG_Params *)&decode_static_params);

}

/*****************************************************************************
 * Prototype : jpeg_encode
 * description  : JPEG Encode
 * Input :   Uint8 *pin_buf
                   Uint8 *pout_buf
 * Output : None
 * Return Value :
 * Calls :
 * Called By  :

 * Modification History :
 * 1.Date : 2013/10/17
 *   Author : Gzz
 *   Modification : Created function

*****************************************************************************/

void jpeg_encode(Uint8 *pin_buf, Uint8 *pout_buf)
{
	FILE *fp ;
	Uint8 file_name[256];
	static Uint32 num_frame = 0;
	sprintf(file_name, "E://test_jpeg//jpeg%d.jpg",num_frame);
	num_frame++;

	/* Input/Output Buffer Descriptors                                          */
    XDM1_BufDesc inputBufDesc, outputBufDesc;
    IIMGENC1_Fxns *IIMGENC1Fxns;

    /*record had encoded byte num*/
    XDAS_UInt32 TotalBytes = 0;

    IIMGENC1_Status	status;
    IIMGENC1_InArgs	inArgs;
    IIMGENC1_OutArgs	outArgs;
    IIMGENC1_DynamicParams dynamic_params;

    status.size = sizeof(IIMGENC1_Status);
    status.extendedError = 0;
    inArgs.size = sizeof(IIMGENC1_InArgs);
    outArgs.size = sizeof(IIMGENC1_OutArgs);
    outArgs.extendedError = 0;
    outArgs.bytesGenerated = 0;
    outArgs.currentAU = 0;

    fp = fopen(file_name,"wb");

    memcpy((void *)&dynamic_params, (void *)&encode_dynamic_default_params, sizeof(IIMGENC1_DynamicParams));
    dynamic_params.generateHeader = XDM_ENCODE_AU;//直接编码AU

    IIMGENC1Fxns = (IIMGENC1_Fxns *)jpeg_encode_handle->fxns;
    
    /* Activate the Algorithm                                               */
    jpeg_encode_handle->fxns->algActivate(jpeg_encode_handle);

    IIMGENC1Fxns->control((IIMGENC1_Handle)jpeg_encode_handle, XDM_SETPARAMS,
        (IIMGENC1_DynamicParams *)&dynamic_params,
        (IIMGENC1_Status *)&status);//设置算法所需的参数

    IIMGENC1Fxns->control((IIMGENC1_Handle)jpeg_encode_handle, XDM_GETBUFINFO,
    	(IIMGENC1_DynamicParams *)&dynamic_params,
    	(IIMGENC1_Status *)&status);//获取输入输出buffer的信息
    	
    /* DeActivate the Algorithm                                               */
    jpeg_encode_handle->fxns->algDeactivate(jpeg_encode_handle);

    /* set space for buffer descriptors                                      */
    inputBufDesc.numBufs  = status.bufInfo.minNumInBufs ;
    inputBufDesc.descs[0].bufSize = status.bufInfo.minInBufSize[0] ;
    inputBufDesc.descs[0].buf = (XDAS_Int8 *)pin_buf;

    outputBufDesc.descs[0].buf = (XDAS_Int8 *)pout_buf;
    outputBufDesc.numBufs  = status.bufInfo.minNumOutBufs ;
    outputBufDesc.descs[0].bufSize = status.bufInfo.minOutBufSize[0] ;

    /* Activate the Algorithm                                               */
    jpeg_encode_handle->fxns->algActivate(jpeg_encode_handle);

    IIMGENC1Fxns->control((IIMGENC1_Handle)jpeg_encode_handle, XDM_SETPARAMS,
        (IIMGENC1_DynamicParams *)&dynamic_params,
        (IIMGENC1_Status *)&status);//设置算法所需的参数

    /* Basic Algorithm process() call   */
    IIMGENC1Fxns->process((IIMGENC1_Handle)jpeg_encode_handle,
       (XDM1_BufDesc *)&inputBufDesc,
	(XDM1_BufDesc *)&outputBufDesc,
	(IIMGENC1_InArgs *)&inArgs,
	(IIMGENC1_OutArgs *)&outArgs);//处理信息

    CACHE_wbInvAllL1d(CACHE_WAIT);
    CACHE_wbInvAllL2(CACHE_WAIT);

    TotalBytes += outArgs.bytesGenerated;
    fwrite(pout_buf,1,TotalBytes,fp);
    DEBUG("Out JPEG bytes = %d", TotalBytes);
    DEBUG("compress_rate = %d%%", IMAGE_TOTAL_SIZE/TotalBytes);
    fclose(fp);

    IIMGENC1Fxns->control((IIMGENC1_Handle)jpeg_encode_handle, XDM_SETPARAMS,
        (IIMGENC1_DynamicParams *)&dynamic_params,
        (IIMGENC1_Status *)&status);//设置算法所需的参数

    while (outArgs.currentAU < status.totalAU)//如果当前编码输出的AU比实际的要小，就继续编码
    {
	  /* Basic Algorithm process() call */
        IIMGENC1Fxns->process((IIMGENC1_Handle)jpeg_encode_handle,
            (XDM1_BufDesc *)&inputBufDesc,(XDM1_BufDesc *)&outputBufDesc,
            (IIMGENC1_InArgs *)&inArgs,
            (IIMGENC1_OutArgs *)&outArgs);//处理信息
            
        TotalBytes +=outArgs.bytesGenerated;

        CACHE_wbInvAllL1d(CACHE_WAIT);
        CACHE_wbInvAllL2(CACHE_WAIT);
            IIMGENC1Fxns->control((IIMGENC1_Handle)jpeg_encode_handle, XDM_SETPARAMS,
        (IIMGENC1_DynamicParams *)&dynamic_params,
        (IIMGENC1_Status *)&status);//设置算法所需的参数
        
    }

    jpeg_encode_handle->fxns->algDeactivate(jpeg_encode_handle);
    jpeg_encode_handle->fxns->algFree(jpeg_encode_handle, (IALG_MemRec *)enc_memTab);

}


/*****************************************************************************
 * Prototype : jpeg_decode
 * description  : JPEG Decode
 * Input :   Uint8 *pin_buf
                   Uint8 *pout_buf
                   Uint32 dim
 * Output : None
 * Return Value :
 * Calls :
 * Called By  :

 * Modification History :
 * 1.Date : 2013/10/17
 *   Author : Gzz
 *   Modification : Created function

*****************************************************************************/
void jpeg_decode(Uint8 *pin_buf, Uint8 *pout_buf, Uint32 dim )
{
    /* Input/Output Buffer Descriptors                                          */
    XDM1_BufDesc inputBufDesc, outputBufDesc;
    IIMGDEC1_Fxns *IIMGDEC1Fxns;

    /*record decoded last byte num*/
    XDAS_UInt32 bytesConsumed = 0;

    FILE *fp ;

    fp = fopen("E:\\jpeg8.jpg", "rb");
    fread(jpeg,1, 33052,fp);
    fclose(fp);
    
    JPEGDEC_Status	status;
    JPEGDEC_InArgs	inArgs;
    JPEGDEC_OutArgs	outArgs;
    JPEGDEC_DynamicParams dynamic_params;

    status.imgdecStatus.size = sizeof(IJPEGDEC_Status);
    inArgs.imgdecInArgs.size = sizeof(IJPEGDEC_InArgs);
    inArgs.imgdecInArgs.numBytes = dim;//带解码的JPEG图像大小
    outArgs.imgdecOutArgs.size = sizeof(IJPEGDEC_OutArgs);

    memcpy((void *)&dynamic_params, (void *)&decode_dynamic_default_params, sizeof(JPEGDEC_DynamicParams));
    dynamic_params.imgdecDynamicParams.decodeHeader = XDM_PARSE_HEADER;//解析信息头
    dynamic_params.frame_numbytes = dim; //一帧JPEG的图像大小

    /* set space for buffer descriptors  */
    inputBufDesc.descs[0].buf = (XDAS_Int8 *)jpeg;
    inputBufDesc.descs[0].bufSize = (XDAS_Int32 )dim;
    outputBufDesc.descs[0].buf = (XDAS_Int8 *)yuv;
    outputBufDesc.descs[0].bufSize = (XDAS_Int32)JPEG_DECODE_INPUT_BUFFER_SIZE ;
  
    IIMGDEC1Fxns = (IIMGDEC1_Fxns *)jpeg_decode_handle->fxns;
    jpeg_decode_handle->fxns->algActivate(jpeg_decode_handle);

    /* Get Buffer information                                              */
    IIMGDEC1Fxns->control((IIMGDEC1_Handle)jpeg_decode_handle, XDM_GETBUFINFO,
    (IIMGDEC1_DynamicParams *)&dynamic_params,
    (IIMGDEC1_Status *)&status);//获取buffer的信息

    /* Fill up the buffers as required by algorithm                        */
    inputBufDesc.numBufs = status.imgdecStatus.bufInfo.minNumInBufs ;//算法需要的输入缓存区的最小buf个数
    inputBufDesc.descs[0].bufSize = status.imgdecStatus.bufInfo.minInBufSize[0];//根据算法需求返回的buffer信息。
    outputBufDesc.numBufs = status.imgdecStatus.bufInfo.minNumOutBufs ;
    outputBufDesc.descs[0].bufSize = status.imgdecStatus.bufInfo.minOutBufSize[0];

    IIMGDEC1Fxns->control((IIMGDEC1_Handle)jpeg_decode_handle, XDM_SETPARAMS,
        (IIMGDEC1_DynamicParams *)&dynamic_params,
        (IIMGDEC1_Status *)&status);//设置算法所需的参数

    /* Basic Algorithm process() call   */
    IIMGDEC1Fxns->process((IIMGDEC1_Handle)jpeg_decode_handle,
       (XDM1_BufDesc *)&inputBufDesc,
	(XDM1_BufDesc *)&outputBufDesc,
	(IIMGDEC1_InArgs *)&inArgs,
	(IIMGDEC1_OutArgs *)&outArgs);//处理头信息

    CACHE_wbInvAllL1d(CACHE_WAIT);
    CACHE_wbInvAllL2(CACHE_WAIT);  //cache back to DDR2

    IIMGDEC1Fxns->control((IIMGDEC1_Handle)jpeg_decode_handle, XDM_GETSTATUS,
        (IIMGDEC1_DynamicParams *)&dynamic_params,
        (IIMGDEC1_Status *)&status);//获取当前状态

    dynamic_params.imgdecDynamicParams.decodeHeader = XDM_DECODE_AU;//解码数据单元
    IIMGDEC1Fxns->control((IIMGDEC1_Handle)jpeg_decode_handle, XDM_RESET,
        (IIMGDEC1_DynamicParams *)&dynamic_params,
        (IIMGDEC1_Status *)&status);//复位所有的结构体和算法buffer被flash

    bytesConsumed = 0;

    /* DeActivate the Algorithm */
//    jpeg_decode_handle->fxns->algDeactivate(jpeg_decode_handle);

    /* Do-While Loop for Decode Call     */
    do
    {
        IIMGDEC1Fxns->control((IIMGDEC1_Handle)jpeg_decode_handle, XDM_GETBUFINFO,
            (IIMGDEC1_DynamicParams *)&dynamic_params,
            (IIMGDEC1_Status *)&status);//获取buffer的信息
            
        /* Fill up the buffers as required by algorithm                        */
        inputBufDesc.numBufs = status.imgdecStatus.bufInfo.minNumInBufs ;//算法需要的输入缓存区的最小buf个数
        inputBufDesc.descs[0].bufSize = status.imgdecStatus.bufInfo.minInBufSize[0];//根据算法需求返回的buffer信息。
        outputBufDesc.numBufs = status.imgdecStatus.bufInfo.minNumOutBufs ;
        outputBufDesc.descs[0].bufSize = status.imgdecStatus.bufInfo.minOutBufSize[0];
         
        IIMGDEC1Fxns->control((IIMGDEC1_Handle)jpeg_decode_handle, XDM_SETPARAMS,
            (IIMGDEC1_DynamicParams *)&dynamic_params,
            (IIMGDEC1_Status *)&status);//设置算法所需的参数
  
        IIMGDEC1Fxns->process((IIMGDEC1_Handle)jpeg_decode_handle,
            (XDM1_BufDesc *)&inputBufDesc,
            (XDM1_BufDesc *)&outputBufDesc,
            (IIMGDEC1_InArgs *)&inArgs,
            (IIMGDEC1_OutArgs *)&outArgs);//解码处理
            
        bytesConsumed += outArgs.imgdecOutArgs.bytesConsumed;//记录一次编码完成的字节数

        CACHE_wbInvAllL1d(CACHE_WAIT);
        CACHE_wbInvAllL2(CACHE_WAIT);  //cache back to DDR2

        IIMGDEC1Fxns->control((IIMGDEC1_Handle)jpeg_decode_handle, XDM_GETSTATUS,
            (IIMGDEC1_DynamicParams *)&dynamic_params,
            (IIMGDEC1_Status *)&status);//获取解码后的状态

        if(status.end_of_seq)
         {
            break;//解码完成标志
         }
    }while(1);

    jpeg_decode_handle->fxns->algDeactivate(jpeg_decode_handle);
    jpeg_decode_handle->fxns->algFree(jpeg_decode_handle, (IALG_MemRec *)dec_memTab);
    

}


