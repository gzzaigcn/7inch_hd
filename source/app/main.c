/******************************************************************************

   Copyright (C), 2014-,    Zjut Image Processing Lab.    All rights reserved. 

*******************************************************************************
 * File Name : main.c
 * Version : 1.0
 * Author : gzz
 * Created : 2014/9/3
 * Last Modified :
  Description   : 7inch hd aid main enter
 * Function List :
              main
 * Modification History :
   1.Date : 2014/9/3
     Author : gzz
     Modification : Created file
 
******************************************************************************/
#include <stdio.h>
#include "dm6437.h"
#include "dm6437_cache.h"
#include "dm6437_edma3.h"
#include "dm6437_vpfe.h"
#include "dm6437_vpbe.h"
#include "camera.h"
#include "norflash_fs.h"
#include "global.h"
#include "realplay.h"
#include "lcd.h"
//#include "playback.h"
#include "norflash.h"


unsigned int sys_work_mode = REAL_PLAY_MODE;

 int main(void){

    /* dm6437 init:PINMUX,I2C,GPIO */
    EVMDM6437_init();
    EVMDM6437_GPIO_init();

    /* cache and edema init */
    Cache_InitCache();
    EDMA_init();

    Interrupt_init();

    lcd_init();
    vpbe_init();

    open_camera(CAMERA_OV5640);
//    open_camera(CAMERA_OV2710);

//    tmd2771_init();
    vpfe_init();

//    dm6437_mcbsp_init();

//    wv511_init();
//    while(1);
//    norflash_fs_cfg_init();

//    load_system_params();
///    norflash_fs_fat_init();
    while(1)
    {
        switch(sys_work_mode)
        {
            
            case REAL_PLAY_MODE:
                realplay_process();
                break;
                
            case PLAY_BACK_MODE:
            //    playback_process();
                break;

            default:
            	break;

        }
        
    }
    

    return 1;
    
}
