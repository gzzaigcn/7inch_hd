/******************************************************************************

   Copyright (C), 2013-,    Zjut Image Processing Lab.    All rights reserved. 

*******************************************************************************
 * File Name : image_alg.h
 * Version : 1.0
 * Author : Gzz
 * Created : 2013/8/23
 * Last Modified :
 * Description : image_alg.c header file
 * Function List :
 * Modification History :
   1.Date : 2013/8/23
     Author : Gzz
     Modification : Created file
 
******************************************************************************/

#ifndef __IMAGE_ALG_H__
#define __IMAGE_ALG_H__

#include "dm6437.h"
#include "image_process.h"

#define STATE_MOVE    1
#define STATE_STATIC 0

#define MOVE_UP_THRESHOLD    
#define MOVE_DOWN_THRESHOLD
#define MOVE_LEFT_THRESHOLD
#define MOVE_RIGHT_THRESHOLD

#define MARK_NURTRON 21
#define MARK_4X6 22
#define MARK_16X16 23

#define MOVE_STATIC_ASIIC 24
#define MOVE_UP_ASIIC         25
#define MOVE_DOWN_ASIIC   26
#define MOVE_LEFT_ASIIC     27
#define MOVE_RIGHT_ASIIC   28

#define IMAGE_ALL_NULL 0
#define IMAGE_ALL_WHITE 126
#define IMAGE_ALL_BLACK 127

/*define the image information after image goal cutting off*/
typedef struct 
{

  Uint32 x_left;
  Uint32 x_right;
  Uint32 y_up;
  Uint32 y_down;
  Int32 width;
  Int32 height;
  Uint32 center_x;
  Uint32 center_y;
  
}subimage_info;



#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */


typedef void (*PFUN_SET_IMAGE_COLOR)(Uint8 *image_buf, Uint32 width, Uint32 height, Uint32 stride, Uint8 * color_table);

typedef void (*PFUN_COPY_IMAGE)(Uint8 *inbuf, Uint8 *outbuf, Uint32 SrcWidth, Uint32 DstWidth, Uint32 width, Uint32 height);

typedef void (*PFUN_TRANS_GRAY_LINER)(Uint32 OutBuffer, Uint32 InBuffer, Uint32 SrcStride, Uint32 DstStride, Uint32 Width, Uint32 Height);

typedef Uint32 (*PFUN_CAL_BLOCK_GRAY)(Uint32 in_buf, Uint32 blk_w, Uint32 blk_h, Uint32 stride);



extern void copy_image_c(Uint8 *outbuf, Uint8 *inbuf,  Uint32 SrcWidth, Uint32 DstWidth, Uint32 width, Uint32 height);
void image_vision_convert(Uint8 *image_src, Uint32 src_width, Uint32 src_height, Uint32 dst_width, Uint32 dst_height);

extern void average_filter(Uint32 src_width, Uint32 src_height);

extern void image_histogram(Uint8 *image_src, Uint32 src_width, Uint32 src_height, Uint32 dst_width, Uint32 dst_height);
extern void delete_noise(Uint32 src_width, Uint32 src_height);
extern void get_simlarity(Uint32 ascii_id);
extern void image_alg_init();

extern Int8 image_binary(Uint32 src_width, Uint32 src_height);
extern void image_cutting(Uint32 src_width, Uint32 src_height);
extern void image_match(recog_result *recog_result);
extern void goal_image_resize();

extern void raw_image_resize(Uint32 raw_w, Uint32 raw_h);

extern void disp_raw_image(Uint8 *vpbe_buf, Uint32 disp_w, Uint32 disp_h);

extern void disp_4x6_block(Uint8 *vpbe_buf, recog_result *recog_result);

extern void disp_16x16_block(Uint8 *vpbe_buf, recog_result *recog_result);

extern void image_thining();
extern void set_image_color_c(Uint8 *image_buf, Uint32 width, Uint32 height, Uint32 stride, Uint8 * color_table);

extern void jpeg_decode(Uint8 *pin_buf, Uint8 *pout_buf, Uint32 dim );

extern void jpeg_encode(Uint8 *pin_buf, Uint8 *pout_buf);


/*otsu algorithm api*/
extern void create_gray_table();
extern void clear_gray_hist();

extern void trans_gray_liner_c(Uint32 OutBuffer, Uint32 InBuffer, Uint32 SrcStride, Uint32 DstStride, Uint32 Width, Uint32 Height);

extern Uint32 cal_opt_threshold(Uint32 Width, Uint32 Height );

extern void binary_based_block();

extern void cal_gray_hist();



#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __IMAGE_ALG_H__ */
