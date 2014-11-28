
#include "global.h"
#include "dm6437.h"
#include "dm6437_uart.h"
#include "image_process.h"
#include <csl_edma.h>
#include <csl_edmaAux.h>
#include <soc.h>
#include <cslr_edmacc.h>
#include "dm6437_gpio.h"
#include "wireless_rf.h"
#include "led.h"
#include "buzzer.h"
#include "dm6437_vpfe.h"
#include "dm6437_vpbe.h"
#include "dm6437_edma3.h"
#include "stdio.h"
#include "csl_cache.h"

#define GPIO13_INT

extern UART_Handle uart1_handle;
extern unsigned char uart_rx_buf[32];
unsigned char uart_rx_buf_num;


extern Uint8 resize_done_flag  ;
extern Uint8 recv_buf_overrun_flag;



#ifdef GPIO13_INT
void GPIO_IntInit()
{

    GPIO_BINTEN = 0x0 ;	 //Bank0 ([GP[0]-GP[15] interrupts are enabled.

#ifdef IMPLANT_VISION_2
    GPIO_CLR_RIS_TRIG01 = (1 << 13) ; //clear GP[13]: Rise edge interrupt
    GPIO_SET_FAL_TRIG01 = (1 << 13) ; //set GP[13]: FAL edge interrupt
#endif

#ifdef IMPLANT_VISION_1
    GPIO_SET_RIS_TRIG01 = (1 << 13) ; //set GP[13]: Rise edge interrupt
    GPIO_CLR_FAL_TRIG01 = (1 << 13) ; //clear GP[13]: FAL edge interrupt
#endif

}

void enable_gpio13_int()
{
    GPIO_BINTEN = 0x1;
}

void disable_gpio13_int()
{
    GPIO_BINTEN = 0;
    TIMER0_TRC &= ~(1 << 6); //disable the timer0.
}
#endif


void Interrupt_init()
{
	CSR=0x100; 	 /* disable all interrupts			  *///EN=1表示小端格式，全局中断不使能
	IER=1; 		 /* disable all interrupts except NMI */
	ICR=0xffff;	 /* clear all pending interrupts	  */  //清除ICF中INT4-INT15的所有中断的标志位

	ISTP = 0x10800000;     //中断向量表ISTP所在的地址，可以自己指定
	 
	INTC_EVTCLR0 = 0xFFFFFFFF; 
	INTC_EVTCLR1 = 0xFFFFFFFF; 
	INTC_EVTCLR2 = 0xFFFFFFFF; 
	INTC_EVTCLR3 =	0xFFFFFFFF;   
	//INTC_EVTFLAG1=0x00000000;
	INTC_EVTMASK3 = 0xFFFFFFFF;
	INTC_EVTMASK2 = 0xFFFFFFFF;
	INTC_EVTMASK1 = 0xFFFFFFFF;
	INTC_EVTMASK0 = 0xFFFFFFFF; //所有中断都不进行合并,独立

       /*allocate interrupt number in 0-15*/
	INTC_INTMUX1 = 0x1b1D1c04;  //hist->Int7, preview->Int6, h3a->Int5, Timer0->Int4
	INTC_INTMUX2 = 0x22201E55;  //edma3->Int11, venc->Int10, resizer->Int9, Uart1->Int8
	INTC_INTMUX3 = 0x48515018;  //GPIOBANK0->Int15, pwm1->Int14,pwm0->Int13,ccdc->Int12

	IER |= 0x00007Ff2;         //所有来至于INT4-INT15的中断源都使能
//	CSR=0x01 ;		 /* enable all interrupts			 *///全局中断使能

       CSR |= 0x01 ;       /* enable all interrupts            *///全局中断使能
    
}




/*                             Int_uart1                                */

#define uart1getdata(A, B)  EVMDM6437_UART_getdata(uart1_handle, A, B)
#define uart1getdatanum()   EVMDM6437_UART_getnum_rx( uart1_handle )
static void fill_uart_send_fifo16();
static wait_recv_fifo_empety();

static void fill_uart_send_fifo16()
{
    Uint8 i;
    for (i = 0; i < 16; i++)    //FIFO 16Bytes
    {  
        if(uart1_tx.num > 0)
        {
            UART1_THR = * uart1_tx.pdata++;         
            uart1_tx.num--;
            if ( uart1_tx.pdata == uart1_tx.buffer + UART_BUF_SIZE) 
            {
                uart1_tx.pdata = uart1_tx.buffer;   
            }
        }
    }
}



static wait_recv_fifo_empety()
{
    while ( UART1_LSR & 0x1 )        //wait recv fifo get null.all datas have been read.
    {
        *uart1_rx.pempty = UART1_RBR;                   
        uart1_rx.num++;				
        uart1_rx.pempty++;

        if (uart1_rx.pempty == uart1_rx.buffer + UART_BUF_SIZE) 
        {
            uart1_rx.pempty = uart1_rx.buffer;
        }
    }
#if 0
        if(uart1_rx.num > UART_BUF_SIZE)  
        {
            /*stop to recv more datas since that
                 the buffer is filled to UART_BUF_SIZE*/
            uart_obj1.regs->IER &= ~0x1; 
            recv_buf_overrun_flag = 1;
            break;
            
        }
#endif
    
}



