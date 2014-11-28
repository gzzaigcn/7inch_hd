/******************************************************************************

   Copyright (C), 2014-,    Du-Health Electron Co.    All rights reserved. 

*******************************************************************************
 * File Name : norflash_fs.c
 * Version : 1.0
 * Author : gzz
 * Created : 2014/9/23
 * Last Modified :
  Description   : a small file system for image save/delete/preview manager and cfg
 * Function List :
              delete_image
              erase_block_info
              file_list_init
              get_block_info
              get_next_blocks_to_save_img
              get_next_block_to_save_cfg
              get_next_block_to_save_fat_info
              load_fat_info
              load_image
              load_system_params
              norflash_fs_cfg_init
              norflash_fs_fat_init
              norflash_fs_format
              norflash_fs_load_cfg_params
              norflash_fs_load_fat_info
              norflash_fs_save_cfg_params
              norflash_fs_save_fat_info
              save_image
              save_system_params
              set_defalut_cfg_params
              set_file_lock
              update_block_info
              used_file_list_add_node
 * Modification History :
   1.Date : 2014/9/23
     Author : gzz
     Modification : Created file
 
******************************************************************************/
#include "stdio.h"
#include "string.h"
#include "norflash.h"
#include "norflash_fs.h"


#define NORFLASH_BLOCK_SIGN      "be used"
#define SYSTEM_PARAMS_SIGN        "init ok"

/*static global variable for noflash file system*/
static norflash_fs_info_t  norflash_fs_info;

static norflash_blk_info_t  norflash_blk_info[NORFLASH_TOTAL_BLOCK_NUM];
static norflash_file_list_t   norflash_blk_file_list[NORFLASH_TOTAL_BLOCK_NUM];
static norflash_file_list_t   *file_lock_array[NORFLASH_TOTAL_BLOCK_NUM];

norflash_file_list_t  free_file;
norflash_file_list_t  used_file;

/*Global 7inch_hd system params*/
system_params_t sys_params;
system_params_t *h_sys_params = &sys_params;



static void erase_block_info(Uint32 blk_num)
{
    Uint32 addr ;
    
    norflash_blk_info_t *info = norflash_blk_info+blk_num;

    //reset block info
    memset((void *)info, 0xff, sizeof(norflash_blk_info_t));

    addr= NORFLASH_BLOCK_ADDR(SAV_BLK_INFO_BASE) + blk_num*sizeof(norflash_blk_info_t);
    norflash_write_datas(addr, (Uint8 *)info, sizeof(norflash_blk_info_t));    
}

static norflash_blk_info_t* get_block_info(Uint8 blk_num)
{
    Uint32 addr;
    norflash_blk_info_t *info = norflash_blk_info+blk_num;

    addr= NORFLASH_BLOCK_ADDR(SAV_BLK_INFO_BASE) + blk_num*sizeof(norflash_blk_info_t);
    norflash_read_datas(addr, (Uint8 *)info, sizeof(norflash_blk_info_t));

    return info;

}

static void update_block_info(Uint32 blk_num, norflash_blk_info_t *info)
{

    Uint32 addr ;

    addr= NORFLASH_BLOCK_ADDR(SAV_BLK_INFO_BASE) + blk_num*sizeof(norflash_blk_info_t);
    norflash_write_datas(addr, (Uint8 *)info, sizeof(norflash_blk_info_t));

}



/*************************************************************************
***************************************************************************/
/**********Function() for System configure paramters in norflash file system***********/ 

void norflash_fs_cfg_init()
{
    
    Uint32 i;
    norflash_blk_info_t *p_blk_info = NULL;
    
    memset(&norflash_fs_info, 0x00, sizeof(norflash_fs_info_t));
    memset(&norflash_blk_file_list, 0x00, sizeof(norflash_blk_file_list));

    for(i = 0; i < CFG_SAV_BLOCK_NUM; i++)
    {
        p_blk_info = get_block_info(i+CFG_SAV_BLOCK_BASE);

        if(!strcmp(p_blk_info->sign, NORFLASH_BLOCK_SIGN))
        {
            
            if(p_blk_info->file_name == 0)
            {
                norflash_fs_info.block_state[i+ CFG_SAV_BLOCK_BASE] = NORFLASH_BLOCK_STATE_FMTTED;//the block is formated
                continue;
            }
            if(p_blk_info->file_name > norflash_fs_info.cfg_file_name)
            {
                /*if cfg has been existed and saved after system power on, then set init flag = 1 */
                norflash_fs_info.fs_first_inited |= 1;
                
                norflash_fs_info.block_state[i+ CFG_SAV_BLOCK_BASE] = NORFLASH_BLOCK_STATE_USED;
                norflash_fs_info.cfg_prev_block_num =  norflash_fs_info.cfg_cur_block_num;
                norflash_fs_info.cfg_cur_block_num = i+ CFG_SAV_BLOCK_BASE;
                norflash_fs_info.cfg_file_name = p_blk_info->file_name;
            }
            else
            {
                norflash_fs_info.block_state[i+ CFG_SAV_BLOCK_BASE] = NORFLASH_BLOCK_STATE_USED;
                norflash_fs_info.cfg_prev_block_num = i+ CFG_SAV_BLOCK_BASE;
            }
        }
        
    }
    
}

