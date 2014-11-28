/******************************************************************************

   Copyright (C), 2014-,    Du-Health Electron Co.    All rights reserved. 

*******************************************************************************
 * File Name : dm6437_vpbe.c
 * Version : 1.0
 * Author : gzz
 * Created : 2014/9/3
 * Last Modified :
  Description   : dm6437 vpbe module 
 * Function List :
 * Modification History :
   1.Date : 2014/9/3
     Author : gzz
     Modification : Created file
 
******************************************************************************/
#include "dm6437_vpbe.h"
#include "global.h"

#define VPBE_BUF_NUM 8
    
#pragma DATA_SECTION(vpbe_frame_buf,"L3_DATA3")
#pragma DATA_ALIGN(vpbe_frame_buf,128)
unsigned char vpbe_frame_buf[VPBE_BUF_NUM][IMAGE_W * IMAGE_H * 2];

unsigned char vpbe_frame_buf_offset = 0;
unsigned char vpbe_free_buf_offset = 1;
    
    
    
/*****************************************************************************
 * Prototype : vpbe_venc_cvbs
 * Description : 
 * Viedo Output Configure :  CVBS 640*480 interlace frame
 * Input : Uint32 outbuffer
 * Output : None
 * Return Value : 
 * Calls : 
 * Called By  : 
 
 * Modification History :
 * 1.Date : 2013/7/29
 *   Author : Gzz
 *   Modification : Created function
 
*****************************************************************************/
static void vpbe_venc_cvbs(Uint32 outbuffer)
{

    VPSS_CLK_CTRL       = 0x00000018;   // Enable DAC and VENC clock, both at 27 MHz
    VPBE_PCR            = 0;            // No clock div, clock enable
 
     /** Setup OSD  VIDEO */  
         
    VPBE_OSD_BASEPX     = 0x7a; //BASEP_X;122
    VPBE_OSD_BASEPY     = 0x12; //BASEP_Y;18

    VPBE_OSD_MODE       = 0x00007C00;       //OSD and Video HSize expand to 720; VSize to 576;Expansion filter enable
    VPBE_OSD_VIDWINMD   = 0x00000003;   // enable vwindow 0,Frame mode
    VPBE_OSD_OSDWIN0MD  = 0;            // Disable both osd windows and cursor window
    VPBE_OSD_OSDWIN1MD  = 0;
    VPBE_OSD_RECTCUR    = 0;

    VPBE_OSD_VIDWIN0OFST = IMAGE_W >> 4;
    VPBE_OSD_VIDWIN0ADR  = (Uint32)outbuffer;
    VPBE_OSD_VIDWIN0XP  = 0;
    VPBE_OSD_VIDWIN0YP  = 0;
    VPBE_OSD_VIDWIN0XL  = 720;
    VPBE_OSD_VIDWIN0YL  = 576 >> 1; //frame mode :filed line num
    VPBE_OSD_MISCCTL    = 0;  //CLUT ROM0

    /* VPFE Venc setup */
    VPBE_VENC_VMOD      = 0x0000043; //SDTV,CVBS,interlace,PAL

    VPBE_VENC_VIDCTL     = 0x00001101;
    VPBE_VENC_RGBCTL     = 0x00000000;
    VPBE_VENC_SYNCCTL    = 0x00000000;        
    VPBE_VENC_VDPRO     = 0 << 8;//DACCLK = 27MHz
     //VPBE_VENC_VDPRO     = 1 << 8;
     //    VPBE_VENC_DACTST    = 0;

    VPBE_VENC_DACTST = 0x0000e000; //Power down DAC1.2.3, enable DAC0
    VPBE_VENC_DACSEL    = 0x000000;    //ALL CVBS 
    VPBE_VENC_OSDCLK0    = 0x1;
    VPBE_VENC_OSDCLK1   = 0x2; 
}


