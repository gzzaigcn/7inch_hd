#include "stdio.h"
#include "string.h"
#include "global.h"
#include "img_alg.h"
#include "dm6437_edma3.h"


Uint32 gray_hist_table[256*2];

Int32 otsu_thrd_table[OSTU_BLK_XNUM*OSTU_BLK_YNUM+1];
Int32 avg_high_table[OSTU_BLK_XNUM*OSTU_BLK_YNUM+1] = {0};
Int32 avg_low_table[OSTU_BLK_XNUM*OSTU_BLK_YNUM+1] = {0};

static Uint32 otsu_threshold = 128;

Uint8 color_table_Y[256];
Uint8 color_table_Cb[256];
Uint8 color_table_Cr[256];

/*非真彩变色表，对应Y Cb Cr值，最后一位表示是否深色背景浅色字的模式*/
//[0]为前景，[1]为背景
#pragma DATA_SECTION(flase_color_type_table, "L1_DATA0")
#pragma DATA_ALIGN(flase_color_type_table, 4)
Uint8 flase_color_type_table[12][2][4] =  
{
  {{0, 128, 128, 0},{255, 128, 128, 0}},   // Black  White
  {{35, 212, 114, 0},{255, 128, 128, 0}},  // Blue   White
  {{0, 128, 128, 0},{210, 16, 146, 0}},    // Black  Yellow
  {{35, 212, 114, 0},{210, 16, 146, 0}},   // Blue   Yellow
  {{0, 128, 128, 0},{148, 128, 128, 0}},   // Black  Gray  
  {{0, 128, 128, 0},{147, 184, 204, 0}},   // Black  Purple  
  {{0, 128, 128, 0},{176, 189, 66, 0}},    // Black  lightBlue  
  {{0, 128, 128, 0},{176, 28, 183, 0}},    // Black  Orange 
  {{0, 128, 128, 0},{165, 45, 95, 0}},   // Black  lightGreen 
  {{42, 114, 97, 0},{255, 128, 128, 0}},   // Green white 
  {{34, 160, 160, 0},{255, 128, 128, 0}},  // Purple White 
  {{34, 51, 206, 0},{255, 128, 128, 0}},   // Red White 
};

/*assamble function declare*/
FUN_GRAY_COLOR_TRANS GrayTransTable_sa;
FUN_FLASE_COLOR_TRANS ColorTransTable_sa;
FUN_TRUE_COLOR_TRANS ContrastBrightSaturationTable_sa;
FUN_GRAY_COLOR_HIST_TRANS GrayTransStatTable_sa;
FUN_FLASE_COLOR_HIST_TRANS ColorTransStatTable_sa;
FUN_TRUE_COLOR_HIST_TRANS ContrastBrightSaturationStatTable_sa;


/*function point to assmable function*/
PFUN_TRUE_COLOR_TRANS true_color_trans;
PFUN_GRAY_COLOR_TRANS gray_color_trans;
PFUN_FLASE_COLOR_TRANS false_color_trans;

PFUN_TRUE_COLOR_HIST_TRANS true_color_hist_trans;
PFUN_GRAY_COLOR_HIST_TRANS gray_color_hist_trans;
PFUN_FLASE_COLOR_HIST_TRANS false_color_hist_trans;

extern Uint32 ostu_enable_flag;
extern Uint32 ostu_thrd_cnt;


/**********************Function for OTSU algorithm based-block*******************************************/
void clear_gray_hist()
{
     memset((Uint8 *)gray_hist_table, 0, sizeof(gray_hist_table));
}

void cal_gray_hist()
{
    Int32 i;

    for(i=0; i<256; i++)
    {
        gray_hist_table[i] = gray_hist_table[i] + gray_hist_table[256 + i]; //2Pixels
    }

}

