/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */

#ifndef _SOC_H_
#define _SOC_H_

/* ============================================================================
 *  Revision History
 *  ===============
 *  14-Mar-2005 brn Moved the Event Ids from csl_intc.h to soc64plus.h
 *  24-Aug-2005 brn Moved the soc64pls.h and socEdma.h.
 * ============================================================================
 */

#include <cslr.h>
/**************************************************************************\
* 64 soc file
\**************************************************************************/

/** @brief Definition for static inline */
#ifndef CSL_IDEF_INLINE
#define CSL_IDEF_INLINE static inline
#endif



/** @brief Bandwidth Management instance number */
#define CSL_BWMNGMT                         (0)

/** @brief CACHE instance number */
#define CSL_CACHE                           (0)

/** @brief EDC instance number */
#define CSL_EDC                             (0)

/** @brief EDMA instance number */
#define CSL_EDMA                            (0)

/** @brief IDMA instance number */
#define CSL_IDMA                            (0)

/** @brief Interrupt controller instance number */
#define CSL_INTC                            (0)

/** @brief MCBSP instance number */
#define CSL_MCBSP                           (0)

/** @brief Memory Protection L2 instance number */
#define CSL_MEMPROT_L2                      (0)

/** @brief Memory Protection L1P instance number */
#define CSL_MEMPROT_L1P                     (1)

/** @brief Memory Protection L1D instance number */
#define CSL_MEMPROT_L1D                     (2)

/** @brief Memory Protection Config (CFG) instance number */
#define CSL_MEMPROT_CONFIG                  (3)

/** @brief Power down instance number */
#define CSL_PWRDWN                          (0)


/** @brief Bandwidth Management module base address */
#define CSL_BWMNGMT_0_REGS                  (0x01820200u)

/** #brief Cache Module base address  */
#define CSL_CACHE_0_REGS                    (0x01840000u)

/** @brief EDC module base address */
#define CSL_EDC_0_REGS                      (0x01846000u)

/** @brief Base address of Channel controller  module base address */
#define CSL_EDMACC_0_REGS                   (0x01C00000u)

/** @brief Base address of Transfer controller0 module base address */
#define CSL_EDMATC_0_REGS                   ( 0x1C10000u)

/** @brief Base address of Transfer controller1 module base address */
#define CSL_EDMATC_1_REGS                   ( 0x1C10400u)

/** @brief IDMA module base address */
#define CSL_IDMA_0_REGS                     (0x01820000u)

/** @brief Base address of INTC module base address */
#define CSL_INTC_0_REGS                     (0x01800000u)

/** @brief Base address of MCBSP module base address */
#define CSL_MCBSP_0_REGS                    (0x01E02000)


/*  Memory Protection specific details */
/** @brief Base address of UMC Memory protection module base address */
#define CSL_MEMPROT_L2_REGS                 (0x184A000u)

/** @brief Base address of PMC memory Protection module base address */
#define CSL_MEMPROT_L1P_REGS                (0x184A400u)

/** @brief Base address of DMC memory protection module base address */
#define CSL_MEMPROT_L1D_REGS                (0x184AC00u)

/** @brief Base address of CONFIG memory protection module base address */
#define CSL_MEMPROT_CONFIG_REGS             (0x1820300u)

/** @brief Base address of PDC module base address */
#define CSL_PWRDWN_PDC_REGS                 (0x01810000)

/** @brief Base address of L2 power Down module base address */
#define CSL_PWRDWN_L2_REGS                  (0x0184c000)

/*****************************************************************************\
* Interrupt Event IDs
\*****************************************************************************/

/**
 * @brief   Interrupt Event IDs
 */
