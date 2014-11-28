/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005                 
 *                                                                              
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.             
 *   ===========================================================================
 */
 
 /** \file cslr_memprot_L1D.h
 * 
 * \brief This file contains the Register Desciptions for MEMPROT_L1D
 * 
 *********************************************************************/
 
#ifndef _CSLR_MEMPROTL1D_H_
#define _CSLR_MEMPROTL1D_H_ 

#include <cslr.h>

#include <tistdtypes.h>

/**************************************************************************\
* Register Overlay Structure
\**************************************************************************/
typedef struct  {
    volatile Uint32 MPFAR;
    volatile Uint32 MPFSR;
    volatile Uint32 MPFCR;
    volatile Uint8 RSVD0[244];
    volatile Uint32 MPLK0;
    volatile Uint32 MPLK1;
    volatile Uint32 MPLK2;
    volatile Uint32 MPLK3;
    volatile Uint32 MPLKCMD;
    volatile Uint32 MPLKSTAT;
    volatile Uint8 RSVD1[232];
    volatile Uint32 MPPA[32];
} CSL_Memprotl1dRegs;

typedef volatile CSL_Memprotl1dRegs  *CSL_Memprotl1dRegsOvly;
/**************************************************************************\
* Field Definition Macros
\**************************************************************************/

/* MPFAR */

#define CSL_MEMPROTL1D_MPFAR_ADDR_MASK   (0xFFFFFFFFu)
#define CSL_MEMPROTL1D_MPFAR_ADDR_SHIFT  (0x00000000u)
#define CSL_MEMPROTL1D_MPFAR_ADDR_RESETVAL (0x00000000u)

#define CSL_MEMPROTL1D_MPFAR_RESETVAL    (0x00000000u)

/* MPFSR */

#define CSL_MEMPROTL1D_MPFSR_RESERVED_MASK (0xFFFF0000u)
#define CSL_MEMPROTL1D_MPFSR_RESERVED_SHIFT (0x00000010u)
#define CSL_MEMPROTL1D_MPFSR_RESERVED_RESETVAL (0x00000000u)

#define CSL_MEMPROTL1D_MPFSR_FID_MASK    (0x0000FE00u)
#define CSL_MEMPROTL1D_MPFSR_FID_SHIFT   (0x00000009u)
#define CSL_MEMPROTL1D_MPFSR_FID_RESETVAL (0x00000000u)

/*----FID Tokens----*/
#define CSL_MEMPROTL1D_MPFSR_FID_FAULT   (0x00000001u)
#define CSL_MEMPROTL1D_MPFSR_FID_OK      (0x00000000u)

#define CSL_MEMPROTL1D_MPFSR_LE_MASK     (0x00000100u)
#define CSL_MEMPROTL1D_MPFSR_LE_SHIFT    (0x00000008u)
#define CSL_MEMPROTL1D_MPFSR_LE_RESETVAL (0x00000000u)

#define CSL_MEMPROTL1D_MPFSR_SECE_MASK   (0x00000080u)
#define CSL_MEMPROTL1D_MPFSR_SECE_SHIFT  (0x00000007u)
#define CSL_MEMPROTL1D_MPFSR_SECE_RESETVAL (0x00000000u)

/*----SECE Tokens----*/
#define CSL_MEMPROTL1D_MPFSR_SECE_FAULT  (0x00000001u)
#define CSL_MEMPROTL1D_MPFSR_SECE_OK     (0x00000000u)

#define CSL_MEMPROTL1D_MPFSR_ATYPE_MASK  (0x0000003Fu)
#define CSL_MEMPROTL1D_MPFSR_ATYPE_SHIFT (0x00000000u)
#define CSL_MEMPROTL1D_MPFSR_ATYPE_RESETVAL (0x00000000u)

/*----ATYPE Tokens----*/
#define CSL_MEMPROTL1D_MPFSR_ATYPE_NONE  (0x00000000u)
#define CSL_MEMPROTL1D_MPFSR_ATYPE_UXE   (0x00000001u)
#define CSL_MEMPROTL1D_MPFSR_ATYPE_UWE   (0x00000002u)
#define CSL_MEMPROTL1D_MPFSR_ATYPE_URE   (0x00000004u)
#define CSL_MEMPROTL1D_MPFSR_ATYPE_SXE   (0x00000008u)
#define CSL_MEMPROTL1D_MPFSR_ATYPE_SWE   (0x00000010u)
#define CSL_MEMPROTL1D_MPFSR_ATYPE_SRE   (0x00000020u)
#define CSL_MEMPROTL1D_MPFSR_ATYPE_INVCLFILL (0x0000003Fu)
#define CSL_MEMPROTL1D_MPFSR_ATYPE_INVCLWB (0x00000012u)

