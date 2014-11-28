/******************************************************************************

   Copyright (C), 2014-,    Du-Health Electron Co.    All rights reserved. 

*******************************************************************************
 * File Name : dm6437_uart.c
 * Version : 1.0
 * Author : gzz
 * Created : 2014/9/3
 * Last Modified :
  Description   : dm6437 uart module setup
 * Function List :
              EVMDM6437_UART_close
              EVMDM6437_UART_delchar
              EVMDM6437_UART_getdata
              EVMDM6437_UART_getnum_rx
              EVMDM6437_UART_get_handle
              EVMDM6437_UART_open
              EVMDM6437_UART_putchar
              EVMDM6437_UART_putdata
              EVMDM6437_UART_putstring
 * Modification History :
   1.Date : 2014/9/3
     Author : gzz
     Modification : Created file
 
******************************************************************************/
#include "dm6437_uart.h"
#include "global.h"

UART_OBJ uart_obj0,uart_obj1;
UART_QUEUE uart0_rx, uart1_rx, uart0_tx, uart1_tx;

/*UART0 Malloc RX and TX Memory*/
#pragma DATA_SECTION(uart0_rx_buf, "L3_DATA0");
#pragma DATA_ALIGN(uart0_rx_buf, 128);
static Uint8 uart0_rx_buf[UART_BUF_SIZE];
#pragma DATA_SECTION(uart0_tx_buf, "L3_DATA0");
#pragma DATA_ALIGN(uart0_tx_buf, 128);
static Uint8 uart0_tx_buf[UART_BUF_SIZE];

/*UART1 Malloc RX and TX Memory*/
#pragma DATA_SECTION(uart1_rx_buf, "L3_DATA0");
#pragma DATA_ALIGN(uart1_rx_buf, 128);
static Uint8 uart1_rx_buf[UART_BUF_SIZE];
#pragma DATA_SECTION(uart1_tx_buf, "L3_DATA0");
#pragma DATA_ALIGN(uart1_tx_buf, 128);
static Uint8 uart1_tx_buf[UART_BUF_SIZE];


UART_Handle EVMDM6437_UART_get_handle(Uint16 UartId)
{
	UART_Handle	uart_handle;
	switch (UartId)
    {
        case 0:
            uart_handle = &uart_obj0;
            break;
		case 1:
			uart_handle = &uart_obj1;
			break;
		default:
			return ( UART_Handle )-1;
	}
	return uart_handle;
            	
}


UART_Handle EVMDM6437_UART_open(Uint16 UartId,
								   Uint16 UartBaud,
								   Uint8 UartWordLen,
								   Uint8 UartStopBits,
								   Uint8 UartParity
								   )
{
	UART_Handle	uart_handle;
	
	
	switch (UartId)
    {
        case 0:                                                                      //Uart0 Configure
            uart_handle = &uart_obj0;
            uart_handle->regs = (UART_REGS* )UART0_BASE;
			uart0_rx.buffer = uart0_rx_buf;
			uart0_tx.buffer = uart0_tx_buf;
			uart_handle->rx = &uart0_rx;
			uart_handle->tx = &uart0_tx;
			break;
            
        case 1:                                                                    //Uart1 Configure
            uart_handle = &uart_obj1;
            uart_handle->regs = (UART_REGS* )UART1_BASE;
			uart1_rx.buffer = uart1_rx_buf;
			uart1_tx.buffer = uart1_tx_buf;
			uart_handle->rx = &uart1_rx;
			uart_handle->tx = &uart1_tx;
            break;
            
        default:
			return ( UART_Handle )-1;
            
    }
	uart_handle->rx->num = 0;
	uart_handle->rx->pdata = uart_handle->rx->buffer;
	uart_handle->rx->pempty = uart_handle->rx->buffer;

	uart_handle->tx->num = 0;
	uart_handle->tx->pdata = uart_handle->tx->buffer;
	uart_handle->tx->pempty = uart_handle->tx->buffer;

	

	uart_handle->regs->PWREMU_MGMT = 0;     	// Reset UART TX & RX components

    _wait( 100 );

    uart_handle->regs->DLL = UartBaud & 0xff;   // Set baud rate
    uart_handle->regs->DLH = (UartBaud >> 8) & 0xff;

    uart_handle->regs->FCR = 0x0007;             //FIFO mode,Clear UART TX & RX FIFOs
    uart_handle->regs->FCR = 0x00C1;        	//Set FIFO trigle level 14 bytes
//    uart_handle->regs->FCR = 0x0007;             //FIFO mode,Clear UART TX & RX FIFOs
  //   uart_handle->regs->FCR = 0x0000;        	//Set FIFO trigle level 1bytes
    //uart_handle->regs->FCR = 0x0000;        	// Disable TX & RX FIFOs
    uart_handle->regs->IER = 0x0001;        	// enable recieve interrupts,disable send interrupt and Rec line error.
    uart_handle->regs->LCR = UartWordLen + UartStopBits + UartParity;
    uart_handle->regs->MCR = 0x0000;        	// RTS & CTS disabled,
                                            	// Loopback mode disabled,
                                            	// Autoflow disabled

    uart_handle->regs->PWREMU_MGMT = 0x6001; 	// Emulation Free,
                                             	// Enable TX & RX componenets

    return uart_handle;
}


