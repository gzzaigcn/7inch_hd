/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 *  ============================================================================
 */
 
/** @mainpage Target Specific Boot Load Definitions
 *
 * @section Introduction
 *
 * @subsection xxx Purpose and Scope
 * The purpose of this section is to describe the Target specific content required
 * for use with generic boot loader.
 *
 * @subsection aaa Terms and Abbreviations
 *   -# GBL:  Generic Boot Loader 
 *   -# TSB:  Target Specific Boot
 *
 * @subsection References
 *    -# CSL-001-DES, CSL 3.x Design Specification DocumentVersion 1.02
 *
 */

/** @file target.h
 *
 * @brief    Header file defining Target specific content for device boot
 *
 * Description
 *    - Relevant enumerations, structure definitions
 *      and function declarations
 *
 * Modification 
 *    - modified on: Jan/9/2006
 *    - reason: Created the sources
 *
 * 
 * @author anonymous.
 *
 */
 
#ifndef __TARGET_H
#define  __TARGET_H
    
/**************************************************************************\
* Dependent Headers
\**************************************************************************/ 
#include "tistdtypes.h"

#ifndef TRUE

#define TRUE    ((int) 1)
#define FALSE   ((int) 0)
#endif

typedef volatile unsigned int		VUint32;
typedef volatile unsigned short 	VUint16;
typedef volatile unsigned char	 	VUint8;

/* volatile signed quantities */
typedef volatile int				VInt32;
typedef volatile short 				VInt16;
typedef volatile char	 			VInt8; 

//Return type defines 
#define E_PASS    0x00000000u
#define E_FAIL    0x00000001u
#define E_TIMEOUT 0x00000002u 

// BIT mask defines
//  BIT masks
#define BIT0    0x00000001
#define BIT1    0x00000002
#define BIT2    0x00000004
#define BIT3    0x00000008
#define BIT4    0x00000010
#define BIT5    0x00000020
#define BIT6    0x00000040
#define BIT7    0x00000080
#define BIT8    0x00000100
#define BIT9    0x00000200
#define BIT10   0x00000400
#define BIT11   0x00000800
#define BIT12   0x00001000
#define BIT13   0x00002000
#define BIT14   0x00004000
#define BIT15   0x00008000
#define BIT16   0x00010000
#define BIT17   0x00020000
#define BIT18   0x00040000
#define BIT19   0x00080000
#define BIT20   0x00100000
#define BIT21   0x00200000
#define BIT22   0x00400000
#define BIT23   0x00800000
#define BIT24   0x01000000
#define BIT25   0x02000000
#define BIT26   0x04000000
#define BIT27   0x08000000
#define BIT28   0x10000000
#define BIT29   0x20000000
#define BIT30   0x40000000
#define BIT31   0x80000000

/* -------------------------------------------------------------------------- *
 *    System Control Module register structure                                *
 * -------------------------------------------------------------------------- */ 
typedef struct _sys_module_regs_
{
	VUint32 PINMUX[2];      //0x00
	VUint32 DSPBOOTADDR;    //0x08
	VUint32 BOOTCOMPLT;     //0x0C
	VUint8 RSVD0[4];		//0x10
	VUint32 BOOTCFG;        //0x14
	VUint8 RSVD1[16];		//0x18
	VUint32 DEVICE_ID;		//0x28
	VUint8 RSVD2[4];		//0x2C
	VUint32 UHPICTL;  		//0x30
	VUint8 RSVD3[8];		//0x34
	VUint32 MSTPRI[2];		//0x3C
	VUint32 VPSS_CLKCTL;	//0x44
	VUint32 VDD3P3V_PWDN;   //0x48
	VUint32 DDRVTPER;       //0x4C
	VUint8 RSVD4[52];       //0x50
	VUint32 TIMERCTL;       //0x84
	VUint32 EDMATCCFG;      //0x88
} sysModuleRegs;

