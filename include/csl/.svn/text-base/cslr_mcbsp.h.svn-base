/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005                 
 *                                                                              
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.             
 *   ===========================================================================
 */
 
#ifndef _CSLR_MCBSP_H_
#define _CSLR_MCBSP_H_

/** \file cslr_mcbsp.h
 * 
 * \brief This file contains the Register Desciptions for MCBSP
 * 
 *********************************************************************/

#include <cslr.h>

#include <tistdtypes.h>

/**************************************************************************\
* Register Overlay Structure
\**************************************************************************/
typedef struct  {
    volatile Uint32 DRR;
    volatile Uint32 DXR;
    volatile Uint32 SPCR;
    volatile Uint32 RCR;
    volatile Uint32 XCR;
    volatile Uint32 SRGR;
    volatile Uint8 RSVD0[12];
    volatile Uint32 PCR;
} CSL_McbspRegs;

/**************************************************************************\
* Overlay structure typedef definition
\**************************************************************************/
typedef volatile CSL_McbspRegs             *CSL_McbspRegsOvly;

/**************************************************************************\
* Field Definition Macros
\**************************************************************************/

/* DRR */

#define CSL_MCBSP_DRR_DRR_MASK           (0xFFFFFFFFu)
#define CSL_MCBSP_DRR_DRR_SHIFT          (0x00000000u)
#define CSL_MCBSP_DRR_DRR_RESETVAL       (0x00000000u)

#define CSL_MCBSP_DRR_RESETVAL           (0x00000000u)

/* DXR */

#define CSL_MCBSP_DXR_DXR_MASK           (0xFFFFFFFFu)
#define CSL_MCBSP_DXR_DXR_SHIFT          (0x00000000u)
#define CSL_MCBSP_DXR_DXR_RESETVAL       (0x00000000u)

#define CSL_MCBSP_DXR_RESETVAL           (0x00000000u)

/* SPCR */

#define CSL_MCBSP_SPCR_FREE_MASK         (0x02000000u)
#define CSL_MCBSP_SPCR_FREE_SHIFT        (0x00000019u)
#define CSL_MCBSP_SPCR_FREE_RESETVAL     (0x00000000u)

#define CSL_MCBSP_SPCR_SOFT_MASK         (0x01000000u)
#define CSL_MCBSP_SPCR_SOFT_SHIFT        (0x00000018u)
#define CSL_MCBSP_SPCR_SOFT_RESETVAL     (0x00000000u)

#define CSL_MCBSP_SPCR_FRST_MASK         (0x00800000u)
#define CSL_MCBSP_SPCR_FRST_SHIFT        (0x00000017u)
#define CSL_MCBSP_SPCR_FRST_RESETVAL     (0x00000000u)

#define CSL_MCBSP_SPCR_GRST_MASK         (0x00400000u)
#define CSL_MCBSP_SPCR_GRST_SHIFT        (0x00000016u)
#define CSL_MCBSP_SPCR_GRST_RESETVAL     (0x00000000u)

#define CSL_MCBSP_SPCR_XINTM_MASK        (0x00300000u)
#define CSL_MCBSP_SPCR_XINTM_SHIFT       (0x00000014u)
#define CSL_MCBSP_SPCR_XINTM_RESETVAL    (0x00000000u)

#define CSL_MCBSP_SPCR_XSYNCERR_MASK     (0x00080000u)
#define CSL_MCBSP_SPCR_XSYNCERR_SHIFT    (0x00000013u)
#define CSL_MCBSP_SPCR_XSYNCERR_RESETVAL (0x00000000u)

/*----XSYNCERR Tokens----*/
#define CSL_MCBSP_SPCR_XSYNCERR_CLEAR    (0x00000000u)

#define CSL_MCBSP_SPCR_XEMPTY_MASK       (0x00040000u)
#define CSL_MCBSP_SPCR_XEMPTY_SHIFT      (0x00000012u)
#define CSL_MCBSP_SPCR_XEMPTY_RESETVAL   (0x00000000u)

