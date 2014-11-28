/******************************************************************************

   Copyright (C), 2014-,    Du-Health Electron Co.    All rights reserved. 

*******************************************************************************
 * File Name : dm6437_vpfe.c
 * Version : 1.0
 * Author : gzz
 * Created : 2014/9/3
 * Last Modified :
  Description   : dm6437 vpfe module
 * Function List :
 * Modification History :
   1.Date : 2014/9/3
     Author : gzz
     Modification : Created file
 
******************************************************************************/
#include "dm6437.h"
#include "dm6437_vpfe.h"
#include "global.h"
#include "image_alg.h"
#include "dm6437_cache.h"
#include "csl_cache.h"
#include "coefs.h"



#pragma DATA_SECTION(vpfe_frame_buf,"L3_DATA0")
#pragma DATA_ALIGN(vpfe_frame_buf,128)
unsigned char vpfe_frame_buf[8][RAW_IMAGE_W * RAW_IMAGE_H * 2];

#pragma DATA_SECTION(vpfe_ccdc_buf,"L3_DATA0")
#pragma DATA_ALIGN(vpfe_ccdc_buf,128)
unsigned char vpfe_ccdc_buf[2][RAW_IMAGE_W * RAW_IMAGE_H];

/*AF/AWB outbuffer H3A modules*/
#pragma DATA_SECTION(vpfe_af_out_buf,"L3_DATA1");
#pragma DATA_ALIGN(vpfe_af_out_buf, 128);
unsigned int vpfe_af_out_buf[1280 * 720];

#pragma DATA_SECTION(vpfe_ae_out_buf,"L3_DATA1");
#pragma DATA_ALIGN(vpfe_ae_out_buf, 128);
unsigned short vpfe_ae_out_buf[2][1280 * 720  * 2];
volatile char vpfe_ae_out_buf_offset = 0;


#pragma DATA_SECTION(vpfe_fpc_buf,"L3_DATA1")
#pragma DATA_ALIGN(vpfe_fpc_buf, 128)
unsigned int vpfe_fpc_buf[128];

#pragma DATA_SECTION(lens_shading_buf,"L3_DATA1")
#pragma DATA_ALIGN(lens_shading_buf, 128)
unsigned char lens_shading_buf[1280 * 720]; 


#pragma DATA_SECTION(resize_frame_buf, "L3_DATA2")
#pragma DATA_ALIGN(resize_frame_buf, 128)
unsigned char resize_frame_buf[4][IMAGE_W * IMAGE_H * 2];





unsigned char vpfe_frame_buf_offset = 0;
unsigned char vpfe_free_buf_offset = 1;
unsigned char resize_frame_buf_offset = 0;



const char cfa_coef[] =
{
    R_PHASE,
    GR_PHASE,
    GB_PHASE,
    B_PHASE
};



