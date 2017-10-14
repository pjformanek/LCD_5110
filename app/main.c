//*****************************************************************************
//
//! File:			main.c
//! Version:		1.0.0.0
//! Date:			Oct. 10, 2017
//! Author:			PFormanek
//!
//!	Description:	program to interface nokia5110 LCD module
//
//
//*****************************************************************************
#include "Includes.h"

int main(void)
{
/****************************************************
 * Pins required for nokia5110LCD
 *
 * SCE:		Chip enable pin		( OUTPUT )PC13
 * RESET:	Resets LCD			( OUTPUT )PE6
 * D/C:		Data/Command select	( OUTPUT )PE4
 * SDIN:	Serial Data In		( OUTPUT )PE5
 * SCLK:	Serial Clock		( OUTPUT )PE3
 *
 * need to initialize the clocks, and the gpio
 *
 *
 */
	SystemInit();
	//turn on the HSE clock 8MHz xtal
	RCC->CR |= 0x00010000;
	//wait for the HSERDY bit
	while (!(RCC->CR & 0x0002000));
	//turn off the LSI clock
	RCC->CR &= 0xFFFFFFFE;
	//enables the GPIOC and GPIOE AHB1 clock
	RCC->AHB1ENR = 0x00100014;

	HAL_GPIO_DeInit(GPIOC,GPIO_PIN_All);
	HAL_GPIO_DeInit(GPIOE,GPIO_PIN_All);

	GPIO_InitTypeDef LCD_Pins;
	LCD_Pins.Pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
	LCD_Pins.Mode = GPIO_MODE_OUTPUT_OD;
	LCD_Pins.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOE, &LCD_Pins);
	LCD_Pins.Pin = GPIO_PIN_13;
	HAL_GPIO_Init(GPIOC, &LCD_Pins);

    while(1)
    {
    }
}
//! @}
//! @}
