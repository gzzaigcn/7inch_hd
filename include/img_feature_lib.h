/******************************************************************************

   Copyright (C), 2013-,    Zjut Image Processing Lab.    All rights reserved. 

*******************************************************************************
 * File Name : img_feature_table.h
 * Version : 1.0
 * Author : Gzz
 * Created : 2013/9/16
 * Last Modified :
 * Description : img_feature_table.c header file
 * Function List :
 * Modification History :
   1.Date : 2013/9/16
     Author : Gzz
     Modification : Created file
 
******************************************************************************/

#ifndef __IMG_FEATURE_LIB_H__
#define __IMG_FEATURE_LIB_H__

#include "dm6437.h"

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/*all feature temp number */
#define FEATURE_TMEP_NUM 128*3


/*declare 0-9 image featrue template that normal*/
extern Uint8  temp_array_0[];
extern Uint8  temp_array_1[];
extern Uint8  temp_array_2[];
extern Uint8  temp_array_3[];
extern Uint8  temp_array_4[];
extern Uint8  temp_array_5[];
extern Uint8  temp_array_6[];
extern Uint8  temp_array_7[];
extern Uint8  temp_array_8[];
extern Uint8  temp_array_9[];

/*declare 0-9 image featrue template that turn left by 5 degree*/
extern Uint8  temp_array_0L[];
extern Uint8  temp_array_1L[];
extern Uint8  temp_array_2L[];
extern Uint8  temp_array_3L[];
extern Uint8  temp_array_4L[];
extern Uint8  temp_array_5L[];
extern Uint8  temp_array_6L[];
extern Uint8  temp_array_7L[];
extern Uint8  temp_array_8L[];
extern Uint8  temp_array_9L[];

/*declare 0-9 image featrue template that turn right by 5 degree*/
extern Uint8  temp_array_0R[];
extern Uint8  temp_array_1R[];
extern Uint8  temp_array_2R[];
extern Uint8  temp_array_3R[];
extern Uint8  temp_array_4R[];
extern Uint8  temp_array_5R[];
extern Uint8  temp_array_6R[];
extern Uint8  temp_array_7R[];
extern Uint8  temp_array_8R[];
extern Uint8  temp_array_9R[];



/*declare A-Z image featrue template that normal*/
extern Uint8  temp_array_A[];

extern Uint8  temp_array_B[];

extern Uint8  temp_array_C[];

extern Uint8  temp_array_D[];

extern Uint8  temp_array_E[];

extern Uint8  temp_array_F[];

extern Uint8  temp_array_G[];

extern Uint8  temp_array_H[];

extern Uint8  temp_array_I[];

extern Uint8  temp_array_J[];

extern Uint8  temp_array_K[];

extern Uint8  temp_array_L[];

extern Uint8  temp_array_M[];

extern Uint8  temp_array_N[];

extern Uint8  temp_array_O[];

extern Uint8  temp_array_P[];

extern Uint8  temp_array_Q[];

extern Uint8  temp_array_R[];

extern Uint8  temp_array_S[];

extern Uint8  temp_array_T[];

extern Uint8  temp_array_U[];

extern Uint8  temp_array_V[];

extern Uint8  temp_array_W[];

extern Uint8  temp_array_X[];

extern Uint8  temp_array_Y[];

extern Uint8  temp_array_Z[];

/*declare A-Z image featrue template that turn left by 5 degree*/
extern Uint8  temp_array_AL[];

extern Uint8  temp_array_BL[];

extern Uint8  temp_array_CL[];

extern Uint8  temp_array_DL[];

extern Uint8  temp_array_EL[];

extern Uint8  temp_array_FL[];

extern Uint8  temp_array_GL[];

extern Uint8  temp_array_HL[];

extern Uint8  temp_array_IL[];

extern Uint8  temp_array_JL[];

extern Uint8  temp_array_KL[];

extern Uint8  temp_array_LL[];

extern Uint8  temp_array_ML[];

extern Uint8  temp_array_NL[];

extern Uint8  temp_array_OL[];

extern Uint8  temp_array_PL[];

extern Uint8  temp_array_QL[];

extern Uint8  temp_array_RL[];

extern Uint8  temp_array_SL[];

extern Uint8  temp_array_TL[];

extern Uint8  temp_array_UL[];

extern Uint8  temp_array_VL[];

extern Uint8  temp_array_WL[];

extern Uint8  temp_array_XL[];

extern Uint8  temp_array_YL[];

extern Uint8  temp_array_ZL[];


/*declare A-Z image featrue template that turn right by 5 degree*/
extern Uint8  temp_array_AR[];