void vpfe_ccdc_raw()
{

    /*10bit Raw data ,HD=1,VD=0,CCDC data width = 12bit,VD/HD enbale*/
//    VPFE_CCDC_SYN_MODE  = 0x00010604;  //ccdc output to vpi preview,not ccdc output formatter(DDR2)
    VPFE_CCDC_SYN_MODE = 0x00010604;
    VPFE_CCDC_HD_VD_WID = 0x0;
    VPFE_CCDC_PIX_LINES = 0;  //no used when VD are input
    //VPFE_CCDC_PIX_LINES = 0x02cF047f;
    
     /*
      *  sph = 1, nph = 1440, according to page 32-33 of the CCDC spec
      *  for BT.656 mode
      *  active NTSV video window
      */
    VPFE_CCDC_HORZ_INFO = 1280-1;
    
    VPFE_CCDC_HSIZE_OFF = 1280*2;   // Horizontal line offset
    VPFE_CCDC_VERT_START = 0;           // Vertical start line
    VPFE_CCDC_VERT_LINES = 720-1; // Vertical lines
    
    VPFE_CCDC_CULLING   = 0xFFFF00FF;   // Disable cullng
    
    VPFE_CCDC_SDOFST    = 0;   
    VPFE_CCDC_SDR_ADDR  = (Uint32)vpfe_ccdc_buf[0];
    VPFE_CCDC_CLAMP     = 0;
    VPFE_CCDC_DCSUB     = 0;
    VPFE_CCDC_COLPTN    =  0xEE44EE44; //0x11BB11BB;//BGb...//GrR
    VPFE_CCDC_BLKCMP    = 0;
    VPFE_CCDC_VDINT     = 0;
    VPFE_CCDC_ALAW      = 0;
    VPFE_CCDC_REC656IF  = 0x00000000; //Not BT656

    VPFE_CCDC_CCDCFG    = 0x00000000; // Y even position; no swap to store，UYVY
    VPFE_CCDC_FMTCFG    = (1 << 15) + (6 << 12);  //FMTCFG.VPEN =1 ,VPI enable and select 0-9 10-bit input 
    VPFE_CCDC_FMT_HORZ  = 1280;
    VPFE_CCDC_FMT_VERT  = 720;
    
    VPFE_CCDC_FMT_ADDR0 = 0;
    VPFE_CCDC_FMT_ADDR1 = 0;
    VPFE_CCDC_FMT_ADDR2 = 0;
    VPFE_CCDC_FMT_ADDR3 = 0;
    VPFE_CCDC_FMT_ADDR4 = 0;
    VPFE_CCDC_FMT_ADDR5 = 0;
    VPFE_CCDC_FMT_ADDR6 = 0;
    VPFE_CCDC_FMT_ADDR7 = 0;
    VPFE_CCDC_PRGEVEN_0 = 0;
    VPFE_CCDC_PRGEVEN_1 = 0;
    VPFE_CCDC_PRGODD_0  = 0;
    VPFE_CCDC_PRGODD_1  = 0;

    VPFE_CCDC_FPC= (unsigned int )vpfe_fpc_buf;
    VPFE_CCDC_FPC_ADDR = (1 << 16) + (0 << 15) + 0;
    
    VPFE_CCDC_VP_OUT    = (1280 << 4) + (720 << 17);
    
    VPFE_CCDC_PCR       = 0x0000001;   // Enable CCDC

}



