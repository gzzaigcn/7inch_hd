/******************************************************************************

   Copyright (C), 2013-,    Zjut Image Processing Lab.    All rights reserved. 

*******************************************************************************
 * File Name : osd.h
 * Version : 1.0
 * Author : Gzz
 * Created : 2013/8/8
 * Last Modified :
 * Description : osd.c header file
 * Function List :
 * Modification History :
   1.Date : 2013/8/8
     Author : Gzz
     Modification : Created file
 
******************************************************************************/

#ifndef __OSD_H__
#define __OSD_H__


#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

extern void display_osd_logo(Uint8 *logo_buf);
extern void display_osd_string(Uint8 *str, Uint32 x, Uint32 y);
extern void display_osd_image_info(Uint8 *direct_str, Uint8 *char_str, Uint32 x, Uint32 y);
extern unsigned char * get_assic_bmp_array(unsigned char bmp_char);
extern Uint32 get_osd_bmp_len(Uint8 * bmp_buffer);
extern void memset_osd_buf(Uint8 *osd_buf_addr, Uint8 * bmp_buffer, Uint32 xline_offset);
extern void osd_bmp_array_init();

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __OSD_H__ */