#define    CSL_INTC_EVENTID_0       (0)
#define    CSL_INTC_EVENTID_1       (1)
#define    CSL_INTC_EVENTID_2       (2)
#define    CSL_INTC_EVENTID_3       (3)
#define    CSL_INTC_EVENTID_4       (4)
#define    CSL_INTC_EVENTID_5       (5)
#define    CSL_INTC_EVENTID_6       (6)
#define    CSL_INTC_EVENTID_7       (7)
#define    CSL_INTC_EVENTID_8       (8)
#define    CSL_INTC_EVENTID_9       (9)
#define    CSL_INTC_EVENTID_10      (10)
#define    CSL_INTC_EVENTID_11      (11)
#define    CSL_INTC_EVENTID_12      (12)
#define    CSL_INTC_EVENTID_13      (13)
#define    CSL_INTC_EVENTID_14      (14)
#define    CSL_INTC_EVENTID_15      (15)
#define    CSL_INTC_EVENTID_16      (16)
#define    CSL_INTC_EVENTID_17      (17)
#define    CSL_INTC_EVENTID_18      (18)
#define    CSL_INTC_EVENTID_19      (19)
#define    CSL_INTC_EVENTID_20      (20)
#define    CSL_INTC_EVENTID_21      (21)
#define    CSL_INTC_EVENTID_22      (22)
#define    CSL_INTC_EVENTID_23      (23)
#define    CSL_INTC_EVENTID_24      (24)
#define    CSL_INTC_EVENTID_25      (25)
#define    CSL_INTC_EVENTID_26      (26)
#define    CSL_INTC_EVENTID_27      (27)
#define    CSL_INTC_EVENTID_28      (28)
#define    CSL_INTC_EVENTID_29      (29)
#define    CSL_INTC_EVENTID_30      (30)
#define    CSL_INTC_EVENTID_31      (31)
#define    CSL_INTC_EVENTID_32      (32)
#define    CSL_INTC_EVENTID_33      (33)
#define    CSL_INTC_EVENTID_34      (34)
#define    CSL_INTC_EVENTID_35      (35)
#define    CSL_INTC_EVENTID_36      (36)
#define    CSL_INTC_EVENTID_37      (37)
#define    CSL_INTC_EVENTID_38      (38)
#define    CSL_INTC_EVENTID_39      (39)
#define    CSL_INTC_EVENTID_40      (40)
#define    CSL_INTC_EVENTID_41      (41)
#define    CSL_INTC_EVENTID_42      (42)
#define    CSL_INTC_EVENTID_43      (43)
#define    CSL_INTC_EVENTID_44      (44)
#define    CSL_INTC_EVENTID_45      (45)
#define    CSL_INTC_EVENTID_46      (46)
#define    CSL_INTC_EVENTID_47      (47)
#define    CSL_INTC_EVENTID_48      (48)
#define    CSL_INTC_EVENTID_49      (49)
#define    CSL_INTC_EVENTID_50      (50)
#define    CSL_INTC_EVENTID_51      (51)
#define    CSL_INTC_EVENTID_52      (52)
#define    CSL_INTC_EVENTID_53      (53)
#define    CSL_INTC_EVENTID_54      (54)
#define    CSL_INTC_EVENTID_55      (55)
#define    CSL_INTC_EVENTID_56      (56)
#define    CSL_INTC_EVENTID_57      (57)
#define    CSL_INTC_EVENTID_58      (58)
#define    CSL_INTC_EVENTID_59      (59)
#define    CSL_INTC_EVENTID_60      (60)
#define    CSL_INTC_EVENTID_61      (61)
#define    CSL_INTC_EVENTID_62      (62)
#define    CSL_INTC_EVENTID_63      (63)
#define    CSL_INTC_EVENTID_64      (64)
#define    CSL_INTC_EVENTID_65      (65)
#define    CSL_INTC_EVENTID_66      (66)
#define    CSL_INTC_EVENTID_67      (67)
#define    CSL_INTC_EVENTID_68      (68)
#define    CSL_INTC_EVENTID_69      (69)
#define    CSL_INTC_EVENTID_70      (70)
#define    CSL_INTC_EVENTID_71      (71)
#define    CSL_INTC_EVENTID_72      (72)
#define    CSL_INTC_EVENTID_73      (73)
#define    CSL_INTC_EVENTID_74      (74)
#define    CSL_INTC_EVENTID_75      (75)
#define    CSL_INTC_EVENTID_76      (76)
#define    CSL_INTC_EVENTID_77      (77)
#define    CSL_INTC_EVENTID_78      (78)
#define    CSL_INTC_EVENTID_79      (79)
#define    CSL_INTC_EVENTID_80      (80)
#define    CSL_INTC_EVENTID_81      (81)
#define    CSL_INTC_EVENTID_82      (82)
#define    CSL_INTC_EVENTID_83      (83)
#define    CSL_INTC_EVENTID_84      (84)
#define    CSL_INTC_EVENTID_85      (85)
#define    CSL_INTC_EVENTID_86      (86)
#define    CSL_INTC_EVENTID_87      (87)
#define    CSL_INTC_EVENTID_88      (88)
#define    CSL_INTC_EVENTID_89      (89)
#define    CSL_INTC_EVENTID_90      (90)
#define    CSL_INTC_EVENTID_91      (91)
#define    CSL_INTC_EVENTID_92      (92)
#define    CSL_INTC_EVENTID_93      (93)
#define    CSL_INTC_EVENTID_94      (94)
#define    CSL_INTC_EVENTID_95      (95)
#define    CSL_INTC_EVENTID_96      (96)
#define    CSL_INTC_EVENTID_97      (97)
#define    CSL_INTC_EVENTID_98      (98)
#define    CSL_INTC_EVENTID_99      (99)
#define    CSL_INTC_EVENTID_100     (100)
#define    CSL_INTC_EVENTID_101     (101)
#define    CSL_INTC_EVENTID_102     (102)
#define    CSL_INTC_EVENTID_103     (103)
#define    CSL_INTC_EVENTID_104     (104)
#define    CSL_INTC_EVENTID_105     (105)
#define    CSL_INTC_EVENTID_106     (106)
#define    CSL_INTC_EVENTID_107     (107)
#define    CSL_INTC_EVENTID_108     (108)
#define    CSL_INTC_EVENTID_109     (109)
#define    CSL_INTC_EVENTID_110     (110)
#define    CSL_INTC_EVENTID_111     (111)
#define    CSL_INTC_EVENTID_112     (112)
#define    CSL_INTC_EVENTID_113     (113)
#define    CSL_INTC_EVENTID_114     (114)
#define    CSL_INTC_EVENTID_115     (115)
#define    CSL_INTC_EVENTID_116     (116)
#define    CSL_INTC_EVENTID_117     (117)
#define    CSL_INTC_EVENTID_118     (118)
#define    CSL_INTC_EVENTID_119     (119)
#define    CSL_INTC_EVENTID_120     (120)
#define    CSL_INTC_EVENTID_121     (121)
#define    CSL_INTC_EVENTID_122     (122)
#define    CSL_INTC_EVENTID_123     (123)
#define    CSL_INTC_EVENTID_124     (124)
#define    CSL_INTC_EVENTID_125     (125)
#define    CSL_INTC_EVENTID_126     (126)
#define    CSL_INTC_EVENTID_127     (127)

