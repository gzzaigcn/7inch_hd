/******************************************************************************

   Copyright (C), 2013-,    Zjut Image Processing Lab.    All rights reserved. 

*******************************************************************************
 * File Name : wireless_rf.h
 * Version : 1.0
 * Author : Gzz
 * Created : 2013/8/8
 * Last Modified :
 * Description : wireless_rf.c header file
 * Function List :
 * Modification History :
   1.Date : 2013/8/8
     Author : Gzz
     Modification : Created file
 
******************************************************************************/

#ifndef __WIRELESS_RF_H__
#define __WIRELESS_RF_H__

#include "dm6437.h"
#include "dm6437_gpio.h"

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#define RF_GPIO_ID GPIO13
#define MCBSP1_GPIO_ID GPIO107

#define PINMUX_MCBSP1_DX     0
#define PINMUX_MCBSP1_GPIO 1

#define RF_SEND_BUF_SIZE 1000*1024 // 10K
#define RF_RECV_BUF_SIZE  256 // 

/*MCBSP1 4Byte every ARRAY
wf init 4x6 lattices by send 1ms s-wave = 400 Bytes¡£20ms = 8000 bytes*/
#define SWAVE_BYTES_SIZE(mills)  mills*400


#define BIT0_MASK 0x01
#define BIT1_MASK 0x02
#define BIT2_MASK 0x04
#define BIT3_MASK 0x08
#define BIT4_MASK 0x10
#define BIT5_MASK 0x20
#define BIT6_MASK 0x40
#define BIT7_MASK 0x80


/*Wireless RF and Lattice 4X6 Communication Protocol*/
#define RF_BIT0 (0)
#define RF_BIT1 (1)
#define LOGIC_0  ((RF_BIT1 << 2) | (RF_BIT0 << 1) | (RF_BIT0))  // 100B
#define LOGIC_1  ((RF_BIT1 << 2) | (RF_BIT1 << 1) | (RF_BIT0))  // 110B
#define DATA_SYNC  ((RF_BIT1 << 5) | (RF_BIT1 << 4) | (RF_BIT1 << 3) | (RF_BIT1 << 2) | (RF_BIT0 << 1) | (RF_BIT0))  //111100B
#define CMD_SYNC  ((RF_BIT1 << 5) | (RF_BIT1 << 4) | (RF_BIT1 << 3) | (RF_BIT1 << 2) | (RF_BIT1 << 1) | (RF_BIT0)) //111110B
#define SYNC_TYPE_LEN  6



/*MCBSP 24bit = 3Byte ecery ARRAY
   wf init 4x6 lattices by send 200ms s-wave = 80000 Bytes¡£20ms = 8000 bytes
*/
#define MCBSP1_EDMA_AIDX 4
#define INIT_LATTICE_CYCLE     8000
//#define INIT_LATTICE_DATA_LEN (INIT_LATTICE_CYCLE/3)+1
#define INIT_LATTICE_DATA_LEN 2000

typedef enum 
{
    IMPLANT_SET_LEVEL_CMD = 0,
    IMPLANT_FREEZE_LEVEL_CMD,
    RF_CMD,
    RF_DATA 
}RF_PACKET_TYPE;


typedef struct
{
    
  Uint8 *buf;
  Uint16 data_bytes_size;
  Uint16 swave_mills;
  RF_PACKET_TYPE type;
    
}rf_packet;

typedef rf_packet* rf_packet_handle;

/*
typedef struct
{

   Uint32 header;
   Uint8 buf[255];
   
}rf_recv_packet;

typedef rf_recv_packet* rf_recv_packet_handle;
*/


extern void switch_mcbsp1_pinmux_mode(Uint8 mcbsp1_pinmux);
extern void set_mcbsp1_edma_param(Uint32 src_address, Uint16 acnt, Uint16 bcnt, Uint32 channel);
extern void start_mcbsp1_edma();
extern void  start_timer0();
extern void stop_timer0();
extern void timer0_init(Uint32 times);

extern void timer0_12_init(Uint32 times);
extern void start_timer0_12();
extern void stop_timer0_12();


extern void config_send_packet_handle(Uint8 *buf, Uint32 buf_size, Uint32 swave_mills, RF_PACKET_TYPE type);
extern void wait_mcbsp1_edma();
extern void wireless_rf_init();
extern Uint8 wireless_rf_recv_data(Uint8 flag, Uint32 delay);
extern void wireless_rf_send_cmd(rf_packet_handle send_packet_handle);
extern void wireless_rf_send_data(rf_packet_handle send_packet_handle, Uint8 electrode_num);
extern void wireless_rf_send_Swave(Uint32 time_ms);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __WIRELESS_RF_H__ */
