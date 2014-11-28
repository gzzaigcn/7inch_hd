/*  ===========================================================================
 *  Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *  Use of this software is controlled by the terms and conditions found in the
 *  license agreement under which this software has been supplied.
 *  ===========================================================================
 */

/** @mainpage MCBSP CSL 3.x
 *
 * @section Introduction
 *
 * @subsection xxx Purpose and Scope
 * The purpose of this document is to identify a set of common CSL APIs for
 * the MCBSP module across various devices. The CSL developer is expected to
 * refer to this document while designing APIs for these modules. Some of the
 *  listed APIs may not be applicable to a given MCBSP module.While other cases
 * this list of APIs may not be sufficient to cover all the features of a
 *  particular MCBSP Module. The CSL developer should use his discretion
 *  designing new APIs or extending the existing ones to cover these.
 *
 * @subsection aaa Terms and Abbreviations
 *   -# CSL:  Chip Support Library
 *   -# API:  Application Programmer Interface
 *
 * @subsection References
 *    -# CSL 3.x Technical Requirements Specifications Version 0.5, dated
 *       May 14th, 2003
 *
 *
 */


/** @file csl_mcbsp.h
 *
 *  @brief Header file for functional layer of McBSP CSL
 *
 *  Path: \\(CSLPATH)\\ipmodules\\dspmcbsp\\src
 *
 *  Description
 *  - The different symbolic constants, enumerations, structure definitions
 *    and function prototype declarations
 *
 *  @date    29 June, 2004
 *  @author  Pratheesh Gangadhar
 */

/* ============================================================================
 *  Revision History
 *  ===============
 *  05-Sep-2005 Srinivas_N  Updated as for new specifications.
 *
 *  23-Aug-2005 Srinivas_N  Updated for doxygen documentation and butification
 *
 *  15-Feb-2005 Srinivas_N
 *               -  updated CSL_McbspObj and added CSL_McbspBaseAddress,
 *                   CSL_McbspParam,CSL_McbspContext,CSL_McbspConfig structures.
 *                 - Updated comments for H/W control cmd and status query enums.
 *                 - Added prototypes for CSL_mcbspGetBaseAdddress and
 *                   CSL_mcbspHwSetupRaw.
 *                 - Changed prototypes of CSL_mcbspInit, CSL_mcbspOpen.
 *                 - Updated respective comments along with that of
 *                   CSL_mcbspClose.
 * ============================================================================
 */

/**
 * @defgroup CSL_MCBSP_API MCBSP
 */

/**
 * @defgroup CSL_MCBSP_DATASTRUCT MCBSP Data Structures
 * @ingroup CSL_MCBSP_API
 */
/**
 * @defgroup CSL_MCBSP_SYMBOL  Symbols
 * @ingroup CSL_MCBSP_API
 */
/**
 * @defgroup CSL_MCBSP_ENUM  Enumerated Data Types
 * @ingroup CSL_MCBSP_API
 */
/**
 * @defgroup CSL_MCBSP_FUNCTION  Functions
 * @ingroup CSL_MCBSP_API
 */

#ifndef _CSL_MCBSP_H_
#define _CSL_MCBSP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <soc.h>
#include <csl_types.h>
#include <csl_error.h>
#include <cslr_mcbsp.h>
#include <csl_resId.h>
/**************************************************************************\
* MCBSP global macro declarations
\**************************************************************************/

/** @defgroup CSL_MCBSP_IO_SYMBOL General purpose IO pin selection
 * @ingroup CSL_MCBSP_SYMBOL
 *
 * Use this symbol as pin mask for @a CSL_mcbspIoRead() and
 * @a CSL_mcbspIoWrite() functions
 *
 * @{ */
/** I/O Pin Input/Output configuration for CLKX Pin       */
#define CSL_MCBSP_IO_CLKX                             (1)

/** I/O Pin Input/Output configuration for FSX  Pin       */
#define CSL_MCBSP_IO_FSX                              (2)

/** Not Configurable. Always Output.                      */
#define CSL_MCBSP_IO_DX                               (4)

/** I/O Pin Input/Output configuration for CLKR Pin       */
#define CSL_MCBSP_IO_CLKR                             (8)

/** I/O Pin Input/Output configuration for FSR Pin        */
#define CSL_MCBSP_IO_FSR                              (16)

/** Not Configurable. Always Input.                        */
#define CSL_MCBSP_IO_DR                               (32)
/**
@} */

/** @defgroup CSL_MCBSP_CTRL_SYMBOL Enable/Disable Controls
 * @ingroup CSL_MCBSP_SYMBOL
 *
 * Use this symbol as enable/disable control bitmask for
 * @a CSL_mcbspHwControl() function
 *
 * @{ */
/** To enable Receiver in resetControl Function             */
#define CSL_MCBSP_CTRL_RX_ENABLE                      (1)

/** To enable Transmitter in resetControl Function          */
#define CSL_MCBSP_CTRL_TX_ENABLE                      (2)

/** To disable Receiver in resetControl Function            */
#define CSL_MCBSP_CTRL_RX_DISABLE                     (4)

/** To disable Transmitter in resetControl Function         */
#define CSL_MCBSP_CTRL_TX_DISABLE                     (8)

/** To enable Frame Sync Generation in resetControl Function */
#define CSL_MCBSP_CTRL_FSYNC_ENABLE                   (16)

/** To enable Sample Rate Generator in resetControl Function */
#define CSL_MCBSP_CTRL_SRG_ENABLE                     (32)

/** To disable Frame Sync Generation in resetControl Function */
#define CSL_MCBSP_CTRL_FSYNC_DISABLE                  (64)

/** To disable Sample Rate Generator in resetControl Function */
#define CSL_MCBSP_CTRL_SRG_DISABLE                    (128)
/**
@} */

/** @defgroup CSL_DEVSTATUS_SYMBOL RCV/XMT status symbols
 * @ingroup CSL_MCBSP_SYMBOL
 *
 * Use this symbol to compare the return value of @a CSL_mcbspGetHwStatus()
 * function for @a CSL_MCBSP_QUERY_DEV_STATUS query
 * \n For eg:- On RFULL event, (response & CSL_MCBSP_RFULL) == 0x0004
 *
 * @{ */
/** RCV ready status */
#define CSL_MCBSP_RRDY        0x0001
/** XMT ready status */
#define CSL_MCBSP_XRDY        0x0002
/** RCV full status */
#define CSL_MCBSP_RFULL       0x0004
/** XMT empty status */
#define CSL_MCBSP_XEMPTY      0x0008
/** RCV frame sync error status */
#define CSL_MCBSP_RSYNCERR    0x0010
/** XMT frame sync error status */
#define CSL_MCBSP_XSYNCERR    0x0020
/**
@} */

