/******************************************************************************

   Copyright (C), 2014-,    Du-Health Electron Co.    All rights reserved. 

*******************************************************************************
 * File Name : dm6437_i2c.c
 * Version : 1.0
 * Author : gzz
 * Created : 2014/9/3
 * Last Modified :
  Description   : dm6437 I2C module setup
 * Function List :
              EVMDM6437_I2C_close
              EVMDM6437_I2C_init
              EVMDM6437_I2C_loopback
              EVMDM6437_I2C_read
              EVMDM6437_I2C_reset
              EVMDM6437_I2C_write
 * Modification History :
   1.Date : 2014/9/3
     Author : gzz
     Modification : Created file
 
******************************************************************************/
#include "dm6437_i2c.h"
volatile int i2c_inuse = 0;
Int32 i2c_timeout = 0x10000;

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  _I2C_init( )                                                            *
 *                                                                          *
 *      Enable and initalize the I2C module                                 *
 *      The I2C clk is set to run at 100 KHz                                *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 EVMDM6437_I2C_init( )
{
    #if 0
//    I2C_ICMDR   = 0;                    // Reset I2C
//    I2C_ICPSC   = 13;                   // Config prescaler for 27MHz
//    I2C_ICCLKL  = 5;                    // Config clk LOW for 100 kHz
//    I2C_ICCLKH  = 5;                    // Config clk HIGH for 100 kHz
//    I2C_ICMDR  |= ICMDR_IRS;            // Release I2C from reset
    I2C_ICMDR   = 0;                    // Reset I2C
    I2C_ICPSC   = 2;                   // Config prescaler for 27MHz
    I2C_ICCLKL  = 40;                    // Config clk LOW for 100 kHz
    I2C_ICCLKH  = 40;                    // Config clk HIGH for 100 kHz
    I2C_ICMDR  |= ICMDR_IRS;            // Release I2C from reset    
    #else
    I2C_ICMDR   = 0;                    // Reset I2C
    I2C_ICPSC   = 2;                   // Config prescaler for 27MHz
    I2C_ICCLKL  = 7;                    // Config clk LOW for 400 kHz
    I2C_ICCLKH  = 7;                    // Config clk HIGH for 400 kHz
    I2C_ICMDR  |= ICMDR_IRS;            // Release I2C from reset
    #endif 
    return 0;
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  _I2C_close( )                                                           *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 EVMDM6437_I2C_close( )
{
    I2C_ICMDR = 0;                      // Reset I2C
    return 0;
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  _I2C_reset( )                                                           *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 EVMDM6437_I2C_reset( )
{
    EVMDM6437_I2C_close( );
    EVMDM6437_I2C_init( );
    return 0;
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  _I2C_write( i2c_addr, data, len )                                       *
 *                                                                          *
 *      I2C write in Master mode                                            *
 *                                                                          *
 *      i2c_addr    <- I2C slave address                                    *
 *      data        <- I2C data ptr                                         *
 *      len         <- # of bytes to write                                  *
 *                                                                          *
 *      Returns:    0: PASS                                                 *
 *                 -1: FAIL Timeout                                         *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 EVMDM6437_I2C_write( Uint16 i2c_addr, Uint8* data, Uint16 len )
{
    Int32 timeout, i;
	if(i2c_inuse == 1)return -1;
	i2c_inuse = 1;
    I2C_ICCNT = len;                    // Set length
    I2C_ICSAR = i2c_addr;               // Set I2C slave address
    I2C_ICMDR = ICMDR_STT               // Set for Master Write
              | ICMDR_TRX
              | ICMDR_MST
              | ICMDR_IRS
              | ICMDR_FREE;

    _wait( 10 );                        // Short delay

    for ( i = 0 ; i < len ; i++ )
    {
        I2C_ICDXR = data[i];            // Write

        timeout = i2c_timeout;
        do
        {
            if ( timeout-- < 0 )
            {
                EVMDM6437_I2C_reset( );
                i2c_inuse = 0;
                return -1;
            }
        } while ( ( I2C_ICSTR & ICSTR_ICXRDY ) == 0 );// Wait for Tx Ready
    }

    I2C_ICMDR |= ICMDR_STP;             // Generate STOP
	i2c_inuse = 0;
    return 0;
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  _I2C_read( i2c_addr, data, len )                                        *
 *                                                                          *
 *      I2C read in Master mode                                             *
 *                                                                          *
 *      i2c_addr    <- I2C slave address                                    *
 *      data        <- I2C data ptr                                         *
 *      len         <- # of bytes to write                                  *
 *                                                                          *
 *      Returns:    0: PASS                                                 *
 *                 -1: FAIL Timeout                                         *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 EVMDM6437_I2C_read( Uint16 i2c_addr, Uint8* data, Uint16 len )
{
    Int32 timeout, i;
    if(i2c_inuse == 1)return -1;
    i2c_inuse = 1;
    I2C_ICCNT = len;                    // Set length
    I2C_ICSAR = i2c_addr;               // Set I2C slave address
    I2C_ICMDR = ICMDR_STT               // Set for Master Read
              | ICMDR_MST
              | ICMDR_IRS
              | ICMDR_FREE;

    _wait( 10 );                         // Short delay

    for ( i = 0 ; i < len ; i++ )
    {
        timeout = i2c_timeout;
        do
        {
            if ( timeout-- < 0 )
            {
                EVMDM6437_I2C_reset( );
                i2c_inuse = 0;
                return -1;
            }
        } while ( ( I2C_ICSTR & ICSTR_ICRRDY ) == 0 );// Wait for Rx Ready

        data[i] = I2C_ICDRR;            // Read
    }

    I2C_ICMDR |= ICMDR_STP;             // Generate STOP
	i2c_inuse = 0;
    return 0;
}

Int16 EVMDM6437_I2C_loopback( Uint16 i2c_addr, Uint8* data, Uint16 len )
{
    Int32  i;

	 char trans_val[8]={'l','o','o','p','b','a','c','k'};
     char rec_val[8];

    //I2C_ICCNT = len;                    // Set length
    //I2C_ICSAR = i2c_addr;               // Set I2C slave address

	I2C_ICMDR = ICMDR_STT               // Set for Master Read
          | ICMDR_MST
          | ICMDR_TRX
          | ICMDR_DLB
          | ICMDR_RM 
          | ICMDR_IRS;
  

    _wait( 10 );                        // Short delay

    for(i=0; i<(sizeof(trans_val)/sizeof(trans_val[0])); i++)
    {
      while ( ( I2C_ICSTR & ICSTR_ICXRDY ) == 0 );

	  I2C_ICDXR = trans_val[i]; 

      while ( ( I2C_ICSTR & ICSTR_ICRRDY ) == 0 );

	  rec_val[i] = I2C_ICDRR;

    }

	 for(i=0; i<(sizeof(trans_val)/sizeof(trans_val[0])); i++)
    {  
   if(trans_val[i]==rec_val[i])
   {
   
   }
     //printf("transmit: %c  receive: %c\n",trans_val[i],rec_val[i]);
   else
     {
       //printf(" error\n");
       //printf("\nI2C Loopback Test:  FAILED");
       return(1);
     } 
    }
      return 0;
}