#define CSL_MCBSP_SPCR_XRDY_MASK         (0x00020000u)
#define CSL_MCBSP_SPCR_XRDY_SHIFT        (0x00000011u)
#define CSL_MCBSP_SPCR_XRDY_RESETVAL     (0x00000000u)

#define CSL_MCBSP_SPCR_XRST_MASK         (0x00010000u)
#define CSL_MCBSP_SPCR_XRST_SHIFT        (0x00000010u)
#define CSL_MCBSP_SPCR_XRST_RESETVAL     (0x00000000u)

#define CSL_MCBSP_SPCR_DLB_MASK          (0x00008000u)
#define CSL_MCBSP_SPCR_DLB_SHIFT         (0x0000000Fu)
#define CSL_MCBSP_SPCR_DLB_RESETVAL      (0x00000000u)

#define CSL_MCBSP_SPCR_RJUST_MASK        (0x00006000u)
#define CSL_MCBSP_SPCR_RJUST_SHIFT       (0x0000000Du)
#define CSL_MCBSP_SPCR_RJUST_RESETVAL    (0x00000000u)

#define CSL_MCBSP_SPCR_RINTM_MASK        (0x00000030u)
#define CSL_MCBSP_SPCR_RINTM_SHIFT       (0x00000004u)
#define CSL_MCBSP_SPCR_RINTM_RESETVAL    (0x00000000u)

#define CSL_MCBSP_SPCR_RSYNCERR_MASK     (0x00000008u)
#define CSL_MCBSP_SPCR_RSYNCERR_SHIFT    (0x00000003u)
#define CSL_MCBSP_SPCR_RSYNCERR_RESETVAL (0x00000000u)

/*----RSYNCERR Tokens----*/
#define CSL_MCBSP_SPCR_RSYNCERR_CLEAR    (0x00000000u)

#define CSL_MCBSP_SPCR_RFULL_MASK        (0x00000004u)
#define CSL_MCBSP_SPCR_RFULL_SHIFT       (0x00000002u)
#define CSL_MCBSP_SPCR_RFULL_RESETVAL    (0x00000000u)

#define CSL_MCBSP_SPCR_RRDY_MASK         (0x00000002u)
#define CSL_MCBSP_SPCR_RRDY_SHIFT        (0x00000001u)
#define CSL_MCBSP_SPCR_RRDY_RESETVAL     (0x00000000u)

#define CSL_MCBSP_SPCR_RRST_MASK         (0x00000001u)
#define CSL_MCBSP_SPCR_RRST_SHIFT        (0x00000000u)
#define CSL_MCBSP_SPCR_RRST_RESETVAL     (0x00000000u)

#define CSL_MCBSP_SPCR_RESETVAL          (0x00000000u)

/* RCR */

#define CSL_MCBSP_RCR_RPHASE_MASK        (0x80000000u)
#define CSL_MCBSP_RCR_RPHASE_SHIFT       (0x0000001Fu)
#define CSL_MCBSP_RCR_RPHASE_RESETVAL    (0x00000000u)

#define CSL_MCBSP_RCR_RFRLEN2_MASK       (0x7F000000u)
#define CSL_MCBSP_RCR_RFRLEN2_SHIFT      (0x00000018u)
#define CSL_MCBSP_RCR_RFRLEN2_RESETVAL   (0x00000000u)

#define CSL_MCBSP_RCR_RWDLEN2_MASK       (0x00E00000u)
#define CSL_MCBSP_RCR_RWDLEN2_SHIFT      (0x00000015u)
#define CSL_MCBSP_RCR_RWDLEN2_RESETVAL   (0x00000000u)

/*----RWDLEN2 Tokens----*/
#define CSL_MCBSP_RCR_RWDLEN2_8BITS      (0x00000000u)
#define CSL_MCBSP_RCR_RWDLEN2_12BITS     (0x00000001u)
#define CSL_MCBSP_RCR_RWDLEN2_16BITS     (0x00000002u)
#define CSL_MCBSP_RCR_RWDLEN2_20BITS     (0x00000003u)
#define CSL_MCBSP_RCR_RWDLEN2_24BITS     (0x00000004u)
#define CSL_MCBSP_RCR_RWDLEN2_32BITS     (0x00000005u)