interrupt void Int_Uart1ISR()
{
    UART_INT_TYPE int_type;

    int_type = (UART_INT_TYPE)((uart_obj1.regs->IIR & 0xe) >> 1);

    switch ( int_type )
    {
        
        case UART_THREINT:      //send int
        {
            fill_uart_send_fifo16();
            break;		
        }

       case UART_RLSINT:   //Receiver line status:break or overrun error,need to clear it
       {
        /*Uint32 ret = uart_obj1.regs->LSR;
        while ( UART1_LSR & 0x1 )
        {
        	ret = UART1_RBR;
        }*/
       }
            break;

       case UART_RADINT:    //No_FIFO:Receiver data available or FIFO:reached trigger level
       case UART_RTOINT:     //Receiver time-out (only FIFO Mode)
       {
            wait_recv_fifo_empety(); 
            break;
       }

        default:
            break;
	}
}


extern unsigned char vpfe_ccdc_buf[2][IMAGE_W * IMAGE_H * 2];
volatile Uint8 vpfe_ccdc_buf_offset = 0;
/*                             Int_CcdcISR                                */
interrupt void Int_CcdcISR(void)
{
    vpfe_ccdc_buf_offset = 1-vpfe_ccdc_buf_offset;
    VPFE_CCDC_SDR_ADDR = (Uint32)vpfe_ccdc_buf[vpfe_ccdc_buf_offset];

}



volatile Uint8 preview_done_flag = 0; 
extern unsigned char vpfe_frame_buf[8][RAW_IMAGE_W * RAW_IMAGE_H * 2];

/*                             Int_PreviewISR                                */
interrupt void Int_PreviewISR(void)
{
    
    set_vpfe_frame_to_free(); //set next frame to free
    VPFE_PREV_WSDR_ADDR = get_vpfe_free_buf();//get free buffer
    preview_done_flag = 1;

}


extern unsigned int vpfe_af_out_buf[1280 * 720]; 
extern unsigned int vpfe_ae_out_buf[2][1280 * 720  * 2];
volatile extern char vpfe_ae_out_buf_offset;
volatile int h3a_af_value = 0;
volatile Uint8 h3a_done_flag = 0;

