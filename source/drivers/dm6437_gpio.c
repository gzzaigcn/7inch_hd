/******************************************************************************

   Copyright (C), 2014-,    Du-Health Electron Co.    All rights reserved. 

*******************************************************************************
 * File Name : dm6437_gpio.c
 * Version : 1.0
 * Author : gzz
 * Created : 2014/9/3
 * Last Modified :
  Description   : dm6437 GPIO setup
 * Function List :
              EVMDM6437_GPIO_checkOutput
              EVMDM6437_GPIO_getInput
              EVMDM6437_GPIO_init
              EVMDM6437_GPIO_setDir
              EVMDM6437_GPIO_setOutput
 * Modification History :
   1.Date : 2014/9/3
     Author : gzz
     Modification : Created file
 
******************************************************************************/

#include "dm6437_gpio.h"

static GPIO_Handle Gpio_Handle[4] = {
    ( GPIO_Handle )&GPIO_MODULE_01,
    ( GPIO_Handle )&GPIO_MODULE_23,
    ( GPIO_Handle )&GPIO_MODULE_45,
    ( GPIO_Handle )&GPIO_MODULE_6
};

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  _GPIO_init( )                                                           *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 EVMDM6437_GPIO_init( )
{
    GPIO_PCR = 1;                           // Free GPIO from emulation
    return 0;
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  _GPIO_setDir( number, direction )                                       *
 *                                                                          *
 *      number    <- GPIO#                                                  *
 *      direction <- 0:OUT 1:IN                                             *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 EVMDM6437_GPIO_setDir( Uint16 number, Uint8 direction )
{
    Uint32 bank_id = ( number >> 5 );
    Uint32 pin_id  = ( 1 << ( number & 0x1f ) );
    GPIO_Handle gpio_handle = Gpio_Handle[bank_id];

    if ( ( direction & 1 ) == GPIO_OUT )
        gpio_handle->regs->DIR &= ~pin_id;  // Set to OUTPUT
    else
        gpio_handle->regs->DIR |= pin_id;   // Set to INPUT

    return 0;
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  _GPIO_setOutput( number, output )                                       *
 *                                                                          *
 *      number  <- GPIO#                                                    *
 *      value   <- 0:LOW 1:HIGH                                             *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 EVMDM6437_GPIO_setOutput( Uint16 number, Uint8 output )
{
    Uint32 bank_id = ( number >> 5 );
    Uint32 pin_id  = ( 1 << ( number & 0x1f ) );
    GPIO_Handle gpio_handle = Gpio_Handle[bank_id];

    if ( ( output & 1 ) == 0 )
        gpio_handle->regs->CLR_DATA = pin_id;  // Set to LOW
    else
        gpio_handle->regs->SET_DATA = pin_id;  // Set to HIGH

    return 0;
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  _GPIO_getInput( number )                                                *
 *                                                                          *
 *      number      <- GPIO#                                                *
 *                                                                          *
 *      Returns:    0:LOW                                                   *
 *                  1:HIGH                                                  *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 EVMDM6437_GPIO_getInput( Uint16 number )
{
    Uint32 input;
    Uint32 bank_id = ( number >> 5 );
    Uint32 pin_id  = ( number & 0x1f );
    GPIO_Handle gpio_handle = Gpio_Handle[bank_id];

    input = gpio_handle->regs->IN_DATA;
    input = ( input >> pin_id ) & 1;

    return input;
}


Int16 EVMDM6437_GPIO_checkOutput( Uint16 number )
{
    Uint32 bank_id = ( number >> 5 );
    Uint32 pin_id  = ( number & 0x1f );
	Uint32 CheckValue;
    
    GPIO_Handle gpio_handle = Gpio_Handle[bank_id];    
    CheckValue = gpio_handle->regs->OUT_DATA;
    CheckValue = (CheckValue >> pin_id)&1; 
            
    return CheckValue; 
}