#define CSL_MCBSP_RCR_RCOMPAND_MASK      (0x00180000u)
#define CSL_MCBSP_RCR_RCOMPAND_SHIFT     (0x00000013u)
#define CSL_MCBSP_RCR_RCOMPAND_RESETVAL  (0x00000000u)

#define CSL_MCBSP_RCR_RFIG_MASK          (0x00040000u)
#define CSL_MCBSP_RCR_RFIG_SHIFT         (0x00000012u)
#define CSL_MCBSP_RCR_RFIG_RESETVAL      (0x00000000u)

#define CSL_MCBSP_RCR_RDATDLY_MASK       (0x00030000u)
#define CSL_MCBSP_RCR_RDATDLY_SHIFT      (0x00000010u)
#define CSL_MCBSP_RCR_RDATDLY_RESETVAL   (0x00000000u)

#define CSL_MCBSP_RCR_RFRLEN1_MASK       (0x00007F00u)
#define CSL_MCBSP_RCR_RFRLEN1_SHIFT      (0x00000008u)
#define CSL_MCBSP_RCR_RFRLEN1_RESETVAL   (0x00000000u)

#define CSL_MCBSP_RCR_RWDLEN1_MASK       (0x000000E0u)
#define CSL_MCBSP_RCR_RWDLEN1_SHIFT      (0x00000005u)
#define CSL_MCBSP_RCR_RWDLEN1_RESETVAL   (0x00000000u)

/*----RWDLEN1 Tokens----*/
#define CSL_MCBSP_RCR_RWDLEN1_8BITS      (0x00000000u)
#define CSL_MCBSP_RCR_RWDLEN1_12BITS     (0x00000001u)
#define CSL_MCBSP_RCR_RWDLEN1_16BITS     (0x00000002u)
#define CSL_MCBSP_RCR_RWDLEN1_20BITS     (0x00000003u)
#define CSL_MCBSP_RCR_RWDLEN1_24BITS     (0x00000004u)
#define CSL_MCBSP_RCR_RWDLEN1_32BITS     (0x00000005u)

#define CSL_MCBSP_RCR_RWDREVRS_MASK      (0x00000010u)
#define CSL_MCBSP_RCR_RWDREVRS_SHIFT     (0x00000004u)
#define CSL_MCBSP_RCR_RWDREVRS_RESETVAL  (0x00000000u)

#define CSL_MCBSP_RCR_RESETVAL           (0x00000000u)

/* XCR */

#define CSL_MCBSP_XCR_XPHASE_MASK        (0x80000000u)
#define CSL_MCBSP_XCR_XPHASE_SHIFT       (0x0000001Fu)
#define CSL_MCBSP_XCR_XPHASE_RESETVAL    (0x00000000u)

#define CSL_MCBSP_XCR_XFRLEN2_MASK       (0x7F000000u)
#define CSL_MCBSP_XCR_XFRLEN2_SHIFT      (0x00000018u)
#define CSL_MCBSP_XCR_XFRLEN2_RESETVAL   (0x00000000u)

#define CSL_MCBSP_XCR_XWDLEN2_MASK       (0x00E00000u)
#define CSL_MCBSP_XCR_XWDLEN2_SHIFT      (0x00000015u)
#define CSL_MCBSP_XCR_XWDLEN2_RESETVAL   (0x00000000u)

/*----XWDLEN2 Tokens----*/
#define CSL_MCBSP_XCR_XWDLEN2_8BITS      (0x00000000u)
#define CSL_MCBSP_XCR_XWDLEN2_12BITS     (0x00000001u)
#define CSL_MCBSP_XCR_XWDLEN2_16BITS     (0x00000002u)
#define CSL_MCBSP_XCR_XWDLEN2_20BITS     (0x00000003u)
#define CSL_MCBSP_XCR_XWDLEN2_24BITS     (0x00000004u)
#define CSL_MCBSP_XCR_XWDLEN2_32BITS     (0x00000005u)