inline static Uint32 get_next_block_to_save_cfg()
{
    
    if((norflash_fs_info.cfg_cur_block_num == 0) ||
                        norflash_fs_info.cfg_cur_block_num == (CFG_SAV_BLOCK_BASE+CFG_SAV_BLOCK_NUM-1))
    {
        return CFG_SAV_BLOCK_BASE;
        
    }
    else
    {
        return (norflash_fs_info.cfg_cur_block_num+1);
    }    
    
}

static void norflash_fs_save_cfg_params(Uint8 *params, Uint32 len)
{

    Uint32 blk_num;
    norflash_blk_info_t *p_blk_info = NULL;

    /*erase previous cfg params block*/
    if(norflash_fs_info.cfg_prev_block_num > 0)
    {
        erase_block_info(norflash_fs_info.cfg_prev_block_num);
        norflash_fs_info.block_state[norflash_fs_info.cfg_prev_block_num] = NORFLASH_BLOCK_STATE_IDLE;
    }
    
    blk_num = get_next_block_to_save_cfg();//find a new block to save cfg
    p_blk_info = norflash_blk_info + blk_num;

    /*init current cfg block info*/
    p_blk_info->file_name = ++norflash_fs_info.cfg_file_name;
    p_blk_info->file_type = 0x00;
    strcpy(p_blk_info->sign, NORFLASH_BLOCK_SIGN);
    
    /*update block info to norflash*/    
   update_block_info(blk_num, p_blk_info);
    
    norflash_fs_info.cfg_prev_block_num = norflash_fs_info.cfg_cur_block_num;
    norflash_fs_info.cfg_cur_block_num = blk_num;
    norflash_fs_info.cfg_file_name = p_blk_info->file_name;
    norflash_fs_info.block_state[blk_num] = NORFLASH_BLOCK_STATE_USED;

    /*write cfg params to norflash with one page unit*/
    Uint32 addr = NORFLASH_BLOCK_ADDR(blk_num);
    norflash_write_datas(addr, params, len);
    
}



static Int32 norflash_fs_load_cfg_params(Uint8 *params, Uint32 len, Uint32 is_current)
{
    Uint32 blk_num;

    if(is_current)
    {
        blk_num = norflash_fs_info.cfg_cur_block_num;
    }
    else
    {
        blk_num = norflash_fs_info.cfg_prev_block_num;
    }
    
    if(blk_num == 0)//valid block
        return -1;

    Uint32 addr = NORFLASH_BLOCK_ADDR(blk_num);
    norflash_read_datas(addr, params, len);

    return 0;
    
}



static void set_defalut_cfg_params(cfg_params_t *cfg)
{
    cfg->reserved = 0;
}


void save_system_params()
{

    /*set the cfg params block sign haved been inited*/
    strcpy(h_sys_params->sign, SYSTEM_PARAMS_SIGN);
    norflash_fs_save_cfg_params((Uint8 *)h_sys_params, sizeof(system_params_t));

}


void load_system_params()
{
    Int32 ret;

    /*first get cfg params from current block number */
    ret = norflash_fs_load_cfg_params((Uint8 *)h_sys_params, sizeof(system_params_t), 1);
    if(ret == 0)
    {
        if(!strcmp(h_sys_params->sign, SYSTEM_PARAMS_SIGN) ) 
        {
            return;// find a vaild system params
        }
    }

    /*then get cfg params from previous block number */
    ret = norflash_fs_load_cfg_params((Uint8 *)h_sys_params, sizeof(system_params_t), 0);
    if(ret == 0)
    {
        if(!strcmp(h_sys_params->sign, SYSTEM_PARAMS_SIGN) ) 
        {
            return;// find vaild system params
        }
    }

    /*if it's the first power on, then set default params and save it*/
    set_defalut_cfg_params(&h_sys_params->cfg_params);
    save_system_params();
    
}