/**************************************************************************\
*  Parameterizable Configuration:- These are fed directly from the RTL
*  parameters for the given SOC
\**************************************************************************/

#define CSL_EDMA_NUM_DMACH             64
#define CSL_EDMA_NUM_QDMACH            4
#define CSL_EDMA_NUM_PARAMENTRY        128
#define CSL_EDMA_NUM_EVQUE             2
#define CSL_EDMA_CHMAPEXIST            0
#define CSL_EDMA_NUM_REGIONS           4
#define CSL_EDMA_MEMPROTECT            0

/**************************************************************************\
* Channel Instance count
\**************************************************************************/
/** @brief Number of Generic Channel instances */
#define CSL_EDMA_CHA_CNT              68

/** @brief Enumerations for EDMA channels
 *
 *  There are 72 EDMA channels - 64 EDMA Channels and 8 QDMA Channels.
 *  The enum values indicate the number of the channel.
 *  This is passed as a parameter in @a CSL_dmaOpen() to indicate the
 *  channel instance that the user wants to acquire.  The CSL_DMA_CHA_ANY
 *  indicates the user is willing to use any available generic channel.
 *  The CSL_DMA_CHA_ANY does not apply to the dedicated LCD channel.
 *
 */

#define    CSL_EDMA_CHA0                      0  /**< Channel 0 */
#define    CSL_EDMA_CHA1                      1  /**< Channel 1 */
#define    CSL_EDMA_CHA2                      2  /**< Channel 2 */
#define    CSL_EDMA_CHA3                      3  /**< Channel 3 */
#define    CSL_EDMA_CHA4                      4  /**< Channel 4 */
#define    CSL_EDMA_CHA5                      5  /**< Channel 5 */
#define    CSL_EDMA_CHA6                      6  /**< Channel 6 */
#define    CSL_EDMA_CHA7                      7  /**< Channel 7 */
#define    CSL_EDMA_CHA8                      8  /**< Channel 8 */
#define    CSL_EDMA_CHA9                      9  /**< Channel 9 */
#define    CSL_EDMA_CHA10                     10 /**< Channel 10*/
#define    CSL_EDMA_CHA11                     11 /**< Channel 11*/
#define    CSL_EDMA_CHA12                     12 /**< Channel 12*/
#define    CSL_EDMA_CHA13                     13 /**< Channel 13*/
#define    CSL_EDMA_CHA14                     14 /**< Channel 14*/
#define    CSL_EDMA_CHA15                     15 /**< Channel 15*/
#define    CSL_EDMA_CHA16                     16 /**< Channel 16*/
#define    CSL_EDMA_CHA17                     17 /**< Channel 17*/
#define    CSL_EDMA_CHA18                     18 /**< Channel 18*/
#define    CSL_EDMA_CHA19                     19 /**< Channel 19*/
#define    CSL_EDMA_CHA20                     20 /**< Channel 20*/
#define    CSL_EDMA_CHA21                     21 /**< Channel 21*/
#define    CSL_EDMA_CHA22                     22 /**< Channel 22*/
#define    CSL_EDMA_CHA23                     23 /**< Channel 23*/
#define    CSL_EDMA_CHA24                     24 /**< Channel 24*/
#define    CSL_EDMA_CHA25                     25 /**< Channel 25*/
#define    CSL_EDMA_CHA26                     26 /**< Channel 26*/
#define    CSL_EDMA_CHA27                     27 /**< Channel 27*/
#define    CSL_EDMA_CHA28                     28 /**< Channel 28*/
#define    CSL_EDMA_CHA29                     29 /**< Channel 29*/
#define    CSL_EDMA_CHA30                     30 /**< Channel 30*/
#define    CSL_EDMA_CHA31                     31 /**< Channel 31*/
#define    CSL_EDMA_CHA32                     32 /**< Channel 32*/
#define    CSL_EDMA_CHA33                     33 /**< Channel 33*/
#define    CSL_EDMA_CHA34                     34 /**< Channel 34*/
#define    CSL_EDMA_CHA35                     35 /**< Channel 35*/
#define    CSL_EDMA_CHA36                     36 /**< Channel 36*/
#define    CSL_EDMA_CHA37                     37 /**< Channel 37*/
#define    CSL_EDMA_CHA38                     38 /**< Channel 38*/
#define    CSL_EDMA_CHA39                     39 /**< Channel 39*/
#define    CSL_EDMA_CHA40                     40 /**< Channel 40*/
#define    CSL_EDMA_CHA41                     41 /**< Channel 41*/
#define    CSL_EDMA_CHA42                     42 /**< Channel 42*/
#define    CSL_EDMA_CHA43                     43 /**< Channel 43*/
#define    CSL_EDMA_CHA44                     44 /**< Channel 44*/
#define    CSL_EDMA_CHA45                     45 /**< Channel 45*/
#define    CSL_EDMA_CHA46                     46 /**< Channel 46*/
#define    CSL_EDMA_CHA47                     47 /**< Channel 47*/
#define    CSL_EDMA_CHA48                     48 /**< Channel 48*/
#define    CSL_EDMA_CHA49                     49 /**< Channel 49*/
#define    CSL_EDMA_CHA50                     50 /**< Channel 50*/
#define    CSL_EDMA_CHA51                     51 /**< Channel 51*/
#define    CSL_EDMA_CHA52                     52 /**< Channel 52*/
#define    CSL_EDMA_CHA53                     53 /**< Channel 53*/
#define    CSL_EDMA_CHA54                     54 /**< Channel 54*/
#define    CSL_EDMA_CHA55                     55 /**< Channel 55*/
#define    CSL_EDMA_CHA56                     56 /**< Channel 56*/
#define    CSL_EDMA_CHA57                     57 /**< Channel 57*/
#define    CSL_EDMA_CHA58                     58 /**< Channel 58*/
#define    CSL_EDMA_CHA59                     59 /**< Channel 59*/
#define    CSL_EDMA_CHA60                     60 /**< Channel 60*/
#define    CSL_EDMA_CHA61                     61 /**< Channel 61*/
#define    CSL_EDMA_CHA62                     62 /**< Channel 62*/
#define    CSL_EDMA_CHA63                     63 /**< Channel 63*/
#define    CSL_EDMA_QCHA0                     64 /**< QDMA Channel 0*/
#define    CSL_EDMA_QCHA1                     65 /**< QDMA Channel 1*/
#define    CSL_EDMA_QCHA2                     66 /**< QDMA Channel 2*/
#define    CSL_EDMA_QCHA3                     67 /**< QDMA Channel 3*/
#define    CSL_EDMA_QCHA4                     68 /**< QDMA Channel 4*/
#define    CSL_EDMA_QCHA5                     69 /**< QDMA Channel 5*/
#define    CSL_EDMA_QCHA6                     70 /**< QDMA Channel 6*/
#define    CSL_EDMA_QCHA7                     71  /**< QDMA Channel 7*/