/*                             Int_H3aISR                                */
interrupt void Int_H3aISR(void)
{
    Uint32 tmp, i;
    
    
    if((VPFE_H3A_PCR & (1 << 18)) || (VPFE_H3A_PCR & (1 << 15)))//ae is busy
    {
        return ;
    }

    else
    {
        vpfe_ae_out_buf_offset =1 - vpfe_ae_out_buf_offset;
        VPFE_H3A_AEWBUFST = (unsigned int)vpfe_ae_out_buf[vpfe_ae_out_buf_offset];
		
        tmp = 0;
        vpfe_af_out_buf[200] =  (vpfe_af_out_buf[2] >> 1) + vpfe_af_out_buf[6] + vpfe_af_out_buf[10];
        tmp += vpfe_af_out_buf[200];
        vpfe_af_out_buf[201] =  ((vpfe_af_out_buf[12 + 2] >> 1) + vpfe_af_out_buf[12 + 6] + vpfe_af_out_buf[12 + 10]);
        tmp += vpfe_af_out_buf[201];
        vpfe_af_out_buf[202] = (vpfe_af_out_buf[24 + 2] >> 1) + vpfe_af_out_buf[24 + 6] + vpfe_af_out_buf[24 + 10];
        tmp += vpfe_af_out_buf[202];
        vpfe_af_out_buf[203] = ((vpfe_af_out_buf[36 + 2] >> 1) + vpfe_af_out_buf[36 + 6] + vpfe_af_out_buf[36 + 10]);
        tmp += vpfe_af_out_buf[203];
        vpfe_af_out_buf[204] = ((vpfe_af_out_buf[48 + 2] >> 1) + vpfe_af_out_buf[48 + 6] + vpfe_af_out_buf[48 + 10]) ;
        tmp += vpfe_af_out_buf[204];

        vpfe_af_out_buf[205] = ((vpfe_af_out_buf[60 + 2] >> 1) + vpfe_af_out_buf[60 + 6] + vpfe_af_out_buf[60 + 10]);
        tmp += vpfe_af_out_buf[205];
        vpfe_af_out_buf[206] = ((vpfe_af_out_buf[72 + 2] >> 1) + vpfe_af_out_buf[72 + 6] + vpfe_af_out_buf[72 + 10]);
        tmp += vpfe_af_out_buf[206];
        vpfe_af_out_buf[207] = ((vpfe_af_out_buf[84 + 2] >> 1) + vpfe_af_out_buf[84 + 6] + vpfe_af_out_buf[84 + 10]);
        tmp += vpfe_af_out_buf[207];
        tmp += vpfe_af_out_buf[207];
        vpfe_af_out_buf[208] = ((vpfe_af_out_buf[96+ 2] >> 1) + vpfe_af_out_buf[96 + 6] + vpfe_af_out_buf[96 + 10]);
        tmp += vpfe_af_out_buf[208];
        vpfe_af_out_buf[209] = ((vpfe_af_out_buf[108 + 2] >> 1) + vpfe_af_out_buf[108 + 6] + vpfe_af_out_buf[108 + 10]);
        tmp += vpfe_af_out_buf[209];

        vpfe_af_out_buf[210] = ((vpfe_af_out_buf[120 + 2] >> 1) + vpfe_af_out_buf[120 + 6] + vpfe_af_out_buf[120 + 10]) ;
        tmp += vpfe_af_out_buf[210];
        vpfe_af_out_buf[211] = ((vpfe_af_out_buf[120 + 12 + 2] >> 1) + vpfe_af_out_buf[120 + 12 + 6] + vpfe_af_out_buf[120 + 12 + 10]);
        tmp += vpfe_af_out_buf[211];
        vpfe_af_out_buf[212] = (vpfe_af_out_buf[120 + 24 + 2] >> 1) + vpfe_af_out_buf[120 + 24 + 6] + vpfe_af_out_buf[120 + 24 + 10];
        tmp += vpfe_af_out_buf[212];
        vpfe_af_out_buf[213] = ((vpfe_af_out_buf[120 + 36 + 2] >> 1) + vpfe_af_out_buf[120 + 36 + 6] + vpfe_af_out_buf[120 + 36 + 10]);
        tmp += vpfe_af_out_buf[213];
        vpfe_af_out_buf[214] = ((vpfe_af_out_buf[120 + 48 + 2] >> 1) + vpfe_af_out_buf[120 + 48 + 6] + vpfe_af_out_buf[120 + 48 + 10]) ;
        tmp += vpfe_af_out_buf[214];

        tmp = tmp >> 4;//计算16个Paxels的平均值
        for(i = 0; i < 15; i++)
        {
        	if(vpfe_af_out_buf[200 + i] < tmp)
        	{
        		vpfe_af_out_buf[200 + i] = tmp;//取为平均值
        	}
        }
        h3a_af_value = 0;
        h3a_af_value += vpfe_af_out_buf[200] + vpfe_af_out_buf[204] + vpfe_af_out_buf[210] + vpfe_af_out_buf[214] 
        			+ vpfe_af_out_buf[202] + vpfe_af_out_buf[206] + vpfe_af_out_buf[208] + vpfe_af_out_buf[212];
        h3a_af_value += (vpfe_af_out_buf[201] + vpfe_af_out_buf[203] + vpfe_af_out_buf[205] + vpfe_af_out_buf[209]
                    + vpfe_af_out_buf[211] + vpfe_af_out_buf[213]+ vpfe_af_out_buf[202] + vpfe_af_out_buf[206] + vpfe_af_out_buf[208] + vpfe_af_out_buf[212])<< 1 ; 
        h3a_af_value += vpfe_af_out_buf[207]<<2;
        h3a_af_value = h3a_af_value >> 5;//计算32个值后最终统计出一个AF的平均值
    }

    h3a_done_flag = 1;

}



/*                             Int_HistISR                                */
interrupt void Int_HistISR(void)
{
 
}


/*                             Int_ResizeISR                                */
interrupt void Int_ResizeISR(void)
{
    resize_done_flag = 1;
}


/*                             Int_VencISR                                */
interrupt void Int_VencISR(void)
{

	VPBE_OSD_VIDWIN0ADR = get_vpbe_frame_buf(); // get processed image buffer addr
}


/*                             Int_Edma3ISR                                */
interrupt void Int_Edma3ISR(void)
{
    

}





/*                             Int_Timer0_34ISR                                */
interrupt void Int_Timer0_34ISR(void)
{

}



/*                             Int_Timer1_12ISR                                */
interrupt void Int_Timer1_12ISR(void)
{

}



/*                             Int_Timer1_34ISR                                */
interrupt void Int_Timer1_34ISR(void)
{
    TIMER1_TRC &= ~(1 << 22); //disable the timer1_34
    TIMER1_TIM34 = 0; // clear timer1_34 count value    
}




Uint8 rf_test_flag = 0;
#if 0
interrupt void Int_Timer0ISR(void)
{
	TIMER0_TGCR = 0;
    TIMER0_TRC &= ~(1 << 6); //disable the timer0.
    TIMER0_TIM12 = 0;
    TIMER0_TIM34 = 0;// clear timer0 count value
    rf_test_flag = 1;
}
#endif


/*                             Int_GPIOBANK0ISR                                */
interrupt void Int_GPIOBANK0ISR()
{
    /*start timer0*/
    TIMER0_TRC |= (1 << 6); //Timer0 one-time mode enable,start timer.
    GPIO_BINTEN = 0 ;	 //Bank0 ([GP[0]-GP[15] interrupts are disabled.
}



interrupt void Int_PWM0ISR()
{
    
}


    
        


