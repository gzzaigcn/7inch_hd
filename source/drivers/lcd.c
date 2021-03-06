/******************************************************************************

   Copyright (C), 2014-,    Du-Health Electron Co.    All rights reserved. 

*******************************************************************************
 * File Name : lcd.c
 * Version : 1.0
 * Author : gzz
 * Created : 2014/11/10
 * Last Modified :
  Description   : 800*400 lcd  driver
 * Function List :
              EVMDM6437_PWM1_Init
              EVMDM6437_PWM1_Start
              lcd_init
 * Modification History :
   1.Date : 2014/11/10
     Author : gzz
     Modification : Created file
 
******************************************************************************/
#include "dm6437_gpio.h"
#include "lcd.h"

Int16 EVMDM6437_PWM1_Init( )
{

	PWM1_PH1D = 24000;
	PWM1_PER = 27000;
	PWM1_CFG = 0
		| (1 << 17)	//[OPST] 0:Idle mode, 1:Running mode
		| (1 << 16)	//[CURLEV] PWM output status, 0:Low 1:High
		| (0 << 6)	//[INTEN] Interrupt enable, 0:Disable 1:Enable
		| (0 << 5)	//[INACTOUT] Inactive output level, 0:Low 1:High
		| (1 << 4)	//[P1OUT] First-phase output level, 0:Low 1:High
		| (0 << 3)	//[EVTRIG]
		| (2 << 0);	//[MODE]

	return 0;
}

Int16 EVMDM6437_PWM1_Start( )
{
	PWM1_PCR = 1;
	PWM1_START = 1;
	return 0;
}


/*****************************************************************************
 * Prototype : LCD_init
 * description  : LCD hardware initation.
 * Input :  None 
 * Output : None
 * Return Value : void
 * remind: GPIO_init(),set the relative PINMUX!!
 * 	   
 ****************************************************************************/ 
void lcd_init(void)
{
    EVMDM6437_GPIO_setDir(GPIO65, GPIO_OUT);//LCD_PWR
    EVMDM6437_GPIO_setDir(GPIO62, GPIO_OUT);//LCD_ON
    //EVMDM6437_GPIO_setDir(GPIO83,GPIO_OUT);//LCD_BLACKLED  //when LCD_BLACKLED use pwm0 to control, ignore GPIO83

    EVMDM6437_GPIO_setOutput(GPIO65, 0);
    EVMDM6437_GPIO_setOutput(GPIO62, 1);
    //EVMDM6437_GPIO_setOutput(GPIO83,1);
    EVMDM6437_PWM1_Init( );	//Set the PWM1 out is 1Khz , duty cycle is 50%
    EVMDM6437_PWM1_Start( );
}



