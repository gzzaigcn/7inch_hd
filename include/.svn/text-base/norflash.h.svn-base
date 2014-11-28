/******************************************************************************

   Copyright (C), 2013-,    Zjut Image Processing Lab.    All rights reserved. 

*******************************************************************************
 * File Name : norflash.h
 * Version : 1.0
 * Author : Gzz
 * Created : 2013/8/14
 * Last Modified :
 * Description : norflash.c header file
 * Function List :
 * Modification History :
   1.Date : 2013/8/14
     Author : Gzz
     Modification : Created file

   1.Date : 2013/10/30
     Author : Gzz
     Modification : modify struct system_param_type
******************************************************************************/
#include "dm6437.h"

#ifndef __NORFLASH_H__
#define __NORFLASH_H__

/*Macro for 16MB Norflash:page/sector/block/chip size*/
#define NORFLASH_PAGE_SIZE         256
#define NORFLASH_SECTOR_SIZE     4*1024 //4KB
#define NORFLASH_BLOCK_SHIFT     15
#define NORFLASH_BLOCK_SIZE       (1 << NORFLASH_BLOCK_SHIFT)  //32KB
#define NORFLASH_ALL_SIZE           (512*NORFLASH_BLOCK_SIZE) //16MB

#define NORFLASH_BLOCK_ADDR(blk_num)    (blk_num << NORFLASH_BLOCK_SHIFT)


/****Macro for 16MB Norflash SPI Read/Write COMMAND******/

//Read/Write Array Commands
#define NORFLASH_NORMAL_READ_CMD            0x03    // normal read  
#define NORFLASH_FATS_READ_CMD              0x0b    // fast read  

#define NORFLASH_PP_CMD                 0x02 // page program
#define NORFLASH_SE_CMD                 0x20   //4K Sector Erase
#define NORFLASH_BE_CMD              0x52   // 32KB Block Erase
#define NORFLASH_CE_CMD            0xC7 // 16MB Chip Erase 
#define NORFLASH_RMFG_ID_CMD        0x9F // Read manufacturer's ID.

//Register/Setting Commands
#define NORFLASH_WREN_CMD             0x06 // write enable
#define NORFLASH_WRSR_CMD             0x01 // write status register
#define NORFLASH_RDSR_CMD              0x05 //read status register
#define NORFLASH_DP_CMD                  0xb9 //deep power down
#define NORFLASH_RDP_CMD                0xab //release from deep power down
#define NORFLASH_RDID_CMD               0x9F //read identific-ation

typedef enum {

    NORFLASH_ERASE_SECTOR = 0,
    NORFLASH_ERASE_BLOCK,
    NORFLASH_ERASE_CHIP
     
}NORFLASH_ERASE_MOD;



#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

extern Uint8 norflash_detect();

extern void norflash_erase(Uint32 erase_addr, NORFLASH_ERASE_MOD erase_mod);

extern void norflash_erase_blocks(Uint32 start_blk, Uint32 blk_cnt);

extern void norflash_read_datas(Uint32 addr, Uint8 *data, Uint32 len);

extern void norflash_write_datas(Uint32 addr, Uint8 *data, Uint32 len);

extern void norflash_write_page(Uint32 blk_num, Uint32 page_num, Uint8 *data);


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __NORFLASH_H__ */