Uint32 cal_local_opt_thrd(Uint32 Width, Uint32 Height, Uint32 blk_index)
{
    //int *pixelCount =  (int *)ImageSlice0;
    int *pixelPro;
    long sum_mi = 0;
    long sum_low_mi = 0;
    long sum_high_mi = 0;
    long sum= 0;
    long sum_low= 0;
    long sum_high= 0;
    int i, pixelSum = Width * Height;
    int u0, u1;
    long deltaTmp, deltaMax ;  
    int avg_diff;
       
    pixelPro =  (int *)(gray_hist_table + 256);//存放当前像素点灰度级在一帧中的比例
    deltaMax = 0;

    //计算每个像素在整幅图像中的比例  
    for(i = 0; i < 256; i++)
    {  
        pixelPro[i] = ((long)(gray_hist_table[i]) << 20) / pixelSum; //计算当前像素点灰度级在一帧中的比例
        sum_mi += i * pixelPro[i] ;//计算前i个像素点的灰度总值
        sum += pixelPro[i];//计算像素点的256个灰度级的比例和
    }  

    for(i = 0; i < 256; i++) //遍历灰度级[0,255]  
    {  
        sum_low += pixelPro[i];//前景的所占的比例
        sum_low_mi += i * pixelPro[i];//求前景的灰度总和
        
        sum_high_mi = sum_mi - sum_low_mi;//求背景的灰度总和
        sum_high = sum - sum_low;//背景所占的比例
        if(sum_low == 0)continue;
        if(sum_high == 0)break;

        u0 = (sum_low_mi << 8)/ sum_low;  //背景平均的灰度值

        u1 = (sum_high_mi << 8) / sum_high;   //前景平均的灰度值

        deltaTmp = ((long)(sum_low) *(long)(sum_high) >> 20) *((u0 - u1) *(u0 - u1)>>16);// 2<<20的因子

        if(deltaTmp > deltaMax)//类间方差最大
        {  
            deltaMax = deltaTmp;
            
            otsu_thrd_table[blk_index] =  i;
            avg_low_table[blk_index] = u0;
            avg_high_table[blk_index] = u1;
        }  

    }      

    return 1;
}


void cal_ostu_global_threshold()
{
        
    int i;
    int vaild_num = 0;
    int KickOffValue = 5000;
    int Thrd = 0;
    Uint32 blk_num = OSTU_BLK_XNUM*OSTU_BLK_YNUM;

    for(i = 0; i < blk_num; i++)
    {
        if((avg_high_table[i] - avg_low_table[i]) > KickOffValue)
        {
            Thrd += otsu_thrd_table[i];
            vaild_num++;
        }
    }    

    if(vaild_num >= 4)
    {
        Thrd /= vaild_num;
    }

    else
    {
        
        Thrd = 0;
        
        for(i=0; i < blk_num; i++)
        {
            Thrd += otsu_thrd_table[i];
        }   
        
        Thrd /= blk_num;
        
    }

    if(Thrd < 40)
    {
        Thrd  = 40;  
    }

    else if(Thrd > 210)
    {
        Thrd = 210; 
    }

    if (((Thrd+2) < otsu_threshold) || ((Thrd-2) > otsu_threshold))
    {
        otsu_threshold = Thrd; //update threshold   
    }

}



/**********************Function for Transfer color algorithm*******************************************/
void create_color_table(Uint8 true_color, Uint8 flase_color_type)
{
    Int32 fA, fB;
    Int32 fA2, fB2;
    Int32 i,j;

    Uint8 *front_color;
    Uint8 *back_color;
    Uint8 color_diff, color_avg;

    Uint8 temp_y, temp_cb, temp_cr;
    

    if(true_color == TRUE_COLOR_MODE)//true mode
    {
        fA = 16;
        fB = 0;
        
        for (i = 0; i<256; i++)
        {
            j = (fA*i << 4) + fB;
            if(j > 255)
            {
                j = 255;
            }
            else if(j < 0)	
            {
                j = 0;
            }

            color_table_Y[i] = j;
        }
        return ;
    }
    else //false color
    {
        
        if(flase_color_type == WHITE_BLACK_TYPE ||flase_color_type == BLACK_WHITE_TYPE) //black_white, white_balck
        {
            
            fA = 144;
            fB = 128 - (fA)*(otsu_threshold) /16; //一级灰度拉伸系数

            fA2 = 2;
            fB2 = -128;//二级灰度拉伸系数
            
            for(i=0; i<256; i++)
            {
                
                j = fA*i/16+fB;
                
                if(j > 255)
                {
                    j = 255;
                }
                else if(j < 0) 
                {
                    j = 0;
                }
		
		  j = fA2*j+fB2;
                if(j > 255)
                {
                    j = 255;
                }
                else if(j < 0) 
                {
                    j = 0;
                } 

                color_table_Y[i] = j;

            }
        }
        else //other false color mode
        {
            front_color = flase_color_type_table[flase_color_type>>1][0];
            back_color = flase_color_type_table[flase_color_type>>1][1];   

            color_diff = (back_color[0] - front_color[0]);
            color_avg = ((Uint32)back_color[0] + front_color[0])/2;
      
            for(i=0; i<256; i++)
            {
                
                j = fA*i/16+fB;

                if(j > 255)
                {
                    j = 255;
                }
                else if(j < 0) 
                {
                    j = 0;
                } 

                temp_y = fA2*j+fB2;
                if(temp_y >= 255)
                {
                    temp_y = back_color[0];
                    temp_cb = back_color[1];
                    temp_cr = back_color[2]; 
                }
                
                else if(temp_y <= 0) 
                {
                    temp_y = front_color[0];
		      temp_cb = front_color[1];
		      temp_cr = front_color[2];
                }
                
		  else
                {

                    temp_y = ((color_diff*temp_y)>>0x8) + front_color[0];
                    if((front_color[0] == 255) || (front_color[0] == 0))  
                    {
                        temp_cb = back_color[1]; 
                        temp_cr = back_color[2];  
	             }
                    else if((back_color[0] == 255) || (back_color[0] == 0))
                    {
                        temp_cb = front_color[1]; 
                        temp_cr = front_color[2];  
                    }
                    else
                    {
                        if(temp_y > color_avg)
                        {
                            temp_cb = back_color[1]; 
                            temp_cr = back_color[2]; 
                        }
                        else 
                        {
                            temp_cb = front_color[1]; 
                            temp_cr = front_color[2]; 
                        }
                    }
                  
		  }
                color_table_Y[i]  =  temp_y;
                color_table_Cb[i] =  temp_cb;
                color_table_Cr[i] =  temp_cr;
            }
        }
    }

}


