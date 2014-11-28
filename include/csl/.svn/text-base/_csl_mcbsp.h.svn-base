/*  ===========================================================================
 *  Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *  Use of this software is controlled by the terms and conditions found in the
 *  license agreement under which this software has been supplied.
 *  ===========================================================================
 */

/** @file _csl_mcbsp.h
 *
 *  @brief Header file for private functional layer of McBSP CSL
 *
 *  Path: \\(CSLPATH)\\ipmodules\\mcbsp\\src
 */

/* ============================================================================
 *  Revision History
 *  ===============
 *  23-Aug-2005 Srinivas  Updated for doxygen documentation and butification
 * ============================================================================
 */

#ifndef __CSL_MCBSP_H_
#define __CSL_MCBSP_H_

#include <csl_types.h>
#include <csl_error.h>
#include <csl_mcbsp.h>

/**************************************************************************\
* MCBSP Private function declarations
\**************************************************************************/

/** ===========================================================================
 *   @n@b _CSL_mcbspClearFrmSyncErr
 *
 *   @b Description
 *   @n Clear Frame Sync Error for Receiver and Transmitter.
 *
 *   @b Arguments
 *   @verbatim
            hMcbsp       Handle to MCBSP Obj used

            chanType     Selects receiver/transmitter.
 *   @endverbatim
 *
 *   <b> Return Value </b> None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n Serial Port Control register of the MCBSP.
 *
 *   @b Example
 *   @verbatim

      CSL_McbspHandle hMcbsp;
      hMcbsp = CSL_mcbspOpen(hMcbsp,CSL_MCBSP_0, CSL_EXCLUSIVE, &status, NULL);
      _CSL_mcbspClearFrmSyncErr( hMcbsp, CSL_MCBSP_RX);
 *   @endverbatim
 *  ===========================================================================
 */
void  _CSL_mcbspClearFrmSyncErr(
    CSL_McbspHandle                        hMcbsp,
    CSL_McbspChType                        chanType
);


/** ===========================================================================
 *   @n@b _CSL_mcbspIoModeCtrl
 *
 *   @b Description
 *   @n Configure selected McBSP pins for Input/Output
 *
 *   @b Arguments
 *   @verbatim
        hMcbsp       Handle to MCBSP Obj used

        outputSel    Select Pins for output. Bitwise OR of CSL_MCBSP_IO_XXXX

        inputSel     Select Pins for input. Bitwise OR of CSL_MCBSP_IO_XXXX
 *   @endverbatim
 *
 *   <b> Return Value </b> None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n Pin Control register of the MCBSP.
 *
 *   @b Example
 *   @verbatim
      ...

      CSL_McbspHandle hMcbsp;
      hMcbsp = CSL_mcbspOpen(hMcbsp,CSL_MCBSP_0, CSL_EXCLUSIVE, &status, NULL);
      _CSL_mcbspIoModeCtrl( hMcbsp,  CSL_MCBSP_IO_CLKX | CSL_MCBSP_IO_CLKR,
                           CSL_MCBSP_IO_FSX | CSL_MCBSP_IO_CLKR );
 *   @endverbatim
 *  ===========================================================================
 */
void  _CSL_mcbspIoModeCtrl(
    CSL_McbspHandle                         hMcbsp,
    CSL_BitMask16                           outputSel,
    CSL_BitMask16                           inputSel
);


/** ===========================================================================
 *   @n@b _CSL_mcbspResetCtrl
 *
 *   @b Description
 *   @n Enable/Disable Frame Sync Logic/Sample Rate Generator and Receiver and
 *      Transmitter Operation
 *
 *   @b Arguments
 *   @verbatim
            hMcbsp       Handle to MCBSP Obj used

            selectMask   Selects enable/disable of receiverCfg/transmitter.
                         Bitwise OR of MCBSP_CTRL_XXXX
 *   @endverbatim
 *
 *   <b> Return Value </b> None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n Serial Port Control register of the MCBSP.
 *
 *   @b Example
 *   @verbatim
      ...

      CSL_McbspHandle hMcbsp;
      hMcbsp = CSL_mcbspOpen(hMcbsp,CSL_MCBSP_0, CSL_EXCLUSIVE, &status, NULL);
      _CSL_mcbspResetCtrl( hMcbsp, CSL_MCBSP_CTRL_SRG_ENABLE |
                          CSL_MCBSP_CTRL_FSYNC_DISABLE |
                          CSL_MCBSP_CTRL_RX_ENABLE |
                          CSL_MCBSP_CTRL_TX_ENABLE );
 *   @endverbatim
 *  ===========================================================================
 */
void  _CSL_mcbspResetCtrl(
    CSL_McbspHandle                         hMcbsp,
    CSL_BitMask16                           selectMask
);


/** ===========================================================================
 *   @n@b _CSL_mcbspRegReset
 *
 *   @b Description
 *   @n Function to reset all the registers values
 *
 *   @b Arguments
 *   @verbatim
            hMcbsp       Handle to MCBSP Obj used
 *   @endverbatim
 *
 *   <b> Return Value </b> None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n Hardware registers of the MCBSP.
 *
 *   @b Example
 *   @verbatim
      ...

      CSL_McbspHandle hMcbsp;
      hMcbsp = CSL_mcbspOpen(hMcbsp,CSL_MCBSP_0, CSL_EXCLUSIVE, &status, NULL);
      _CSL_mcbspRegReset(hMcbsp);
 *   @endverbatim
 *  ===========================================================================
 */
void  _CSL_mcbspRegReset(
    CSL_McbspHandle                         hMcbsp
);

#endif

