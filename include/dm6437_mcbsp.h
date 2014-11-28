/******************************************************************************

   Copyright (C), 2014-,    Du-Health Electron Co.    All rights reserved. 

*******************************************************************************
 * File Name : dm6437_mcbsp.h
 * Version : 1.0
 * Author : gzz
 * Created : 2014/9/16
 * Last Modified :
 * Description : dm6437_mcbsp.h header file
 * Function List :
 * Modification History :
   1.Date : 2014/9/16
     Author : gzz
     Modification : Created file
 
******************************************************************************/

#ifndef __DM6437_MCBSP_H__
#define __DM6437_MCBSP_H__

#include "dm6437.h"
#include "dm6437_gpio.h"


#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */



/* -------------------------------------------------------------------------- *
 *    MCBSP register structure        - see spru943a                          *
 * -------------------------------------------------------------------------- */
typedef struct {
    volatile Uint32 DRR;
    volatile Uint32 DXR;
    volatile Uint32 SPCR;
    volatile Uint32 RCR;
    volatile Uint32 XCR;
    volatile Uint32 SRGR;
    volatile Uint32 MCR;
    volatile Uint32 RCERE0;
    volatile Uint32 XCERE0;
    volatile Uint32 PCR;
    volatile Uint32 RCERE1;
    volatile Uint32 XCERE1;
    volatile Uint32 RCERE2;
    volatile Uint32 XCERE2;
    volatile Uint32 RCERE3;
    volatile Uint32 XCERE3;     
} mcbsp_regs;


typedef enum mcbsp_mod{
    MCBSP_SPI24_8bit = 0,
    MCBSP_SPI24_32bit
}MCBSP_SPI_MOD;



typedef struct {
    mcbsp_regs *regs;
    MCBSP_SPI_MOD mod;
}mcbsp_obj;
typedef  mcbsp_obj * mcbsp_handle;



#define MCBSP_PCR_FSXM_MASK          (0x00000800u)
#define MCBSP_PCR_CLKXM_MASK         (0x00000200u)
#define MCBSP_PCR_FSXP_MASK          (0x00000008u)
#define MCBSP_PCR_FSRP_MASK          (0x00000004u)
#define MCBSP_PCR_CLKRP_MASK         (0x00000001u)
#define MCBSP_RCR_RDATDLY_SHIFT      (0x00000010u)
#define MCBSP_RCR_RWDLEN1_SHIFT      (0x00000005u)
#define MCBSP_RCR_RWDLEN2_SHIFT      (0x00000015u)
#define MCBSP_XCR_XDATDLY_SHIFT      (0x00000010u)
#define MCBSP_XCR_XWDLEN1_SHIFT      (0x00000005u)
#define MCBSP_XCR_XWDLEN2_SHIFT      (0x00000015u)
#define MCBSP_XCR_XPHASE_SHIFT       (0x0000001Fu)
#define MCBSP_SRGR_CLKSM_MASK        (0x20000000u)
#define MCBSP_SRGR_CLKSM_SHIFT       (0x0000001Du)
#define MCBSP_SRGR_FPER_SHIFT        (0x00000010u)
#define MCBSP_SRGR_FWID_SHIFT        (0x00000008u)
#define MCBSP_SRGR_CLKGDV_SHIFT      (0x00000000u)
#define MCBSP_SPCR_CLKSTP_MASK       (0x00001800u)
#define MCBSP_SPCR_CLKSTP_SHIFT      (0x0000000Bu)
#define MCBSP_SPCR_FREE_MASK         (0x02000000u)
#define MCBSP_SPCR_GRST_MASK         (0x00400000u)
#define MCBSP_SPCR_FRST_MASK         (0x00800000u)
#define MCBSP_SPCR_RRST_MASK         (0x00000001u)
#define MCBSP_SPCR_XRST_MASK         (0x00010000u)
#define MCBSP_SPCR_XRDY_MASK         (0x00020000u)
#define MCBSP_SPCR_XRDY_SHIFT        (0x00000011u)
#define MCBSP_SPCR_RRDY_MASK         (0x00000002u)
#define MCBSP_SPCR_RRDY_SHIFT        (0x00000001u) 
#define MCBSP_RCR_RWDLEN1_MASK       (0x000000E0u)
#define MCBSP_RCR_RWDLEN1_SHIFT      (0x00000005u)
#define MCBSP_XCR_XWDLEN2_MASK       (0x00E00000u)
#define MCBSP_XCR_XWDLEN2_SHIFT      (0x00000015u)
#define MCBSP_XCR_XFRLEN1_MASK       (0x00007F00u)
#define MCBSP_XCR_XFRLEN1_SHIFT      (0x00000008u)
#define MCBSP_RCR_RFRLEN1_MASK       (0x00007F00u)
#define MCBSP_RCR_RFRLEN1_SHIFT      (0x00000008u)


/*GPIO High/Level for MCBSP SPI CS*/
#define SPI_CS_HIGH()  do{ EVMDM6437_GPIO_setOutput(GPIO97,1); \
                                                         _waitusec(1); }while(0)
                                                                
#define SPI_CS_LOW()  do{ EVMDM6437_GPIO_setOutput(GPIO97,0); \
                                                        _waitusec(1); }while(0)


extern void dm6437_mcbsp_init();

extern Uint8 mcbsp_spi_read_byte();

extern void mcbsp_spi_write_byte(Uint8 data);


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __DM6437_MCBSP_H__ */
