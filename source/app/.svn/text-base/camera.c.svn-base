#include <stdio.h>
#include "camera.h"
#include "ov2710.h"
#include "ov5640.h"
#include "actuator.h"

camera_ops *camera_handle = NULL;

camera_ops camera_list[SUPPORT_CAMERA_NUM] =
{
    camera_list_item(ov2710),
    camera_list_item(ov5640),
};


void open_camera(Uint32 camera_id)
{
    camera_ops *ops;
    Int8 ret;
    
    ops = &camera_list[camera_id];
//    ops = &camera_list[CAMERA_OV5640];

    ops->camera_ctrl_power(CAMERA_CTRL_PWR_ON);

    ret = ops->camera_init();
    if(ret < 0)
    {
        camera_handle = NULL;
    }

    /*vcm actuator init*/
//    wv511_init();
    
    camera_handle = ops;
    
}

void close_camera()
{
    
    camera_handle->camera_ctrl_power(CAMERA_CTRL_PWR_OFF);
    
}

/*camera enter stangdby sleep mode */
void enter_camera_stby()
{
    
    camera_handle->camera_ctrl_power(CAMERA_CTRL_STBY_ON);
            
}

/*camera enter stangdby sleep mode */
void exit_camera_stby()
{
    
    camera_handle->camera_ctrl_power(CAMERA_CTRL_STBY_OFF);
    
}


