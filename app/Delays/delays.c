 /******************************************************************************
  * @file    delays.c
  * @author  Paul Formanek
  * @version V1.0.0
  * @date    23April2014
  * @brief   delay functions
  ******************************************************************************/
#include "stm32f4xx.h"
#include "delays.h"

extern TimingDelay;

/***PJF
 * @brief	Inserts a delay time.
 * @param	nTime: specifies the delay time length, in milliseconds
 * @retval	None
 */
void DelayMs(uint32_t nTime)
{
	TimingDelay = nTime;

	while(TimingDelay !=0 );
}

/***PJF
 * @brief	Decrements the TimingDelay variable
 * @param	None
 * @retval	None
 */
void TimingDelay_Decrement(void)
{
	if(TimingDelay != 0x00)
	{
		TimingDelay--;
	}
}