/** @defgroup CSL_EMCBSP_SYMBOL Error codes
 * @ingroup CSL_MCBSP_SYMBOL
 *
 * @{ */
/** Invalid Control Command */
#define CSL_EMCBSP_INVCNTLCMD                         (CSL_EMCBSP_FIRST - 0)

/** Invalid Query */
#define CSL_EMCBSP_INVQUERY                           (CSL_EMCBSP_FIRST - 1)

/** Invalid Parameter */
#define CSL_EMCBSP_INVPARAMS                          (CSL_EMCBSP_FIRST - 2)

/** Invalid Size */
#define CSL_EMCBSP_INVSIZE                            (CSL_EMCBSP_FIRST - 3)

/** 'Does not exist' */
#define CSL_EMCBSP_NOTEXIST                           (CSL_EMCBSP_FIRST - 4)

/** Invalid mode to conduct operation */
#define CSL_EMCBSP_INVMODE                            (CSL_EMCBSP_FIRST - 5)
/**
@} */

/**
 * @defgroup CSL_MCBSP_DEFAULT_SYMBOL MCBSP CSL Defaults
 * @ingroup CSL_MCBSP_SYMBOL
 *
 * @{ */

/** Data Setup defaults */
#define CSL_MCBSP_DATASETUP_DEFAULTS   {            \
   (CSL_McbspPhase)CSL_MCBSP_PHASE_SINGLE,          \
   (CSL_McbspWordLen)CSL_MCBSP_WORDLEN_16,          \
   1,                                               \
   (CSL_McbspWordLen)0,                             \
   0,                                               \
   (CSL_McbspFrmSync)CSL_MCBSP_FRMSYNC_DETECT,      \
   (CSL_McbspCompand)CSL_MCBSP_COMPAND_OFF_MSB_FIRST, \
   (CSL_McbspDataDelay)CSL_MCBSP_DATADELAY_0_BIT,   \
   (CSL_McbspRjustDxena)0,                          \
   (CSL_McbspIntMode)CSL_MCBSP_INTMODE_ON_READY,     \
   (CSL_McbspBitReversal)CSL_MCBSP_32BIT_REVERS_DISABLE }\


/** Clock Setup defaults */
#define CSL_MCBSP_CLOCKSETUP_DEFAULTS  {                \
 (CSL_McbspFsClkMode)CSL_MCBSP_FSCLKMODE_EXTERNAL,      \
 (CSL_McbspFsClkMode)CSL_MCBSP_FSCLKMODE_EXTERNAL,      \
 (CSL_McbspTxRxClkMode)CSL_MCBSP_TXRXCLKMODE_INTERNAL,  \
 (CSL_McbspTxRxClkMode)CSL_MCBSP_TXRXCLKMODE_EXTERNAL,  \
 (CSL_McbspFsPol)0,                                     \
 (CSL_McbspFsPol)0,                                     \
 (CSL_McbspClkPol)0,                                    \
 (CSL_McbspClkPol)0,                                    \
 1,                                                     \
 0x40,                                                  \
 0xFF,                                                  \
 (CSL_McbspSrgClk)0,                                    \
    (CSL_McbspTxFsMode)CSL_MCBSP_TXFSMODE_SRG              }\

/** Default Emulation mode - Stop */
#define CSL_MCBSP_DLBMODE_DEFAULT  CSL_MCBSP_DLBMODE_OFF

/** Default Emulation mode - Stop */
#define CSL_MCBSP_EMUMODE_DEFAULT  CSL_MCBSP_EMU_STOP

/** Default DX state */
#define CSL_MCBSP_DXSTATE_DEFAULT  CSL_MCBSP_DX_HIGHZ

/** Extend Setup default - NULL */
#define CSL_MCBSP_EXTENDSETUP_DEFAULT  NULL


/**
@} */

/**************************************************************************\
* MCBSP global typedef declarations
\**************************************************************************/

/**
 * @defgroup CSL_MCBSP_WORDLEN_ENUM Word length
 * @ingroup CSL_MCBSP_ENUM
 *
 * @brief Word lengths supported on MCBSP
 *
 * Use this symbol for setting Word Length in each Phase for every Frame
 * @{ */
typedef enum {
    /** Word Length for Frame is 8 */
    CSL_MCBSP_WORDLEN_8        =                  0,
    /** Word Length for Frame is 12 */
    CSL_MCBSP_WORDLEN_12       =                  1,
    /** Word Length for Frame is 16 */
    CSL_MCBSP_WORDLEN_16       =                  2,
    /** Word Length for Frame is 20 */
    CSL_MCBSP_WORDLEN_20       =                  3,
    /** Word Length for Frame is 24 */
    CSL_MCBSP_WORDLEN_24       =                  4,
    /** Word Length for Frame is 32 */
    CSL_MCBSP_WORDLEN_32       =                  5
} CSL_McbspWordLen;
/**
@} */

/**
 * @defgroup CSL_MCBSP_COMPAND_ENUM Companding options
 * @ingroup CSL_MCBSP_ENUM
 *
 * @brief MCBSP companding options
 *
 * Use this symbol to set Companding related options
 * @{ */
typedef enum {
    /** no companding for msb */
    CSL_MCBSP_COMPAND_OFF_MSB_FIRST =                 0,
    /** no companding for lsb */
    CSL_MCBSP_COMPAND_OFF_LSB_FIRST =                 1,
    /** mu-law comapanding enable for channel */
    CSL_MCBSP_COMPAND_MULAW         =                 2,
    /** A-law comapanding enable for channel */
    CSL_MCBSP_COMPAND_ALAW          =                 3
} CSL_McbspCompand;
/**
@} */

/**
 * @defgroup CSL_MCBSP_DATADELAY_ENUM Data delay
 * @ingroup CSL_MCBSP_ENUM
 *
 * @brief Data delay in bits
 *
 * Use this symbol to set XMT/RCV Data Delay (in bits)
 * @{ */
typedef enum {
    /** sets XMT/RCV Data Delay is 0 */
    CSL_MCBSP_DATADELAY_0_BIT      =                 0,
    /** sets XMT/RCV Data Delay is 1 */
    CSL_MCBSP_DATADELAY_1_BIT      =                 1,
    /** sets XMT/RCV Data Delay is 2 */
    CSL_MCBSP_DATADELAY_2_BITS     =                 2
} CSL_McbspDataDelay;
/**
@} */

/**
 * @defgroup CSL_MCBSP_EVENT_ENUM Interrupt mode
 * @ingroup CSL_MCBSP_ENUM
 *
 * @brief MCBSP Interrupt mode
 *
 * Use this symbol to set Interrupt mode (i.e. source of interrupt generation).
 * This symbol is used on both RCV and XMT for RINT and XINT generation mode.
 * @{ */