static void vpbe_venc_lcd(Uint32 outbuffer)
{
    
    VPSS_CLK_CTRL		= 0x000000019;   // Enable DAC and VENC clock, both at 27 MHz
    VPBE_PCR			= 0;			 // No clock div, clock enable
#if 1
    /*
     * Setup OSD
     */
    VPBE_OSD_MODE		= 0x0000003f;   // Blackground color blue using clut in ROM0
    VPBE_OSD_OSDWIN0MD	= 0;			// Disable both osd windows and cursor window
    VPBE_OSD_OSDWIN1MD	= 0;
    VPBE_OSD_RECTCUR	= 0;

    VPBE_OSD_VIDWIN0OFST = IMAGE_W >> 4;
    VPBE_OSD_VIDWIN0ADR = outbuffer;
    //	VPBE_OSD_PPVWIN0ADR = buffer1;
    VPBE_OSD_BASEPX 	= BASEP_X;	 
    VPBE_OSD_BASEPY 	= BASEP_Y;
    VPBE_OSD_VIDWIN0XP	= 0;
    VPBE_OSD_VIDWIN0YP	= 0;	//why is double of Xp?
    VPBE_OSD_VIDWIN0XL	= IMAGE_W;
    //VPBE_OSD_VIDWIN0YL  = height >> 1; 
    VPBE_OSD_VIDWIN0YL	= IMAGE_H;
    VPBE_OSD_MISCCTL	= 0;	//change the color if set bit 7 ,but don't know the principle
    //	VPBE_OSD_MISCCTL	= 0x80;

    VPBE_OSD_VIDWINMD	= 0x00000001;   // Disable vwindow 1 and enable vwindow 0
    								   // Field mode with no up-scaling
#endif
    //VPBE_VENC_VMOD  = 0x00000043;   // Standard PAL interlaced output
    VPBE_VENC_VMOD	= 0x00002053|(0 << 4);	 // Standard PAL interlaced output

    VPBE_VENC_VIDCTL = 0x00002000|(1 << 4);
    VPBE_VENC_LCDOUT = 0x00000001;

    VPBE_VENC_DCLKCTL = 0x0000001;
    VPBE_VENC_DCLKPTN0 = 0x1;	//	 

    VPBE_VENC_HSPLS = 1*2;// 40*2
    VPBE_VENC_HINT = 862*2-1;// 1056*2 - 1
    VPBE_VENC_HSTART = 46*2; // (40 + 4)*2
    VPBE_VENC_HVALID = 800*2; // 800*2

    VPBE_VENC_VSPLS = 1;// 10
    VPBE_VENC_VINT = 522-1;//0x20C; // 525 - 1
    VPBE_VENC_VSTART = 23;//0xc; // 10 + 2
    VPBE_VENC_VVALID = 480;//0x1E0;  // 480  

    //	VPBE_VENC_HSDLY = 1;
    //	VPBE_VENC_VSDLY = 1;

    VPBE_VENC_SYNCCTL = 0xf|(0 << 11); //Set HSYNC, VSYNC as active low

    VPBE_VENC_RGBCTL = 0x0|(1 << 10);

    VPBE_VENC_VDPRO 	=  0 << 8 |(0 << 9) | (0 << 11);

    VPBE_VENC_DACTST = 0|(0xf << 12);	//DAC Power-down mode
    VPBE_VENC_DACSEL	= 0x000000;
	
}


/*****************************************************************************
 * Prototype : vpbe_init
 * description  : DM6437 VPBE init
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

void vpbe_init()
{
    int i , j;
    for (j = 0; j < 8; j++) 
    {
        for (i = 0; i < IMAGE_W * IMAGE_H; i++) 
        {
            vpbe_frame_buf[j][(i << 1)] = 128;       // U,V = 128
            vpbe_frame_buf[j][(i << 1) + 1] = 0x00; //Y=0 . Black color
        }
    }    
    
//    vpbe_venc_cvbs( (Uint32)vpbe_frame_buf[vpbe_frame_buf_offset]);
    vpbe_venc_lcd((Uint32)vpbe_frame_buf[vpbe_frame_buf_offset]);

}

Uint32 get_vpbe_frame_buf()
{
    Uint32 ret;
    Uint8 temp ;

    if (((vpbe_free_buf_offset + 8 - vpbe_frame_buf_offset) & 7) > 3) {// interlace less than 3 line
        vpbe_frame_buf_offset = (vpbe_free_buf_offset + 5) & 7;
    }
    
    ret = (Uint32)vpbe_frame_buf[vpbe_frame_buf_offset];
    temp = (vpbe_frame_buf_offset+1) & 7;
    if((temp != vpbe_free_buf_offset) && (temp != (vpbe_free_buf_offset+7) & 7 )){ // interlace more than 1 line
        vpbe_frame_buf_offset = temp;
    }

    return ret;
}


Uint32 get_vpbe_free_buf()
{
    return (Uint32)vpbe_frame_buf[vpbe_free_buf_offset];
}


void set_vpbe_frame_to_free()
{
    Uint8 temp ;
    temp = (vpbe_free_buf_offset+1) & 7;

    if(temp != vpbe_frame_buf_offset)
    {
        vpbe_free_buf_offset = temp;
    }
}