extern Uint8  temp_array_BR[];

extern Uint8  temp_array_CR[];

extern Uint8  temp_array_DR[];

extern Uint8  temp_array_ER[];

extern Uint8  temp_array_FR[];

extern Uint8  temp_array_GR[];

extern Uint8  temp_array_HR[];

extern Uint8  temp_array_IR[];

extern Uint8  temp_array_JR[];

extern Uint8  temp_array_KR[];

extern Uint8  temp_array_LR[];

extern Uint8  temp_array_MR[];

extern Uint8  temp_array_NR[];

extern Uint8  temp_array_OR[];

extern Uint8  temp_array_PR[];

extern Uint8  temp_array_QR[];

extern Uint8  temp_array_RR[];

extern Uint8  temp_array_SR[];

extern Uint8  temp_array_TR[];

extern Uint8  temp_array_UR[];

extern Uint8  temp_array_VR[];

extern Uint8  temp_array_WR[];

extern Uint8  temp_array_XR[];

extern Uint8  temp_array_YR[];

extern Uint8  temp_array_ZR[];


/*declare a-z image featrue template that normal*/
extern Uint8  temp_array_a[];

extern Uint8  temp_array_b[];

extern Uint8  temp_array_c[];

extern Uint8  temp_array_d[];

extern Uint8  temp_array_e[];

extern Uint8  temp_array_f[];

extern Uint8  temp_array_g[];

extern Uint8  temp_array_h[];

extern Uint8  temp_array_i[];

extern Uint8  temp_array_j[];

extern Uint8  temp_array_k[];

extern Uint8  temp_array_l[];

extern Uint8  temp_array_m[];

extern Uint8  temp_array_n[];

extern Uint8  temp_array_o[];

extern Uint8  temp_array_p[];

extern Uint8  temp_array_q[];

extern Uint8  temp_array_r[];

extern Uint8  temp_array_s[];

extern Uint8  temp_array_t[];

extern Uint8  temp_array_u[];

extern Uint8  temp_array_v[];

extern Uint8  temp_array_w[];

extern Uint8  temp_array_x[];

extern Uint8  temp_array_y[];

extern Uint8  temp_array_z[];

/*declare a-z image featrue template that turn left by 5 degree*/
extern Uint8  temp_array_aL[];

extern Uint8  temp_array_bL[];

extern Uint8  temp_array_cL[];

extern Uint8  temp_array_dL[];

extern Uint8  temp_array_eL[];

extern Uint8  temp_array_fL[];

extern Uint8  temp_array_gL[];

extern Uint8  temp_array_hL[];

extern Uint8  temp_array_iL[];

extern Uint8  temp_array_jL[];

extern Uint8  temp_array_kL[];

extern Uint8  temp_array_lL[];

extern Uint8  temp_array_mL[];

extern Uint8  temp_array_nL[];

extern Uint8  temp_array_oL[];

extern Uint8  temp_array_pL[];

extern Uint8  temp_array_qL[];

extern Uint8  temp_array_rL[];

extern Uint8  temp_array_sL[];

extern Uint8  temp_array_tL[];

extern Uint8  temp_array_uL[];

extern Uint8  temp_array_vL[];

extern Uint8  temp_array_wL[];

extern Uint8  temp_array_xL[];

extern Uint8  temp_array_yL[];

extern Uint8  temp_array_zL[];


/*declare a-z image featrue template that turn right by 5 degree*/
extern Uint8  temp_array_aR[];

extern Uint8  temp_array_bR[];

extern Uint8  temp_array_cR[];

extern Uint8  temp_array_dR[];

extern Uint8  temp_array_eR[];

extern Uint8  temp_array_fR[];

extern Uint8  temp_array_gR[];

extern Uint8  temp_array_hR[];

extern Uint8  temp_array_iR[];

extern Uint8  temp_array_jR[];

extern Uint8  temp_array_kR[];

extern Uint8  temp_array_lR[];

extern Uint8  temp_array_mR[];

extern Uint8  temp_array_nR[];

extern Uint8  temp_array_oR[];

extern Uint8  temp_array_pR[];

extern Uint8  temp_array_qR[];

extern Uint8  temp_array_rR[];

extern Uint8  temp_array_sR[];

extern Uint8  temp_array_tR[];

extern Uint8  temp_array_uR[];

extern Uint8  temp_array_vR[];

extern Uint8  temp_array_wR[];

extern Uint8  temp_array_xR[];

extern Uint8  temp_array_yR[];

extern Uint8  temp_array_zR[];

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __IMG_FEATURE_LIB_H__ */