/***************************************************************************
***************************************************************************/
/**********Function() for image file manager system base fat***********/ 

inline static Uint32 get_next_block_to_save_fat_info()
{
    
    if((norflash_fs_info.fat_cur_block_num == 0) ||
                        norflash_fs_info.fat_cur_block_num == (FAT_SAV_BLOCK_BASE+FAT_SAV_BLOCK_NUM-1))
    {
        return FAT_SAV_BLOCK_BASE;
        
    }
    else
    {
        return (norflash_fs_info.fat_cur_block_num+1);
    }    
    
}


static Int32 norflash_fs_load_fat_info(Uint8 *fat_info, Uint32 len, Uint32 is_current)
{
    Uint32 blk_num;

    if(is_current)
    {
        blk_num = norflash_fs_info.fat_cur_block_num;
    }
    else
    {
        blk_num = norflash_fs_info.fat_prev_block_num;
    }

    if(blk_num == 0)//no block
        return -1;
    
    Uint32 addr = NORFLASH_BLOCK_ADDR(blk_num);
    norflash_read_datas(addr, fat_info, len);

    return 0;
}



static void load_fat_info()
{
    img_file_info_t *p_img_flie_info;
    

    p_img_flie_info = norflash_fs_info.img_file_info; //image fs information

    /*load current the newest fat information*/
    Int32 ret = norflash_fs_load_fat_info((Uint8 *)p_img_flie_info, sizeof(img_file_info_t)*NORFLASH_TOTAL_BLOCK_NUM, 1);
    if(ret == 0 && p_img_flie_info[NORFLASH_TOTAL_BLOCK_NUM-1].img_file_name == 999999999)
    {
        /*the user have saved the system file fat info before trun off*/
        norflash_fs_info.fat_info_inited = 1;
        return ;
    }
    
    /*load previous old fat information*/
    ret = norflash_fs_load_fat_info((Uint8 *)p_img_flie_info, sizeof(img_file_info_t)*NORFLASH_TOTAL_BLOCK_NUM, 0);
    if(ret == 0 && p_img_flie_info[NORFLASH_TOTAL_BLOCK_NUM-1].img_file_name == 999999999)
    {
        /*the user have saved the system file fat info before trun off*/
        norflash_fs_info.fat_info_inited = 1;
        return ;
    }
    
}

static void used_file_list_add_node(norflash_file_list_t *used_node, norflash_file_list_t *new_node)
{

    /*used file list node according to the biggest file_name to lowest 1*/
    if(new_node->file_name > used_node->file_name)
    {
        while( used_node->prev !=NULL && new_node->file_name > used_node->prev->file_name)
        {
            used_node = used_node->prev;//move node to higher node
        }
        used_node->prev->next = new_node;
        new_node->next = used_node;
        used_node->prev = new_node;
        new_node->prev = used_node->prev;
    }
    else
    {
        while(used_node->next !=NULL && new_node->file_name < used_node->next->file_name)
        {
            used_node = used_node->next;//move node to lower node
        }
        if(used_node->next == NULL)
        {
            used_node->next = new_node;
            new_node->prev = used_node;
            new_node->next = NULL;
        }
        else
        {
            used_node->next->prev = new_node;
            new_node->next = used_node->next;
            used_node->next = new_node;
            new_node->prev = used_node;
        }
    }
    
}