typedef enum {
    /** Interrupt generated on RRDY of RCV or XRDY of XMT */
    CSL_MCBSP_INTMODE_ON_READY         =                  0,
    /** Interrupt generated on end of 16-channel block transfer
     *  in multichannel mode */
    CSL_MCBSP_INTMODE_ON_EOB           =                  1,
    /** Interrupt generated on frame sync */
    CSL_MCBSP_INTMODE_ON_FSYNC         =                  2,
    /** Interrupt generated on synchronisation error */
    CSL_MCBSP_INTMODE_ON_SYNCERR       =                  3
} CSL_McbspIntMode;
/**
@} */

/**
 * @defgroup CSL_MCBSP_FSCLKMODE_ENUM Frame sync clock source
 * @ingroup CSL_MCBSP_ENUM
 *
 * @brief Frame sync clock source
 *
 * Use this symbol to set the frame sync clock source as internal or external
 * @{ */
typedef enum {
    /** frame sync clock source as internal */
    CSL_MCBSP_FSCLKMODE_EXTERNAL    =                  0,
    /** frame sync clock source as external */
    CSL_MCBSP_FSCLKMODE_INTERNAL    =                  1
} CSL_McbspFsClkMode;
/**
@} */

/**
 * @defgroup CSL_MCBSP_CLKMODE_ENUM Clock Mode
 * @ingroup CSL_MCBSP_ENUM
 *
 * @brief Clock source
 *
 * Use this symbol to set the clock source as internal or external
 * @{ */
typedef enum {
    /** clock source as internal */
    CSL_MCBSP_TXRXCLKMODE_EXTERNAL    =                  0,
    /** clock source as external */
    CSL_MCBSP_TXRXCLKMODE_INTERNAL    =                  1
} CSL_McbspTxRxClkMode;
/**
@} */

/**
 * @defgroup CSL_MCBSP_FSPOLAR_ENUM Frame sync polarity
 * @ingroup CSL_MCBSP_ENUM
 *
 * @brief Frame sync polarity
 *
 * Use this symbol to set frame sync polarity as active-high or active-low
 * @{ */
typedef enum {
    /** frame sync polarity is active-high */
    CSL_MCBSP_FSPOL_ACTIVE_HIGH      =                  0,
    /** frame sync polarity is active-low */
    CSL_MCBSP_FSPOL_ACTIVE_LOW       =                  1
} CSL_McbspFsPol;
/**
@} */

/**
 * @defgroup CSL_MCBSP_CLKPOLAR_ENUM Clock polarity
 * @ingroup CSL_MCBSP_ENUM
 *
 * @brief Clock polarity
 *
 * Use this symbol to set XMT or RCV clock polarity as rising or falling edge
 * @{ */
typedef enum {
    /** XMT clock polarity is rising edge */
    CSL_MCBSP_CLKPOL_TX_RISING_EDGE      =                 0,
    /** RCV clock polarity is falling edge */
    CSL_MCBSP_CLKPOL_RX_FALLING_EDGE     =                 0,
    /** SRG clock polarity is rising edge */
    CSL_MCBSP_CLKPOL_SRG_RISING_EDGE     =                 0,
    /** XMT clock polarity is falling edge */
    CSL_MCBSP_CLKPOL_TX_FALLING_EDGE     =                 1,
    /** RCV clock polarity is rising edge */
    CSL_MCBSP_CLKPOL_RX_RISING_EDGE      =                 1,
    /** SRG clock polarity Is falling edge */
    CSL_MCBSP_CLKPOL_SRG_FALLING_EDGE    =                 1
} CSL_McbspClkPol;
/**
@} */

/**
 * @defgroup CSL_MCBSP_SRGCLK_ENUM SRG clock source
 * @ingroup CSL_MCBSP_ENUM
 *
 * @brief SRG clock source
 *
 * Use this symbol to select input clock source for Sample Rate Generator
 * @{ */
typedef enum {
    /** input clock source for Sample Rate Generator is CLKS pin */
    CSL_MCBSP_SRGCLK_CLKS                 =                  0,
    /** input clock source for Sample Rate Generator is CPU */
    CSL_MCBSP_SRGCLK_CLKCPU               =                  1,
    /** input clock source for Sample Rate Generator is BCLKR pin */
    CSL_MCBSP_SRGCLK_CLKR                 =                  2,
    /** input clock source for Sample Rate Generator is BCLKX pin */
    CSL_MCBSP_SRGCLK_CLKX                 =                  3
} CSL_McbspSrgClk;
/**
@} */

/**
 * @defgroup CSL_MCBSP_TXFSMODE_ENUM XMT Frame Sync generation mode
 * @ingroup CSL_MCBSP_ENUM
 *
 * @brief XMT Frame Sync generation mode
 *
 * Use this symbol to set XMT Frame Sync generation mode
 * @{ */
typedef enum {
    /** Disables the frame sync generation mode */
    CSL_MCBSP_TXFSMODE_DXRCOPY  =                  0,
    /** Enables the frame sync generation mode */
    CSL_MCBSP_TXFSMODE_SRG      =                  1
} CSL_McbspTxFsMode;
/**
@} */

/**
 * @defgroup CSL_MCBSP_EMU_ENUM Emulation mode setting
 * @ingroup CSL_MCBSP_ENUM
 *
 * @brief Emulation mode setting
 *
 * Use this symbol to set the Emulation Mode
 * @{ */
typedef enum {
    /** Emulation mode stop */
    CSL_MCBSP_EMU_STOP             =                  0,
    /** Emulation mode TX stop */
    CSL_MCBSP_EMU_TX_STOP          =                  1,
    /** Emulation free run mode */
    CSL_MCBSP_EMU_FREERUN          =                  2
} CSL_McbspEmu;
/**
@} */

/**
 * @defgroup CSL_MCBSP_CHANTYPE_ENUM Channel type: TX, RX or both
 * @ingroup CSL_MCBSP_ENUM
 *
 * @brief Channel type: TX, RX ot both
 *
 * Use this symbol to select the channel type for @a CSL_mcbspHwControl()
 * @a CSL_MCBSP_CMD_CLEAR_FRAME_SYNC command
 * @{ */
typedef enum {
    /** Channel type is RX */
    CSL_MCBSP_CHTYPE_RX                   =             1,
    /** Channel type is TX */
    CSL_MCBSP_CHTYPE_TX                   =             2,
    /** Channel type is TXRX */
    CSL_MCBSP_CHTYPE_TXRX                 =             4
} CSL_McbspChType;
/**
@} */

/**
 * @defgroup CSL_MCBSP_DLBMODE_ENUM Digital Loopback mode selection
 * @ingroup CSL_MCBSP_ENUM
 *
 * @brief Digital Loopback mode selection
 *
 * Use this symbol to enable/disable digital loopback mode
 * @{ */
