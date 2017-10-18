//****************************************************************************
//
//! File:			lcd.h
//! Version:		1.0.0.0
//! Author:			PFormanek
//! Date:			Oct. 14, 2017
//!
//!	Description:	header file for the LCD module
//
//
//****************************************************************************

#ifndef _lcd_h
#define _lcd_h

/*
			---------------------------------------
							Includes
			---------------------------------------
*/
#include "Includes.h"

/*
			---------------------------------------
							Defines
			---------------------------------------
*/
#define u8 						uint8_t

#define HI						1
#define LO						0

//These are the specific GPIO pins selected for the LCD module
//They should be adjust based on the uController used
//@group LCDPortPins
#define LCDSCEPin				13
#define LCDSCEPort				GPIOC
#define LCDDCPin				4
#define LCDDCPort				GPIOE
#define LCDResetPin				6
#define LCDResetPort			GPIOE
#define LCDSDINPin				5
#define LCDSDINPort				GPIOE
#define LCDSCLKPin				3
#define LCDSCLKPort				GPIOE

#define LCDCommandMode  		0
#define LCDDataMode				1

//These defines are the bit values of the LCD commands
//@group LCDFuncSet
#define LCDPowerDown 			0x24
#define LCDSelect				0x20
#define LCDHorizontalAddressing	0x20
#define LCDVerticalAddressing	0x22
#define LCDBasicInstructions	0x20
#define LCDExtendedInstructions	0x21

//@group LCDDispConf
#define LCDBlankDisplay			0x08
#define LCDNormalMode			0x0C
#define LCDAllOn				0x09
#define LCDInverseMode			0x0D

//@group LCDSetTempCoeff
#define LCDTempCoeff0			0x04
#define LCDTempCoeff1			0x05
#define LCDTempCoeff2			0x06
#define LCDTempCoeff3			0x07

//@group LCDSetBias
#define LCDBiasLevel0			0x17
#define LCDBiasLevel1			0x16
#define LCDBiasLevel2			0x15
#define LCDBiasLevel3			0x14
#define LCDBiasLevel4			0x13
#define LCDBiasLevel5			0x12
#define LCDBiasLevel6			0x11
#define LCDBiasLevel7			0x10

/*
			----------------------------------------
							Variables
			----------------------------------------
*/
/*
			----------------------------------------
							Functions
			----------------------------------------
*/

void LCDWriteBit(u8 bit);
void LCDWriteByte(u8 byte);
void LCDWrite(u8 mode, u8 data);
void LCDDispConf(u8 command);
void LCDSetX(u8 X);
void LCDSetY(u8 Y);
void LCDSetXY(u8 X, u8 Y);
void LCDSetTempCoeff(u8 tempCoeff);
void LCDSetBias(u8 biasLevel);
void LCDSetVop(u8 vopLevel);
void LCDInit(void);


#endif
//END OF _lcd_h