void vpfe_preview_init()
{
    int i;
    
    VPFE_PREV_PCR = 0;  
    
    i = 3; // i = 3;
    if(i == 0)
    {		
    	VPFE_PREV_HORZ_INFO = (2 << 16) + 1280 - 4;
    	VPFE_PREV_VERT_INFO = (2 << 16) + 720 - 4;
    }
    else if(i == 1)
    {
    	VPFE_PREV_HORZ_INFO = (3 << 16) + 1280 - 6;
    	VPFE_PREV_VERT_INFO = (2 << 16) + 720 - 4;	
    }
    else if(i == 2)
    {
    	VPFE_PREV_HORZ_INFO = (2 << 16) + 1280 - 4;
    	VPFE_PREV_VERT_INFO = (3 << 16) + 720 - 6;	
    }
    else if(i == 3)
    {
    	VPFE_PREV_HORZ_INFO = (3 << 16) + 1280 - 6;
    	VPFE_PREV_VERT_INFO = (3 << 16) + 720 - 6 - 20;	
    }


    VPFE_PREV_RADR_OFFSET = 1280;
    VPFE_PREV_WADD_OFFSET = 1280*2;//输出的YUV422信号写入到DDR2中的每行的偏移

    VPFE_PREV_DSDR_ADDR = (unsigned int )lens_shading_buf;
    VPFE_PREV_DRKF_OFFSET = 1280;

    VPFE_PREV_WBGAIN = 0x22202022;//0x22202034;WB
    VPFE_PREV_WB_DGAIN = 0x120;
    VPFE_PREV_WBSEL = 0xee44ee44;//0x11BB11BB;   //B-Gb-Gr-R

/*    VPFE_PREV_RGB_MAT1 = 0x0000100;
    VPFE_PREV_RGB_MAT2 = 0x0000000;
    VPFE_PREV_RGB_MAT3 = 0x0000100;
    VPFE_PREV_RGB_MAT4 = 0x0000000;
    VPFE_PREV_RGB_MAT5 = 0x100;  */
  
    VPFE_PREV_RGB_MAT1 = 0x0f8a01a1;
    VPFE_PREV_RGB_MAT2 = 0x0fa10fd5;
    VPFE_PREV_RGB_MAT3 = 0x0f9b01c4;
    VPFE_PREV_RGB_MAT4 = 0x0fb10fbd;
    VPFE_PREV_RGB_MAT5 = 0x192;
  

    VPFE_PREV_CSC0 = 0x4c + (0x96 << 10) + (0x1D << 20);
    VPFE_PREV_CSC1 = 0x3d4 + (0x3ac << 10) + (0x80 << 20);
    VPFE_PREV_CSC2 = 0x80 + (0x395 << 10) + (0x3eb << 20);
    VPFE_PREV_CNT_BRT = 0x1000;
    VPFE_PREV_SET_TBL_ADDR = 0x1400;

//    VPFE_PREV_BLKADJOFF = (32 << 16) + (32 << 8) +32;
    for(i = 0; i < 576; i++)
    {
        VPFE_PREV_SET_TBL_DATA = cfa_coef[i];
    }

    VPFE_PREV_NF = 8;
    VPFE_PREV_CFA = 0x2828;
    VPFE_PREV_HMED = 0;
    VPFE_PREV_WSDR_ADDR = (Uint32)vpfe_frame_buf[0];  //priview最终的输出ddr中的地址vpfe_frame_buffer
    VPFE_PREV_AVE = (1 << 4) | (1<< 2);

    VPFE_PREV_PCR = 0x04100400;  //source来源于VPI，不是DDR2；输出到SDRAM，顺序为CbYCrY,UYVY
    VPFE_PREV_PCR |= 1;//最后使能preview
    
}

void vpfe_h3a_init()
{
    VPFE_H3A_PCR = 0;
    VPFE_H3A_PCR = 0xFFC217FA;//Sum mode

    /*AF*/
    VPFE_H3A_AFPAX1 = 0x00770072;
    VPFE_H3A_AFPAX2 = (0 << 13) +(2 << 6) + 4;
    VPFE_H3A_AFPAXSTART = 0x00280012;
    VPFE_H3A_AFIIRSH = 0x00000024;
    VPFE_H3A_AFBUFST = (unsigned int )vpfe_af_out_buf;
    VPFE_H3A_AFCOEF010 = 0x00000040;
    VPFE_H3A_AFCOEF032 = 0x00150000;    
    VPFE_H3A_AFCOEFF054 =  0x00150016;      
    VPFE_H3A_AFCOEFF076 = 0x00000000;       
    VPFE_H3A_AFCOEFF098 = 0x00200FF0;       
    VPFE_H3A_AFCOEFF0010 =  0x00000FF0;     
    VPFE_H3A_AFCOEF110 =  0x00000040;   
    VPFE_H3A_AFCOEF132 =  0x00150000;   
    VPFE_H3A_AFCOEFF154 =  0x00150016;      
    VPFE_H3A_AFCOEFF176 =  0x0FE30000;      
    VPFE_H3A_AFCOEFF198 =  0x00200FF0;      
    VPFE_H3A_AFCOEFF1010 =  0x00000FF0;

     /*AEW*/
    VPFE_H3A_AEWINSTART = (264 << 16) + 127;
    VPFE_H3A_AEWINBLK = (72 << 16) +  95;
    VPFE_H3A_AEWWIN1 = (95 << 24) + (127 << 13) + (1 << 6) + 3;
    VPFE_H3A_AEWSUBWIN = (5 << 8) + 7;
    VPFE_H3A_AEWBUFST = (unsigned int)vpfe_ae_out_buf[vpfe_ae_out_buf_offset];  

    VPFE_H3A_PCR |= 1 + (1<<16);
}