#define CSL_MCBSP_XCR_XCOMPAND_MASK      (0x00180000u)
#define CSL_MCBSP_XCR_XCOMPAND_SHIFT     (0x00000013u)
#define CSL_MCBSP_XCR_XCOMPAND_RESETVAL  (0x00000000u)

#define CSL_MCBSP_XCR_XFIG_MASK          (0x00040000u)
#define CSL_MCBSP_XCR_XFIG_SHIFT         (0x00000012u)
#define CSL_MCBSP_XCR_XFIG_RESETVAL      (0x00000000u)

#define CSL_MCBSP_XCR_XDATDLY_MASK       (0x00030000u)
#define CSL_MCBSP_XCR_XDATDLY_SHIFT      (0x00000010u)
#define CSL_MCBSP_XCR_XDATDLY_RESETVAL   (0x00000000u)

#define CSL_MCBSP_XCR_XFRLEN1_MASK       (0x00007F00u)
#define CSL_MCBSP_XCR_XFRLEN1_SHIFT      (0x00000008u)
#define CSL_MCBSP_XCR_XFRLEN1_RESETVAL   (0x00000000u)

#define CSL_MCBSP_XCR_XWDLEN1_MASK       (0x000000E0u)
#define CSL_MCBSP_XCR_XWDLEN1_SHIFT      (0x00000005u)
#define CSL_MCBSP_XCR_XWDLEN1_RESETVAL   (0x00000000u)

/*----XWDLEN1 Tokens----*/
#define CSL_MCBSP_XCR_XWDLEN1_8BITS      (0x00000000u)
#define CSL_MCBSP_XCR_XWDLEN1_12BITS     (0x00000001u)
#define CSL_MCBSP_XCR_XWDLEN1_16BITS     (0x00000002u)
#define CSL_MCBSP_XCR_XWDLEN1_20BITS     (0x00000003u)
#define CSL_MCBSP_XCR_XWDLEN1_24BITS     (0x00000004u)
#define CSL_MCBSP_XCR_XWDLEN1_32BITS     (0x00000005u)

#define CSL_MCBSP_XCR_XWDREVRS_MASK      (0x00000010u)
#define CSL_MCBSP_XCR_XWDREVRS_SHIFT     (0x00000004u)
#define CSL_MCBSP_XCR_XWDREVRS_RESETVAL  (0x00000000u)

#define CSL_MCBSP_XCR_RESETVAL           (0x00000000u)

/* SRGR */

#define CSL_MCBSP_SRGR_CLKSM_MASK        (0x20000000u)
#define CSL_MCBSP_SRGR_CLKSM_SHIFT       (0x0000001Du)
#define CSL_MCBSP_SRGR_CLKSM_RESETVAL    (0x00000001u)

#define CSL_MCBSP_SRGR_FSGM_MASK         (0x10000000u)
#define CSL_MCBSP_SRGR_FSGM_SHIFT        (0x0000001Cu)
#define CSL_MCBSP_SRGR_FSGM_RESETVAL     (0x00000000u)

#define CSL_MCBSP_SRGR_FPER_MASK         (0x0FFF0000u)
#define CSL_MCBSP_SRGR_FPER_SHIFT        (0x00000010u)
#define CSL_MCBSP_SRGR_FPER_RESETVAL     (0x00000000u)

#define CSL_MCBSP_SRGR_FWID_MASK         (0x0000FF00u)
#define CSL_MCBSP_SRGR_FWID_SHIFT        (0x00000008u)
#define CSL_MCBSP_SRGR_FWID_RESETVAL     (0x00000000u)

#define CSL_MCBSP_SRGR_CLKGDV_MASK       (0x000000FFu)
#define CSL_MCBSP_SRGR_CLKGDV_SHIFT      (0x00000000u)
#define CSL_MCBSP_SRGR_CLKGDV_RESETVAL   (0x00000001u)

#define CSL_MCBSP_SRGR_RESETVAL          (0x20000001u)

