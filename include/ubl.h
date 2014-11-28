/* --------------------------------------------------------------------------
    FILE        : ubl.h
    PURPOSE     : UBL main header file
    PROJECT     : User Boot-Loader and Flasher
    AUTHOR      : Texas Instruments Incorporated
    DATE	    : Mar-15-2007  
 
    HISTORY
        v1.00 completion
 	        Jan-22-2007

   Copyright 2007 Texas Instruments Incorporated
 ----------------------------------------------------------------------------- */

#ifndef _UBL_H_
#define _UBL_H_

#include "tistdtypes.h"
#include "dm6437.h"
//UBL version number
#define UBL_VERSION_STRING "1.00"
#ifdef UBL_NAND
#define UBL_FLASH_TYPE "NAND"
#endif

#ifdef UBL_NOR
#define UBL_FLASH_TYPE "NOR"
#endif

#ifdef UBL_I2C
#define UBL_LASH_TYPE "I2C"
#endif

// Define MagicNumber constants
#define MAGIC_NUMBER_VALID	(0xA1ACED00)
//#define AIS_MAGIC_NUMBER	(0x41504954)

/* Used by UBL when doing UART boot */
#define UBL_UART_BOOT		(0xA1ACED00)		/* Safe boot mode */
#define UBL_NOR_BURN		(0xA1ACED11)		/* Download via UART & Burn NOR with UBL readable header and BIN data*/
#define UBL_NOR_ERASE		(0xA1ACED22)		/* Download via UART & Global erase the NOR Flash*/
#define UBL_NAND_BURN		(0xA1ACED33)		/* Download via UART & Burn NAND - Image is binary */
#define UBL_NAND_ERASE		(0xA1ACED44)		/* Download via UART & Global erase the NAND Flash*/

// Define UBL image size
#define UBL_IMAGE_SIZE      (0x00003800)

// Define maximum downloadable image size
#define MAX_IMAGE_SIZE 		(0x01000000u)
#define RAM_START_ADDR 		(0x80000000u)
#define RAM_END_ADDR 		((RAM_START_ADDR + DDR_RAM_SIZE))


typedef struct {
	Uint32 magicNum;	/* Expected magic number */
	Uint32 entryPoint;	/* Entry point of the user application */
	Uint32 numPage;		/* Number of pages where boot loader is stored */
	Uint32 block;		/* starting block number where User boot loader is stored */
	Uint32 page;		/* starting page number where boot-loader is stored */
	Uint32 ldAddress;	/* Starting RAM address where image is to copied - XIP Mode */
	Uint32 numBlock;
	Uint32 MaxEndBlock;
} NAND_BOOT;

typedef struct {
	Uint32		magicNum;
	Uint32		entryPoint;	
	Uint32		appSize;
	Uint32		ldAddress;	/* Starting RAM address where image is to copied - XIP Mode */
} NOR_BOOT;


typedef enum BootMode_ {
    NO_BOOT 		= 0x0,		// Emulation boot
	HPI_x27 		= 0x1, 		// Requires Fastboot (x27 PLL)
	HPI 			= 0x2, 		// Fastboot => x20 PLL, no Fastboot => PLL bypass
	HPI_x15		 	= 0x3, 		// Requires Fastboot (x15 PLL)
	EMIFA 			= 0x4,		// Fastboot => AIS (x20 PLL), No Fastboot => XiP (PLL bypass)
	I2C 			= 0x5,		// Fastboot => x20 PLL, no Fastboot => PLL bypass
	SPI 			= 0x6,		// Fastboot => x20 PLL, no Fastboot => PLL bypass
	NAND 			= 0x7,		// Fastboot => x20 PLL, no Fastboot => PLL bypass
	UART_NO_FC 		= 0x8,		// Fastboot => x20 PLL, no Fastboot => PLL bypass
	EMIFA_NOAIS 	= 0x9,		// Requires Fastboot (x20 PLL), no AIS parsing
	UART_FC 		= 0xE		// Fastboot => x20 PLL, no Fastboot => PLL bypass
} BootMode;

// ---------------- Function prototypes ----------------

#pragma FUNC_IS_PURE(boot);
void boot( void );
Int32 main(void);

#endif //_UBL_H_