/*****************************************************************************
 * Prototype : vpfe_init
 * description  : vpfe init
 * Input : None
 * Output : None
 * Return Value : 
 * Calls : 
 * Called By  : 
 
 * Modification History :
 * 1.Date : 2013/8/5
 *   Author : Gzz
 *   Modification : Created function
 
*****************************************************************************/
void vpfe_init()
{
    int i , j;
    
    for (j = 0; j < 8; j++) {
        for (i = 0; i < IMAGE_W * IMAGE_H; i++) {
            vpfe_frame_buf[j][(i << 1)] = 128;        // U,V = 128
            vpfe_frame_buf[j][(i << 1) + 1] = 0xff;	//Y=0xff, white color
        }
    }

   /*for(i = 0; i < IMAGE_W*IMAGE_H; i++)
    {
         lens_shading_buf[i] = 0x80;
    }
    */
    vpfe_free_buf_offset = 1;

    vpfe_preview_init();
//    vpfe_h3a_init();
    vpfe_ccdc_raw();
    vpfe_resizer_init();

}

Uint32 get_vpfe_frame_buf()
{
    Uint8 temp;
    Uint32 ret;
      
    ret = (Uint32)vpfe_frame_buf[vpfe_frame_buf_offset];
    temp = (vpfe_frame_buf_offset+1) & 7;

    if ((temp !=  (vpfe_free_buf_offset+7)) && (temp != vpfe_free_buf_offset) ) //interlace more than 1 line
    {
        vpfe_frame_buf_offset = temp;
    }

    return ret;
}


Uint32 get_vpfe_free_buf()
{
    /*return vpfe free buff to capture and store*/
    return (Uint32)vpfe_frame_buf[vpfe_free_buf_offset];
}


void set_vpfe_frame_to_free()
{
    Uint8 temp;
    temp = (vpfe_free_buf_offset+1) & 7;

    if (temp != vpfe_frame_buf_offset)// sure not overlap vpfe frame buffer
    {
        vpfe_free_buf_offset = temp;
    }
    
}

