/******************************************************************************

   Copyright (C), 2014-,    Du-Health Electron Co.    All rights reserved. 

*******************************************************************************
 * File Name : norflash_fs.h
 * Version : 1.0
 * Author : gzz
 * Created : 2014/9/18
 * Last Modified :
 * Description : norflash_fs.c header file
 * Function List :
 * Modification History :
   1.Date : 2014/9/18
     Author : gzz
     Modification : Created file
 
******************************************************************************/

#ifndef __NORFLASH_FS_H__
#define __NORFLASH_FS_H__

/*Macro for Block Partition*/
#define NORFLASH_TOTAL_BLOCK_NUM       512

/*(BLOCKS)SBL+APP: 0, 1-60*/
#define DM6437_SBL_BLOCK_BASE                 0
#define DM6437_SBL_BLOCK_NUM                  1
#define DM6437_APP_BLOCK_BASE                1
#define DM6437_APP_BLOCK_NUM                 59

/*(BLOCKS) OSD Bin, 61-60*/
#define DM6437_OSD_BLOCK_BASE                  60
#define DM6437_OSD_BLOCK_NUM                   99

/*BLOCKS (BLK_INFO+CFG+FATS+IMA):159, 160-167, 168-175, 176-511(42*8)*/
#define SAV_BLK_INFO_BASE       159
#define CFG_SAV_BLOCK_BASE    160    
#define CFG_SAV_BLOCK_NUM      8    
#define FAT_SAV_BLOCK_BASE      (CFG_SAV_BLOCK_BASE +  CFG_SAV_BLOCK_NUM)
#define FAT_SAV_BLOCK_NUM        8
#define IMG_SAV_BLOCK_BASE        (FAT_SAV_BLOCK_BASE + FAT_SAV_BLOCK_NUM)

#define CFG_SAV_SIZE_NUM_OF_PAGE	1
#define FAT_SAV_SZIE_NUM_OF_PAGE 16
#define IMG_SAV_SIZE_NUM_OF_BLOCK  8 //define BLOCK NUM for a saved image size
#define IMG_SAV_SIZE_NUM_OF_PAGE   1024


typedef struct norflash_blk_info{

    Uint32 file_name;
    Uint32  file_type;
    Int8   sign[8];

}norflash_blk_info_t;


typedef struct nor_flash_file_list{
    
    struct nor_flash_file_list *prev;
    struct nor_flash_file_list *next;
    Uint32 file_name;
    Uint32 file_type;	
    Uint32 block_num;
    Int32 buf_num;

}norflash_file_list_t;

typedef struct img_file_info {

    Uint32 img_file_name;
    Uint32 img_file_type;

}img_file_info_t;


typedef struct norflash_fs_info{

    Uint8 block_state[NORFLASH_TOTAL_BLOCK_NUM];
    Uint8 fs_first_inited;
    Uint32 cfg_prev_block_num;
    Uint32 cfg_cur_block_num;
    Uint32 cfg_file_name;
    
    Uint32 fat_prev_block_num;
    Uint32 fat_cur_block_num;
    Uint32 fat_file_name;
    Uint32 newest_img_block_num;
    Uint32 img_file_num;
    Uint32 free_file_num;
    Uint32 fat_info_inited;	
    img_file_info_t img_file_info[NORFLASH_TOTAL_BLOCK_NUM];
	
}norflash_fs_info_t;

typedef enum BLOCK_STATE{

    NORFLASH_BLOCK_STATE_IDLE = 0,
    NORFLASH_BLOCK_STATE_USED = 1,
    NORFLASH_BLOCK_STATE_IMAGE = 2,
    NORFLASH_BLOCK_STATE_FMTTED = 0xfe,
    NORFLASH_BLOCK_STATE_ERROR = 0xff,

}NORFLASH_BLOCK_STATE;

/*System Configure Params*/
typedef struct {

    Uint32 reserved;

}cfg_params_t;

typedef struct {

    cfg_params_t cfg_params;
    Int8 sign[8];
    
}system_params_t;
typedef system_params_t* handle_sys_params;


/**/
#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

extern void save_image(Uint8 *img_buf, Uint32 file_type);
extern void delete_image(Uint32 num);
extern void load_image(Uint32 num);


extern void norflash_fs_cfg_init();
extern void norflash_fs_fat_init();

extern void save_system_params();
extern void load_system_params();

extern void save_fat_info();



#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __NORFLASH_FS_H__ */
