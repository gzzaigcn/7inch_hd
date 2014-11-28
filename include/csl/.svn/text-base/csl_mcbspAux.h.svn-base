/*  ===========================================================================
 *  Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *  Use of this software is controlled by the terms and conditions found in the
 *  license agreement under which this software has been supplied.
 *  ===========================================================================
 */

/** @file csl_mcbspAux.h
 *
 * @brief  Header file for functional layer of CSL
 *
 * Description
 *    - The decribes the definitions of the inline functions
 *
 *  Path: \\(CSLPATH)\\ipmodules\\mcbsp\\src
 */

/* ============================================================================
 *  Revision History
 *  ===============
 *  15-Feb-2005 NSR File Created from CSL_mcbspHwControl.c 
 *                  And CSL_mcbspGetHwStatus.c.
 *
 * ============================================================================
 */

#ifndef _CSL_MCBSPAUX_H_
#define _CSL_MCBSPAUX_H_

#include<csl_mcbsp.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  Status Query Functions of mcbsp.
 */

/** ===========================================================================
 *   @n@b CSL_mcbspGetDevStatus
 *
 *   @b Description
 *   @n This function enables the MCBSP module.
 *
 *   @b Arguments
 *   @verbatim

            hMcbsp          Handle to MCBSP instance

            response        Placeholder to return status.

     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *    @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim

        CSL_mcbspGetDevStatus (hMcbsp, response);

     @endverbatim
 * ===========================================================================
 */
CSL_IDEF_INLINE
void CSL_mcbspGetDevStatus (
    /** Pointer to the object that holds reference to the
     *  instance of MCBSP requested after the call
     */
    CSL_McbspHandle        hMcbsp,

    /** Placeholder to return the status. @a void* casted */
    void                 *response
)
{
    *(CSL_BitMask16*)response =
                (( CSL_FEXT(hMcbsp->regs->SPCR, MCBSP_SPCR_RRDY)) | \
               ( CSL_FEXT(hMcbsp->regs->SPCR, MCBSP_SPCR_XRDY)     << (1)) | \
               ( CSL_FEXT(hMcbsp->regs->SPCR, MCBSP_SPCR_RFULL)    << (2)) | \
               ( CSL_FEXT(hMcbsp->regs->SPCR, MCBSP_SPCR_XEMPTY)   << (3)) | \
               ( CSL_FEXT(hMcbsp->regs->SPCR, MCBSP_SPCR_RSYNCERR) << (4)) | \
               ( CSL_FEXT(hMcbsp->regs->SPCR, MCBSP_SPCR_XSYNCERR) << (5)));
}


/** ===========================================================================
 *   @n@b CSL_mcbspGetTxRstStat
 *
 *   @b Description
 *   @n This function enables the MCBSP module.
 *
 *   @b Arguments
 *   @verbatim

            hMcbsp          Handle to MCBSP instance

            response        Placeholder to return status.

     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *    @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim

        CSL_mcbspGetTxRstStat (hMcbsp, response);

     @endverbatim
 * ===========================================================================
 */
CSL_IDEF_INLINE
void CSL_mcbspGetTxRstStat (
    /** Pointer to the object that holds reference to the
     *  instance of MCBSP requested after the call
     */
    CSL_McbspHandle        hMcbsp,

    /** Placeholder to return the status. @a void* casted */
    void                 *response
)
{
    *(CSL_McbspRstStat *)response = 
                 (CSL_McbspRstStat)(CSL_FEXT(hMcbsp->regs->SPCR, MCBSP_SPCR_XRST));
}


/** ===========================================================================
 *   @n@b CSL_mcbspGetRxRstStat
 *
 *   @b Description
 *   @n This function enables the MCBSP module.
 *
 *   @b Arguments
 *   @verbatim

            hMcbsp          Handle to MCBSP instance

            response        Placeholder to return status.

     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *    @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim

       CSL_mcbspGetRxRstStat (hMcbsp, response);

     @endverbatim
 * ===========================================================================
 */
CSL_IDEF_INLINE
void CSL_mcbspGetRxRstStat (
    /** Pointer to the object that holds reference to the
     *  instance of MCBSP requested after the call
     */
    CSL_McbspHandle        hMcbsp,

    /** Placeholder to return the status. @a void* casted */
    void                 *response
)
{
     *(CSL_McbspRstStat *)response = 
                 (CSL_McbspRstStat)(CSL_FEXT(hMcbsp->regs->SPCR, MCBSP_SPCR_RRST));
}


#ifdef __cplusplus
}
#endif

#endif /* CSL_MCBSPAUX_H_ */