typedef enum {
    /** disable digital loopback mode */
    CSL_MCBSP_DLBMODE_OFF                  =            0,
    /** enable digital loopback mode */
    CSL_MCBSP_DLBMODE_ON                   =            1
} CSL_McbspDlbMode;
/**
@} */

/**
 * @defgroup CSL_MCBSP_PHASE_ENUM Phase count selection
 * @ingroup CSL_MCBSP_ENUM
 *
 * @brief Phase count selection
 *
 * Use this symbol to select number of phases per frame
 * @{ */
typedef enum {
    /** Single phase for frame */
    CSL_MCBSP_PHASE_SINGLE                =             0,
    /** Dual phase for frame */
    CSL_MCBSP_PHASE_DUAL                  =             1
} CSL_McbspPhase;
/**
@} */

/**
 * @defgroup CSL_MCBSP_FRMSYNC_ENUM Frame sync ignore status
 * @ingroup CSL_MCBSP_ENUM
 *
 * @brief Frame sync ignore status
 *
 * Use this symbol to detect or ignore frame synchronisation
 * @{ */
typedef enum {
    /** detect frame synchronisation */
    CSL_MCBSP_FRMSYNC_DETECT                  =         0,
    /** ignore frame synchronisation */
    CSL_MCBSP_FRMSYNC_IGNORE                  =         1
} CSL_McbspFrmSync;
/**
@} */

/**
 * @defgroup CSL_MCBSP_RJUSTDXENA_ENUM RJUST or DXENA settings
 * @ingroup CSL_MCBSP_ENUM
 *
 * @brief RJUST or DXENA settings
 *
 * Use this symbol for setting up RCV sign-extension and justification mode
 * or enabling/disabling XMT DX pin delay
 * @{ */
typedef enum {
    /** RCV setting - right justify, fill MSBs with zeros */
    CSL_MCBSP_RJUSTDXENA_RJUST_RZF                 =    0,
    /** RCV setting - right justify, sign-extend the data into MSBs */
    CSL_MCBSP_RJUSTDXENA_RJUST_RSE                 =    1,
    /** RCV setting - left justify, fill LSBs with zeros */
    CSL_MCBSP_RJUSTDXENA_RJUST_LZF                 =    2
} CSL_McbspRjustDxena;
/**
@} */

/**
 * @defgroup CSL_MCBSP_CLKGSYNCMODE_ENUM CLKG sync mode selection
 * @ingroup CSL_MCBSP_ENUM
 *
 * @brief CLKG sync mode selection
 *
 * Use this symbol to enable/disable CLKG synchronisation when
 * input CLK source for SRGR is external
 * @{ */
typedef enum {
    /** disable CLKG synchronisation */
    CSL_MCBSP_CLKGSYNCMODE_OFF                 =        0,
    /** enable CLKG synchronisation */
    CSL_MCBSP_CLKGSYNCMODE_ON                  =        1
} CSL_McbspClkgSyncMode;
/**
@} */

/**
 * @defgroup CSL_MCBSP_RSTSTAT_ENUM Tx/Rx reset status
 * @ingroup CSL_MCBSP_ENUM
 *
 * @brief Tx/Rx reset status
 *
 * Use this symbol to compare the output of @a CSL_mcbspGetHwStatus() for
 * @a CSL_MCBSP_QUERY_TX_RST_STAT and @a CSL_MCBSP_QUERY_RX_RST_STAT queries
 *
 * @{ */
typedef enum {
    /** disable the XRST bit */
    CSL_MCBSP_RSTSTAT_TX_IN_RESET             =         0,
    /** disable the RRST bit */
    CSL_MCBSP_RSTSTAT_RX_IN_RESET             =         0,
    /** enable the XRST bit */
    CSL_MCBSP_RSTSTAT_TX_OUTOF_RESET          =         1,
    /** enaable the RRST bit */
    CSL_MCBSP_RSTSTAT_RX_OUTOF_RESET          =         1
} CSL_McbspRstStat;
/**
@} */


/**
 * @defgroup CSL_MCBSP_BITREVERS_ENUM 32-bit Reversal
 * @ingroup CSL_MCBSP_ENUM
 *
 * @brief McBSP512 32-bit reversal feature
 *
 *
 * @{ */
typedef enum {
    CSL_MCBSP_32BIT_REVERS_DISABLE  = 0,/**< 32-bit reversal disabled */
    CSL_MCBSP_32BIT_REVERS_ENABLE    = 1 /**< 32-bit reversal enabled. 32-bit
          data is received LSB first. Word length should be set for
          32-bit operation; else operation undefined  */
} CSL_McbspBitReversal;
/**
@} */


/**
 * @defgroup CSL_MCBSP_DXSTATE_ENUM DX Pin State
 * @ingroup CSL_MCBSP_ENUM
 *
 * @brief Transmit pin mode configuration
 *
 *
 * @{ */
typedef enum {
    /**< High Z */
    CSL_MCBSP_DX_HIGHZ   = 0,
    /**< Driven as 1 */
    CSL_MCBSP_DX_LOGIC_1 = 1,
    /**< Driven as 0 */
    CSL_MCBSP_DX_LOGIC_0 = 2
} CSL_McbspDxState;
/**
@} */


/**
 * @defgroup CSL_MCBSP_CONTROLCMD_ENUM Control commands
 * @ingroup CSL_MCBSP_CONTROL_API
 * @{ */
/**
 * This is the set of control commands that are passed to
 * @a CSL_mcbspHwControl(), with an optional argument type-casted to @a void*
 *
 * The arguments, if any, to be passed with each command are specified
 * next to that command.
 */
typedef enum {
/**
 * Clears frame sync error for XMT or RCV
 *
 * @param (CSL_McbspChType *)
 * @return CSL_SOK
 */
    CSL_MCBSP_CMD_CLEAR_FRAME_SYNC =                  0,
/**
 * Configures selected MCBSP pins for Input/Output
 *
 * @param (CSL_McbspIoControl *)
 * @return CSL_SOK
 */
    CSL_MCBSP_CMD_IO_MODE_CONTROL  =                  1,

/**
 * Resets all the registers to their power-on default values
 *
 * @param None
 * @return CSL_SOK
 */
    CSL_MCBSP_CMD_REG_RESET        =                  2,

/**
 *  Enable/Disable - Frame Sync, Sample Rate Generator and XMT/RCV Operation
 *
 * @param (CSL_BitMask16 *)
 * @return CSL_SOK
 */
    CSL_MCBSP_CMD_RESET_CONTROL    =                  3

} CSL_McbspControlCmd;
/**
@} */

/**
 * @defgroup CSL_MCBSP_QUERYCMD_ENUM Query commands
 * @ingroup CSL_MCBSP_QUERY_API
 * @{ */
