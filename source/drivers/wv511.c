/******************************************************************************

   Copyright (C), 2014-,    Du-Health Electron Co.    All rights reserved. 

*******************************************************************************
 * File Name : wv511.c
 * Version : 1.0
 * Author : gzz
 * Created : 2014/9/9
 * Last Modified :
  Description   : vcm driver ic:wv511 module
 * Function List :
              wv511_write
 * Modification History :
   1.Date : 2014/9/9
     Author : gzz
     Modification : Created file
 
******************************************************************************/

#include "stdio.h"
#include "dm6437_gpio.h"
#include "dm6437_i2c.h"
#include "actuator.h"
#include "debug.h"



#define MODULE_NAME "wv511"

#define WV511_I2C_ADDR  (0x18 >> 1)
#define WV511_ID 0x2710

/*The wv511 IOUT goes to the target code directly*/
#define WV511_DIRECT_MODE 

#define WV511_TOATL_STEPS 64
#define WV511_POS_MIN 0
#define WV511_POS_MAX  640

#define WV511_PWR_ON    1
#define WV511_PWR_OFF  0

#define WV511_PWDN_MASK 0x8000



actuator_ctrl_t wv511_ctrl;

Uint16 setp_position_table[2*WV511_TOATL_STEPS];



/*****************************************************************************
 * Prototype : wv511_write
 * description  : wv511 write by i2c: data: i2c_addr+2byte Data
 * Input :   Uint16 data  
 * Output : None
 * Return Value : static
 * Calls : 
 * Called By  : 
 
 * Modification History :
 * 1.Date : 2014/9/9
 *   Author : gzz
 *   Modification : Created function
 
*****************************************************************************/
static void wv511_write(Uint16 u16)
{
    Int16 ret;
    Uint8 data[2];

    data[0] = (u16 & 0xff00) >> 8;//addr MSB first
    data[1] = u16 & 0x00ff;
    
    ret = EVMDM6437_I2C_write(WV511_I2C_ADDR, data, 2);
    if(ret < 0)
    {
        DEV_ERR("WV511 failed to write");
    }
}


/*****************************************************************************
 * Prototype : wv511_set_code
 * description  : set wv511 Slew Rate Value
 * Input :   actuator_ctrl_t act_ctrl  
                   Uint16 new_code           
                   Uint16 sr                 
 * Output : None
 * Return Value : static
 * Calls : 
 * Called By  : 
 
 * Modification History :
 * 1.Date : 2014/9/9
 *   Author : gzz
 *   Modification : Created function
 
*****************************************************************************/
void wv511_set_code(Uint16 new_code)
{
    Uint16 last_code;
	Uint16 target_code;
	Uint16 max_code, min_code;
    Uint16 diff;
    Uint16 dir;
    Uint16 range;


    last_code = wv511_ctrl.curr_code;
    max_code = wv511_ctrl.active_max;
    min_code = wv511_ctrl.active_min;
    range = wv511_ctrl.active_max-wv511_ctrl.active_min;

    if(last_code > new_code) ///negative 
    {
        diff = last_code - new_code;
        dir = 0;
    }
    else if(last_code < new_code) //positive
    {
        diff = new_code - last_code;
        dir = 1;        
    }
    else
    {
        return;
    }
    target_code = last_code; //start from last code 
#ifdef WV511_DIRECT_MODE
    wv511_write(( new_code << 4) | 0x00);
#else

    Uint16 sr; // vcm slew rate
    Uint16 delta_code;
    if(dir < 0)
    {
       if( (diff >= 1) && (new_code <= (min_code + range/8)) &&
                     (last_code >= (min_code + range/6)) )
       {
            Uint32 delay;
            if(target_code >= max_code - range/5)
                delay=30;
            else if(target_code >= min_code + range/6))
                delay=20;
            else
                delay=10;
            
            sr=0xf;
            target_code=range/8 + min_code;

            wv511_write((target_code & 0x3ff) << 4 | sr);
            wv511_ctrl.curr_code = target_code; //save to current code 
            _waitusec(delay*1100);
                    
       }
       else if(diff > (range/6) && new_code < min_code + (range/6))
       {
            int loop=0;
            sr=0x3;
            
            if(diff>(range/3))
                delta_code=(diff+1)/3;
            else
                delta_code=(diff+1)/2;

            while(target_code > new_code)
            {
                
                if(loop++ == 3)
                    break;

                if(target_code > delta_code)
                    target_code = target_code - delta_code;
                else
                    break;
                
                if(target_code < new_code || target_code <= delta_code)
                    break;
                
                wv511_write((target_code & 0x3ff) << 4 | sr);
                wv511_ctrl.curr_code = target_code; //save to current code 

               _waitusec(12000);
                
            }
       }
       else
       {
            sr = 0x3 & 0xff;
            wv511_write((new_code & 0x3ff) << 4 | sr);
       }
       
    }
    else //positive direction
    {
        
        if( (diff > range/5)  && ( new_code >= (max_code -range/10)) &&
                (last_code <= (min_code - range/6)))
        {
            int delay;

            if(new_code >= max_code - range/10)
                delay = 20;
            else
                delay = 10;

            if(new_code >= max_code - range/10) 
                target_code = max_code - range/10;

            sr = 0x0f;
            wv511_write((target_code & 0x3ff) << 4 | sr);
            wv511_ctrl.curr_code = target_code; //save to current code 
            _waitusec(delay*1100);
            
        }
        
        if(target_code < new_code)
        {
            sr = 0x1;
            wv511_write((new_code & 0x3ff) << 4 | sr);
        }
                
    }
#endif   

    wv511_ctrl.curr_code = new_code ;//save new vcm code

}

/*
void wv511_set_pos(Uint16 pos)
{
    
}*/
/*
static void init_position_table()
{
    
}
*/

void wv511_ctrl_power(Uint8 ctrl_id)
{
    
    switch(ctrl_id)
    {
        case ACTUATOR_PWR_ON://power on

            EVMDM6437_GPIO_setDir(VCM_ACTUATOR_GPIO_POWER, GPIO_OUT);
            EVMDM6437_GPIO_setOutput(VCM_ACTUATOR_GPIO_POWER, WV511_PWR_ON);            

            break;

        case ACTUATOR_PWR_OFF:

            EVMDM6437_GPIO_setOutput(VCM_ACTUATOR_GPIO_POWER, WV511_PWR_OFF);     
            EVMDM6437_GPIO_setDir(VCM_ACTUATOR_GPIO_POWER, GPIO_IN);
            
            break;

        case ACTUATOR_STBY_ON: //stby on

            wv511_write(WV511_PWDN_MASK);
            break;

        case ACTUATOR_STBY_OFF: //stby off

            wv511_write((~WV511_PWDN_MASK));
            break;

        default:
            break;
    }

    
}


void wv511_init()
{
    
    wv511_ctrl.active_min = WV511_POS_MIN;
    wv511_ctrl.active_max = WV511_POS_MAX;
    
    wv511_ctrl.curr_pos = 0;
    wv511_ctrl.curr_code = 0;

    wv511_ctrl_power(ACTUATOR_PWR_ON);

   Uint32 code = 0;
    while(1)
    {
        if(code == 1000)
        {
            code = 0;
        }
        else
            code+= 100;
        
        wv511_set_code(code);
        _waitusec(100000);
    }
}

