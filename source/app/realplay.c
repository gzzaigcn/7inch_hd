#include "global.h"
#include "dm6437_vpfe.h"
#include "dm6437_vpbe.h"
#include "dm6437_edma3.h"
#include "img_alg.h"
#include "realplay.h"

#define ZOOM_LEVEL_NUM 16

extern volatile Uint8 preview_done_flag; 


Uint8 scale_rsz[ZOOM_LEVEL_NUM] = {64, 128};
volatile Uint8 scale_level = 1;


Uint32 display_buf;
Uint32 image_src_buf;
Uint32 resized_buf;

Uint32 color_mode = TRUE_COLOR_MODE; //1:flase color, 0:true color
Uint32 flase_color_type = WHITE_BLACK_TYPE; //flase color transfer type

Uint32 ostu_enable_flag  = 1;
Uint32 ostu_thrd_cnt = 0;

void realplay_process()
{
    if(preview_done_flag)
    {

        image_src_buf = get_vpfe_frame_buf();
//        resized_buf = get_resize_frame_buf();
        display_buf = get_vpbe_free_buf();

//        ostu_enable_flag = 1;
//        ostu_thrd_cnt++;
        wait_resize();
        set_resizer(image_src_buf, display_buf, 256, 256);
        start_resize();
        
/*        
        if(color_mode == TRUE_COLOR_MODE)// flase color mode
        {
            true_color_dma_process(resized_buf, display_buf, IMAGE_W, IMAGE_W, IMAGE_W, IMAGE_H);
        }
        else
        {
            false_color_dma_process(resized_buf, display_buf, flase_color_type, IMAGE_W, IMAGE_W, IMAGE_W, IMAGE_H);
        }

        if(ostu_enable_flag)
        {
            if(ostu_thrd_cnt == OSTU_BLK_XNUM)
            {
                ostu_thrd_cnt = 0;
                cal_ostu_global_threshold();
            }
        }
*/
        set_vpbe_frame_to_free();
        preview_done_flag = 0;
        
    }
}


