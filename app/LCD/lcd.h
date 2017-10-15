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
			------------------------------------
						Defines				
			------------------------------------
*/
typedef u8 						uint8_t

#define F_OSC
#define HI						1
#deinfe LO						0

//These are the specific GPIO pins selected for the LCD module
//They should be adjust based on the uController used
#define LCDSCE					PC13 //PF FIX set GPIO pin
#define LCDDC					PE4
#define LCDRST					PE6
#define LCDSDIN					PE5
#define LCDSCLK					PE3		

#define LCDCommandMode  		0
#define LCDDataMode				1

//These defines are the bit values of the LCD commands
//@param LCDFuncSet
#define LCDPowerDown 			0x24
#define LCDSelect				0x20
#define LCDHorizontalAddressing	0x20
#define LCDVerticalAddressing	0x22
#define LCDBasicInstructions	0x20
#define LCDExtendedInstructions	0x21

//@param LCDDispConf
#define LCDBlankDisplay			0x08
#define LCDNormalMode			0x0C
#define LCDAllOn				0x09
#define LCDInverseMode			0x0D

//@param LCDSetTempCoeff
#define LCDTempCoeff0			0x04
#define LCDTempCoeff1			0x05
#define LCDTempCoeff2			0x06
#define LCDTempCoeff3			0x07

//@param LCDSetBias
#define LCDBiasLevel0			0x17
#define LCDBiasLevel1			0x16
#define LCDBiasLevel2			0x15
#define LCDBiasLevel3			0x14
#define LCDBiasLevel4			0x13
#define LCDBiasLevel5			0x12
#define LCDBiasLevel6			0x11
#define LCDBiasLevel7			0x10
/*
			------------------------------------
						Variables				
			------------------------------------
*/
/*
			------------------------------------
						Functions				
			------------------------------------
*/

void LCDWriteData(void);
void LCDDispConf(void);
void LCDSetX(u8 X);
void LCDSetY(u8 Y);
void LCDSetXY(u8 X, u8 Y);
void LCDSetTempCoeff(u8 tempCoeff);
void LCDSetBias(u8 biasLevel);
void LCDSetVop(u8 vopLevel);
void LCDInit(void);
void LCDWriteBit(u8 bit);
void LCDWriteByte(u8 byte);

void GPIOPinState(u8 GPIOPin, u8 state);
void GPIOPinToggle(u8 GPIOPin);
#endif //END OF _lcd_h