void true_color_dma_process(Uint32 inbuf, Uint32 outbuf, Uint32 src_width, Uint32 dst_width, Uint32 width, Uint32 height)
{

    Uint32 i, j, k;
    Uint32 i_next, j_next;
    Uint8 *p_inbuf = (Uint8 *)inbuf ;
    Uint8 *p_outbuf =  (Uint8 *)outbuf ;
    Uint8 *p_slice_inbuf;
    Uint8 *p_slice_outbuf;
    
    Uint32 ostu_blk_x, ostu_blk_y;
    Uint32 ostu_blk_index;

    create_color_table(TRUE_COLOR_MODE, 0);
    
    UpdateSrcDstParam(pEdmaccRegs, DstChannel0, p_inbuf, pEDMADstBuf0);
    StartEdma(pEdmaccRegs, DstChannel0);

    ostu_blk_x = (ostu_thrd_cnt-1) % OSTU_BLK_XNUM;

    for(i = 0; i < SLICE_YNUM; i++)
    {
        for(j = 0; j < SLICE_XNUM; j++)
        {
            WaitEdma(pEdmaccRegs, DstChannel0);

            /*get slice address in L0*/
            p_slice_inbuf = pEDMADstBuf0;
            p_slice_outbuf = pEDMASrcBuf0;
            p_outbuf = (Uint8 *)outbuf + i*IMAGE_W*2*SLICE_H + j*SLICE_W*2;

            SwapEDMABuffer();

            if(j < SLICE_XNUM -1)
            {
                j_next = j+1;
                i_next = i;
            }
            else //the first block in next stride line
            {
                j_next = 0;
                i_next = i+1;//next line
            }

            if(i_next < SLICE_YNUM) 
            {
                p_inbuf =(Uint8 *)inbuf + i_next*IMAGE_W*2*SLICE_H + j_next*SLICE_W*2;

                /*move a slice from DDR to L0D*/
                UpdateSrcDstParam(pEdmaccRegs, DstChannel0, p_inbuf, pEDMADstBuf0);
                StartEdma(pEdmaccRegs, DstChannel0);
            }

            /*process 3 blocks in column dirction, that 3 small slice*/
            if((ostu_enable_flag == 1) && (j == ostu_blk_x) && (i >= ostu_blk_y || i >= ostu_blk_y+2))
            {
                
                true_color_hist_trans((Uint32)p_slice_outbuf, (Uint32)p_slice_inbuf, SLICE_W << 1, SLICE_W << 1, SLICE_W, SLICE_W, SLICE_H, color_table_Y, gray_hist_table);

                if(i == ostu_blk_y+2)//one ostu block hist include 3 small slice
                {
                    ostu_blk_index = ostu_blk_x*4 + k;//3      
                    cal_gray_hist();
                    cal_local_opt_thrd(OSTU_BLK_W, OSTU_BLK_H, ostu_blk_index);
                    clear_gray_hist();
                    k++;
                }
            } 
            else
            {
                true_color_trans((Uint32)p_slice_outbuf, (Uint32)p_slice_inbuf, SLICE_W << 1, SLICE_W << 1, SLICE_W, SLICE_W, SLICE_H, color_table_Y);
            }

            if((i !=0) || (j != 0))//not the first
            {
                WaitEdma(pEdmaccRegs, SrcChannel0);
            }
            UpdateSrcDstParam(pEdmaccRegs, SrcChannel0, p_slice_outbuf, p_outbuf);
            StartEdma(pEdmaccRegs, SrcChannel0);
            
        }
    }
    
    WaitEdma(pEdmaccRegs, SrcChannel0);//wait the last processed block be moved to DDR2  
    
    return;
}

