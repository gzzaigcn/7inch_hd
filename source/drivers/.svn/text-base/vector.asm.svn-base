

*
* Copyright (C) 2003 Texas Instruments Incorporated
* All Rights Reserved
*
*
*---------vecs_timer1.asm---------
*
* Assembly file to set up interrupt service table (IST)
*

*------------------------------------------------------------------------------
* Global symbols defined here and exported out of this file
*------------------------------------------------------------------------------
   .global _vectors
   .global _c_int00
   .global _vector1
   .global _vector2
   .global _vector3
   .global _vector4
   .global _Int_Uart1ISR
   .global _Int_CcdcISR
   .global _Int_ResizeISR
   .global _Int_PreviewISR
   .global _Int_H3aISR
   .global _Int_HistISR
   .global _Int_VencISR
   .global _Int_Timer0_12ISR
   .global _Int_Timer0_34ISR
   .global _Int_Timer1_12ISR
   .global _Int_Timer1_34ISR
   .global _Int_PWM0ISR
   .global _Int_PWM1ISR
   .global _Int_GPIOBANK0ISR
   .global _Int_GPIOBANK1ISR
   .global _Int_Edma3ISR
   .global _vector15

*------------------------------------------------------------------------------
* Global symbols referenced in this file but defined somewhere else. 
* Remember that your interrupt service routines need to be referenced here.
*------------------------------------------------------------------------------
   .ref _c_int00
   .ref _Int_GPIOBANK0ISR
   .ref _Int_Timer0_12ISR
   .ref _Int_Timer0_34ISR
   .ref _Int_Timer1_12ISR   
   .ref _Int_Timer1_34ISR
   .ref _Int_PWM0ISR
   .ref _Int_ResizeISR
   .ref _Int_VencISR
   .ref _Int_CcdcISR
   .ref _Int_Uart1ISR
   .ref _Int_Edma3ISR
   .ref _Int_PreviewISR
   .ref _Int_H3aISR
   .ref _Int_HistISR
   
*------------------------------------------------------------------------------
* This is a macro that instantiates one entry in the interrupt service table.
*------------------------------------------------------------------------------
VEC_ENTRY .macro addr
    STW   B0,*--B15
    MVKL  addr,B0
    MVKH  addr,B0
    B     B0
    LDW   *B15++,B0
    NOP   2
    NOP   
    NOP   
   .endm


*------------------------------------------------------------------------------
* This is a dummy interrupt service routine used to initialize the IST.
*------------------------------------------------------------------------------
_vec_dummy:
  B    B3
  NOP  5

*------------------------------------------------------------------------------
* This is the actual interrupt service table (IST). It is properly aligned and
* is located in the subsection .text:vecs. This means if you do not explicitly
* specify this section in your linker command file, it will default and link
* into the .text section. Remember to set the ISTP register to point to this
* table.
*------------------------------------------------------------------------------
 .sect ".vectors"
 ;.align 1024

_vectors:
_vector0:   VEC_ENTRY _c_int00    ;RESET
_vector1:   VEC_ENTRY _vec_dummy  ;NMI
_vector2:   VEC_ENTRY _vec_dummy  ;RSVD
_vector3:   VEC_ENTRY _vec_dummy
_vector4:   VEC_ENTRY _vec_dummy
_vector5:   VEC_ENTRY _Int_H3aISR
_vector6:   VEC_ENTRY _Int_PreviewISR
_vector7:   VEC_ENTRY _Int_HistISR
_vector8:   VEC_ENTRY _Int_Uart1ISR
_vector9:   VEC_ENTRY _Int_ResizeISR
_vector10:  VEC_ENTRY _Int_VencISR
_vector11:  VEC_ENTRY _Int_Edma3ISR
_vector12:  VEC_ENTRY _Int_CcdcISR
_vector13:  VEC_ENTRY _Int_PWM0ISR
_vector14:  VEC_ENTRY _vec_dummy
_vector15:  VEC_ENTRY _vec_dummy

*------------------------------------------------------------------------------