/*RSZ = (input/output *256) range(64-512): ratio :0.5-4X*/
static void config_4taps_8phases()
{
    
    /********resize fliter coefficient: 4taps 7phase**********/
    VPFE_RESZ_HFILT10       = 0x01000000;	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0x28 )
    VPFE_RESZ_HFILT32       = 0x00000000;	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0x2C )
    VPFE_RESZ_HFILT54       = 0x00F603FA;	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0x30 )
    VPFE_RESZ_HFILT76       = 0x00000010;	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0x34 )
    VPFE_RESZ_HFILT98       = 0x00DB03F9;	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0x38 )
    VPFE_RESZ_HFILT1110     = 0x0000002C;	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0x3C )
    VPFE_RESZ_HFILT1312     = 0x00B303FB;	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0x40 )
    VPFE_RESZ_HFILT1514     = 0x03FF0053;	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0x44 )
    VPFE_RESZ_HFILT1716     = 0x008203FD;	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0x48 )
    VPFE_RESZ_HFILT1918     = 0x03FD0084;	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0x4C )
    VPFE_RESZ_HFILT2120     = 0x005303FF;	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0x50 )
    VPFE_RESZ_HFILT2322     = 0x03FB00B3;	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0x54 )
    VPFE_RESZ_HFILT2524     = 0x002C0000;	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0x58 )
    VPFE_RESZ_HFILT2726     = 0x03F900DB;	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0x5C )
    VPFE_RESZ_HFILT2928     = 0x00100000;	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0x60 )
    VPFE_RESZ_HFILT3130     = 0x03FA00F6;	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0x64 )
    VPFE_RESZ_VFILT10       = 0x01000000;	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0x68 ) 0x01000000
    VPFE_RESZ_VFILT32       = 0x00000000;	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0x6C ) 0x00000000
    VPFE_RESZ_VFILT54       = 0x00F603FA;	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0x70 ) 0x00F7FFF5
    VPFE_RESZ_VFILT76       = 0x00000010;	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0x74 ) 0xFFFF0017
    VPFE_RESZ_VFILT98       = 0x00DB03F9;	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0x78 ) 0x00DEFFEF
    VPFE_RESZ_VFILT1110     = 0x0000002C;	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0x7C ) 0xFFFB003A
    VPFE_RESZ_VFILT1312     = 0x00B303FB;	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0x80 ) 0x00BAFFEE
    VPFE_RESZ_VFILT1514     = 0x03FF0053;	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0x84 ) 0xFFF60064
    VPFE_RESZ_VFILT1716     = 0x008203FD;	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0x88 ) 0x0090FFF1
    VPFE_RESZ_VFILT1918     = 0x03FD0084;	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0x8C ) 0xFFF10090
    VPFE_RESZ_VFILT2120     = 0x005303FF;	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0x90 ) 0x0064FFF6
    VPFE_RESZ_VFILT2322     = 0x03FB00B3;	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0x94 ) 0xFFEE00BA
    VPFE_RESZ_VFILT2524     = 0x002C0000;	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0x98 ) 0x003AFFFB
    VPFE_RESZ_VFILT2726     = 0x03F900DB;	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0x9C ) 0xFFEF00DE
    VPFE_RESZ_VFILT2928     = 0x00100000;	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0xA0 ) 0x0017FFFF
    VPFE_RESZ_VFILT3130     = 0x03FA00F6;	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0xA4 ) 0xFFF500F7
    VPFE_RESZ_YENH          = 0x00000000;	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0xA8 )     

}