#define CSL_MEMPROTL1D_MPFSR_RESETVAL    (0x00000000u)

/* MPFCR */

#define CSL_MEMPROTL1D_MPFCR_RESERVED_MASK (0xFFFFFFFEu)
#define CSL_MEMPROTL1D_MPFCR_RESERVED_SHIFT (0x00000001u)
#define CSL_MEMPROTL1D_MPFCR_RESERVED_RESETVAL (0x00000000u)

#define CSL_MEMPROTL1D_MPFCR_MPFCLR_MASK (0x00000001u)
#define CSL_MEMPROTL1D_MPFCR_MPFCLR_SHIFT (0x00000000u)
#define CSL_MEMPROTL1D_MPFCR_MPFCLR_RESETVAL (0x00000000u)

/*----MPFCLR Tokens----*/
#define CSL_MEMPROTL1D_MPFCR_MPFCLR_CLEAR (0x00000001u)

#define CSL_MEMPROTL1D_MPFCR_RESETVAL    (0x00000000u)

/* MPLK0 */

#define CSL_MEMPROTL1D_MPLK0_RESERVED_MASK (0xFFFFFFFFu)
#define CSL_MEMPROTL1D_MPLK0_RESERVED_SHIFT (0x00000000u)
#define CSL_MEMPROTL1D_MPLK0_RESERVED_RESETVAL (0x00000000u)

#define CSL_MEMPROTL1D_MPLK0_RESETVAL    (0x00000000u)

/* MPLK1 */

#define CSL_MEMPROTL1D_MPLK1_RESERVED_MASK (0xFFFFFFFFu)
#define CSL_MEMPROTL1D_MPLK1_RESERVED_SHIFT (0x00000000u)
#define CSL_MEMPROTL1D_MPLK1_RESERVED_RESETVAL (0x00000000u)

#define CSL_MEMPROTL1D_MPLK1_RESETVAL    (0x00000000u)

/* MPLK2 */

#define CSL_MEMPROTL1D_MPLK2_RESERVED_MASK (0xFFFFFFFFu)
#define CSL_MEMPROTL1D_MPLK2_RESERVED_SHIFT (0x00000000u)
#define CSL_MEMPROTL1D_MPLK2_RESERVED_RESETVAL (0x00000000u)

#define CSL_MEMPROTL1D_MPLK2_RESETVAL    (0x00000000u)

/* MPLK3 */

#define CSL_MEMPROTL1D_MPLK3_RESERVED_MASK (0xFFFFFFFFu)
#define CSL_MEMPROTL1D_MPLK3_RESERVED_SHIFT (0x00000000u)
#define CSL_MEMPROTL1D_MPLK3_RESERVED_RESETVAL (0x00000000u)

#define CSL_MEMPROTL1D_MPLK3_RESETVAL    (0x00000000u)

/* MPLKCMD */

#define CSL_MEMPROTL1D_MPLKCMD_RESERVED_MASK (0xFFFFFFF8u)
#define CSL_MEMPROTL1D_MPLKCMD_RESERVED_SHIFT (0x00000003u)
#define CSL_MEMPROTL1D_MPLKCMD_RESERVED_RESETVAL (0x00000000u)

#define CSL_MEMPROTL1D_MPLKCMD_KEYR_MASK (0x00000004u)
#define CSL_MEMPROTL1D_MPLKCMD_KEYR_SHIFT (0x00000002u)
#define CSL_MEMPROTL1D_MPLKCMD_KEYR_RESETVAL (0x00000000u)

/*----KEYR Tokens----*/
#define CSL_MEMPROTL1D_MPLKCMD_KEYR_YES  (0x00000001u)
#define CSL_MEMPROTL1D_MPLKCMD_KEYR_NO   (0x00000000u)

#define CSL_MEMPROTL1D_MPLKCMD_LOCK_MASK (0x00000002u)
#define CSL_MEMPROTL1D_MPLKCMD_LOCK_SHIFT (0x00000001u)
#define CSL_MEMPROTL1D_MPLKCMD_LOCK_RESETVAL (0x00000000u)

/*----LOCK Tokens----*/
#define CSL_MEMPROTL1D_MPLKCMD_LOCK_YES  (0x00000001u)
#define CSL_MEMPROTL1D_MPLKCMD_LOCK_NO   (0x00000000u)

