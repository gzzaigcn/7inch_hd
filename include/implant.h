/******************************************************************************

   Copyright (C), 2013-,    Zjut Image Processing Lab.    All rights reserved. 

*******************************************************************************
 * File Name : implant.h
 * Version : 1.0
 * Author : Gzz
 * Created : 2013/10/30
 * Last Modified :
 * Description : implant.c header file
 * Function List :
 * Modification History :
   1.Date : 2013/10/30
     Author : Gzz
     Modification : Created file
 
******************************************************************************/
#ifndef __IMPLANT_H__
#define __IMPLANT_H__

#include "dm6437.h"
#include "norflash.h"

/*Macro for implant and electrodes imformation */
#define IMPLANT_ELECTRODE_NUM 4*6

#define IMPLANT_ELECTRODE_1    1
#define IMPLANT_ELECTRODE_2    2
#define IMPLANT_ELECTRODE_3    3
#define IMPLANT_ELECTRODE_4    4
#define IMPLANT_ELECTRODE_5    5
#define IMPLANT_ELECTRODE_6    6
#define IMPLANT_ELECTRODE_7    7
#define IMPLANT_ELECTRODE_8    8
#define IMPLANT_ELECTRODE_9    9
#define IMPLANT_ELECTRODE_10  10
#define IMPLANT_ELECTRODE_11  11
#define IMPLANT_ELECTRODE_12  12
#define IMPLANT_ELECTRODE_13  13
#define IMPLANT_ELECTRODE_14  14
#define IMPLANT_ELECTRODE_15  15
#define IMPLANT_ELECTRODE_16  16
#define IMPLANT_ELECTRODE_17  17
#define IMPLANT_ELECTRODE_18  18
#define IMPLANT_ELECTRODE_19  19
#define IMPLANT_ELECTRODE_20  20
#define IMPLANT_ELECTRODE_21  21
#define IMPLANT_ELECTRODE_22  22
#define IMPLANT_ELECTRODE_23  23
#define IMPLANT_ELECTRODE_24  24

#define IMPEDANCE_BYTES 200

#define SWAP2(byte16)                  ((byte16 >> 8) |(byte16 << 8))
#define BYTE16_MSB(byte16)        ((byte16 >> 8) & 0xff)
#define BYTE16_LSB(byte16)          (byte16 & 0xff)

#define STIMULATION_FRQ_LEVEL 2


/*Macro default Implant global param about RF init cmd and return value from implant*/
#define DEF_DEVICE_NAME "DSP_VISIO_24A"
#define DEF_PROGRAM_NAME "AV_DSP.0"


#define DEF_SET_CS_POSITIVE_MODE 0xCF81
#define DEF_SET_CS_NEGATIVE_MODE  0xD601
#define DEF_SET_PULSE_GAP               0x4D28 // 5us gap
#define DEF_SET_PULSE_WIDTH          0x5065 // 50us plus width
#define DEF_SET_STIMULATION_MODE  0x4741
#define DEF_SET_STIMULATION_FRQ  STIMULATION_FRQ_LEVEL
#define DEF_SET_CHANNEL_NUM IMPLANT_ELECTRODE_NUM
#define DEF_SET_STIMULATE_NUM   8
#define DEF_SET_STIMULATE_INTERVAL 500
#define DEF_SET_STIMULATE_TIME 500

/*Macro for setting LEVEL SHIFT that IMPLANT*/
#define IMPLANT_LEVEL_CHECK_CMD   0x4ef7
#define IMPLANT_LEVEL_FREEZE_CMD 0xffff
#define IMPLANT_LINK_CHECK_CMD 0x0801
#define IMPLANT_INIT_INPUT_CMD_BIT_LEN  32
#define IMPLANT_INIT_INPUT_CMD_BYTE_LEN  (IMPLANT_INIT_INPUT_CMD_BIT_LEN >> 3)
#define IMPLANT_INIT_CMD_ACK_BIT_LEN  12
#define IMPLANT_LINKCHECK_CMD_ACK_BIT_LEN 6

/*Macro for default electrode private param in HR_I Encode stimulate*/
#define DEF_SET_PHASE1 0
#define DEF_SET_PHASE2 1
#define DEF_STIMULATE_AMP 128 //max:0xff

/*Macro for implant electrode impedance measurement*/
#define IMPEDANCE_MEASURE_CMD1 0xCF82
#define IMPEDANCE_MEASURE_CMD2 0xD608 
#define IMPEDANCE_MEASURE_CMD3 0x4c51  
#define IMPEDANCE_MEASURE_CMD4 0x5050 
#define IMPEDANCE_MEASURE_CMD5 0x4741

#define IMPEDANCE_MEASURE_EFI_CMD5  0x9000


/*Macro for ADC sample rate for impedance measurement*/
#define ADC_SAMPLE_RATE_2US   0x00
#define ADC_SAMPLE_RATE_4US   0x01
#define ADC_SAMPLE_RATE_8US 0x02
#define ADC_SAMPLE_RATE_16US 0x03
#define ADC_VLOTAGE_GAIN 0

typedef  enum {

     IMPLANT_STATE_CONNECT = 0,
     IMPLANT_STATE_DISCONNECT, 
     IMPLANT_INIT_OK,
     IMPLANT_INIT_ERROR
     
}IMPLANT_STATE;


#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

extern void set_HRI_forst_data_buf();
extern void clear_HRI_forst_data_buf();

extern void update_HRI_forst_data_buf(Uint8 electrode_id, Uint16 encoded_word);

extern  void calulate_even_parity(Uint32 *data, Uint32 bit_size);
extern Uint8 check_even_parity(Uint32 data, Uint32 bit_size);

extern Uint8 check_implant_link_state();

extern Uint16 electrode_HR1_encode(Uint8 electrode_id, Uint8 firstph1, Uint8 secondph1, Uint8 amp);
extern Uint8 electrode_impedance_cmd_init();

extern void freeze_implant_level_shift();

extern IMPLANT_STATE implant_init();
extern IMPLANT_STATE  wait_implant_link();

extern Uint8 parse_impedance(Uint16 *pos_imped, Uint16 *neg_imped);

extern Uint8 extract_impedance_values();

extern Uint8 measure_one_electrode_impedance(Uint8 electrode_id);

extern void send_electrode_measure_cmd(Uint16 elf_cmd);

extern Uint8 send_implant_cmd(Uint16 cmd);

extern Uint8 set_implant_cmd_sequence();
extern void set_implant_level_shift();

extern void start_all_electrode_forestimulate();
extern void start_multi_electrode_forestimulate(Uint8 electrode_id[], Uint8 electrode_num);
extern void start_one_electrode_forestimulate(Uint8 electrode_id);
extern void realy_electrode_forestimulate(Uint8 char_ascii);

extern Uint8 *get_electrode_image(Uint8 img_ascii);
extern Uint8 * get_electrode_4x6_map(Uint8 img_ascii);

extern void set_electrode_stimulate_num(handle_electrode_public_param params);

extern void set_two_electrode_stimulate_interval(handle_electrode_public_param params, Uint8 electrode_num);

extern void timer0_34_init(Uint32 times);

extern void start_timer0_34();

void stop_timer0_34();

extern void init_electrode_image_lib();

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __IMPLANT_H__ */