static void file_list_init()
{
    Uint32 i;

    norflash_file_list_t *p_free_file = &free_file;
    norflash_file_list_t *p_used_file = &used_file;

    p_free_file->next = NULL;
    p_free_file->prev = NULL;
    p_used_file->file_name = 0xffffffff;
    p_used_file->prev = NULL;
    p_used_file->next = NULL;

    if(norflash_fs_info.newest_img_block_num == 0) //none image file in norfalsh file system, all blocks free;
    {
        
        for(i = IMG_SAV_BLOCK_BASE; i + IMG_SAV_SIZE_NUM_OF_BLOCK < NORFLASH_TOTAL_BLOCK_NUM; i += IMG_SAV_SIZE_NUM_OF_BLOCK)
        {
            p_free_file->next = &norflash_blk_file_list[i];
            norflash_blk_file_list[i].next = NULL;
            norflash_blk_file_list[i].prev = p_free_file;
            norflash_blk_file_list[i].file_name = 0;
            norflash_blk_file_list[i].block_num = i;
            p_free_file = &norflash_blk_file_list[i];
            norflash_fs_info.free_file_num++; 
        }
    }
    else //haved existed image file in norflash
    {
        for(i = IMG_SAV_BLOCK_BASE; i + IMG_SAV_SIZE_NUM_OF_BLOCK < NORFLASH_TOTAL_BLOCK_NUM; i += IMG_SAV_SIZE_NUM_OF_BLOCK)
        {

            if(norflash_fs_info.block_state[i] != NORFLASH_BLOCK_STATE_IMAGE)  //the block file is free
            {
                p_free_file->next = &norflash_blk_file_list[i];
                norflash_blk_file_list[i].next = NULL;
                norflash_blk_file_list[i].prev = p_free_file;
                norflash_blk_file_list[i].file_name = 0;
                norflash_blk_file_list[i].block_num = i;
                p_free_file = &norflash_blk_file_list[i]; //move to new node
                norflash_fs_info.free_file_num++; 
            }
            else //block file is used,add to use_fle list
            {
                if(norflash_fs_info.fat_info_inited 
                    && norflash_fs_info.img_file_info[i -IMG_SAV_BLOCK_BASE].img_file_name == norflash_blk_file_list[i].file_name)
                {
                    norflash_blk_file_list[i].file_type =  norflash_fs_info.img_file_info[i -IMG_SAV_BLOCK_BASE].img_file_type;
                }

                else
                {
                    norflash_fs_info.img_file_info[i -IMG_SAV_BLOCK_BASE].img_file_name = norflash_blk_file_list[i].file_name;
                    norflash_fs_info.img_file_info[i -IMG_SAV_BLOCK_BASE].img_file_type = norflash_blk_file_list[i].file_type;
                }
               norflash_blk_file_list[i].buf_num = -1;

               used_file_list_add_node(p_used_file, &norflash_blk_file_list[i]);
               p_used_file = &norflash_blk_file_list[i];
            }
        }
        
    }
    
}

static void norflash_fs_format()
{
    
    Uint32 blk_num;
    norflash_blk_info_t *p_blk_info = NULL;

    memset((Uint8 *)&norflash_fs_info, 0, sizeof(norflash_fs_info_t));

    /*erase total file system blocks*/
    for(blk_num = CFG_SAV_BLOCK_BASE; blk_num < CFG_SAV_BLOCK_BASE+CFG_SAV_BLOCK_NUM; blk_num++)
    {
        erase_block_info(blk_num);
        norflash_erase_blocks(blk_num, 1);
    }

    /*init cfg blocks  info after format, block state to 0xfe*/
    for(blk_num = CFG_SAV_BLOCK_BASE; blk_num < CFG_SAV_BLOCK_BASE+CFG_SAV_BLOCK_NUM; blk_num++)
    {
        norflash_fs_info.block_state[blk_num] = NORFLASH_BLOCK_STATE_FMTTED;
        p_blk_info = &norflash_blk_info[blk_num];
        p_blk_info->file_name = 0;
        strcpy(p_blk_info->sign, NORFLASH_BLOCK_SIGN);
        update_block_info(blk_num, p_blk_info);
    }      
    
}


//通过序号来依次从小到大锁存图片的节怠
//序号越小表面最新的节点(即文件名是最大的)
static void set_file_lock()
{
    Uint32 i;
    norflash_file_list_t *p_used_file = &used_file;


    for(i = 0; i < NORFLASH_TOTAL_BLOCK_NUM; i++)
    {
        file_lock_array[i] = NULL;
    }

    i = 0;
    while(p_used_file->next !=NULL)
    {

        file_lock_array[i++] = p_used_file->next;
        p_used_file = p_used_file->next;

    }

}

