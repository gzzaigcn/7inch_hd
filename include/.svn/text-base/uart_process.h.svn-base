/******************************************************************************

   Copyright (C), 2013-,    Zjut Image Processing Lab.    All rights reserved. 

*******************************************************************************
 * File Name : uart_process.h
 * Version : 1.0
 * Author : Gzz
 * Created : 2013/8/5
 * Last Modified :
 * Description : uart_process.c header file
 * Function List :
 * Modification History :
   1.Date : 2013/8/5
     Author : Gzz
     Modification : Created file
 
******************************************************************************/
#ifndef __UART_PROCESS_H__
#define __UART_PROCESS_H__

#include "dm6437.h"
#include "dm6437_uart.h"

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */



/************************CMD from PC to DM6437*********************************************/
#define PC_CMD_CHECK_CONNECT_DSP 0x1c643700                //check connect DM6437 and PC by Uart1
#define PC_CMD_CHECK_CONNECT_IMPLANT 0x1c643701        //checck connect DM6437 and PC by Uart1
#define PC_CMD_QUERY_SW_VERSION 0x1c643702                 //query dsp device info and software version
#define PC_CMD_MEASURE_IMPEDANCE 0x1c643703                // measure electrode impedance
#define PC_CMD_ELECTRODE_PRESTIMULATE  0x1c643704 // 24 electrodes prestimulate 
#define PC_CMD_UPDATE_ELECTRODE_PUB_PARAM  0x1c643705 // update electrode public params
#define PC_CMD_MULTI_ELECTRODE_STIMULATE  0x1c643706         // update electrode private params,then multile stimulate 
#define PC_CMD_SAVE_CONFIG_PARAM 0x1c643707                          //save all implant config params to flash
#define PC_CMD_GET_CONFIG_PARAM 0x1c643708                        //get all implant config params from dsp
#define PC_CMD_CLEAR_CONFIG_PARAM 0x1c643709                      //clear all implant config params in flash
#define PC_CMD_UPDATA_FW 0x1c64370a      //updata dsp fireware
#define PC_CMD_EXIT_SERIAL_DEBUG 0x1c64370b      //updata dsp fireware

/********************ACK from PC to DM6437*******************************************/
#define PC_ACK_SUCCESS  0x1c6437fd  // ACK from PC ,communicate success
#define PC_ACK_FAILURE  0x1c6437ff // ACK from PC, occur error



/******************Macro for implant test *********************/
#define PC_CMD_Swave  0x1c643705
#define PC_CMD_LS  0x1c643706
#define PC_CMD_FREEZE  0x1c643707

#define PC_CMD_CS  0x1c643708
#define PC_CMD_PLUS_GAP  0x1c643709
#define PC_CMD_PLUS_WD 0x1c64370a
#define PC_CMD_ST_MODE 0x1c64370b


/************************CMD from DM6437 to PC*********************************************/
#define DM6437_CMD_PACKET_DEF_ID 0x0001 // default packet id 
#define DM6437_CMD_PC_CONNECT                 0x64371c00   // pc connect dsp 
#define DM6437_CMD_IMPLANT_CONNECT       0x64371c01  //dsp connect implant
#define DM6437_CMD_IMPLANT_DISCONNECT      0x64371c02 // dsp disconnect implant

#define DM6437_CMD_UPLOAD_SW_INFO  0x64371c03            //upload device info and software version to PC
#define DM6437_CMD_UPLOAD_IMPEDANCE 0x64371c04           //upload be measured impedance
#define DM6437_CMD_UPLOAD_ELECTRODE_PRI_PARAM 0x64371c05    //upload electrode private param when prestimulate
#define DM6437_CMD_UPLOAD_CONFIG_PARAM 0x64371c06         //uploade dsp all config param

#define DM6437_UPDATA_FW_SUCCESS 0x64371cf0
#define DM6437_UPDATA_FW_FAILURE 0x64371cf1

#define DM6437_ACK_SUCCESS          0x64371cfd
#define DM6437_ACK_OVERRUN         0x64371cfe
#define DM6437_ACK_FAILURE          0x64371cff



/*Uart Packet header information*/
typedef struct{
    Uint32 cmd;
    Uint32 num;
}uart_packet_header;
#define UART_PACKET_HEAD_SIZE   sizeof(uart_packet_header)

typedef uart_packet_header * uart_packet_header_handle;

/*Uart Packet stuct definition*/
typedef struct{
    uart_packet_header p_head;
    Uint8   buf[UART_BUF_SIZE -UART_PACKET_HEAD_SIZE -4];
    Uint32 crc;
}uart_packet;

typedef uart_packet* uart_packet_handle;


extern Int32 ASC2INT(Uint8 *pBuf, Uint32 Start, Uint32 End);
extern void cmd_wait_ack(Uint32 cmd);
extern void packet_wait_ack();

extern void serial_process();

extern void uart1_ack();
extern void  uart1_init(  );
extern void uart1_poll();
extern Uint8 uart1_recv_packet();
extern void uart1_resend();
extern void uart1_send_cmd(Uint32 cmd);
extern void uart1_send_packet(Uint32 cmd, Uint8 *buf, Uint32 buf_size, Uint32 packet_id);

extern unsigned int update_crc(unsigned int *data_ptr, unsigned int section_size, unsigned int crc);


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __UART_PROCESS_H__ */
