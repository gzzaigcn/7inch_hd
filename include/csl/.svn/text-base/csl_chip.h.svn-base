/*   ==========================================================
 *   Copyright (c) Texas Instruments Inc , 2004
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied
 *   priovided
 *   ==========================================================
*/
/** @file csl_chipGem.h
 *
 *  @brief CSL chip APIs, data structures
 *
 *  Description
 *	- All API's used for accessing(read/write) of control
 *  registers are documented here.
 *  @date 15th Apr, 2004
 */
/** 
@defgroup CSL_CHIP CSL Chip Module 
*/
#ifndef _CSL_CHIP_H_
#define _CSL_CHIP_H_
#include <csl.h>
#include <cslr_chip.h>


/**************************************************************************\
* CHIP global macro declarations
\**************************************************************************/
/**************************************************************************\
* CHIP global typedef declarations
\**************************************************************************/
/**
@addtogroup CSL_CHIP
@{
*/typedef enum  {
	AMR = 0,
	CSR = 1,
	IFR = 2,
	ISR = 2,
	ICR = 3,
	IER = 4,
	ISTP= 5,
	IRP= 6,
	NRP= 7,
	ERP= 7,    
	TSCL= 10,
	TSCH= 11,
	ARP= 12,
	ILC= 13,
	RILC= 14,
	PCE1= 16,
	DNUM= 17,    
	SSR= 21,
	GPLYA= 22,
	GPLYB= 23,
	GFPGFR= 24,
	DIER= 25,
	TSR= 26,
	ITSR= 27,
	NTSR= 28,
	ETSR= 28,
	EFR= 29,
	ECR= 29,
	IERR= 31
}CSL_ChipReg;

/**
@}
*/
/**************************************************************************\
* CHIP global function declarations
\**************************************************************************/
/*
@addtogroup CSL_CHIP
@{
@brief This API does the Chip initialization
*/
void  _CSL_chipInit(
    void
);
/**
@}
*/
/**
@addtogroup CSL_CHIP
@{
@brief This API writes specified control registers with the 
   specificied value 'val'.
   
 * Writes into the specified control chip register.
 *
 * @b Example:
 * @verbatim

 	Uint32 oldamr;
 	oldamr = CSL_chipWritereg(AMR,56);

 * @endverbatim
 * 
 * @return Old value of programmed register
 * 
 */
Uint32  CSL_chipWriteReg(
    CSL_ChipReg               reg,
    CSL_Reg32                 val
);
/**
@}
*/
/**
@addtogroup CSL_CHIP
@{
@brief This API reads the specified control register.

   
 * Writes into the specified control chip register.
 *
 * @b Example:
 * @verbatim

 	Uint32 oldamr;
 	oldamr = CSL_chipReadReg(AMR);

 * @endverbatim
 * 
 * @return Value to be read
 * 
 */
Uint32  CSL_chipReadReg(
    CSL_ChipReg               reg
);
/**
@}
*/

#endif