#define SYSTEM ((sysModuleRegs*) 0x01C40000)
#define RESET_ADDR 0x00100000
#define SYS_VDD3P3V_PWRDN_MCBSP_MASK     (0x00000080u)
#define SYS_PINMUX1_MB0BK_MASK           (0x00C00000u)
#define SYS_PINMUX1_MB0BK_SHIFT          (0x00000016u)
#define SYS_PINMUX1_TIM0BK_MASK          (0x00070000u)
#define SYS_PINMUX1_TIM0BK_SHIFT         (0x00000010u)
#define SYS_VDD3P3V_PWRDN_MCBSP_MASK     (0x00000080u)
#define SYS_VDD3P3V_PWRDN_MCBSP_SHIFT    (0x00000007u)
#define SYS_VDD3P3V_PWRDN_TMR0_MASK      (0x00000100u)
#define SYS_PINMUX0_AEAW_MASK            (0x00070000u)
#define SYS_PINMUX0_AEAW_SHIFT           (0x00000010u)
#define SYS_PINMUX0_AEM_MASK             (0x00000007u)
#define SYS_PINMUX0_AEM_SHIFT            (0x00000000u)
#define SYS_BOOTCFG_8_16_MASK            (0x00010000u)
#define SYS_BOOTCFG_8_16_SHIFT           (0x00000011u)
#define SYS_BOOTCFG_AEAW_MASK            (0x00007000u)
#define SYS_BOOTCFG_AEAW_SHIFT           (0x000000Cu)
#define SYS_BOOTCFG_AEM_MASK             (0x00000700u)
#define SYS_BOOTCFG_AEM_SHIFT            (0x0000008u)
#define BOOTCFG_BOOTWIDTH_BIT_SHIFT      (0x00000011u)

typedef struct _cache_regs_
{
    VUint32 L2CFG;
    VUint8 RSVD0[28];
    VUint32 L1PCFG;
    VUint32 L1PCC;
    VUint8 RSVD1[24];
    VUint32 L1DCFG;
    VUint32 L1DCC;
    VUint8 RSVD2[16312];
    VUint32 L2WBAR;
    VUint32 L2WWC;
    VUint8 RSVD3[8];
    VUint32 L2WIBAR;
    VUint32 L2WIWC;
    VUint32 L2IBAR;
    VUint32 L2IWC;
    VUint32 L1PIBAR;
    VUint32 L1PIWC;
    VUint8 RSVD4[8];
    VUint32 L1DWIBAR;
    VUint32 L1DWIWC;
    VUint8 RSVD5[8];
    VUint32 L1DWBAR;
    VUint32 L1DWWC;
    VUint32 L1DIBAR;
    VUint32 L1DIWC;
    VUint8 RSVD6[4016];
    VUint32 L2WB;
    VUint32 L2WBINV;
    VUint32 L2INV;
    VUint8 RSVD7[28];
    VUint32 L1PINV;
    VUint8 RSVD8[20];
    VUint32 L1DWB;
    VUint32 L1DWBINV;
    VUint32 L1DINV;
    VUint8 RSVD9[12212];
    VUint32 MAR[256];
} cacheRegs;

#define CACHE ((cacheRegs*)(0x01840000))

/* -------------------------------------------------------------------------- *
 *    PLL Register structure - See spru978.pdf, Chapter 5 for more details.   *
 * -------------------------------------------------------------------------- */
typedef struct _PLL_regs_
{
	VUint32 PID;                // 0x000
	VUint8 RSVD0[224];          // 0x004
	VUint32 RSTYPE;             // 0x0E4
	VUint8 RSVD1[24];           // 0x0E8
	VUint32 PLLCTL;             // 0x100
	VUint8 RSVD2[12];           // 0x104
	VUint32 PLLM;               // 0x110
	VUint8 RSVD3[4];            // 0x114
	VUint32 PLLDIV1;            // 0x118
	VUint32 PLLDIV2;            // 0x11C
	VUint32 PLLDIV3;            // 0x120
	VUint32 OSCDIV1;            // 0x124
	VUint8 RSVD4[4];            // 0x128
	VUint32 BPDIV;              // 0x12C
	VUint8 RSVD5[8];            // 0x130
	VUint32 PLLCMD;             // 0x138
	VUint32 PLLSTAT;            // 0x13C
	VUint32 ALNCTL;             // 0x140
	VUint32 DCHANGE;            // 0x144
	VUint32 CKEN;               // 0x148
	VUint32 CKSTAT;             // 0x14C
	VUint32 SYSTAT;             // 0x150
} PLLRegs;

#define PLL1 ((PLLRegs*) 0x01C40800)
#define PLL2 ((PLLRegs*) 0x01C40C00)

/* -------------------------------------------------------------------------- *
 *    Power/Sleep Ctrl Register structure - See spru978.pdf, Chapter 6        * 
 *       for more details.                                                    *
 * -------------------------------------------------------------------------- */