/**
 * This is the set of query commands to get the status of various
 * operations in MCBSP
 *
 * The arguments, if any, to be passed with each command are specified
 * next to that command. */
typedef enum {
/**
 * Queries the status of RRDY, XRDY, RFULL, XEMPTY, RSYNCERR and XSYNCERR
 * events and returns them in supplied CSL_BitMask16 argument
 *
 *
 * @param  (CSL_BitMask16 *)
 * @return CSL_SOK
 * @see CSL_DEVSTATUS_SYMBOL
 */
    CSL_MCBSP_QUERY_DEV_STATUS =                     1,
/**
 * Queries XMT reset status
 *
 * @param  (CSL_McbspRstStat *)
 * @return CSL_SOK
 */
    CSL_MCBSP_QUERY_TX_RST_STAT =                    2,
/**
 * Queries RCV reset status
 *
 * @param  (CSL_McbspRstStat *)
 * @return CSL_SOK
 */
    CSL_MCBSP_QUERY_RX_RST_STAT =                    3
} CSL_McbspHwStatusQuery;
/**
@} */

/**
 * @brief This will have the base-address information for the peripheral
 *  instance
 */
typedef struct {
    /** Base-address of the Configuration registers of MCBSP.
     */
    CSL_McbspRegsOvly regs;
} CSL_McbspBaseAddress;

/**
 * @brief MCBSP specific parameters. Present implementation doesn't have
 *  any specific parameters.
 */
typedef struct {
    /** Bit mask to be used for module specific parameters.
     *  The below declaration is just a place-holder for future
     *  implementation.
     */
    CSL_BitMask16   flags;
} CSL_McbspParam;

/**
 * @brief MCBSP specific context information. Present implementation doesn't
 *  have any Context information.
 */

typedef struct {
    /** Context information of MCBSP.
     *  The below declaration is just a place-holder for future
     *  implementation.
     */
    Uint16  contextInfo;
} CSL_McbspContext;

/** @addtogroup CSL_MCBSP_DATASTRUCT
*
* @{ */
/**
 * @brief Pointer to this structure is used as the third argument in
 * @a CSL_mcbspHwControl() for IO mode control operations (selecting the pins
 *        to use as input and output.
 */
typedef struct CSL_McbspIoControl {
    /** Pinmask to select one or more output pins */
    CSL_BitMask16           outputsel;

    /** Pinmask to select one or more input pins */
    CSL_BitMask16           inputsel;
} CSL_McbspIoControl;
/**
@} */


/** @addtogroup CSL_MCBSP_DATASTRUCT
*
* @{ */
/**
 * @brief This is a sub-structure in @ CSL_McbspHwSetup. This structure is
 *        used for configuring input/output data related parameters.
 */
typedef struct CSL_McbspDataSetup {
    /** Number of phases in a frame */
    CSL_McbspPhase              phaseNum;

    /** Number of bits per word in phase 1 */
    CSL_McbspWordLen     wordLength1;

    /** Number of words per frame in phase 1 */
    Uint16              frmLength1;

    /** Number of bits per word in phase 2 */
    CSL_McbspWordLen     wordLength2;

    /** Number of words per frame in phase 2 */
    Uint16              frmLength2;

    /** Frame Sync ignore */
    CSL_McbspFrmSync              frmSyncIgn;

    /** Companding options */
    CSL_McbspCompand        compand;

    /** Data delay in number of bits */
    CSL_McbspDataDelay      dataDelay;

    /** Controls DX delay for XMT or sign-extension and justification for RCV*/
    CSL_McbspRjustDxena              rjust_dxenable;

    /** Interrupt event mask */
    CSL_McbspIntMode       IntEvent;

    /** 32-bit reversal feature */
    CSL_McbspBitReversal             wordReverse;
} CSL_McbspDataSetup;
/**
@} */

/** @addtogroup CSL_MCBSP_DATASTRUCT
*
* @{ */
/**
 * @brief This is a sub-structure in @a CSL_McbspHwSetup. This structure is
 *        used for configuring Clock and Frame Sync generation parameters.
 */
typedef struct CSL_McbspClkSetup {
    /** XMT frame sync mode */
    CSL_McbspFsClkMode        frmSyncTxMode;

    /** RCV frame sync mode */
    CSL_McbspFsClkMode        frmSyncRxMode;

    /** XMT clock mode */
    CSL_McbspTxRxClkMode      clkTxMode;

    /** RCV clock mode */
    CSL_McbspTxRxClkMode      clkRxMode;

    /** XMT frame sync polarity */
    CSL_McbspFsPol            frmSyncTxPolarity;

    /** RCV frame sync polarty */
    CSL_McbspFsPol            frmSyncRxPolarity;

    /** XMT clock polarity */
    CSL_McbspClkPol           clkTxPolarity;

    /** RCV clock polarity */
    CSL_McbspClkPol           clkRxPolarity;

    /** SRG frame sync pulse width */
    Uint16                    srgFrmPulseWidth;

    /** SRG frame sync period */
    Uint16                    srgFrmPeriod;

    /** SRG divide-down ratio */
    Uint16                    srgClkDivide;

    /** SRG input clock mode */
    CSL_McbspSrgClk           srgInputClkMode;

    /** SRG XMT frame-synchronisatoin mode */
    CSL_McbspTxFsMode         srgTxFrmSyncMode;
} CSL_McbspClkSetup;
/**
@} */

/** @addtogroup CSL_MCBSP_DATASTRUCT
*
* @{ */
/**
 * @brief This is the Setup structure for configuring MCBSP using
 *        @a CSL_mcbspHwSetup() function.
 */
typedef struct CSL_McbspHwSetup {
    /** Digital Loopback mode */
    CSL_McbspDlbMode        dlbMode;

    /** RCV data setup related parameters */
    CSL_McbspDataSetup      *rxdataset;

    /** XMT data setup related parameters */
    CSL_McbspDataSetup      *txdataset;

    /** Clock configuration parameters */
    CSL_McbspClkSetup       *clkset;

    /** Emulation mode parameters */
    CSL_McbspEmu            emumode;

   /**  Transmit pin mode configuration, this is used to configure the DX pin
        state while the time slot is disabled */
    CSL_McbspDxState        dxState;

    /** Any extra parameters, for future use */
    void                    *extendSetup;
} CSL_McbspHwSetup;
/**
@} */

/** @addtogroup CSL_MCBSP_DATASTRUCT
*
* @{ */
/**
 * @brief This structure/object holds the context of the instance of MCBSP
 * opened using @a CSL_mcbspOpen() function.
 *
 * Pointer to this object is passed as MCBSP Handle to all MCBSP CSL APIs.
 * @a CSL_mcbspOpen() function intializes this structure based on the
 * parameters passed
 */