void norflash_fs_fat_init()
{
    
    Uint32 i;
    norflash_blk_info_t *p_blk_info = NULL;

    if(norflash_fs_info.fs_first_inited == 0)
    {
        norflash_fs_info.fs_first_inited = 1;
        norflash_fs_format();
    }
    else
    {
        for(i = 0; i < FAT_SAV_BLOCK_NUM; i++)
        {
            p_blk_info = get_block_info(i+FAT_SAV_BLOCK_BASE);

            if(!strcmp(p_blk_info->sign, NORFLASH_BLOCK_SIGN))
            {
                if(p_blk_info->file_name > norflash_fs_info.fat_file_name)
                {
                    norflash_fs_info.block_state[i+ FAT_SAV_BLOCK_BASE] = NORFLASH_BLOCK_STATE_USED;
                    norflash_fs_info.fat_prev_block_num =  norflash_fs_info.fat_cur_block_num;
                    norflash_fs_info.fat_cur_block_num = i+ FAT_SAV_BLOCK_BASE;
                    norflash_fs_info.fat_file_name = p_blk_info->file_name;
                }
                else
                {
                    norflash_fs_info.block_state[i+ FAT_SAV_BLOCK_BASE] = NORFLASH_BLOCK_STATE_USED;
                    norflash_fs_info.fat_prev_block_num = i+ FAT_SAV_BLOCK_BASE;
                }
            }
            
        }

        load_fat_info();

        /*parse saved image blocks file*/
        for(i = IMG_SAV_BLOCK_BASE; i + IMG_SAV_SIZE_NUM_OF_BLOCK <  NORFLASH_TOTAL_BLOCK_NUM; i += IMG_SAV_SIZE_NUM_OF_BLOCK)
        {
            
            p_blk_info = get_block_info(i);

            /*block is image file*/
            if(!strcmp(p_blk_info->sign, NORFLASH_BLOCK_SIGN))
            {
                /*statistics vaild image file num*/
                norflash_fs_info.img_file_num++;
                norflash_fs_info.block_state[i] = NORFLASH_BLOCK_STATE_IMAGE;

                /*image file list node init */
                norflash_blk_file_list[i].block_num = i;
                norflash_blk_file_list[i].file_name = p_blk_info->file_name;
                norflash_blk_file_list[i].file_type = p_blk_info->file_type;
                
                /*find the newest image block num,may be the num will be very low buf file_name is the biggest*/
                norflash_fs_info.newest_img_block_num = (p_blk_info->file_name > norflash_blk_file_list[norflash_fs_info.newest_img_block_num].file_name) 
                                                                                    ? i : norflash_fs_info.newest_img_block_num; 
            }
            
        }
    }

    file_list_init();
    set_file_lock();
}


void save_fat_info()
{

    Uint32 i;
    Uint32 blk_num;
    norflash_blk_info_t *p_blk_info = NULL;
    Uint8 *fat_info = (Uint8 *)norflash_fs_info.img_file_info;

    /*erase previous fat info block*/
    if(norflash_fs_info.fat_prev_block_num > 0)
    {
        erase_block_info(norflash_fs_info.fat_prev_block_num);
        norflash_fs_info.block_state[norflash_fs_info.fat_prev_block_num] = NORFLASH_BLOCK_STATE_IDLE;
    }
    
    blk_num = get_next_block_to_save_fat_info();
    p_blk_info = norflash_blk_info + blk_num;

    /*init current cfg block info*/
    p_blk_info->file_name = ++norflash_fs_info.cfg_file_name;
    p_blk_info->file_type = 0x00;
    strcpy(p_blk_info->sign, NORFLASH_BLOCK_SIGN);
    
    /*update block info to norflash*/    
   update_block_info(blk_num, p_blk_info);

    norflash_fs_info.block_state[blk_num] = NORFLASH_BLOCK_STATE_USED;
    norflash_fs_info.cfg_prev_block_num = norflash_fs_info.cfg_cur_block_num;
    norflash_fs_info.cfg_cur_block_num = blk_num;
    norflash_fs_info.cfg_file_name = ++norflash_fs_info.cfg_file_name;
    norflash_fs_info.img_file_info[NORFLASH_TOTAL_BLOCK_NUM-1].img_file_name = 999999999;

    /*write fat infomation to norflash with one page unit*/
    for(i = 0; i < FAT_SAV_SZIE_NUM_OF_PAGE; i++)
    {
        norflash_write_page(blk_num, i, fat_info+i*NORFLASH_PAGE_SIZE);
    }

}



static Int32 get_next_blocks_to_save_img()
{
    Uint32 free_blk_num;
    
    norflash_file_list_t *p_free_list = &free_file;
    if(norflash_fs_info.free_file_num == 0) //no free blocks 
        return -1;
    
    free_blk_num = p_free_list->next->block_num;
    p_free_list->next = p_free_list->next->next;
   
    norflash_fs_info.free_file_num--;

    return free_blk_num;
}