#define CSL_MEMPROTL1D_MPLKCMD_UNLOCK_MASK (0x00000001u)
#define CSL_MEMPROTL1D_MPLKCMD_UNLOCK_SHIFT (0x00000000u)
#define CSL_MEMPROTL1D_MPLKCMD_UNLOCK_RESETVAL (0x00000000u)

/*----UNLOCK Tokens----*/
#define CSL_MEMPROTL1D_MPLKCMD_UNLOCK_YES (0x00000001u)
#define CSL_MEMPROTL1D_MPLKCMD_UNLOCK_NO (0x00000000u)

#define CSL_MEMPROTL1D_MPLKCMD_RESETVAL  (0x00000000u)

/* MPLKSTAT */

#define CSL_MEMPROTL1D_MPLKSTAT_RESERVED_MASK (0xFFFFFFFCu)
#define CSL_MEMPROTL1D_MPLKSTAT_RESERVED_SHIFT (0x00000002u)
#define CSL_MEMPROTL1D_MPLKSTAT_RESERVED_RESETVAL (0x00000000u)

#define CSL_MEMPROTL1D_MPLKSTAT_SL_MASK  (0x00000002u)
#define CSL_MEMPROTL1D_MPLKSTAT_SL_SHIFT (0x00000001u)
#define CSL_MEMPROTL1D_MPLKSTAT_SL_RESETVAL (0x00000000u)

/*----SL Tokens----*/
#define CSL_MEMPROTL1D_MPLKSTAT_SL_SEC   (0x00000001u)
#define CSL_MEMPROTL1D_MPLKSTAT_SL_NONSEC (0x00000000u)

#define CSL_MEMPROTL1D_MPLKSTAT_LK_MASK  (0x00000001u)
#define CSL_MEMPROTL1D_MPLKSTAT_LK_SHIFT (0x00000000u)
#define CSL_MEMPROTL1D_MPLKSTAT_LK_RESETVAL (0x00000000u)

/*----LK Tokens----*/
#define CSL_MEMPROTL1D_MPLKSTAT_LK_YES   (0x00000001u)
#define CSL_MEMPROTL1D_MPLKSTAT_LK_NO    (0x00000000u)

#define CSL_MEMPROTL1D_MPLKSTAT_RESETVAL (0x00000000u)

/* MPPA */

#define CSL_MEMPROTL1D_MPPA_RESERVED_MASK (0xFFFF0000u)
#define CSL_MEMPROTL1D_MPPA_RESERVED_SHIFT (0x00000010u)
#define CSL_MEMPROTL1D_MPPA_RESERVED_RESETVAL (0x00000000u)

#define CSL_MEMPROTL1D_MPPA_ARID_MASK    (0x0000FF00u)
#define CSL_MEMPROTL1D_MPPA_ARID_SHIFT   (0x00000008u)
#define CSL_MEMPROTL1D_MPPA_ARID_RESETVAL (0x000000FFu)

/*----ARID Tokens----*/
#define CSL_MEMPROTL1D_MPPA_ARID_NOTSEC  (0x000000FFu)
#define CSL_MEMPROTL1D_MPPA_ARID_SEC     (0x00000038u)
#define CSL_MEMPROTL1D_MPPA_ARID_SEC     (0x00000038u)

#define CSL_MEMPROTL1D_MPPA_PSEC_MASK    (0x000000C0u)
#define CSL_MEMPROTL1D_MPPA_PSEC_SHIFT   (0x00000006u)
#define CSL_MEMPROTL1D_MPPA_PSEC_RESETVAL (0x00000003u)

/*----PSEC Tokens----*/
#define CSL_MEMPROTL1D_MPPA_PSEC_SECNOEMU (0x00000000u)
#define CSL_MEMPROTL1D_MPPA_PSEC_SECEMU  (0x00000001u)
#define CSL_MEMPROTL1D_MPPA_PSEC_SEC     (0x00000003u)

#define CSL_MEMPROTL1D_MPPA_ATYPE_MASK   (0x0000003Fu)
#define CSL_MEMPROTL1D_MPPA_ATYPE_SHIFT  (0x00000000u)
#define CSL_MEMPROTL1D_MPPA_ATYPE_RESETVAL (0x0000003Fu)

/*----ATYPE Tokens----*/
#define CSL_MEMPROTL1D_MPPA_ATYPE_NOTSEC (0x0000003Fu)
#define CSL_MEMPROTL1D_MPPA_ATYPE_SEC    (0x00000038u)

#define CSL_MEMPROTL1D_MPPA_RESETVAL     (0x0000FFFFu)

#endif