/* PCR */

#define CSL_MCBSP_PCR_FSXM_MASK          (0x00000800u)
#define CSL_MCBSP_PCR_FSXM_SHIFT         (0x0000000Bu)
#define CSL_MCBSP_PCR_FSXM_RESETVAL      (0x00000000u)

/*----FSXM Tokens----*/
#define CSL_MCBSP_PCR_FSXM_INPUT         (0x00000000u)
#define CSL_MCBSP_PCR_FSXM_OUTPUT        (0x00000001u)

#define CSL_MCBSP_PCR_FSRM_MASK          (0x00000400u)
#define CSL_MCBSP_PCR_FSRM_SHIFT         (0x0000000Au)
#define CSL_MCBSP_PCR_FSRM_RESETVAL      (0x00000000u)

/*----FSRM Tokens----*/
#define CSL_MCBSP_PCR_FSRM_INPUT         (0x00000000u)
#define CSL_MCBSP_PCR_FSRM_OUTPUT        (0x00000001u)

#define CSL_MCBSP_PCR_CLKXM_MASK         (0x00000200u)
#define CSL_MCBSP_PCR_CLKXM_SHIFT        (0x00000009u)
#define CSL_MCBSP_PCR_CLKXM_RESETVAL     (0x00000000u)

/*----CLKXM Tokens----*/
#define CSL_MCBSP_PCR_CLKXM_INPUT        (0x00000000u)
#define CSL_MCBSP_PCR_CLKXM_OUTPUT       (0x00000001u)

#define CSL_MCBSP_PCR_CLKRM_MASK         (0x00000100u)
#define CSL_MCBSP_PCR_CLKRM_SHIFT        (0x00000008u)
#define CSL_MCBSP_PCR_CLKRM_RESETVAL     (0x00000000u)

/*----CLKRM Tokens----*/
#define CSL_MCBSP_PCR_CLKRM_INPUT        (0x00000000u)
#define CSL_MCBSP_PCR_CLKRM_OUTPUT       (0x00000001u)

#define CSL_MCBSP_PCR_SCLKME_MASK        (0x00000080u)
#define CSL_MCBSP_PCR_SCLKME_SHIFT       (0x00000007u)
#define CSL_MCBSP_PCR_SCLKME_RESETVAL    (0x00000000u)

#define CSL_MCBSP_PCR_DXSTAT_MASK        (0x00000020u)
#define CSL_MCBSP_PCR_DXSTAT_SHIFT       (0x00000005u)
#define CSL_MCBSP_PCR_DXSTAT_RESETVAL    (0x00000000u)

#define CSL_MCBSP_PCR_DRSTAT_MASK        (0x00000010u)
#define CSL_MCBSP_PCR_DRSTAT_SHIFT       (0x00000004u)
#define CSL_MCBSP_PCR_DRSTAT_RESETVAL    (0x00000000u)

#define CSL_MCBSP_PCR_FSXP_MASK          (0x00000008u)
#define CSL_MCBSP_PCR_FSXP_SHIFT         (0x00000003u)
#define CSL_MCBSP_PCR_FSXP_RESETVAL      (0x00000000u)

#define CSL_MCBSP_PCR_FSRP_MASK          (0x00000004u)
#define CSL_MCBSP_PCR_FSRP_SHIFT         (0x00000002u)
#define CSL_MCBSP_PCR_FSRP_RESETVAL      (0x00000000u)

#define CSL_MCBSP_PCR_CLKXP_MASK         (0x00000002u)
#define CSL_MCBSP_PCR_CLKXP_SHIFT        (0x00000001u)
#define CSL_MCBSP_PCR_CLKXP_RESETVAL     (0x00000000u)

#define CSL_MCBSP_PCR_CLKRP_MASK         (0x00000001u)
#define CSL_MCBSP_PCR_CLKRP_SHIFT        (0x00000000u)
#define CSL_MCBSP_PCR_CLKRP_RESETVAL     (0x00000000u)

#define CSL_MCBSP_PCR_RESETVAL           (0x00000000u)

#endif