Uint32 EVMDM6437_UART_close( UART_Handle uart_handle  )
{
    return 0;
}





Uint32 EVMDM6437_UART_putdata( UART_Handle uart_handle, unsigned char * data, Uint16 num  )
{   

    Uint16 temp;
    /*the privious num has not be sent in tx buffer before this sending  */
    Uint16 pri_num = 0;

    /*the current send num*/
    Uint16 cur_num = 0;
    
    uart_handle->regs->IER &= ~0x2;  //disable THR empty interrupt,stop send

    pri_num = uart_handle->tx->num;    
    if (num == 0)
        return 0;   // no datas to send

    /*if send num plus pri_num is larger than buffer max_size*/        
    else if (num >= (UART_BUF_SIZE - pri_num))
    {
        cur_num = UART_BUF_SIZE - pri_num;
    }
    
    else
    {
        cur_num = num;
    }
    
    temp = cur_num;
    while (temp > 0)
    {

        uart_handle->tx->num++;
        *uart_handle->tx->pempty++ = *data++; //write data to tx buffer
        if (uart_handle->tx->pempty == uart_handle->tx->buffer + UART_BUF_SIZE)//reach to buffer end
        {
            uart_handle->tx->pempty = uart_handle->tx->buffer;
        }
        temp--;
        
        /*
        if(uart_handle->tx->num == UART_BUF_SIZE)//the buffer size reached the max num
        {
            break;
        }
        */
    }

    if (pri_num == 0)     // no datas in previous tx buffer,that buffer is null
    {
         uart_handle->tx->num--;
         uart_handle->regs->THR = *uart_handle->tx->pdata; // write the fisrt byte to THR register,clear int event.
         uart_handle->tx->pdata++;
         if (uart_handle->tx->pdata == uart_handle->tx->buffer + UART_BUF_SIZE)
         {
            uart_handle->tx->pdata = uart_handle->tx->buffer;
         }
         uart_handle->regs->IER |= 0x2;  //enable THR empty interrupt
    }
    else   //send previous and present datas
    {
        uart_handle->regs->IER |= 0x2;  //enable THR empty interrupt,continous send
    }

    return cur_num;
}


Uint32 EVMDM6437_UART_putchar(UART_Handle uart_handle, unsigned char data)
{
	return EVMDM6437_UART_putdata(uart_handle, &data, 1);	
}

 

 Uint32 EVMDM6437_UART_putstring(UART_Handle uart_handle, unsigned char *data)
 {
 	Uint16 num = 0;
	unsigned char *p = data;
	
	while(* p++)num++;
	return EVMDM6437_UART_putdata(uart_handle, data, num);


	
 }

Uint32 EVMDM6437_UART_getdata( UART_Handle uart_handle, unsigned char* data ,Uint16 num)
{
    int len = 0;
	
    while ((uart_handle->rx->num > 0) && (num > 0))
    {
        uart_handle->rx->num--;
        num--;
        len++;
        *data++ = *uart_handle->rx->pdata++;

        if(uart_handle->rx->pdata == uart_handle->rx->buffer + UART_BUF_SIZE)
        {
            uart_handle->rx->pdata = uart_handle->rx->buffer;
        }
    }

    return len;

}


Uint32 EVMDM6437_UART_delchar(UART_Handle uart_handle ,Uint16 num)
{
	unsigned char tem;
	int ret = 0;
	Uint16 i = num;
	while(i --)
	{
		ret += EVMDM6437_UART_getdata(uart_handle, &tem, 1);
	}
	return ((ret == num) ?  0:-1);	
}


Uint32 EVMDM6437_UART_getnum_rx( UART_Handle uart_handle )
{
	return uart_handle->rx->num;	
}