#if 0
/*RSZ = (input/output *256) range(513-1024): ratio :0.25-0.5X*/
static void config_7taps_4phases()
{
    
    /********resize fliter coefficient: 7taps 4phase**********/
    VPFE_RESZ_HFILT10       = 0x001303ff;   // *( volatile Uint32* )( VPFE_RESZ_BASE + 0x28 )
    VPFE_RESZ_HFILT32       = 0x0070006c;   // *( volatile Uint32* )( VPFE_RESZ_BASE + 0x2C )
    VPFE_RESZ_HFILT54       = 0x03ff0013;   // *( volatile Uint32* )( VPFE_RESZ_BASE + 0x30 )
    VPFE_RESZ_HFILT76       = 0x00000000;   // *( volatile Uint32* )( VPFE_RESZ_BASE + 0x34 )
    VPFE_RESZ_HFILT98       = 0x00060000;   // *( volatile Uint32* )( VPFE_RESZ_BASE + 0x38 )
    VPFE_RESZ_HFILT1110     = 0x007e0058;   // *( volatile Uint32* )( VPFE_RESZ_BASE + 0x3C )
    VPFE_RESZ_HFILT1312     = 0x03ff0025;   // *( volatile Uint32* )( VPFE_RESZ_BASE + 0x40 )
    VPFE_RESZ_HFILT1514     = 0x00000000;   // *( volatile Uint32* )( VPFE_RESZ_BASE + 0x44 )
    VPFE_RESZ_HFILT1716     = 0x00000000;   // *( volatile Uint32* )( VPFE_RESZ_BASE + 0x48 )
    VPFE_RESZ_HFILT1918     = 0x0086003d;   // *( volatile Uint32* )( VPFE_RESZ_BASE + 0x4C )
    VPFE_RESZ_HFILT2120     = 0x0000003d;   // *( volatile Uint32* )( VPFE_RESZ_BASE + 0x50 )
    VPFE_RESZ_HFILT2322     = 0x00000000;   // *( volatile Uint32* )( VPFE_RESZ_BASE + 0x54 )
    VPFE_RESZ_HFILT2524     = 0x03ff0000;   // *( volatile Uint32* )( VPFE_RESZ_BASE + 0x58 )
    VPFE_RESZ_HFILT2726     = 0x007e0025;   // *( volatile Uint32* )( VPFE_RESZ_BASE + 0x5C )
    VPFE_RESZ_HFILT2928     = 0x00580060;   // *( volatile Uint32* )( VPFE_RESZ_BASE + 0x60 )
    VPFE_RESZ_HFILT3130     = 0x00000000;   // *( volatile Uint32* )( VPFE_RESZ_BASE + 0x64 )
    VPFE_RESZ_VFILT10       = 0x001303ff;   // *( volatile Uint32* )( VPFE_RESZ_BASE + 0x68 ) 0x01000000
    VPFE_RESZ_VFILT32       = 0x0070006c;   // *( volatile Uint32* )( VPFE_RESZ_BASE + 0x6C ) 0x00000000
    VPFE_RESZ_VFILT54       = 0x03ff0013;   // *( volatile Uint32* )( VPFE_RESZ_BASE + 0x70 ) 0x00F7FFF5
    VPFE_RESZ_VFILT76       = 0x00000000;   // *( volatile Uint32* )( VPFE_RESZ_BASE + 0x74 ) 0xFFFF0017
    VPFE_RESZ_VFILT98       = 0x00060000;   // *( volatile Uint32* )( VPFE_RESZ_BASE + 0x78 ) 0x00DEFFEF
    VPFE_RESZ_VFILT1110     = 0x007e0058;   // *( volatile Uint32* )( VPFE_RESZ_BASE + 0x7C ) 0xFFFB003A
    VPFE_RESZ_VFILT1312     = 0x03ff0025;   // *( volatile Uint32* )( VPFE_RESZ_BASE + 0x80 ) 0x00BAFFEE
    VPFE_RESZ_VFILT1514     = 0x00000000;   // *( volatile Uint32* )( VPFE_RESZ_BASE + 0x84 ) 0xFFF60064
    VPFE_RESZ_VFILT1716     = 0x00000000;   // *( volatile Uint32* )( VPFE_RESZ_BASE + 0x88 ) 0x0090FFF1
    VPFE_RESZ_VFILT1918     = 0x0086003d;   // *( volatile Uint32* )( VPFE_RESZ_BASE + 0x8C ) 0xFFF10090
    VPFE_RESZ_VFILT2120     = 0x0000003d;   // *( volatile Uint32* )( VPFE_RESZ_BASE + 0x90 ) 0x0064FFF6
    VPFE_RESZ_VFILT2322     = 0x00000000;   // *( volatile Uint32* )( VPFE_RESZ_BASE + 0x94 ) 0xFFEE00BA
    VPFE_RESZ_VFILT2524     = 0x03ff0000;   // *( volatile Uint32* )( VPFE_RESZ_BASE + 0x98 ) 0x003AFFFB
    VPFE_RESZ_VFILT2726     = 0x007e0025;   // *( volatile Uint32* )( VPFE_RESZ_BASE + 0x9C ) 0xFFEF00DE
    VPFE_RESZ_VFILT2928     = 0x00060058;   // *( volatile Uint32* )( VPFE_RESZ_BASE + 0xA0 ) 0x0017FFFF
    VPFE_RESZ_VFILT3130     = 0x00000000;   // *( volatile Uint32* )( VPFE_RESZ_BASE + 0xA4 ) 0xFFF500F7
    VPFE_RESZ_YENH          = 0x00000000;// *( volatile Uint32* )( VPFE_RESZ_BASE + 0xA8 )     
    
}
#endif

void config_fliter_coeff()
{
    Uint8 i;
    volatile Uint32 *p_coeff = (volatile Uint32 *)(VPFE_RESZ_BASE + 0x28);
    
    for(i = 0; i < 32; i += 2)
    {
        *(p_coeff++)= ((coefs[0][i+1] & 0x3ff ) << 16) | (coefs[0][i] & 0x3ff);//hrsz
    }


    for(i = 0; i < 32; i += 2)
    {
        *(p_coeff++)= ((coefs[1][i+1] & 0x3ff ) << 16) | (coefs[1][i] & 0x3ff); //vert
    }
    
    VPFE_RESZ_YENH          = 0x00000000;// *( volatile Uint32* )( VPFE_RESZ_BASE + 0xA8 )     
    
}