typedef struct CSL_McbspObj {
    /** Pointer to the register overlay structure of the MCBSP */
    CSL_McbspRegsOvly    regs;

    /** Instance of MCBSP being referred by this object  */
    CSL_InstNum          perNum;
} CSL_McbspObj;

/** @brief This is a pointer to @a CSL_McbspObj and is passed as the first
 * parameter to all MCBSP CSL APIs
 */
typedef struct CSL_McbspObj *CSL_McbspHandle;
/**
@} */

/**************************************************************************\
* Register Configuration Structure of MCBSP
\**************************************************************************/
/** @brief Config structure of MCBSP.
 *
 *  This is used to configure MCBSP using CSL_HwSetupRaw function
 */
typedef struct  {
    /** Config structure of MCBSP. This is used to configure MCBSP
     * using CSL_HwSetupRaw function
     */
    /** Data Transmit Register */
    volatile Uint32 DXR;
    /** Serial Port Control Register */
    volatile Uint32 SPCR;
    /** Receive Control Register */
    volatile Uint32 RCR;
    /** Transmit Control Register */
    volatile Uint32 XCR;
    /** Sample Rate Generator Register */
    volatile Uint32 SRGR;
    /** Pin Control Register */
    volatile Uint32 PCR;
} CSL_McbspConfig;

/** Default Values for Config structure */
#define CSL_MCBSP_CONFIG_DEFAULTS { \
    CSL_MCBSP_DXR_RESETVAL,     \
    CSL_MCBSP_SPCR_RESETVAL,    \
    CSL_MCBSP_RCR_RESETVAL,     \
    CSL_MCBSP_XCR_RESETVAL,     \
    CSL_MCBSP_SRGR_RESETVAL,    \
    CSL_MCBSP_PCR_RESETVAL      \
}

/* ************************************************************************\
 * MCBSP global function declarations
\* ************************************************************************/

/** ===========================================================================
 *   @n@b CSL_mcbspInit
 *
 *   @b Description
 *   @n This function is idempotent in that calling it many times is same as
 *        calling it once.This function initializes the MCBSP CSL data
 *        structures.
 *
 *
 *   @b Arguments
 *   @verbatim
           pContext   Context information for the instance. Should be NULL
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK (Always)
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  CSL system initialization must be successfully completed by invoking
 *     @a CSL_sysInit() before calling this function. This function should be
 *     called before using any of the CSL MCBSP APIs
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
         ...

         CSL_mcbspInit(pContext);

     @endverbatim
 *  ===========================================================================
 */
CSL_Status  CSL_mcbspInit(
    CSL_McbspContext * pContext
);


/** ===========================================================================
 *   @n@b CSL_mcbspOpen
 *
 *   @b Description
 *   @n This function populates the peripheral data object for the MCBSP
 *      instance and returns a handle to the instance.
 *        The open call sets up the data structures for the particular instance
 *        of MCBSP device. The device can be re-opened anytime after it has been
 *      normally closed if so required. The handle returned by this call is
 *      input as an essential argument for rest of the APIs described for
 *      this module.
 *
 *   @b Arguments
 *   @verbatim
              hMcbspObj      Pointer to the MCBSP instance object

              mcbspNum       Instance of the MCBSP to be opened

              pMcbspParam    Pointer to module specific parameters

              pStatus        pointer for returning status of the function call
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_McbspHandle
 *   @n                     Valid MCBSP instance handle will be returned if
                            status value is equal to CSL_SOK.
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n   1.    MCBSP object structure is populated
 *   @n   2.    The status is returned in the status variable. If status
 *              returned is
 *   @li            CSL_SOK             Valid mcbsp handle is returned
 *   @li            CSL_ESYS_FAIL       The mcbsp instance is invalid
 *   @li            CSL_ESYS_INVPARAMS  Invalid parameter
 *
 *   @b Modifies
 *   @n    1. The status variable
 *   @n    2. MCBSP object structure
 *
 *   @b Example
 *   @verbatim
 *        CSL_McbspObj     mcbspObj;
 *        CSL_Status      status;
 *          ...
 *        hMcbsp = CSL_mcbspOpen(&mcbspObj,
 *                            CSL_MCBSP_0,
 *                            CSL_EXCLUSIVE,
 *                            &status);
    @endverbatim
 * ============================================================================
 */
CSL_McbspHandle CSL_mcbspOpen (
    /** Pointer to the object that holds reference to the
     *  instance of MCBSP requested after the call
     */
    CSL_McbspObj                           *hMcbspObj,
    /** Instance of MCBSP to which a handle is requested
     */
    CSL_InstNum                            mcbspNum,
    /** Specifies if MCBSP should be opened with exclusive or
     *  shared access to the associate pins
     */
    CSL_McbspParam            *pMcbspParam,
    /** This returns the status (success/errors) of the call
     */
    CSL_Status                *pStatus
);


/** ===========================================================================
 *   @n@b CSL_mcbspClose
 *
 *   @b Description
 *   @n This function closes the specified instance of MCBSP.
 *
 *   @b Arguments
 *   @verbatim
            hMcbsp            Handle to the MCBSP instance
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Close successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_mcbspInit() and @a CSL_mcbspOpen() must be called
 *       successfully in that order before @a CSL_mcbspClose() can be called.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
            CSL_McbspHandle      hMcbsp;
            CSL_status           status;

            ...

            status = CSL_mcbspClose(hMcbsp);
     @endverbatim
 * =============================================================================
 */
CSL_Status  CSL_mcbspClose(
    /** Pointer to the object that holds reference to the
     *  instance of MCBSP requested after the call
     */
    CSL_McbspHandle                        hMcbsp
);


/** ===========================================================================
 *   @n@b CSL_mcbspHwSetup
 *
 *   @b Description
 *   @n It configures the mcbsp registers as per the values passed
 *      in the hardware setup structure.
 *
 *   <b> Usage Constraints: </b>
 *   Both @a CSL_mcbspInit() and @a CSL_mcbspOpen() must be called successfully
 *   in that order before this function can be called. The setup structure
 *   consists of the logically grouped sub-structures. The main setup structure
 *   as well as these sub-structures must be filled up before calling this
 *   function
 *
 *   @b Arguments
 *   @verbatim
            hMcbsp          Handle to the MCBSP instance
            hwSetup         Pointer to harware setup structure
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Hardware setup successful.
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Hardware structure is not
                                                  properly initialized
 *
 *   @b Modifies
 *   @n The hardware registers of MCBSP.
 *
 *   @b Example
 *   @verbatim

     CSL_mcbspHandle hMcbsp;
     CSL_McbspHwSetup hwSetup = CSL_MCBSP_HWSETUP_DEFAULTS;
     ...

     // Init Successfully done
     ...
     // Open Successfully done
     ...
     CSL_mcbspHwSetup(hMcbsp, &hwSetup);
 *   @endverbatim
 * ============================================================================
 */