/** @brief Enumerations for EDMA Event Queues
 *
 *  There are 8 Event Queues
 *
 */
typedef enum {
    CSL_EDMA_EVT_QUE_DEFAULT   =               0, /**< Queue 0 is default */
    CSL_EDMA_EVT_QUE0          =               0, /**< Queue 0 */
    CSL_EDMA_EVT_QUE1          =               1, /**< Queue 1 */
    CSL_EDMA_EVT_QUE2          =               2, /**< Queue 2 */
    CSL_EDMA_EVT_QUE3          =               3, /**< Queue 3 */
    CSL_EDMA_EVT_QUE4          =               4, /**< Queue 4 */
    CSL_EDMA_EVT_QUE5          =               5, /**< Queue 5 */
    CSL_EDMA_EVT_QUE6          =               6, /**< Queue 6 */
    CSL_EDMA_EVT_QUE7          =               7  /**< Queue 7 */
} CSL_EdmaEventQueue;
/** @brief Enumerations for EDMA Transfer Controllers
 *
 *  There are 8 Transfer Controllers. Typically a one to one mapping exists
 *  between Event Queues and Transfer Controllers.
 *
 */
typedef enum {
    CSL_EDMA_TC0           =               0, /**< TC 0 */
    CSL_EDMA_TC1           =               1, /**< TC 1 */
    CSL_EDMA_TC2           =               2, /**< TC 2 */
    CSL_EDMA_TC3           =               3, /**< TC 3 */
    CSL_EDMA_TC4           =               4, /**< TC 4 */
    CSL_EDMA_TC5           =               5, /**< TC 5 */
    CSL_EDMA_TC6           =               6, /**< TC 6 */
    CSL_EDMA_TC7           =               7  /**< TC 7 */
} CSL_EdmaTc;

/** @brief Enumeration for EDMA Regions
 *
 *
 */

#define CSL_EDMA_REGION_GLOBAL  -1  /**< Global Region */
#define CSL_EDMA_REGION_0  0         /**< EDMA Region 0 */
#define CSL_EDMA_REGION_1  1         /**< EDMA Region 1 */
#define CSL_EDMA_REGION_2  2         /**< EDMA Region 2 */
#define CSL_EDMA_REGION_3  3         /**< EDMA Region 3 */
#define CSL_EDMA_REGION_4  4         /**< EDMA Region 4 */
#define CSL_EDMA_REGION_5  5         /**< EDMA Region 5 */
#define CSL_EDMA_REGION_6  6         /**< EDMA Region 6 */
#define CSL_EDMA_REGION_7  7          /**< EDMA Region 7 */

#endif  /* _SOC64PLUS_H_ */