/********************dm6437 Resize module*************************/
void vpfe_resizer_init()
{

    VPFE_RESZ_PID           = 0x0010FE00;	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0x00 )
    VPFE_RESZ_PCR           = 0x00000000;	//enable 0x01 disable 0x00 // *( volatile Uint32* )( VPFE_RESZ_BASE + 0x04 )
    VPFE_RESZ_RSZ_CNT       = 0x100320fd;  // 15:10  NTSC   720->720  360->480   
    
    VPFE_RESZ_IN_START      = 0x00000000;	
    VPFE_RESZ_SDR_INADD   = 0;		
    VPFE_RESZ_SDR_INOFF    = RAW_IMAGE_W << 1;
    VPFE_RESZ_IN_SIZE       = (RAW_IMAGE_W & 0x1fff) | ((RAW_IMAGE_H & 0x1fff) << 16);	
    
    VPFE_RESZ_OUT_SIZE      = ((IMAGE_W )&0x1fff) | (((IMAGE_H )&0x1fff) << 16);	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0x0C )
    VPFE_RESZ_SDR_OUTADD    = 0;	// *( volatile Uint32* )( VPFE_RESZ_BASE + 0x20 )
    VPFE_RESZ_SDR_OUTOFF = IMAGE_W << 1;
    
    config_4taps_8phases();//scale range:0.5x-4x
}
	

int in_size_extra_value = 3;
void set_resizer(Uint32 inbuffer, Uint32 outbuffer, Uint32 hrsz, Uint32 vrsz)
{
    
    Int32 insize_horz, insize_vert;
    Int32 offset_x, offset_y, start_pixel_x;

    insize_horz = (((IMAGE_W- 1)*hrsz + 16)>>8) + 7; //800
    insize_vert =  (((IMAGE_H - 1)*vrsz + 16)>>8) + 4; //480

    offset_x = ((RAW_IMAGE_W - insize_horz))&0xffffffe0;//保证32bytes对齐
    offset_y = (RAW_IMAGE_H - insize_vert) >> 1;
    start_pixel_x = ((RAW_IMAGE_W - insize_horz) >> 1) & 0x0f;//SDRAM YUV422 0-15 pixels

    VPFE_RESZ_PCR = 0x00000000;
    VPFE_RESZ_RSZ_CNT = 0x10000000 |((hrsz) & 0x3ff) | (((vrsz) & 0x3ff)<<10);  //输入源SDRAM，缩放因子写入
    VPFE_RESZ_IN_SIZE = ((insize_horz + in_size_extra_value)&0x1fff) | (((insize_vert + in_size_extra_value)&0x1fff) << 16) ;//做矫正
    VPFE_RESZ_SDR_INADD = inbuffer + offset_y*(RAW_IMAGE_W << 1) + offset_x;//start address in SDRAM
    VPFE_RESZ_IN_START =  start_pixel_x;
    VPFE_RESZ_SDR_OUTADD = outbuffer;    
    
}


volatile Uint8 resize_done_flag = 1; 

void start_resize()
{
    resize_done_flag = 0;
    VPFE_RESZ_PCR = 0x00000001; //enable resize
}

void wait_resize()
{
    while((VPFE_RESZ_PCR & (1 << 1)));
    while(resize_done_flag == 0);//busy or no inerrupt
}


Uint32 get_resize_frame_buf()
{
    Uint32 ret;
    
    ret = (Uint32)resize_frame_buf[resize_frame_buf_offset];
    resize_frame_buf_offset = (resize_frame_buf_offset+1)&3;

    return ret;
    
}