CSL_Status  CSL_mcbspHwSetup(
    CSL_McbspHandle                        hMcbsp,
    CSL_McbspHwSetup                       *setup
);


/** ============================================================================
 *   @n@b CSL_mcbspHwSetupRaw
 *
 *   @b Description
 *   @n This function initializes the device registers with the register-values
 *      provided through the Config Data structure.
 *
 *   @b Arguments
 *   @verbatim
            hMcbsp          Handle to the Mcbsp instance

            config          Pointer to config structure
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Configuration successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Configuration is not
 *                                                properly initialized
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The registers of the specified MCBSP instance will be setup
 *       according to value passed.
 *
 *   @b Modifies
 *   @n Hardware registers of the specified McBSP instance.
 *
 *   @b Example
 *   @verbatim
        CSL_McbspHandle       hMcbsp;
        CSL_McbspConfig       config = CSL_MCBSP_CONFIG_DEFAULTS;
        CSL_Status            status;

        status = CSL_mcbspHwSetupRaw (hMcbsp, &config);

     @endverbatim
 * ===========================================================================
 */
CSL_Status  CSL_mcbspHwSetupRaw (
    CSL_McbspHandle                        hMcbsp,
    CSL_McbspConfig *         config
);


/** ===========================================================================
 *   @n@b CSL_mcbspRead
 *
 *   @b Description
 *   @n Reads the data from MCBSP. The word length for the read operation is
 *      specefied using @a wordLen argument. According to this word length,
 *      appropriate amount of data will read in the data object (variable);
 *      the pointer to which is passed as the third argument.
 *
 *   @b Arguments
 *   @verbatim
            hMcbsp          Handle to the Mcbsp instance

            wordLen         length of the  word to be read.

            *data           address of the data read.
     @endverbatim
 *
 *   <b> Return Value </b>  Status of the operation
 *
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_mcbspInit() and @a CSL_mcbspOpen() must be called
 *       successfully in that order before @a CSL_mcbspRead() can be called.
 *
 *   <b> Post Condition </b>
 *   @n  None.
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
        Uint16     inData;
        CSL_Status status;
        CSL_McbspHandle hMcbsp;
        ...
        // MCBSP object defined and HwSetup structure defined and initialized
        ...

        // Init, Open, HwSetup successfully done in that order
        ...
        // MCBSP SRG, Frame sync, RCV taken out of reset in that order
        ...
        status = CSL_mcbspRead(hMcbsp,
                             CSL_MCBSP_WORDLEN_16
                             &inData);

     @endverbatim
 * ===========================================================================
 */
CSL_Status  CSL_mcbspRead(
    CSL_McbspHandle                         hMcbsp,
    CSL_McbspWordLen                        wordLen,
    void                                    *data
);


/** ===========================================================================
 *   @n@b CSL_mcbspWrite
 *
 *   @b Description
 *   @n Transmits the data from MCBSP. The word length for the write operation
 *      is specified using @a wordLen argument. According to this word length,
 *      the appropriate amount of data will transmitted from the data object
 *      (variable); the pointer to which is passed as the third argument.
 *
 *   @b Arguments
 *   @verbatim
            hMcbsp          Handle to the Mcbsp instance

            wordLen         length of the data to be wriiten.

            data            address of data to be wriiten.
     @endverbatim
 *
 *   <b> Return Value </b>  Status of the operation
 *
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_mcbspInit() and @a CSL_mcbspOpen() must be called
 *       successfully in that order before @a CSL_mcbspRead() can be called.
 *
 *   <b> Post Condition </b>
 *   @n  The registers of the specified MCBSP instance will be setup
 *       according to value passed.
 *
 *   @b Modifies
 *   @n Hardware registers of the specified NAND instance.
 *
 *   @b Example
 *   @verbatim
      Uint16     outData;
      CSL_Status status;
      CSL_McbspHandle hMcbsp;
      ...
      // MCBSP object defined and HwSetup structure defined and initialized
      ...

      // Init, Open, HwSetup successfully done in that order
      ...
      // MCBSP SRG, Frame sync, XMT taken out of reset in that order
      ...
      outData = 0x1234;
      status = CSL_mcbspWrite(hMcbsp,
                             CSL_MCBSP_WORDLEN_16
                             &outData);
     @endverbatim
 * ===========================================================================
 */
CSL_Status  CSL_mcbspWrite(
    CSL_McbspHandle                         hMcbsp,
    CSL_McbspWordLen                        wordLen,
    void                                    *data
);


/** ===========================================================================
 *   @n@b CSL_mcbspIoWrite
 *
 *   @b Description
 *   @n Sends the data using MCBSP pin which is configured as general purpose
 *      output. The 16-bit data trasnmitted is specified by 'outputData'
 *      argument. MCBSP pin to use in this write operation is identified by
 *      the second arguement.
 *
 *   @b Arguments
 *   @verbatim
            hMcbsp      MCBSP handle returned by successful 'open'

            outputSel   MCBSP pin to be used as general purpose output

            outputData  1 bit output data to be transmitted
 *   @endverbatim
 *
 *   <b> Return Value </b> None
 *
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_mcbspInit() and @a CSL_mcbspOpen() must be called
 *       successfully in that order before @a CSL_mcbspIoWrite() can be called.
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
        Uint16     outData;
        CSL_Status status;
        CSL_McbspHandle hMcbsp;
        ...
        // MCBSP object defined and HwSetup structure defined and initialized
        ...

        // Init, Open, HwSetup successfully done in that order
        ...
        outData = 1;
        inData = CSL_mcbspIoWrite(hMcbsp, CSL_MCBSP_IO_CLKX, outData);

 *   @endverbatim
 *  ===========================================================================
 */
void  CSL_mcbspIoWrite(
    CSL_McbspHandle                         hMcbsp,
    CSL_BitMask16                           outputSel,
    Uint16                                  outputData
);


/** ===========================================================================
 *   @n@b CSL_mcbspIoRead
 *
 *   @b Description
 *   @n Reads the data from MCBSP pin which is configured as general purpose
 *      input. The 16-bit data read from this pin is returned by this API.
 *      MCBSP pin to use in this read operation is identified by the second
 *      arguement.
 *
 *   @b Arguments
 *   @verbatim
            hMcbsp     MCBSP handle returned by successful 'open'

            inputSel   MCBSP pin to be used as general purpose input
 *   @endverbatim
 *
 *   <b> Return Value </b> Uint16 : data read from the pin(s)
 *
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_mcbspInit() and @a CSL_mcbspOpen() must be called
 *       successfully in that order before @a CSL_mcbspIoRead() can be called.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n Pin Control register of the MCBSP.
 *
 *
 *   @b Example
 *   @verbatim
         ...
         Uint16     inData, clkx_data, clkr_data;
         CSL_Status status;
         CSL_BitMask16 inMask;
         CSL_McbspHandle hMcbsp;
         ...
         // MCBSP object defined and HwSetup structure defined and initialized
         ...

         // Init, Open, HwSetup successfully done in that order
         ...
         inMask = CSL_MCBSP_IO_CLKX | CSL_MCBSP_IO_CLKR;
         inData = CSL_mcbspIoRead(hMcbsp, inMask);
         if ((inData & CSL_MCBSP_IO_CLKX) != 0) clkx_data = 1;
         else clkx_data = 0;
         if ((inData & CSL_MCBSP_IO_CLKR) != 0) clkr_data = 1;
         else clkr_data = 0;

 *   @endverbatim
 *  ===========================================================================
 */
