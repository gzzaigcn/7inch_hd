/*
 *  Copyright 2008 by SEED International Ltd.
 *  All rights reserved. Property of SEED International Ltd.
 */

/*
 *  Linker command file
 *
 */
-l rts64plus.lib

-stack          0x00008000      /* Stack Size */
-heap           0x00008000      /* Heap Size */

MEMORY
{
	L1PRAM:     o = 0x10E08000  l = 0x00008000
	L1DRAM_0:   o = 0x10F04000  l = 0x0000C000   //48k L1D RAM
	L1DRAM_1:   o = 0x10F10000  l = 0x00008000   // 32K L1D cache
    VECS:		o = 0x10800000  l = 0x00000800   //IST
    L2RAM:      o = 0x10800800  l = 0x00010000   //L2RAM 64K(higher 64K used for Cache)

    DDR2_0:     o = 0x80000000  l = 0x01000000   /* DDR2,16M*8=128MB*/
	DDR2_1:     o = 0x81000000  l = 0x01000000
	DDR2_2:     o = 0x82000000  l = 0x01000000
	DDR2_3:     o = 0x83000000  l = 0x01000000
    DDR2_4:     o = 0x84000000  l = 0x01000000
    DDR2_5:     o = 0x85000000  l = 0x01000000
	DDR2_6:     o = 0x86000000  l = 0x01000000
	DDR2_7:     o = 0x87000000  l = 0x01000000

}

SECTIONS
{
    .bss        >   DDR2_7
    .cinit      >   DDR2_7
    .cio        >   DDR2_7
    .const      >   DDR2_7
    .data       >   L2RAM
    .far        >   DDR2_7
    .stack      >   DDR2_7
    .switch     >   DDR2_7
    .sysmem     >   DDR2_7
    .text       >   DDR2_7
    .vectors    >   VECS

    L1_DATA0    >   L1DRAM_0
    L1_PROGRAM  >   L1PRAM  
    
	L2_DATA 	>   L2RAM
	L2_PROGRAM	>   L2RAM
	
	L3_DATA0	>   DDR2_0
	L3_DATA1	>   DDR2_1
	L3_DATA2	>   DDR2_2
	L3_DATA3	>   DDR2_3
	L3_DATA4    >   DDR2_4
	L3_DATA5    >   DDR2_5
	L3_DATA6    >   DDR2_6
	L3_DATA7    >   DDR2_7
	L3_PROGRAM  >   DDR2_7

}