typedef struct _PSC_regs_
{
	VUint32 PID;            // 0x00
	VUint8 RSVD0[20];       // 0x04
	VUint32 INTEVAL;        // 0x18
	VUint8 RSVD1[40];	    // 0x1C
	VUint32 MERRPR1;        // 0x44
	VUint8 RSVD2[12];       // 0x48
	VUint32 MERRCR1;        // 0x54
	VUint8 RSVD3[200];      // 0x58
	VUint32 PTCMD;          // 0x120
	VUint8 RSVD4[4];        // 0x124
	VUint32 PTSTAT;         // 0x128
	VUint8 RSVD5[212];      // 0x12C
	VUint32 PDSTAT0;        // 0x200
	VUint8 RSVD6[252];      // 0x204
	VUint32 PDCTL0;         // 0x300
	VUint8 RSVD7[1276];     // 0x304
	VUint32 MDSTAT[39];     // 0x800
	VUint8 RSVD8[356];      // 0x89C
	VUint32 MDCTL[39];      // 0xA00
} PSCRegs;

#define PSC ((PSCRegs*) 0x01C41000)	

/* PSC constants */
#define LPSC_VPSS_MAST      0
#define LPSC_VPSS_SLV       1
#define LPSC_TPCC        	2
#define LPSC_TPTC0       	3
#define LPSC_TPTC1       	4
#define LPSC_TPTC2       	5
#define LPSC_EMAC_MEM       6
#define LPSC_MDIO			7
#define LPSC_EMAC			8
#define LPSC_MCASP0         9
#define LPSC_VLYNQ          11
#define LPSC_HPI			12
#define LPSC_DDR2           13
#define LPSC_EMIFA			14
#define LPSC_PCI			15
#define LPSC_MCBSP0         16
#define LPSC_MCBSP1         17
#define LPSC_I2C            18
#define LPSC_UART0          19
#define LPSC_UART1          20
#define LPSC_HECC           22
#define LPSC_PWM0           23
#define LPSC_PWM1           24
#define LPSC_PWM2           25
#define LPSC_GPIO			26
#define LPSC_TIMER0         27
#define LPSC_TIMER1         28
#define LPSC_DSP            39

#define EMURSTIE_MASK       0x00000200

#define PSC_ENABLE          0x3
#define PSC_DISABLE         0x2
#define PSC_SYNCRESET       0x1
#define PSC_SWRSTDISABLE    0x0

 
/* -------------------------------------------------------------------------- *
 *    DDR2 Memory Ctrl Register structure - See sprue22b.pdf for more details.*
 * -------------------------------------------------------------------------- */
typedef struct _DDR2_MEM_CTL_REGS_
{
	VUint8 RSVD0[4];        //0x00
	VUint32 SDRSTAT;        //0x04
	VUint32 SDBCR;          //0x08
	VUint32 SDRCR;          //0x0C
	VUint32 SDTIMR;         //0x10
	VUint32 SDTIMR2;        //0x14
	VUint8 RSVD1[8];        //0x18 
	VUint32 PBBPR;          //0x20
	VUint8 RSVD2[156];      //0x24 
	VUint32 IRR;            //0xC0
	VUint32 IMR;            //0xC4
	VUint32 IMSR;           //0xC8
	VUint32 IMCR;           //0xCC
	VUint8 RSVD3[20];       //0xD0
	VUint32 DDRPHYCR;       //0xE4
	VUint8 RSVD4[8];        //0xE8
	VUint32 VTPIOCR;        //0xF0
} DDR2Regs;

#define DDRVTPR (*((VUint32*) 0x01C42038))
#define DDR ((DDR2Regs*) 0x20000000)
#define DDR_TEST_PATTERN (0xA55AA55Au)
#define DDR_RAM_SIZE (0x08000000u)

/* -------------------------------------------------------------------------- *
 *    AEMIF Register structure - See spru984.pdf for more details.            *
 * -------------------------------------------------------------------------- */