Uint16  CSL_mcbspIoRead(
    CSL_McbspHandle                         hMcbsp,
    CSL_BitMask16                           inputSel
);


/** ===========================================================================
 *   @n@b CSL_mcbspHwControl
 *
 *   @b Description
 *   @n This function takes an input control command with an optional argument
 *      and accordingly controls the operation/configuration of MCBSP.
 *
 *   @b Arguments
 *   @verbatim
            hMcbsp          Handle to the MCBSP instance

            cmd             The command to this API indicates the action to be
                            taken on MCBSP.

            arg             An optional argument.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             -Status info return successful.
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVCMD     - Invalid command
 *   @li                    CSL_ESYS_FAIL       - Invalid instance number
 *
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_mcbspInit() and @a CSL_mcbspOpen() must be called
 *       successfully in that order before @a CSL_mcbspHwControl() can be
 *       called. Refer to @a CSL_McbspHwControlCmd for the argument type
 *       (@a void*) that needs to be passed with the control command
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n The hardware registers of MCBSP.
 *
 *   @b Example
 *   @verbatim
        CSL_McbspHandle         hMcbsp;
        CSL_McbspHwControlCmd   cmd;
        void                    arg;

        status = CSL_mcbspHwControl (hMcbsp, cmd, &arg);

     @endverbatim
 * ============================================================================
 */
CSL_Status  CSL_mcbspHwControl(
    CSL_McbspHandle                         hMcbsp,
    CSL_McbspControlCmd                     cmd,
    void                                    *arg
);


/** ===========================================================================
 *   @n@b CSL_mcbspGetHwStatus
 *
 *   @b Description
 *   @n Gets the status of different operations or some setup-parameters of
 *      MCBSP. The status is returned through the third parameter.
 *
 *   @b Arguments
 *   @verbatim
            hMcbsp          Handle to the MCBSP instance

            myQuery         The query to this API of MCBSP which indicates the
                            status to be returned.                          

            response        Placeholder to return the status.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             -Status info return successful.
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVQUERY   - Invalid Query command
 *   @li                    CSL_ESYS_FAIL       - Invalid instance number
 *
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_mcbspInit() and @a CSL_mcbspOpen() must be called
 *       successfully in that order before @a CSL_mcbspGetHwStatus() can be 
 *       called. Refer to @a CSL_McbspHwStatusQuery for the argument to be 
 *       passed along with the corresponding query command.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        CSL_McbspHandle hMcbsp;
        CSL_Status status;
        Uint16 response;
        ...
        status = CSL_mcbspGetHwStatus(hMcbsp,
                                     CSL_MCBSP_QUERY_DEV_STATUS,
                                     &response);
        
        if (response & CSL_MCBSP_RRDY) {
            // Receiver is ready to with new data
            ...
        }

     @endverbatim
 * ============================================================================
 */
CSL_Status  CSL_mcbspGetHwStatus(
    CSL_McbspHandle                         hMcbsp,
    CSL_McbspHwStatusQuery                  myQuery,
    void                                    *response
);


/** ===========================================================================
 *   @n@b CSL_mcbspGetHwSetup
 *
 *   @b Description
 *   @n Gets the status of some or all of the setup-parameters of MCBSP.
 *      To get the status of complete MCBSP h/w setup, all the sub-structure
 *      pointers inside the main HwSetup structure, should be non-NULL.
 *
 *   @b Arguments
 *   @verbatim
            hMcBSP          Handle to the MCBSP instance

            setup           Pointer to setup structure which contains the
                            setup information of MCBSP.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Setup info load successful.
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid parameter
 *
 *   <b> Pre Condition </b>
 *   @n Both @a CSL_mcbspInit() and @a CSL_mcbspOpen() must be called 
 *      successfully in that order before @a CSL_mcbspGetHwSetup() can be 
 *      called.
 *
 *   <b> Post Condition </b>
 *   @n  The registers of the specified MCBSP instance will be setup.
 *
 *   @b Modifies
 *   @n Hardware registers of the specified MCBSP instance.
 *
 *   @b Example
 *   @verbatim
        CSL_McBSPHandle       hMcBSP;
        CSL_McBSPHwSetup      setup;
        CSL_Status            status;

        status = CSL_mcbspGetHwSetup (hMcBSP, &setup);
     @endverbatim
 * ============================================================================
 */  
CSL_Status  CSL_mcbspGetHwSetup(
    CSL_McbspHandle                         hMcbsp,
    CSL_McbspHwSetup                       *myHwSetup
);


/** ===========================================================================
 *   @n@b CSL_mcbspGetBaseAddress
 *
 *   @b Description
 *   @n  Function to get the base address of the peripheral instance.
 *       This function is used for getting the base address of the peripheral
 *       instance. This function will be called inside the CSL_mcbspOpen()
 *       function call. This function is open for re-implementing if the user
 *       wants to modify the base address of the peripheral object to point to
 *       a different location and there by allow CSL initiated write/reads into
 *       peripheral MMR's go to an alternate location.
 *
 *   @b Arguments
 *   @verbatim
            mcbspNum          Specifies the instance of MCBSP to be opened.

            pMcbspParam       Module specific parameters.

            pBaseAddress    Pointer to baseaddress structure containing base
                            address details.

     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_OK            Open call is successful
 *   @li                    CSL_ESYS_FAIL     The instance number is invalid.
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  Base Address structure is populated
 *
 *   @b Modifies
 *   @n    1. The status variable
 *
 *         2. Base address structure is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_Status              status;
        CSL_McbspBaseAddress  baseAddress;

       ...
      status = CSL_mcbspGetBaseAddress(CSL_MCBSP_PER_CNT, NULL, &baseAddress);

    @endverbatim
 * ===========================================================================
 */
CSL_Status   CSL_mcbspGetBaseAddress (
        CSL_InstNum              mcbspNum,
        CSL_McbspParam           *pMcbspParam,
        CSL_McbspBaseAddress     *pBaseAddress
);


#ifdef __cplusplus
}
#endif

#endif

