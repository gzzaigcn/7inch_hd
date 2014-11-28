/******************************************************************************

   Copyright (C), 2014-,    Du-Health Electron Co.    All rights reserved. 

*******************************************************************************
 * File Name : norflash.c
 * Version : 1.0
 * Author : gzz
 * Created : 2014/9/23
 * Last Modified :
  Description   : Norflash Modules Drivers
 * Function List :
              norflash_enable_write
              norflash_erase
              norflash_erase_blocks
              norflash_read_datas
              norflash_read_sr
              norflash_wait_idle
              norflash_write_datas
              norflash_write_page
 * Modification History :
   1.Date : 2014/9/23
     Author : gzz
     Modification : Created file
 
******************************************************************************/
#include "norflash.h"
#include "dm6437_mcbsp.h"


#define MODULE_NAME "norflash"

Uint8 norflash_detect()
{
    Uint8 RDID[3];

    SPI_CS_LOW();
    mcbsp_spi_write_byte(NORFLASH_RMFG_ID_CMD);   
    RDID[0] = mcbsp_spi_read_byte();
    RDID[1] = mcbsp_spi_read_byte();
    RDID[2] = mcbsp_spi_read_byte();
    SPI_CS_HIGH();

    if ((RDID[0] == 0xC2) && (RDID[1] == 0x20) && (RDID[2] == 0x18))
        return 1;
    else 
        return 0;
}


static Uint8 norflash_read_sr()
{
    Uint8 status_reg;

    SPI_CS_LOW();
    mcbsp_spi_write_byte(NORFLASH_RDSR_CMD);   
    status_reg = mcbsp_spi_read_byte();
    SPI_CS_HIGH();

    return status_reg;    
}

static void norflash_enable_write()
{
    
    SPI_CS_LOW();
    mcbsp_spi_write_byte(NORFLASH_WREN_CMD);
    SPI_CS_HIGH();

    while(!(norflash_read_sr() & 0x02));//Ensure WEL = 1;
    
}

static void norflash_wait_idle()
{
    while((norflash_read_sr() & 0x01));//Ensure WIP = 0,no busy.
}


void norflash_erase(Uint32 erase_addr, NORFLASH_ERASE_MOD erase_mod)
{ 
    
	switch ( erase_mod ){
    	case NORFLASH_ERASE_SECTOR: { //erase 4KB sector
            norflash_enable_write();

            SPI_CS_LOW();
            mcbsp_spi_write_byte(NORFLASH_SE_CMD);
            mcbsp_spi_write_byte((erase_addr >> 16) & 0xff);
            mcbsp_spi_write_byte((erase_addr >> 8) & 0xff);
            mcbsp_spi_write_byte(erase_addr & 0xff);           
            SPI_CS_HIGH();
            
            norflash_wait_idle();//wait flash idle
            break;
    	}
            
        case NORFLASH_ERASE_BLOCK: {  //erase 32KB BLOCK
            norflash_enable_write();
            
            SPI_CS_LOW();
            mcbsp_spi_write_byte(NORFLASH_BE_CMD);
            mcbsp_spi_write_byte((erase_addr>>16)&0xff);
            mcbsp_spi_write_byte((erase_addr>>8)&0xff);
            mcbsp_spi_write_byte(erase_addr&0xff);
            SPI_CS_HIGH();
            
            norflash_wait_idle();//wait flash idle
            break;
        }

        case NORFLASH_ERASE_CHIP: {//erase all
            norflash_enable_write();
            
            SPI_CS_LOW();
            mcbsp_spi_write_byte(NORFLASH_CE_CMD);
            SPI_CS_HIGH();
            
            norflash_wait_idle();//wait flash idle
            break;
        }
            
        default:
            break;
    }
    
}


void norflash_erase_blocks(Uint32 start_blk, Uint32 blk_cnt)
{
    Uint32 block_addr = 0;
    Uint32 blk_num;

    for(blk_num = start_blk; blk_num < start_blk+blk_cnt; blk_num++)
    {
        block_addr = blk_num << NORFLASH_BLOCK_SHIFT; //convert to block base address
        norflash_erase(block_addr, NORFLASH_ERASE_BLOCK);
    }

}

void norflash_write_page(Uint32 blk_num, Uint32 page_num, Uint8 *data)
{
    Uint32 i;
    Uint32 addr;

    addr = (blk_num << NORFLASH_BLOCK_SHIFT) + page_num*NORFLASH_PAGE_SIZE; 

    norflash_enable_write();
    
    SPI_CS_LOW();
    mcbsp_spi_write_byte(NORFLASH_PP_CMD);
    mcbsp_spi_write_byte((addr >> 16) & 0xff);
    mcbsp_spi_write_byte((addr >> 8) & 0xff);
    mcbsp_spi_write_byte(addr & 0xff);
    
    for( i = 0; i < NORFLASH_PAGE_SIZE; i++) //write 256Bytes for one pagers
    {
        mcbsp_spi_write_byte(*data);
        data++;
    }
    SPI_CS_HIGH();
    
    norflash_wait_idle();//wait flash idle
}



void norflash_write_datas(Uint32 addr, Uint8 *data, Uint32 len)
{
	Uint32 i;
    norflash_enable_write();
    
    SPI_CS_LOW();
    mcbsp_spi_write_byte(NORFLASH_PP_CMD);
    mcbsp_spi_write_byte((addr >> 16) & 0xff);
    mcbsp_spi_write_byte((addr >> 8) & 0xff);
    mcbsp_spi_write_byte(addr & 0xff);
    
    for( i = 0; i < len; i++) 
    {
        mcbsp_spi_write_byte(*data);
        data++;
    }
    SPI_CS_HIGH();
    
    norflash_wait_idle();//wait flash idle
}


void norflash_read_datas(Uint32 addr, Uint8 *data, Uint32 len)
{
    Uint32 i;
    
    SPI_CS_LOW();
    mcbsp_spi_write_byte(NORFLASH_NORMAL_READ_CMD);
    mcbsp_spi_write_byte((addr >> 16) & 0xff);
    mcbsp_spi_write_byte((addr >> 8) & 0xff);
    mcbsp_spi_write_byte(addr & 0xff);
    
    for ( i = 0; i < len ; i++ ) {
        data[i] = mcbsp_spi_read_byte();  //continuous read 
    }
    
    SPI_CS_HIGH();

}




