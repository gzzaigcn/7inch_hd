/******************************************************************************

   Copyright (C), 2014-,    Du-Health Electron Co.    All rights reserved. 

*******************************************************************************
 * File Name : range_sensor.c
 * Version : 1.0
 * Author : gzz
 * Created : 2014/9/13
 * Last Modified :
  Description   : als/ps/IR LED there sensors :TMD27713 Module  Drivers
 * Function List :
 * Modification History :
   1.Date : 2014/9/13
     Author : gzz
     Modification : Created file
 
******************************************************************************/
#include "dm6437.h"
#include "dm6437_gpio.h"
#include "dm6437_i2c.h"
#include "debug.h"
#include "tmd2771.h"
#include "debug.h"

#define MODULE_NAME "TMD2771"


#define TMD2771_INT_GPIO  GPIO66


#define TMD2771_I2C_ADDR  0x39
#define TMD2771_DEVICE_ID 0x29

/*Macro for TMD2771 register address*/
#define TMD2771_REG_ENABLE   0x00    // R/W, Enables states and interrupts
#define TMD2771_REG_ATIME   0x01     // R/W, ALS ADC time
#define TMD2771_REG_PTIME   0x02     // R/W, Proximity ADC time
#define TMD2771_REG_WTIME   0x03  // R/W Wait time

#define TMD2771_REG_AILTL   0x04   //R/W ALS interrupt low threshold low byte
#define TMD2771_REG_AILTH  0x05   //R/W ALS interrupt low threshold high byte
#define TMD2771_REG_AIHTL   0x06    //R/W ALS interrupt high threshold low byte
#define TMD2771_REG_AIHTH   0x07    //R/W ALS interrupt high threshold high byte

#define TMD2771_REG_PILTH   0x08    // R/W Proximity interrupt low threshold low byte
#define TMD2771_REG_PILTL   0x09    // R/W Proximity interrupt low threshold high byte
#define TMD2771_REG_PIHTL   0x0a    // R/W Proximity interrupt low threshold low byte
#define TMD2771_REG_PIHTH   0x0b    // R/W Proximity interrupt high threshold high byte

#define TMD2771_REG_PERS   0x0c     // R/W Interrupt persistence filters
#define TMD2771_REG_CONFIG   0x0d   // R/W Configuration
#define TMD2771_REG_PPLUSE   0x0e   // R/W Proximity pulse count
#define TMD2771_REG_CONTROL   0x0f  // R/W Control register
#define TMD2771_REG_ID   0x12            //R Device ID
#define TMD2771_REG_STATUS   0x13    //R Device status

#define TMD2771_REG_C0DATAL   0x14   //R CH0 ADC low data register
#define TMD2771_REG_C0DATAH   0x15   //R CH0 ADC high data register
#define TMD2771_REG_C1DATAL   0x16     //R CH1 ADC low data register
#define TMD2771_REG_C1DATAH   0x17  //R CH1 ADC high data register
#define TMD2771_REG_PDATAL      0x18        //R Proximity ADC low data register
#define TMD2771_REG_PDATAH   0x19     //R Proximity ADC high data register

/* Support Wait Long the wait cycles are increased by a factor 12X WTIME register */
#define SUPPORT_WAIT_LONG

/*Command register MASK, Command MSB Must  be '1' */
#define COMMAND_REG_MASK 0x80

/*Status Register for TMD2771 */
#define STATUS_PINT_MASK     (1 << 5)
#define STATUS_AINT_MASK     (1 << 4)
#define STATUS_AVAILD_MASK     (1 << 0)


//FIELD ADD Values in Command register code
#define FILED_NO_ACTION          0
#define FILED_CLEAR_PINT       5
#define FILED_CLEAR_AINT       6
#define FILED_CLEAR_APINT     7



static void tmd2771_write(Uint8 reg, Uint8 value)
{
    Int16 ret;
    Uint8 data[2];

    data[0] = reg | COMMAND_REG_MASK;
    data[1] = value;
    
    ret = EVMDM6437_I2C_write(TMD2771_I2C_ADDR, data, 2);
    if(ret < 0)
    {
        DEV_ERR("TMD2771 Write failed");
    }
    
}


static void tmd2771_read(Uint8 reg, Uint8 *value)
{
    Int16 ret;
    reg |= COMMAND_REG_MASK;
    
    /*send reg address to slave*/
    ret = EVMDM6437_I2C_write(TMD2771_I2C_ADDR, &reg, 1);
    if(ret < 0)
    {
        DEV_ERR("TMD2771 Write failed");
        return;
    }

    /*read data on reg from slave*/
    ret = EVMDM6437_I2C_read(TMD2771_I2C_ADDR, value, 1);
    if(ret < 0)
    {
        DEV_ERR("TMD2771 read failed");
    }
    _waitusec(1000);

}

