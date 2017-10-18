//****************************************************************************
//
//! File:			main.c
//! Version:		1.0.0.0
//! Author:			PFormanek
//! Date:			Oct. 10, 2017
//!
//!	Description:	program to interface nokia5110 LCD module
//
//
//****************************************************************************
#include "Includes.h"

uint32_t SYSCLOCKFREQ = 0;

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
 ****************************************************/

	SystemInit();
	HAL_Init();

	//turn on the HSE clock 8MHz Xtal SET HSE_Enable bit
	RCC->CR |= 0x00010000;
	//wait for the HSERDY bit
	while (!(RCC->CR & 0x00020000));
	//turn off the LSI clock
	RCC->CR &= 0xFFFFFFFE;
	RCC_ClkInitTypeDef RCCinit;
	RCCinit.ClockType = RCC_CLOCKTYPE_SYSCLK;
	RCCinit.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
	HAL_RCC_ClockConfig(&RCCinit, 0);

	HAL_SYSTICK_Config(1000);
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK_DIV8);

	SystemCoreClockUpdate();
//	HAL_SuspendTick();

	//enables the GPIOC and GPIOE AHB1 clock
	RCC->AHB1ENR = 0x00100014;

	HAL_GPIO_DeInit(GPIOC,GPIO_PIN_All);
	HAL_GPIO_DeInit(GPIOE,GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6);

	GPIO_InitTypeDef LCD_Pins;
	LCD_Pins.Pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
	LCD_Pins.Mode = GPIO_MODE_OUTPUT_OD;
	LCD_Pins.Pull = GPIO_PULLDOWN;
	LCD_Pins.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOE, &LCD_Pins);
	LCD_Pins.Pin = GPIO_PIN_13;
	HAL_GPIO_Init(GPIOC, &LCD_Pins);

	HAL_ResumeTick();
	SYSCLOCKFREQ = HAL_RCC_GetSysClockFreq();
	LCDInit();

    while(1)
    {
     	LCDWrite(1,0x11);
    }
}


//! @}
//! @}
