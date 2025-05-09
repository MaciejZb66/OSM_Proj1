//###########################################################################
//
// FILE:    hw_memmap.h
//
// TITLE:   Macros defining the memory map of the C28x.
//
//###########################################################################
// $TI Release: F2837xD Support Library v210 $
// $Release Date: Tue Nov  1 14:46:15 CDT 2016 $
// $Copyright: Copyright (C) 2013-2016 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef __HW_MEMMAP_H__
#define __HW_MEMMAP_H__

//*****************************************************************************
//
// The following are defines for the base address of the memories and
// peripherals.
//
//*****************************************************************************

#define USB0_BASE               0x00040000  // USB 0 Controller

#define ADCA_RESULT_BASE        0x00000B00   // ADC-A Result
#define ADCB_RESULT_BASE        0x00000B20   // ADC-B Result
#define ADCC_RESULT_BASE        0x00000B40   // ADC-C Result
#define ADCD_RESULT_BASE        0x00000B60   // ADC-D Result

#define ADCA_BASE               0x00007400   // ADC-A
#define ADCB_BASE               0x00007480   // ADC-B
#define ADCC_BASE               0x00007500   // ADC-C
#define ADCD_BASE               0x00007580   // ADC-D

#define CMPSS1_BASE             0x00005C80   // CMPSS-1
#define CMPSS2_BASE             0x00005CA0   // CMPSS-2
#define CMPSS3_BASE             0x00005CC0   // CMPSS-3
#define CMPSS4_BASE             0x00005CE0   // CMPSS-4
#define CMPSS5_BASE             0x00005D00   // CMPSS-5
#define CMPSS6_BASE             0x00005D20   // CMPSS-6
#define CMPSS7_BASE             0x00005D40   // CMPSS-7
#define CMPSS8_BASE             0x00005D60   // CMPSS-8

#define I2CA_BASE               0x00007300   // I2C-A
#define I2CB_BASE               0x00007340   // I2C-B

#define UARTA_BASE              0x00007200   // SCI-A
#define UARTB_BASE              0x00007210   // SCI-B
#define UARTC_BASE              0x00007220   // SCI-C
#define UARTD_BASE              0x00007230   // SCI-D

#define EQEP1_BASE              0x00005100   // Enhanced EQEP-1
#define EQEP2_BASE              0x00005140   // Enhanced EQEP-2
#define EQEP3_BASE              0x00005180   // Enhanced EQEP-3

#define SPIA_BASE               0x00006100   // SPI-A
#define SPIB_BASE               0x00006110   // SPI-B
#define SPIC_BASE               0x00006120   // SPI-C

#define CANA_BASE               0x00048000   // CAN-A
#define CANB_BASE               0x0004A000   // CAN-B
#define CANA_MSG_RAM            0x00049000
#define CANB_MSG_RAM            0x0004B000

#endif // __HW_MEMMAP_H__

