//****************************************************************************
//
//! File:			lcd.c
//! Version:		1.0.0.0
//! Author:			PFormanek
//! Date:			Oct. 14, 2017
//!
//!	Description:	This file contains all the functions used to 
//					interface with the ucontroller
//
//****************************************************************************

/*
Name:		LCDWriteBit
Args:		u8 bit
Return:		
Desc'n:		Sends one bit of data to the LCD module
*/
void LCDWriteBit(u8 bit){
	GPIOPinState(LCDSCLK, LO);
	GPIOPinState(LCDSDIN, bit);
	GPIOPinState(LCDSCLK, HI);
}

/*
Name:		LCDWriteByte
Args:		u8 byte
Return:		
Desc'n:		Sends one byte of data to the LCD module
*/
void LCDWriteByte(u8 byte){
	u8 loop;
	GPIOPinState(LCDSCE, LO);
	for(loop = 0; loop < 8; loop++){
		if(loop == 7)
			GPIOToggle(LCDDC);
//bitshifts by loop value and masks bit0 to determine each bit value 
//this will sent the byte MSB first
		if((byte<<loop) & 0x80)
			LCDWriteBit(HI);
		else
			LCDWriteBit(LO);
	}
	GPIOToggle(LCDDC);
	GPIOPinState(LCDSCE, HI)
}

/*
Name:		LCDWriteData
Args:		
Return:		
Desc'n:		Writes data to the display RAM
*/
void LCDWrite(u8 mode, u8 data){
	!mode ?
		GPIOPinState(LCDDC, LO):
		GPIOPinState(LCDDC, HI);
	LCDWriteByte(data);
}

/*
Name:		LCDDispConf
Args:		u8 command
Return:		
Desc'n:		Sets the configuration of the display

			command can be one of LCDDispConf params defined in lcd.h
*/
void LCDDispConf(u8 command){
	LCDWrite(0, command);	
}

/*
Name:		LCDSetY
Args:		u8 Y
Return:		void
Desc'n:		Sets the y-address of the RAM
			Y can be a value between 0 and 5
*/
void LCDSetY(u8 Y){
	LCDWrite(0, (0x40 | Y));
}

/*
Name:		LCDSetX
Args:		u8 X
Return:		void
Desc'n:		Sets the x-address of the RAM
			X can ba a value between 0 and 83
*/
void LCDSetX(u8 X){
	LCDWrite(0, (0x80 | X));
}

/*
Name:		LCDSetXY
Args:		u8 X
			u8 Y
Return:		void
Desc'n:		Sets the x and y addresses of the RAm
*/
void LCDSetXy(u8 X, u8 Y){
	LCDSet(X);
	LCDSet(Y);

}

/*
Name:		LCDSetTempCoeff
Args:		u8 tempCoeff
Return:		void
Descn:		Sets temperature coefficient to be in the 
			suitable range for operating temperature. If the display seems
			to be operating sluggish, then the coefficient may need to be
			incresed. There are 4 levels of control
			
			tempCoeff can be one of LCDSetTempCoeff params defined in lcd.h
*/
void LCDSetTempCoeff(u8 tempCoeff){
	LCDFuncSet(LCDExtendedInstructions);
	LCDWrite(0, tempCoeff);
}


/*
Name:		LCDSetBias
Args:		u8 biasLeveln
			can be one of LCDBiasLeveln where n=0..7
Return:		void
Desc'n:		Sets the Bias Voltage level
			There are 8 levels depending on the required MUX rate
			biasLevel(n)			Recommended MUX rate
				7						1:100
				6						1:80
				5						1:65
				4						1:48
				3					  1:40/1:34
				2						1:24
				1						1:18
				0					 1:10/1:9/1:8
*/
void LCDSetBias(u8 biasLeveln){
	LCDFuncSet(LCDExtendedInstructions);
	LCDWrite(0, biasLeveln);
}

/*
Name:		LCDSetVop
Args:		u8 vopLevel
Return:		void
Desc'n:		Configures the display for the operating voltage
			using the below formula to calculate the value of vopLevel
			
			Vlcd = 3.06 + (vopLevel)*0.06
			where Vlcd is the operating voltage or supply voltage of display
			So for a 5V operating voltage
			vopLevel	= (5 - 3.06)/0.06
						= 32.33 ~= 32
			therefore vopLevel = 0x20
		*NOTE the maximum operating voltage of the LCD is 8.5V
*/	
void LCDSetVop(u8 vopLevel){
	LCDFuncSet(LCDExtendedInstructions);
	LCDWrite(0, (0x80 | vopLevel));
}


/*
Name:		LCDFuncSet
Args:		u8 funcSet
Return:		void
Desc'n:		power down control, entry mode, extended instruction set (H)
*/	
void LCDFuncSet(u8 funcSet){
	LCDWrite(0, funcSet);
}

/*
Name:		LCDReset
Args:		void
Return:		void
Desc'n"		Resets the LCD module 
*/
void LCDReset(void){
	GPIOPinState(LO);//PF FIX reset GPIO pin
	DelayMs(5);
	GPIOPinState(HI);//PF FIX set GPIO pin
}

/*
Name:		LCDInit
Args:		void
Return:		void
Desc'n:		Initializes the LCD for operation after power on
			The required steps to initialize the LCD module is:
			
			Create a RESET LCD signal
			
			command 0x21 to set in addition mode (H = 1)
			
			command to set Vop, ex. command 0xC0 for Vlcd = 5V
			
			command to set Temp Coeff, ex. command 0x07 temp coeff of 3
			
			command to set bias voltage level, ex. 0x13 (n=4 1:48)
			
			command 0x20 to set in basic mode (H = 0)
			
			//seems incorrect, these bits will turn on all pixels
			command 0x0C (D=1, E=0) to display results in Normal Mode
			//use instead
			command 0x09 (D=0, E=1) Normal mode
*/	
void LCDInit(void){
	//		Delays may be required between commands max
	//		SCLK freq is 4Mhz
	//		so min SCLK tick is 250ns
	//		typical setup time is 100ns
	LCDReset();
	LCDFuncSet(LCDExtendedInstructions);
	LCDSetVop(0x20);
	LCDSetTempCoeff(LCDTempCoeff0);
	LCDSetBias(LCDBiasLevel4);
	LCDFuncSet(LCDBasicInstructions);
	LCDDispConf(LCDNormalMode);
}

void GPIOPinstate(u8 GPIOPin, u8 state){
	GPIOC->BSRR
}

void GPIOPinToggle(u8 GPIOPin){
	
}