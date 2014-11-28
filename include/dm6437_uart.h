/*
 *  Copyright 2006 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

/*
 *  UART Header file
 *
 */

#ifndef UART_
#define UART_

#include "dm6437.h"

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  UART regs                                                               *
 *                                                                          *
 * ------------------------------------------------------------------------ */
typedef struct {
    volatile Uint32 RBR;
    volatile Uint32 IER;
    volatile Uint32 IIR;
    volatile Uint32 LCR;
    volatile Uint32 MCR;
    volatile Uint32 LSR;
    Uint32 rsvd_18;
    Uint32 rsvd_1c;
    volatile Uint32 DLL;
    volatile Uint32 DLH;
    volatile Uint32 PID1;
    volatile Uint32 PID2;
    volatile Uint32 PWREMU_MGMT;
} UART_REGS;

#define THR     RBR    // THR & RBR occupy the same memory location
#define FCR     IIR    // FCR & IIR occupy the same memory location

/*Set UART parameters */
/*Set Baud rate */
#define baud_2k4	703
#define baud_4k8	352
#define baud_9k6	176
#define baud_19k2	88
#define baud_38k4	44
#define baud_56k	30
#define baud_115k2	15
#define baud_128k	13
/*word length Set*/
#define data_w5     0x00 /*length=5*/
#define data_w6     0x01 /*length=6*/
#define data_w7     0x02 /*length=7*/
#define data_w8     0x03 /*length=8*/

#define data_s1     0x00 /*1 stop bit*/
#define data_s2     0x04 /*1.5 or 2 stop bit*/

#define data_p      0x0000 /*no parity*/
#define data_po     0x0008 /*odd parity*/
#define data_pe     0x0018 /*even parity*/


#define UART_BUF_SIZE     4096

typedef struct
{
	volatile int num;
	volatile Uint8 *pdata;
	volatile Uint8 *pempty;
	volatile Uint8 *buffer;
	 
}UART_QUEUE;

typedef struct 
{
    UART_REGS* regs;
	UART_QUEUE* rx;
	UART_QUEUE* tx; 
} UART_OBJ;


typedef enum
{
    UART_THREINT = 1,
    UART_RADINT  = 2,
    UART_RLSINT = 3,
    UART_RTOINT = 6
}UART_INT_TYPE;

//static UART_REGS* UART_MODULE_0 =  (UART_REGS* )UART0_BASE;
//static UART_REGS* UART_MODULE_1 =  (UART_REGS* )UART1_BASE;

typedef UART_OBJ* UART_Handle;

extern UART_OBJ uart_obj0,uart_obj1;
extern UART_QUEUE uart0_rx, uart1_rx, uart0_tx, uart1_tx;


/* ------------------------------------------------------------------------ *
 *  Prototypes                                                              *
 * ------------------------------------------------------------------------ */
UART_Handle EVMDM6437_UART_open(Uint16 UartId,
								   Uint16 UartBaud,
								   Uint8 UartWordLen,
								   Uint8 UartStopBits,
								   Uint8 UartParity
								   );

UART_Handle EVMDM6437_UART_get_handle(Uint16 UartId);


Uint32 EVMDM6437_UART_close( UART_Handle UartHandle );
Uint32 EVMDM6437_UART_putchar( UART_Handle UartHandle, unsigned char data );
Uint32 EVMDM6437_UART_findchar(UART_Handle uart_handle, unsigned char data);
Uint32 EVMDM6437_UART_getdata( UART_Handle uart_handle, unsigned char * data ,Uint16 num);
Uint32 EVMDM6437_UART_putdata( UART_Handle uart_handle, unsigned char * data, Uint16 num);
Uint32 EVMDM6437_UART_getnum_rx( UART_Handle uart_handle );
Uint32 EVMDM6437_UART_putstring(UART_Handle uart_handle, unsigned char *data);
Uint32 EVMDM6437_UART_delchar(UART_Handle uart_handle ,Uint16 num);

#endif
