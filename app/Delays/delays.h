 /******************************************************************************
  * @file	 	delays.h
  * @author		Paul Formanek
  * @version	V1.0.1
  * @date		23April2014
  * @revised	2017-Oct-16
  * @brief  	delay functions
  ******************************************************************************/
#ifndef _delays_h
#define _delays_h

#include "stm32f4xx.h"
//***PJF new delay function using the new 8MHz external clock
void DelayMs(uint32_t nTime);

//***PJF used in the DelayMs function
void TimingDelay_Decrement(void);

#endif
// END OF _delays_h
