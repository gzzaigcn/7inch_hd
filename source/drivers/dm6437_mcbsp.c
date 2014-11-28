/******************************************************************************

   Copyright (C), 2014-,    Du-Health Electron Co.    All rights reserved. 

*******************************************************************************
 * File Name : dm6437_mcbsp.c
 * Version : 1.0
 * Author : gzz
 * Created : 2014/9/23
 * Last Modified :
  Description   : Dm6437 mcbsp drivers
 * Function List :
              dm6437_mcbsp0_config
              dm6437_mcbsp_init
              mcbsp_spi_read_byte
              mcbsp_spi_write_byte
 * Modification History :
   1.Date : 2014/9/23
     Author : gzz
     Modification : Created file
 
******************************************************************************/
#include "stdio.h"
#include "dm6437_mcbsp.h"
#include "dm6437_gpio.h"


#define MCBSP_0 0
#define MCBSP_1 1


/*The mcbsp  object handle*/
mcbsp_obj mcbsp0_obj;
mcbsp_handle mcbsp0_handle = NULL;


static void dm6437_mcbsp0_config(mcbsp_handle h_mcbsp)
{

    Uint32 spcr, mcr, xcr, rcr, srgr, pcr;

   /* Set SPCR to defaults, Hold Sample-Rate Generator,Transmit/Receive  in reset  */
    h_mcbsp->regs->SPCR = 0;
    h_mcbsp->regs->MCR  = 0;

    spcr = 0x00000000u;
    mcr  = 0x00000000u;
    xcr  = 0x00000000u;
    rcr  = 0x00000000u;
    srgr = 0x00000000u;
    pcr  = 0x00000000u;

    //----------------------------------------------------------------------
    // Set McBSP in SPI Master mode, normally FSX0 would be used
    // as chip-select but to support SPI devices with 24BIT address
    // widht - FSX0 although generated, will be ignored. The SPI, CS, will
    // be connected to TOUT0L, configured as GPIO pin.
    //----------------------------------------------------------------------   
    pcr = pcr | (  MCBSP_PCR_FSXM_MASK | 		// 0x00000A0C
                        MCBSP_PCR_CLKXM_MASK |
	                 MCBSP_PCR_FSXP_MASK |
	                 MCBSP_PCR_FSRP_MASK );


    //------------------------------------------------------------------------
    // For SPI mode a XMIT and RCV delya of 1 is required. The XMIT and RCV
    // frames have been set to send/receive 8 bits.
    //------------------------------------------------------------------------
    rcr = rcr  | (1u << MCBSP_RCR_RDATDLY_SHIFT)		// 0x00010000
	              | (0u << MCBSP_RCR_RWDLEN1_SHIFT) 
                  |(0x0u << MCBSP_RCR_RFRLEN1_SHIFT)	                                              
	              | (0u << MCBSP_RCR_RWDLEN2_SHIFT);

    // SPI 8bit each element
    if(h_mcbsp->mod == MCBSP_SPI24_8bit){
        xcr = xcr  | (1u << MCBSP_XCR_XDATDLY_SHIFT)        // 0x00010000
	               | (0u << MCBSP_XCR_XWDLEN1_SHIFT) 
                      | (0x0u << MCBSP_XCR_XFRLEN1_SHIFT)	                                              
	               | (0u << MCBSP_XCR_XWDLEN2_SHIFT);	
        }

    // SPI 32bit each element
    else if(h_mcbsp->mod == MCBSP_SPI24_32bit){
        xcr = xcr  | (1u << MCBSP_XCR_XDATDLY_SHIFT)        
	               | (5u << MCBSP_XCR_XWDLEN1_SHIFT) 
                      | (0x0u << MCBSP_XCR_XFRLEN1_SHIFT)	                                              
	               | (0u << MCBSP_XCR_XWDLEN2_SHIFT);	        
        }
        

    srgr = srgr | MCBSP_SRGR_CLKSM_MASK				// 0x20400102
	               | (0x40u << MCBSP_SRGR_FPER_SHIFT)  
	               | (0x1u << MCBSP_SRGR_FWID_SHIFT)
//		           | (0x0u << MCBSP_SRGR_FWID_SHIFT) //by gzz
                    | (0x2u  << MCBSP_SRGR_CLKGDV_SHIFT);//SPI CLK=33MHz


    /* Set polarity and phase of CLK using CLKSTP and CLKXP */
    spcr = (spcr &( ~MCBSP_SPCR_CLKSTP_MASK));         // 0x0
                       
    h_mcbsp->regs->MCR = mcr;
    h_mcbsp->regs->PCR = pcr;
    h_mcbsp->regs->XCR = xcr;
    h_mcbsp->regs->RCR = rcr;
    h_mcbsp->regs->SRGR = srgr;
    h_mcbsp->regs->SPCR = spcr;

    //Wait two CLKSRG clocks. This is to ensure proper synchronization internally.
    asm("\tnop 5");

    h_mcbsp->regs->SPCR = ( h_mcbsp->regs->SPCR & (~MCBSP_SPCR_CLKSTP_MASK))
	                |(0x3u << MCBSP_SPCR_CLKSTP_SHIFT);//ÉÏÉýÑØ
                 
    /* Initialization of transmit values and array of received values */

    /* SPI-EEPROM data packet represented in 32 bit format
    * first byte is write enable opcode
     * second, third bytes represnt 16 bit address,
     * fourth byte is the actual data to be written 
     */
     /* Start Sample Rate Generator Clock Generation */
    h_mcbsp->regs->SPCR |= MCBSP_SPCR_FREE_MASK;
    _waitusec(1);

    h_mcbsp->regs->SPCR |= MCBSP_SPCR_GRST_MASK;// grstControl (enable);
    _waitusec(1);

    /* Start Sample Rate Generator Frame Generation */
    h_mcbsp->regs->SPCR |= MCBSP_SPCR_FRST_MASK; //MCBSP_frstControl (enable);
    _waitusec(1);

    /* Enable Receiver */
    h_mcbsp->regs->SPCR |= MCBSP_SPCR_RRST_MASK; //rrstControl  (enable);
    _waitusec(1);

    /* Enable Transmitter */
    h_mcbsp->regs->SPCR |= MCBSP_SPCR_XRST_MASK; //xrstControl (enable);	= 0x02C31801
    _waitusec(1);

    //Wait two CLKSRG clocks. This is to ensure proper synchronization internally.
    asm("\tnop 5");   

}