static void tmd2771_set_special_reg(Uint8 filed_value)
{
    Int16 ret; 
    Uint8 cmd;

    cmd = ((0x11 << 5) + filed_value) | COMMAND_REG_MASK;

    ret = EVMDM6437_I2C_write(TMD2771_I2C_ADDR, &cmd, 1);
    if(ret < 0)
    {
        DEV_ERR("TMD2771 Write failed");
        return;
    }
    
}



void tmd2771_enable(Uint8 en_cfg)
{
    
    en_cfg |= 0x01; //PCON ON
    tmd2771_write(TMD2771_REG_ENABLE, en_cfg);

    /*delay 3ms to ensure oscillator stable*/
    _waitusec(3000);

}

void tmd2771_disable()
{
    tmd2771_write(TMD2771_REG_ENABLE, 0x00);
}




void tmd2771_clear_int()
{
    
    Uint8 status;
    Uint8 cmd;

    /*read TMD2771 status registers*/
    tmd2771_read(TMD2771_REG_STATUS, &status);

    /**/
    if((status & STATUS_PINT_MASK) && (status & STATUS_AINT_MASK))
    {
        tmd2771_set_special_reg(FILED_CLEAR_APINT);
    }

    else if(status & STATUS_AINT_MASK)
    {
        tmd2771_set_special_reg(FILED_CLEAR_AINT);
    }

    else if(status & STATUS_PINT_MASK)
    {
        tmd2771_set_special_reg(FILED_CLEAR_PINT);
    }

    else
    {
        DEV_ERR("invaild interrupt status");
        return;
    }

    
}


/*****************************************************************************
 * Prototype : tmd2771_set_als_thrd
 * description  : set als threshold include upper or lower limit
 * Input :   Uint16 thrd  
                   Uint8 mark   
 * Output : None
 * Return Value : 
 * Calls : 
 * Called By  : 
 
 * Modification History :
 * 1.Date : 2014/9/14
 *   Author : gzz
 *   Modification : Created function
 
*****************************************************************************/
void tmd2771_set_als_thrd(Uint16 thrd, Uint8 mark)
{
    
    Uint8 als_low;
    Uint8 als_high;

    als_low = thrd & 0x00ff;
    als_high = (thrd & 0xff00) >> 8;


    /*set ALS interrupt upper threshold*/    
    if(mark)
    {
        tmd2771_write(TMD2771_REG_AIHTH, als_high);
        tmd2771_write(TMD2771_REG_AIHTL, als_low);
    }

    else //set ALS interrupt lower threshold    
    {
        tmd2771_write(TMD2771_REG_AILTH, als_high);
        tmd2771_write(TMD2771_REG_AILTL, als_low);
    }
    
}


/*****************************************************************************
 * Prototype : tmd2771_set_prox_thrd
 * description  : set proximity threshold include upper or lower limit
 * Input :   Uint16 thrd  
                   Uint8 mark   
 * Output : None
 * Return Value : 
 * Calls : 
 * Called By  : 
 
 * Modification History :
 * 1.Date : 2014/9/14
 *   Author : gzz
 *   Modification : Created function
 
*****************************************************************************/
void tmd2771_set_prox_thrd(Uint16 thrd, Uint8 mark)
{
    
    Uint8 prox_low;
    Uint8 prox_high;

    prox_low = thrd & 0x00ff;
    prox_high = (thrd & 0xff00) >> 8;


    /*set prox interrupt upper threshold*/    
    if(mark)
    {
        tmd2771_write(TMD2771_REG_AIHTH, prox_high);//MSB
        tmd2771_write(TMD2771_REG_AIHTL, prox_low); //LSB
    }

    else //set ALS interrupt lower threshold    
    {
        tmd2771_write(TMD2771_REG_AILTH, prox_high); //MSB
        tmd2771_write(TMD2771_REG_AILTL, prox_low); //LSB
    }
    
}



/*****************************************************************************
 * Prototype : tmd2771_cfg_timer
 * description  : configure timer value for tmd2771
 * Input :   Uint16 atime  
                   Uint16 ptime  
                   Uint8 wtime   
                   Uint8 ppluse  
                   Uint8 pers    
 * Output : None
 * Return Value : 
 * Calls : 
 * Called By  : 
 
 * Modification History :
 * 1.Date : 2014/9/15
 *   Author : gzz
 *   Modification : Created function
 
*****************************************************************************/
void tmd2771_cfg_timer(Uint16 atime, Uint16 ptime, Uint8 wtime, Uint8 ppluse, Uint8 pers)
{
    
    tmd2771_write(TMD2771_REG_ATIME, atime);
    tmd2771_write(TMD2771_REG_PTIME, ptime);
    tmd2771_write(TMD2771_REG_WTIME, wtime);   
    
    tmd2771_write(TMD2771_REG_PPLUSE, ppluse);   
    tmd2771_write(TMD2771_REG_PERS, pers);   

    #ifdef  SUPPORT_WAIT_LONG
    tmd2771_write(TMD2771_REG_CONFIG, 0x01);// enable 12X WTIME
    #else
    tmd2771_write(TMD2771_REG_CONFIG, 0x00);
    #endif
    
}