void false_color_dma_process(Uint32 inbuf, Uint32 outbuf, Uint8 flase_color_type, Uint32 src_width, Uint32 dst_width, Uint32 width, Uint32 height)
{
    Uint32 i, j, k;
    Uint32 i_next, j_next;
    Uint8 *p_inbuf = (Uint8 *)inbuf ;
    Uint8 *p_outbuf =  (Uint8 *)outbuf ;
    Uint8 *p_slice_inbuf;
    Uint8 *p_slice_outbuf;

   Uint32 ostu_blk_x, ostu_blk_y;
   Uint32 ostu_blk_index;

    create_color_table(FLASE_COLOR_MODE, flase_color_type);

    UpdateSrcDstParam(pEdmaccRegs, DstChannel0, p_inbuf, pEDMADstBuf0);
    StartEdma(pEdmaccRegs, DstChannel0);

    if(ostu_enable_flag)
    {
        clear_gray_hist();
    }

    ostu_blk_x = (ostu_thrd_cnt-1)%OSTU_BLK_XNUM;

    for(i = 0; i < SLICE_YNUM; i++)
    {
        for(j = 0; j < SLICE_XNUM; j++)
        {
            WaitEdma(pEdmaccRegs, DstChannel0);

            /*get slice address in L1D*/
            p_slice_inbuf = pEDMADstBuf0;
            p_slice_outbuf = pEDMASrcBuf0;
            p_outbuf = (Uint8 *)outbuf + i*IMAGE_W*2*SLICE_H + j*SLICE_W*2;

            SwapEDMABuffer();

            if(j < SLICE_XNUM -1)
            {
                j_next = j+1;
                i_next = i;
            }
            else //the first block in next stride line
            {
                j_next = 0;
                i_next = i+1;//next line
            }

            if(i_next < SLICE_YNUM) 
            {
                p_inbuf =(Uint8 *)inbuf + i_next*IMAGE_W*2*SLICE_H + j_next*SLICE_W*2;

                /*move a slice from DDR to L1D*/
                UpdateSrcDstParam(pEdmaccRegs, DstChannel0, p_inbuf, pEDMADstBuf0);
                StartEdma(pEdmaccRegs, DstChannel0);
            }
            
            ostu_blk_y = 3*k;

            /*process 3 blocks in column dirction, that 3 small slice*/
            if((ostu_enable_flag == 1) && (j == ostu_blk_x) && (i >= ostu_blk_y || i >= ostu_blk_y+2))
            {
                if(flase_color_type == 0 || flase_color_type == 1)
                {
               //     gray_color_hist_trans((Uint32)p_slice_outbuf, (Uint32)p_slice_inbuf, SLICE_W << 1, SLICE_W << 1, SLICE_W, SLICE_W, SLICE_H, color_table_Y, gray_hist_table);
                }
                else
                {
                 //   false_color_hist_trans((Uint32)p_slice_outbuf, (Uint32)p_slice_inbuf, SLICE_W << 1, SLICE_W << 1, SLICE_W, SLICE_W, SLICE_H, color_table_Y, color_table_Cb, color_table_Cr, gray_hist_table);
                }          
                
                if(i == ostu_blk_y+2)//one ostu block hist include 3 small slice
                {
                    ostu_blk_index = ostu_blk_x*4 + k;//3      
                    cal_gray_hist();
                    cal_local_opt_thrd(OSTU_BLK_W, OSTU_BLK_H, ostu_blk_index);
                    clear_gray_hist();
                    k++;
                }
            }
            else
            {
                if(flase_color_type == BLACK_WHITE_TYPE || flase_color_type == WHITE_BLACK_TYPE)
                {
               //     gray_color_trans((Uint32)p_slice_outbuf, (Uint32)p_slice_inbuf, SLICE_W << 1, SLICE_W << 1, SLICE_W, SLICE_W, SLICE_H, color_table_Y);
                }
                else
                {
                //    false_color_trans((Uint32)p_slice_outbuf, (Uint32)p_slice_inbuf, SLICE_W << 1, SLICE_W << 1, SLICE_W, SLICE_W, SLICE_H, color_table_Y, color_table_Cb, color_table_Cr);
                }
            }


            if((i !=0) || (j != 0))//not the first slice
            {
                WaitEdma(pEdmaccRegs, SrcChannel0);
            }
            UpdateSrcDstParam(pEdmaccRegs, SrcChannel0, p_slice_outbuf, p_outbuf);
            StartEdma(pEdmaccRegs, SrcChannel0);
            
        }
    }
    
    WaitEdma(pEdmaccRegs, SrcChannel0);//wait the last processed block be moved to DDR2  
    
    return;
}


/********************** Function Resize Alogrithm *******************************************/





/**********************Function Color Tansfer Alogrithm *******************************************/

void image_alg_init()
{

    true_color_trans = ContrastBrightSaturationTable_sa;
    gray_color_trans = GrayTransTable_sa;
    false_color_trans = ColorTransTable_sa;
    
    true_color_hist_trans = ContrastBrightSaturationStatTable_sa;
    gray_color_hist_trans = GrayTransStatTable_sa;
    false_color_hist_trans = ColorTransStatTable_sa;
    
}