typedef struct _emif_regs_
{
    VUint32 ERCSR;          // 0x00
    VUint32 AWCCR;          // 0x04
    VUint32 SDBCR;          // 0x08
    VUint32 SDRCR;          // 0x0C
    VUint32 AB1CR;          // 0x10
    VUint32 AB2CR;          // 0x14
    VUint32 AB3CR;          // 0x18
    VUint32 AB4CR;          // 0x1C
    VUint32 SDTIMR;         // 0x20
    VUint32 DDRSR;          // 0x24
    VUint32 DDRPHYCR;       // 0x28
    VUint32 DDRPHYSR;       // 0x2C
    VUint32 TOTAR;          // 0x30
    VUint32 TOTACTR;        // 0x34
    VUint32 DDRPHYID_REV;   // 0x38
    VUint32 SDSRETR;        // 0x3C
    VUint32 EIRR;           // 0x40
    VUint32 EIMR;           // 0x44
    VUint32 EIMSR;          // 0x48
    VUint32 EIMCR;          // 0x4C
    VUint32 IOCTRLR;        // 0x50
    VUint32 IOSTATR;        // 0x54
    VUint8 RSVD0[8];        // 0x58
    VUint32 NANDFCR;        // 0x60
    VUint32 NANDFSR;        // 0x64
    VUint8 RSVD1[8];        // 0x68
    VUint32 NANDF1ECC;      // 0x70
    VUint32 NANDF2ECC;      // 0x74
    VUint32 NANDF3ECC;      // 0x78
    VUint32 NANDF4ECC;      // 0x7C
    VUint8 RSVD2[4];        // 0x80
    VUint32 IODFTECR;       // 0x84
    VUint32 IODFTGCR;       // 0x88
    VUint8 RSVD3[4];        // 0x8C
    VUint32 IODFTMRLR;      // 0x90
    VUint32 IODFTMRMR;      // 0x94
    VUint32 IODFTMRMSBR;    // 0x98
    VUint8 RSVD4[20];       // 0x9C
    VUint32 MODRNR;         // 0xB0
} emifRegs;

#define AEMIF ((emifRegs*) 0x01E00000)

/* -------------------------------------------------------------------------- *
 *    UART Register structure - See sprue33.pdf for more details.             *
 * -------------------------------------------------------------------------- */
typedef struct _uart_regs_
{
	VUint32 RBR;            // 0x00
	VUint32 IER;            // 0x04
	VUint32 IIR;            // 0x08
	VUint32 LCR;            // 0x0C
	VUint32 MCR;            // 0x10
	VUint32 LSR;            // 0x14
	VUint32 MSR;            // 0x18
	VUint32 SCR;            // 0x1C
	VUint8 DLL;             // 0x20
	VUint8 RSVDO[3];
	VUint8 DLH;             // 0x24
	VUint8 RSVD1[3];	
	VUint32 PID1;           // 0x28
	VUint32 PID2;           // 0x2C
	VUint32 PWREMU_MGNT;    // 0x30
} uartRegs;

#define THR RBR
#define FCR IIR

#define UART0 ((uartRegs*) 0x01C20000)
#define UART1 ((uartRegs*) 0x01C20400)

/* -------------------------------------------------------------------------- *
 *    Timer Register structure - See sprue26.pdf for more details.            *
 * -------------------------------------------------------------------------- */
typedef struct _timer_regs_
{
    VUint32 PID12;          // 0x00
    VUint32 EMUMGT_CLKSPD;  // 0x04
    VUint32 GPINT_GPEN;     // 0x08
    VUint32 GPTDAT_GPDIR;   // 0x0C
    VUint32 TIM12;          // 0x10
    VUint32 TIM34;          // 0x14
    VUint32 PRD12;          // 0x18
    VUint32 PRD34;          // 0x1C
    VUint32 TCR;            // 0x20
    VUint32 TGCR;           // 0x24
    VUint32 WDTCR;          // 0x28
} timerRegs;

#define TIMER0 ((timerRegs*) 0x01C21400)
#define TIMER1 ((timerRegs*) 0x01C21800)

/* -------------------------------------------------------------------------- *
 *    INTC register structure and masks - See DM643x datasheet for more info. *
 * -------------------------------------------------------------------------- */