/*****************************************************************************
 * Prototype : dm6437_mcbsp_init
 * Description : 
 * Input : None
 * Output : None
 * Return Value : 
 * Calls : 
 * Called By  : 
 
 * Modification History :
 * 1.Date : 2013/7/29
 *   Author : Gzz
 *   Modification : Created function
 
*****************************************************************************/
void dm6437_mcbsp_init()
{
    mcbsp_handle h_mcbsp;

    h_mcbsp = &mcbsp0_obj;
    h_mcbsp->regs = (mcbsp_regs *)MCBSP0_BASE;
    h_mcbsp->mod = MCBSP_SPI24_8bit;//SPI 8Bytes Mod

    dm6437_mcbsp0_config(h_mcbsp);
    mcbsp0_handle = h_mcbsp; // by gzz
    EVMDM6437_GPIO_setDir( GPIO97, GPIO_OUT );//set GPIO97 OUTPUT
    EVMDM6437_GPIO_setOutput(GPIO97,1);  //SPI CS High State
    
}


/*****************************************************************************
 * Prototype : mcbsp0_spi_write_byte
 * description  : read one byte by MCBSP SPI
 * Input :   Uint8 data  
 * Output : None
 * Return Value : void
 * Calls : 
 * Called By  : 
 
 * Modification History :
 * 1.Date : 2013/7/30
 *   Author : Gzz
 *   Modification : Created function
 
*****************************************************************************/
void mcbsp_spi_write_byte(Uint8 data)
{
    volatile Uint8  tmp;
    
    while(!((mcbsp0_handle->regs->SPCR) & MCBSP_SPCR_XRDY_MASK));
        mcbsp0_handle->regs->DXR = data;

    while(!((mcbsp0_handle->regs->SPCR) & MCBSP_SPCR_RRDY_MASK));
        tmp = mcbsp0_handle->regs->DRR;
            
}


/*****************************************************************************
 * Prototype : mcbsp0_spi_read_byte
 * description  : read one byte by MCBSP SPI
 * Input : None
 * Output : None
 * Return Value : void
 * Calls : 
 * Called By  : 
 
 * Modification History :
 * 1.Date : 2013/7/30
 *   Author : Gzz
 *   Modification : Created function
 
*****************************************************************************/
Uint8 mcbsp_spi_read_byte()
{
    Uint8 tmp;
        
    while(!((mcbsp0_handle->regs->SPCR) & MCBSP_SPCR_XRDY_MASK));
        mcbsp0_handle->regs->DXR = 0x00;

    while(!((mcbsp0_handle->regs->SPCR) & MCBSP_SPCR_RRDY_MASK));
        tmp = mcbsp0_handle->regs->DRR;
        
    return tmp;
}