/*****************************************************************************
 * Prototype : tmd2771_ctrl_analog_block
 * description  : Set Control Register to analog block include als gain/select prox diode /pdrive
 * Input :   CTRL_ALS_GAINS als_gain  
                   CTRL_PROX_DIODE pdiode   
                   CTRL_LED_DRIVE pdrive    
 * Output : None
 * Return Value : 
 * Calls : 
 * Called By  : 
 
 * Modification History :
 * 1.Date : 2014/9/15
 *   Author : gzz
 *   Modification : Created function
 
*****************************************************************************/
void tmd2771_ctrl_analog_block(CTRL_ALS_GAINS als_gain, CTRL_PROX_DIODE pdiode, CTRL_LED_DRIVE pdrive)
{
    Uint8 val = 0;

    val |= als_gain + (pdiode << 4) + (pdrive << 6);

    tmd2771_write(TMD2771_REG_CONTROL, val);
    
}


/*****************************************************************************
 * Prototype : tmd2771_get_als_data
 * description  : get ala adc data from channel0 or channel1
 * Input :   Uint8 channel  
 * Output : None
 * Return Value : 
 * Calls : 
 * Called By  : 
 
 * Modification History :
 * 1.Date : 2014/9/14
 *   Author : gzz
 *   Modification : Created function
 
*****************************************************************************/
Uint16 tmd2771_get_als_data(Uint8 channel)
{
    Uint16 als_data;

    Uint8 als_adc_low;
    Uint8 als_adc_high;

    if(!channel) //
    {
        tmd2771_read(TMD2771_REG_C0DATAL, &als_adc_low);
        tmd2771_read(TMD2771_REG_C0DATAH, &als_adc_high);
    }
    else
    {
        tmd2771_read(TMD2771_REG_C1DATAL, &als_adc_low);
        tmd2771_read(TMD2771_REG_C1DATAH, &als_adc_high);
    }

    als_data = als_adc_low + (als_adc_high << 8);

    return als_data;
}



/*****************************************************************************
 * Prototype : tmd2771_get_prox_adc_data
 * description  : get proximity adc data
 * Input : None
 * Output : None
 * Return Value : 
 * Calls : 
 * Called By  : 
 
 * Modification History :
 * 1.Date : 2014/9/14
 *   Author : gzz
 *   Modification : Created function
 
*****************************************************************************/
Uint16 tmd2771_get_prox_adc_data()
{
    Uint8 prox_adc_low;
    Uint8 prox_adc_high;

    Uint16 prox_data = 0;

    tmd2771_read(TMD2771_REG_PDATAL, &prox_adc_low);
    tmd2771_read(TMD2771_REG_PDATAH, &prox_adc_high);

    prox_data = prox_adc_low + (prox_adc_high << 8);

    return prox_data;
    
}



static Int8 tmd2771_detect()
{
    Uint8 id;

    tmd2771_read(TMD2771_REG_ID, &id);
    if(id != TMD2771_DEVICE_ID)
    {
        return -1;
    }

    return 1;
}


Int8 tmd2771_init()
{
    Int8 ret;

    ret = tmd2771_detect();
    if (ret < 0)
    {
        DEV_ERR("TMD2771 is not found on board");
        return -1;
    }

    DEV_DBG("detect TMD2771");

    /*set TMD27713 Interrupt gpio by rising edge*/
    EVMDM6437_GPIO_setDir(TMD2771_INT_GPIO, GPIO_IN);
    
    /*set default als uppder and lower threshold*/
    tmd2771_set_als_thrd(TMD2771_DEF_ALS_LOWER, TMD2771_LOW_BYTE_MASK);
    tmd2771_set_als_thrd(TMD2771_DEF_ALS_UPPER, TMD2771_HIGH_BYTE_MASK);
    tmd2771_set_prox_thrd(TMD2771_DEF_PROX_LOWER, TMD2771_LOW_BYTE_MASK);
    tmd2771_set_prox_thrd(TMD2771_DEF_PROX_UPPER,  TMD2771_HIGH_BYTE_MASK);

    /*init timers and ppluse or pers*/
    tmd2771_cfg_timer(TMD2771_DEF_ATIME, TMD2771_DEF_PTIME, TMD2771_DEF_WTIME, 
                                        TMD2771_DEF_PERS, TMD2771_DEF_PPULSE);
    
    /*init control register for analog block*/
    tmd2771_ctrl_analog_block(ALS_GAIN_1, PROX_DIODE_BOTH, LED_STRENGTH_100);

    /*enable module:wait timer, proximity, als, also enable als prox interrupt*/
    tmd2771_enable(TMD2771_ENABLE_AEN |TMD2771_ENABLE_PEN |TMD2771_ENALBE_WEN
                                                    |TMD2771_ENALBE_AIEN |TMD2771_ENALBE_PIEN);
    return 1;
}