void save_image(Uint8 *img_buf, Uint32 file_type)
{
    Uint32 i,j;
    Int32 free_num;
    norflash_blk_info_t *p_blk_info = NULL;

    free_num = get_next_blocks_to_save_img();
    if(free_num < 0)
        return ;

    p_blk_info = &norflash_blk_info[free_num];

    /*init current image block info*/
    if (used_file.next !=0)
    {
        p_blk_info->file_name = used_file.next->file_name + 1;
    }
    else
    {
        p_blk_info->file_name = 1;//this is the first saved image file
    }
    p_blk_info->file_type = file_type;
    strcpy(p_blk_info->sign, NORFLASH_BLOCK_SIGN);
    
     /*update block info to norflash*/    
    update_block_info(free_num, p_blk_info);

    /*write image data to norflash. 8 Blocks*/
    for(i = 0; i < IMG_SAV_SIZE_NUM_OF_BLOCK; i++)
    {
        for(j = 0; j < IMG_SAV_SIZE_NUM_OF_PAGE;j++)
        {
            norflash_write_page(free_num+i, j, img_buf+i*NORFLASH_BLOCK_SIZE+j*IMG_SAV_SIZE_NUM_OF_PAGE);
        }
    }

   /*init file list node*/
    norflash_blk_file_list[free_num].file_name = p_blk_info->file_name;
    norflash_blk_file_list[free_num].file_type = file_type;
    norflash_blk_file_list[free_num].block_num = free_num;
    norflash_blk_file_list[free_num].buf_num = -1;

   /*add a new node to used file list*/
   if(used_file.next == NULL) //add to list tail
   {
        norflash_blk_file_list[free_num].prev = &used_file;
        norflash_blk_file_list[free_num].next = used_file.next;
        used_file.next = &norflash_blk_file_list[free_num];
   }
   else //insert new node,used_file->next = the newest file node
   {
        used_file.next->prev = &norflash_blk_file_list[free_num];
        norflash_blk_file_list[free_num].prev = &used_file;
        norflash_blk_file_list[free_num].next = used_file.next;
        used_file.next = &norflash_blk_file_list[free_num];
   }

    /*increase image file number*/
    norflash_fs_info.img_file_num++;
    norflash_fs_info.block_state[free_num] = NORFLASH_BLOCK_STATE_IMAGE;

    /*update imgae fat info*/
    norflash_fs_info.img_file_info[free_num-IMG_SAV_BLOCK_BASE].img_file_name = p_blk_info->file_name;
    norflash_fs_info.img_file_info[free_num-IMG_SAV_BLOCK_BASE].img_file_type = p_blk_info->file_type;

    set_file_lock();

}


void delete_image(Uint32 num)
{
    Uint32 blk_num;
    Uint32 i;
    
    norflash_file_list_t *del_node;
    norflash_file_list_t *temp_node;

    /*根据待删除的图片序号来查找对应的照片节点*/
    if(num >= norflash_fs_info.img_file_num) 
    {
        return ;
    }

    del_node = file_lock_array[num];
    if(del_node == NULL)
    {
        return ;
    }

    blk_num = del_node->block_num;
    erase_block_info(blk_num);

    /*clear image file information*/
    del_node->file_name = 0;
    del_node->file_type = 0;
    norflash_fs_info.img_file_info[blk_num-IMG_SAV_BLOCK_BASE].img_file_name = 0;
    norflash_fs_info.img_file_info[blk_num-IMG_SAV_BLOCK_BASE].img_file_type = 0;

    /*delete one node in used_file list*/
    del_node->prev->next = del_node->next;
    del_node->next->prev = del_node->prev;

    /*then add this used_file node to free_file list tail*/
    temp_node = &free_file;
    while(temp_node->next  != NULL)
    {
        temp_node = temp_node->next;
    }
    temp_node->next = del_node;
    del_node->prev = temp_node;
    del_node->next = NULL;

    norflash_fs_info.free_file_num++;
    norflash_fs_info.img_file_num--;
    norflash_fs_info.block_state[blk_num] = NORFLASH_BLOCK_STATE_IDLE;

    /*delete a iamge file node's lock*/
    for(i = num; i < norflash_fs_info.img_file_num; i++)
    {
        file_lock_array[i] = file_lock_array[i+1];
    }

    file_lock_array[norflash_fs_info.img_file_num] = NULL;
    
}


void load_image(Uint32 num)
{
    
    norflash_file_list_t *img_node;
    Uint32 blk_num;

    if(num >= norflash_fs_info.img_file_num) 
    {
        return ;
    }

    img_node = file_lock_array[num];
    if(img_node == NULL)
    {
        return ;
    }    
    
    blk_num = img_node->block_num;

    Uint32 addr = NORFLASH_BLOCK_ADDR(blk_num);
    norflash_read_datas(addr, 0, 0);

}

void preview_image()
{
}