typedef struct _intc_regs_
{
	VUint32 EVTFLAG[4];		// 0x000
	VUint8 RSVD0[16];		// 0x010
	VUint32 EVTSET[4];		// 0x020
	VUint8 RSVD1[16];		// 0x030
	VUint32 EVTCLR[4];		// 0x040
	VUint8 RSVD2[48];		// 0x050
	VUint32 EVTMASK[4];		// 0x080
	VUint8 RSVD3[16];		// 0x090
	VUint32 MEVTFLAG[4];	// 0x0A0
	VUint8 RSVD4[16];		// 0x0B0
	VUint32 EXPMASK[4];		// 0x0C0
	VUint8 RSVD5[16];		// 0x0D0
	VUint32 MEXPFLAG[4];	// 0x0E0
	VUint32 INTMUX[4];		// 0x100
	VUint8 RSVD6[48];		// 0x110
	VUint32 AEGMUX[2];		// 0x140
	VUint8 RSVD7[56];		// 0x148
	VUint32 INTXSTAT;		// 0x180
	VUint32 INTXCLR;		// 0x184
	VUint32 INTDMASK;		// 0x188
	VUint8 RSVD8[52];		// 0x18C
	VUint32 EVTASRT;		// 0x1C0
} intcRegs;

#define INTC ((intcRegs*) 0x01800000)

/* -------------------------------------------------------------------------- *
 *    I2C register structure        - see spru991a                            *
 * -------------------------------------------------------------------------- */
typedef struct  _i2c_regs {
    VUint32 ICOAR;
    VUint32 ICIMR;
    VUint32 ICSTR;
    VUint32 ICCLKL;
    VUint32 ICCLKH;
    VUint32 ICCNT;
    VUint32 ICDRR;
    VUint32 ICSAR;
    VUint32 ICDXR;
    VUint32 ICMDR;
    VUint32 ICIVR;
    VUint32 ICEMDR;
    VUint32 ICPSC;
    VUint32 ICPID1;
    VUint32 ICPID2;
    VUint8 RSVD14[12];
    VUint32 ICPFUNC;
    VUint32 ICPDIR;
    VUint32 ICPDIN;
    VUint32 ICPDOUT;
    VUint32 ICPDSET;
    VUint32 ICPDCLR;
} i2cRegs;

#define I2C_ICMDR_STP_MASK           (0x0800u)
#define I2C_ICMDR_STT_MASK           (0x2000u)
#define I2C_ICMDR_NACKMOD_MASK       (0x8000u)
#define I2C_ICMDR_TRX_MASK           (0x0200u)
#define I2C_ICMDR_MST_MASK           (0x0400u)
#define I2C_ICMDR_RM_MASK            (0x0080u)
#define I2C_ICMDR_IRS_MASK           (0x0020u)

#define I2C_ICSTR_ICRRDY_MASK        (0x0008u)
#define I2C_ICSTR_NACK_MASK          (0x0002u)
#define I2C_ICSTR_ICXRDY_MASK        (0x0010u)
#define I2C_ICSTR_BB_MASK            (0x1000u)
#define I2C_ICSTR_NACKSNT_MASK       (0x2000u)

#define I2CR ((i2cRegs *) 0x01C21000)


/* -------------------------------------------------------------------------- *
 *    GPIO Bank 6 register structure        - see spru988a                    *
 * -------------------------------------------------------------------------- */
typedef struct  _gpioBank6_regs {
	VUint32 DIR6;
	VUint32 OUT_DATA6;
	VUint32 SET_DATA6;
	VUint32 CLR_DATA6;
	VUint32 IN_DATA6;
	VUint32 SET_RIS_TRIG6;
	VUint32 CLR_RIS_TRIG6;
	VUint32 SET_FAL_TRIG6;
	VUint32 CLR_FAL_TRIG6;
	VUint32 INTSTAT6;
} gpioBank6Regs;

#define GPIO6 ((gpioBank6Regs *) 0x01C67088)
#define GPIO97_MASK         0x2u



// Function Prototypes

// Execute LPSC state transition
void LPSCTransition(Uint8 module, Uint8 state);
void PSCInit();

// Initialization prototypes
void TIMER0Start(void);
int TIMER0Status(void);
void DM643xInit(void);
Uint32 UARTInit(void);
void TIMER0Init(void);
void AEMIFInit(void);
void PLL1Init(void);
void PLL2Init(void);
void DDR2Init(void);
  

#define AEMIF_CS2_ADDRESS_START                          (0x42000000u)
#define L2_ADDRESS_START                                 (0x10800000u)


                                                                                                       
/**************************************************************************\
* Create access to Non-memory mapped control registers
\**************************************************************************/ 
extern volatile cregister Uint32 IFR;
extern volatile cregister Uint32 IER;
extern volatile cregister Uint32 ICR;
extern volatile cregister Uint32 ISR;
extern volatile cregister Uint32 IRP;
extern volatile cregister Uint32 ISTP;
extern volatile cregister Uint32 NRP;

#endif
